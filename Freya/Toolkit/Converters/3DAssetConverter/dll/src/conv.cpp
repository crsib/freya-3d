/* 3DAC source */

#include "freya-3dac/common.h"
#include "freya-3dac/conv.h"

namespace dac
{
    //
    // Mesh
    //


    //Mesh::Mesh(aiMesh* mesh)
    //:   _mesh(mesh)
    //{
    //    hasAnim // ???
    //}

    btVector3 convAmp2Blt(const aiVector3D& v)
    {
        return btVector3(v.x, v.y, v.z);
    }

    scenegraph::AABB Mesh::getAABB() const
    {
        aiVector3D m, M;

        if (_mesh->mNumVertices != 0)
        {
            m = M = _mesh->mVertices[0];

            for (unsigned int i = 1; i < _mesh->mNumVertices; ++i)
            {
                const aiVector3D& v = _mesh->mVertices[i];

                if (v.x < m.x) m.x = v.x;
                if (v.y < m.y) m.y = v.y;
                if (v.z < m.z) m.z = v.z;

                if (v.x > M.x) M.x = v.x;
                if (v.y > M.y) M.y = v.y;
                if (v.z > M.z) M.z = v.z;
            }
        }

        return scenegraph::AABB::FromMM(convAmp2Blt(m), convAmp2Blt(M));
    }

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
	    stream.write((const char*)&write, sizeof(write)); 
    }

    void binWrite(const void* write, unsigned int sz, std::ostream& stream)
    {
	    stream.write((const char*)&write, sz); 
    }

    void binWriteV3(const aiVector3D& v, std::ostream& stream)
    {
	    binWrite<float>(v.x, stream);
        binWrite<float>(v.y, stream);
        binWrite<float>(v.z, stream);
    }

    // Not a miss. Print V3 as V2.
    void binWriteV2(const aiVector3D& v, std::ostream& stream)
    {
	    binWrite<float>(v.x, stream);
        binWrite<float>(v.y, stream);
    }

    void binWriteV2(const aiVector2D& v, std::ostream& stream)
    {
	    binWrite<float>(v.x, stream);
        binWrite<float>(v.y, stream);
    }

    class VertexDecl
    {
    public:

        VertexDecl();

        void add(rvf::USAGE usage, rvf::TYPE type);

        bool has(rvf::USAGE usage) const;

        static int getSize(rvf::TYPE type);

        void writeElements(std::ostream& stream) const; // BAd arcH


        unsigned int getVertexSize() const { return mVertexSize; }

        //std::pair<const void*, unsigned int> rawElements() const;
        //const void* getRawElementsPtr() const;
        //unsigned int getRawElementsSize() const;
        //static rvf::TYPE defaultType4Usage(rvf::USAGE usage);
    
    protected:
        std::vector<FreyaVertexElement> mElements;

        unsigned int mVertexSize;
    };

    VertexDecl::VertexDecl()
    :   mVertexSize(0)
    {
        mElements.push_back(FreyaVertexElement((unsigned)-1,rvf::UNUSED,rvf::DWORD,0));
    }

    void VertexDecl::writeElements(std::ostream& stream) const
    {
        for (size_t i = 0; i < mElements.size(); ++i)
        {
            binWrite<uint32>(mElements[i].streamID, stream);
            binWrite<uint32>(mElements[i].usage,    stream);
            binWrite<uint32>(mElements[i].type,     stream);
            binWrite<uint32>(mElements[i].offset,   stream);
        }
    }

    int VertexDecl::getSize(rvf::TYPE type)
    {
        switch (type) // Because life without hardcoding isn't real life :D
        { // ...But FIXME. What about x64?
        case rvf::FLOAT1: return 4;
		case rvf::FLOAT2: return 4 * 2;
		case rvf::FLOAT3: return 4 * 3;
		case rvf::FLOAT4: return 4 * 4;
		case rvf::DWORD:  return 4;
		case rvf::UBYTE4: return 4 * 1;
        case rvf::SHORT2: return 2 * 2;
        case rvf::SHORT4: return 4 * 2;
        default:
            DAC_ERROR("Unknown vertex format type `" << type << "`!");
            return 0;
        }
    }

    void VertexDecl::add(rvf::USAGE usage, rvf::TYPE type)
    {
        mElements.insert(mElements.end() - 1, 
            FreyaVertexElement(0, usage, type, mVertexSize));

        mVertexSize += getSize(type);
    }

    bool VertexDecl::has(rvf::USAGE usage) const
    {
        for (size_t i = 0; i < mElements.size(); ++i)
            if (mElements[i].usage == usage)
                return true;

        return false;
    }

    rvf::USAGE texIndex2Type(unsigned int index)
    {
        switch (index)
        {
        case 0: return rvf::TEXT_COORD0;
        case 1: return rvf::TEXT_COORD1;
        case 2: return rvf::TEXT_COORD2;
        case 3: return rvf::TEXT_COORD3;
        default: 
            DAC_ERROR(index << " - such big texture index isn't supported by Assimp!");
            return rvf::TEXT_COORD0;
        }
    }

    int GDataExporter::operator()()
    {
        mState = S_EXPORTING;

        aiMesh* mesh = mMesh._mesh;

        DAC_ASSERT(mesh != nullptr);
        DAC_ASSERT(mesh->mPrimitiveTypes == aiPrimitiveType_TRIANGLE);

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

        VertexDecl vdecl;

        vdecl.add(rvf::POSITION, rvf::FLOAT3);
        vdecl.add(rvf::NORMAL,   rvf::FLOAT3);

        unsigned int texIndex = 0;
        // NB! Assimp imports not more than 4 different texture coords
        // TODO: Warn if can
        for (; mesh->HasTextureCoords(texIndex); ++texIndex)
            vdecl.add(texIndex2Type(texIndex), rvf::FLOAT2); // TODO: Third dim.

        // Write vertices declaration
        vdecl.writeElements(out);
	
        if (!mesh->mFaces)
            makeIndices();

	    // 16-bit unsigned int  number_of_indicies
        binWrite<uint16>(mesh->mFaces[0].mNumIndices * mesh->mNumFaces, out);

	    // 16-bit unsigned int array indcies
		for(unsigned face = 0; face < mesh->mNumFaces; ++face)
			for (unsigned int i = 0; i < mesh->mFaces[face].mNumIndices; ++i)
			    binWrite<uint16>(mesh->mFaces[face].mIndices[i], out);

	    // 32-bit unsigned integer 	size_of_vertex_data
        binWrite<uint32>(vdecl.getVertexSize() * mesh->mNumVertices, out);

	    // Raw vertex data
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
        {
            // Found way to do it even more slowly

            if (vdecl.has(rvf::POSITION))
                binWriteV3(mesh->mVertices[i], out);

            if (vdecl.has(rvf::NORMAL))
                binWriteV3(mesh->mNormals[i], out);

            // Textures
            for (unsigned int texi = 0; vdecl.has(texIndex2Type(texi)); ++texi)
                binWriteV2(mesh->mTextureCoords[texi][i], out);
        }

	    out.close();

        mState = S_READY;
        return Task::DONE;
    }

    void GDataExporter::makeIndices()
    {
        DAC_ERROR("Making indices isn't implemented!");
    }

    //
    // Asset
    //

    //
    // AssetLoader
    //
    AssetLoader::AssetLoader(const String& filepath)
    :   mFilepath(filepath), mState(S_LOADING)
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

        if (i == -1) return "";

        for (++i; i < sz; ++i)
            ext += filename[i];

        return ext;
    }

    int AssetLoader::operator() ()
	{
        mState = S_LOADING;

        size_t fileSize;
        void* fileData = core::EngineCore::getFilesystem()->read(mFilepath, &fileSize);

        DAC_ASSERT3(fileData != nullptr, "Can't open file `" << mFilepath << "`!", 
            mState = S_FAILED; return Task::DONE); 

        const aiScene* scene = mImporter.ReadFileFromMemory(fileData, fileSize, 
            aiProcessPreset_TargetRealtime_Fast, getFileExt(mFilepath).c_str());

        // TODO. How do I know that it was from GENERIC_POOL?
        core::memory::Free(fileData, core::memory::GENERIC_POOL);

        DAC_ASSERT3(scene, "Load failed! Assimp desc: " << 
            mImporter.GetErrorString() << "", mState = S_FAILED; return Task::DONE)
        
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

		return Task::DONE;
	}

} // namespace dac