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

    btVector3 convAssimp2Bullet(const aiVector3D& v)
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

        return scenegraph::AABB::FromMM(convAssimp2Bullet(m), convAssimp2Bullet(M));
    }

    //
    // GDataExporter
    //
    GDataExporter::GDataExporter(const std::vector<Mesh>& meshes, const String& filename)
    :   mMeshes(meshes), mFilename(filename), mState(S_EXPORTING)
    {
    }

    // WARNING! Don't call it for unpacked structures, that have to be packed :). Captain.
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

        void writeElements(std::ostream& stream) const;

        unsigned int getVertexSize() const { return mVertexSize; }
    
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

    struct ExportMeshInfo
    {
        VertexDecl vdecl;
        uint16 index_count;
        uint16 buffer_offset;
        uint32 vertex_elem_offset;
    };

    int GDataExporter::operator()()
    {
        mState = S_EXPORTING;

        std::ofstream out(mFilename.c_str(), std::ios_base::binary);

        std::vector<ExportMeshInfo> infos;
        infos.resize(mMeshes.size());

        uint16 index_buffer_offset   = 0;
        uint32 vertex_elem_offset   = 0;
        uint16 number_of_indices    = 0;
        uint32 size_of_vertex_data  = 0;

        //
        // Calculate offsets, counts...
        //

        for (size_t i = 0; i < mMeshes.size(); ++i)
        {
            ExportMeshInfo& info    = infos[i];

            aiMesh* mesh            = mMeshes[i]._mesh;
            info.index_count        = mesh->mNumFaces * 3;

            info.buffer_offset      = index_buffer_offset;
            info.vertex_elem_offset = vertex_elem_offset;
            
            index_buffer_offset     += info.index_count;
            vertex_elem_offset      += mesh->mNumVertices;
            number_of_indices       += info.index_count;

            info.vdecl.add(rvf::POSITION, rvf::FLOAT3);
            info.vdecl.add(rvf::NORMAL,   rvf::FLOAT3);

            unsigned int texIndex = 0;
            // NB! Assimp imports not more than 4 different texture coords
            // TODO: Warn if can
            for (; mesh->HasTextureCoords(texIndex); ++texIndex)
                info.vdecl.add(texIndex2Type(texIndex), rvf::FLOAT2); // TODO: Third dim.

            size_of_vertex_data += mesh->mNumVertices * info.vdecl.getVertexSize();

        }

        //
        // Write batch headers
        //

        
        // Via http://freya3d.org/wiki/WorldDataFormats/GeometricData (20.02.2010)

	    //(16-bit unsigned int) 	num_batches
	    binWrite<uint16>(infos.size(), out);

        for (size_t i = 0; i < infos.size(); ++i)
        {
            ExportMeshInfo& info = infos[i];

	        // 32-bit unsigned integer assembly_type
	        binWrite<uint32>(renderer::Primitive::TRIANGLES, out);

	        // 16-bit unsigned integer index_count 
	        binWrite<uint16>(info.index_count, out);

	        // 16-bit unsigned integer buffer_offset
	        binWrite<uint16>(info.buffer_offset, out);

            renderer::VertexElement vertexElement;

            // Write vertices declaration
            info.vdecl.writeElements(out);
        }

        //
        // Write indices
        //

        // 16-bit unsigned int  number_of_indicies
        binWrite<uint16>(number_of_indices, out);

        for (size_t i = 0; i < infos.size(); ++i)
        {
            ExportMeshInfo& info = infos[i];
            aiMesh* mesh = mMeshes[i]._mesh;
	
		    for(unsigned int face = 0; face < mesh->mNumFaces; ++face)
            {
			    for (unsigned int ind = 0; ind < mesh->mFaces[face].mNumIndices; ++ind)
                    binWrite<uint16>(info.vertex_elem_offset + mesh->mFaces[face].mIndices[ind], out);
            }
        }

        //
        // Write vertices
        //

	    // 32-bit unsigned integer 	size_of_vertex_data
        binWrite<uint32>(size_of_vertex_data, out);

        for (size_t i = 0; i < infos.size(); ++i)
        {
            ExportMeshInfo& info = infos[i];
            aiMesh* mesh = mMeshes[i]._mesh;

	        // Raw vertex data
            for (unsigned int v = 0; v < mesh->mNumVertices; ++v)
            {
                // Found way to do it even more slowly
                if (info.vdecl.has(rvf::POSITION))
                    binWriteV3(mesh->mVertices[v], out);

                if (info.vdecl.has(rvf::NORMAL))
                    binWriteV3(mesh->mNormals[v], out);

                // Textures
                for (unsigned int t = 0; info.vdecl.has(texIndex2Type(t)); ++t)
                    binWriteV2(mesh->mTextureCoords[t][v], out);
            }
        }

	    out.close();

        mState = S_READY;
        return Task::DONE;
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

    void printNode(const aiNode* node, int offset)
    {
        for (int i = 0; i < offset; ++i) 
            std::cout << " ";

        std::cout << node->mName.data << std::endl;

        for (unsigned int i = 0; i < node->mNumChildren; ++i)
            printNode(node->mChildren[i], offset + 1);
    }

    bool hasAnimation(const aiScene* scene, unsigned int meshId)
    {
        for (size_t animIter = 0; animIter < scene->mNumAnimations; ++animIter)
        {
            const aiAnimation* anim = scene->mAnimations[animIter];

            for (size_t nodeIter = 0; nodeIter < anim->mNumChannels; ++nodeIter)
            {
                aiNodeAnim* animNode = anim->mChannels[nodeIter];
                aiNode* sceneNode = scene->mRootNode->FindNode(animNode->mNodeName);

                if (sceneNode)
                {
                    for (size_t meshIter = 0; meshIter < sceneNode->mNumMeshes; ++meshIter)
                    {
                        if (sceneNode->mMeshes[meshIter] == meshId)
                            return true;
                    }
                }
            }
        }

        return false;
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

        // FIXME. How do I know that it was from GENERIC_POOL?
        core::memory::Free(fileData, core::memory::GENERIC_POOL);

        DAC_ASSERT3(scene, "Load failed! Assimp desc: " << 
            mImporter.GetErrorString() << "", mState = S_FAILED; return Task::DONE)
        
        AssetPtr asset(new Asset());
        asset->_scene = scene;
       
        asset->meshes.reserve(scene->mNumMeshes);
        for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
        {
            Mesh mesh;
            mesh._mesh = scene->mMeshes[i];
            mesh.hasAnim = hasAnimation(scene, i);
            asset->meshes.push_back(mesh);
        }

        mAsset = asset; // Assign only when it's done
        mState = S_READY;

		return Task::DONE;
	}

} // namespace dac