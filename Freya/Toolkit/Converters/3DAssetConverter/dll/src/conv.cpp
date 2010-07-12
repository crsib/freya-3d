/* 3DAC source */

#include "freya-3dac/common.h"
#include "freya-3dac/conv.h"

namespace dac
{
    //
    // GDataExporter
    //
    GDataExporter::GDataExporter(const Mesh& mesh, const String& filename)
    :   mMesh(mesh), mFilename(filename), mState(S_EXPORTING)
    {
    }

    // perversion FIXME! And Dangerous!
    template <typename T>
    void binWrite(const T& write, std::ostream& stream)
    {

	    stream.write((char*)&write, sizeof(write)); 
    }

    void binWriteVE(const renderer::VertexElement& write, std::ostream& stream)
    {
        binWrite<uint32>(write.streamID, stream);
        binWrite<uint32>(write.usage,    stream);
        binWrite<uint32>(write.type,     stream);
        binWrite<uint32>(write.offset,   stream);
    }

    int GDataExporter::operator()()
    {
        mState = S_EXPORTING;

        aiMesh* mesh = mMesh._mesh;

        DAC_ASSERT(mesh != nullptr);
        //DAC_ASSERT(mesh->mPrimitiveTypes != aiPrimitiveType_TRIANGLE);

        std::ofstream out(mFilename.c_str(), std::ios_base::binary);

	    // Via http://freya3d.org/wiki/WorldDataFormats/GeometricData (20.02.2010)

	    //(16-bit unsigned int) 	num_batches
	    binWrite<uint16>(1, out);

	    // 32-bit unsigned integer assembly_type
	    binWrite<uint32>(renderer::Primitive::TRIANGLES, out);

	    // 16-bit unsigned integer index_count 
	    binWrite<uint16>(mesh->mNumFaces * 3, out);

	    // 16-bit unsigned integer buffer_offset
	    binWrite<uint16>(0, out);

        renderer::VertexElement vertexElement;

        unsigned int vertexSize = 0;

        binWriteVE(renderer::VertexElement(0, 
            renderer::VertexFormat::POSITION, renderer::VertexFormat::FLOAT3, vertexSize), out);
        vertexSize += sizeof(float) * 3; // FIXME: Make it with engine help :)

		binWriteVE(renderer::VertexElement(0, 
            renderer::VertexFormat::NORMAL, renderer::VertexFormat::FLOAT3, vertexSize), out);
        vertexSize += sizeof(float) * 3;

	    // Last declaration element
	    binWriteVE(renderer::VertexElement((unsigned)-1,renderer::VertexFormat::UNUSED,renderer::VertexFormat::DWORD,0), out);
	
        if (!mesh->mFaces)
            makeIndices();

	    // 16-bit unsigned int  number_of_indicies
        binWrite<uint16>(mesh->mFaces[0].mNumIndices * mesh->mNumFaces, out);

	    // 16-bit unsigned int array indcies
		for(unsigned face = 0; face < mesh->mNumFaces; ++face)
			for (unsigned int i = 0; i < mesh->mFaces[face].mNumIndices; ++i)
			    binWrite<uint16>(mesh->mFaces[face].mIndices[i], out);

	    // 32-bit unsigned integer 	size_of_vertex_data
	    binWrite<uint32>(vertexSize * mesh->mNumVertices, out);

	    // Raw vertex data
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
        {
            binWrite<float>(mesh->mVertices[i].x, out);
            binWrite<float>(mesh->mVertices[i].y, out);
            binWrite<float>(mesh->mVertices[i].z, out);

            binWrite<float>(mesh->mNormals[i].x, out);
            binWrite<float>(mesh->mNormals[i].y, out);
            binWrite<float>(mesh->mNormals[i].z, out);
        }

	    out.close();

        mState = S_READY;
        return ReturnValue::DONE;
    }

    void GDataExporter::makeIndices()
    {
        DAC_ERROR("Not implemented");
    }

    //
    // Mesh
    //


    //
    // Asset
    //

    //
    // AssetLoader
    //
    Assimp::Importer AssetLoader::mImporter;

    AssetLoader::AssetLoader(const String& filename)
    :   mFilename(filename), mState(S_LOADING)
    {
    }

    String getFileExt(const String& filename)
    {
        String ext;
        int sz = (int)filename.size();
        int i = sz - 1;

        for (; i >= 0; --i)
            if (filename[i] == '.')
                break;

        for (++i; i < sz; ++i)
            ext += filename[i];

        return ext;
    }

    int AssetLoader::operator() ()
	{
        mState = S_LOADING;

        core::filesystem::Filesystem* fs = core::EngineCore::getFilesystem();
		size_t fileSize;
        void* fileData = fs->read(mFilename, &fileSize);

        DAC_ASSERT3(fileData != nullptr, "Can't open file `" << mFilename << "`!", 
            mState = S_FAILED; return ReturnValue::DONE);

        const aiScene* scene = mImporter.ReadFileFromMemory(fileData, fileSize, 
            aiProcessPreset_TargetRealtime_Fast, getFileExt(mFilename).c_str());
        
        String err;

        if (scene == nullptr)
        {
            err = mImporter.GetErrorString();
        }

        DAC_ASSERT3(scene != nullptr, "No scene!", 
            mState = S_FAILED; return ReturnValue::DONE);
        
        AssetPtr asset(new Asset());

        asset->_scene = scene;

        asset->meshes.reserve(scene->mNumMeshes);

        for (size_t i = 0; i < scene->mNumMeshes; ++i)
        {
            Mesh mesh;
            mesh._mesh = scene->mMeshes[i];
            asset->meshes.push_back(mesh);
        }

        mAsset = asset; // Assign only when it's done
        mState = S_READY;
		return ReturnValue::DONE;
	}

} // namespace dac