/* File         : build_headers: main.cpp
 * Author       : Dmitry Vedenko
 * E-Mail       : dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include <fstream>
#include <iostream>
#include <iomanip>
#include <llvm/Support/Path.h>
#include <llvm/Support/Regex.h>

#include <cstdio>
#include <cstring>
#include <memory>

#include <zlib.h>

#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

typedef struct file_data
{
	std::string		short_name;
	std::string		data;
} file_data_t;

typedef boost::shared_ptr<file_data_t> file_data_ptr_t;
typedef std::vector<file_data_ptr_t> file_list_t;

static file_list_t					file_list;

static size_t						uncompressed_size = 0;

void	header_files_collector(const llvm::sys::Path& base_path,const llvm::sys::Path& current_dir)
{
	if(llvm::sys::path::filename(current_dir.str())== ".svn")//We do not want to parse .svn directories
		return;
	std::set<llvm::sys::Path> paths;
	std::string err;
	if(!current_dir.getDirectoryContents(paths,&err))
	{
		for(std::set<llvm::sys::Path>::iterator it = paths.begin(), end = paths.end(); it != end; ++it)
		{
			if(it->isDirectory())
				header_files_collector(base_path, *it);
			else
			{
				std::string relative_path = it->str().substr(base_path.str().length());
				std::clog << "-- Reading " << relative_path  << " ";
				file_data_ptr_t file_ptr ( new file_data_t );
				file_ptr->short_name = relative_path;
				//Now, we need to read the contents
				FILE* f = fopen(it->c_str(),"rb");
				assert(f);

				fseek(f,0,SEEK_END);
				size_t sz = ftell(f);
				fseek(f,0,SEEK_SET);
				std::clog << (sz / 1024.0) << "Kb" << std::endl;
				
				uncompressed_size += sz + relative_path.length()*sizeof(char);

				std::auto_ptr<char> mem ( new char[sz] );
				assert(mem.get());
				fread(mem.get(),1,sz,f);
				fclose(f);

				file_ptr->data = std::string(mem.get(),sz);
				file_list.push_back(file_ptr);
			}
		}//for(auto it = paths.begin(), end = paths.end(); it != end; ++it)
	} //if(current_dir.getDirectoryContents(paths,NULL))
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		std::cerr << "Usage: build_headers {input dir} {output file}" << std::endl;
		return -1;
	}
	std::clog << "Reading " << argv[1] << std::endl;

	llvm::sys::Path path(argv[1]);
	header_files_collector(path,path);

	std::clog << "Preparing buffer " << std::endl;

	//Buffer structure is (size_t) name_length, (size_t) file_length name (not zt) file_data (not zt)
	//So, the complete input buffer size is uncompressed_size + 2*sizeof(size_t)

	size_t offset = 0;
	size_t full_size = file_list.size() * 2 * sizeof(size_t) + uncompressed_size;

	std::auto_ptr<unsigned char>   __managed_buf (new unsigned char [full_size]);
	unsigned char* buffer = __managed_buf.get();

	for(size_t i = 0; i < file_list.size(); ++i)
	{
		file_data_ptr_t file = file_list[i];

		size_t* val= reinterpret_cast<size_t*>(buffer + offset);
		*val = file->short_name.length();
		offset += sizeof(size_t);

		val= reinterpret_cast<size_t*>(buffer + offset);
		*val = file->data.length();
		offset += sizeof(size_t);

		::memcpy(buffer + offset,file->short_name.data(), file->short_name.length());
		offset += file->short_name.length();
		::memcpy(buffer + offset,file->data.data(), file->data.length());
		offset += file->data.length();
	}

	std::cout << "Compressing " << (full_size / 1024.0) << "Kb" << std::endl;
	
	int ret;
	z_stream strm;

	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	ret = deflateInit(&strm, 9); //Very aggressive compression
	if (ret != Z_OK)
		return ret;

	std::auto_ptr<unsigned char>   __zmanaged_buf (new unsigned char [full_size]);
	unsigned char* zlib_buffer = __zmanaged_buf.get();

	strm.avail_in = full_size;
	strm.avail_out = full_size;

	strm.next_in = buffer;
	strm.next_out = zlib_buffer;

	ret = deflate(&strm,Z_FINISH);

	assert(ret == Z_OK || ret == Z_STREAM_END);
	assert(strm.avail_out);

	size_t compressed_size = full_size - strm.avail_out;

	deflateEnd(&strm);

	std::clog << "Compressed size: " << (compressed_size / 1024.0) << " Kb\nGenerating C++ file" << std::endl;

	//Create output stream
	std::ofstream stream;
	
	stream.open(argv[2],std::ios_base::out);

	stream << "//This file is generated. Please, do not edit it\n//All contents will be lost, when build_headers is called next time\n\n";
	stream 
		<< "#include <cstdlib>\n\n"

		<< "extern const size_t num_files;\n"
		<< "extern const size_t uncompressed_size;\n"
		<< "extern const size_t compressed_size;\n\n"
		<< "extern unsigned char	compressed_headers[];\n\n"

		<< "const size_t num_files = " << file_list.size() << ";\n"
		<< "const size_t compressed_size = " << compressed_size << ";\n"
		<< "const size_t uncompressed_size = " << full_size << ";\n\n"

		<< "unsigned char compressed_headers[] = {\n\t";

	for(size_t i = 0; i < compressed_size; ++i)
	{
		stream << std::setw(3) << (int)zlib_buffer[i] << ", ";
		if( ( (i + 1) % 16 ) == 0)
			stream << "\n\t";
	}

	stream << "\n};\n\n";
	stream.flush();
	stream.close();
	
	return 0;
}