/* 3DAC header */

#ifndef _3DAC_CONV_H
#define _3DAC_CONV_H

#include "common.h"

namespace dac 
{
    namespace rvf = renderer::VertexFormat;

    // Copied because of problems with Freya engine allocations
    struct FreyaVertexElement// : public EngineSubsystem
    {
	    FreyaVertexElement(unsigned sid,renderer::VertexFormat::USAGE usg,renderer::VertexFormat::TYPE tp,unsigned off)
	    : streamID(sid),usage(usg),type(tp),offset(off){}
	    FreyaVertexElement(){}
	    unsigned				streamID;
	    renderer::VertexFormat::USAGE		usage;
	    renderer::VertexFormat::TYPE		type;
	    unsigned 				offset;
    };

    class _3DAC_EXPORT Exception : public std::exception
    {
    public:

        Exception(const String& msg) : mMsg(msg) {}

        const char* what() const { return mMsg.c_str(); }

    protected:
        String mMsg;
    };

    class _3DAC_EXPORT IOException : public Exception
    {
    public:
        IOException(const String& msg) : Exception(msg) {}
    };


    // No need in incapsulation
    class _3DAC_EXPORT Mesh
    {
    public:

        bool hasAnim;

        aiMesh* _mesh;

    public:

        //Mesh(aiMesh* mesh);

        scenegraph::AABB getAABB() const;
    };

    class _3DAC_EXPORT GDataExporter : public core::taskmanager::Task
    {
    public:
        enum State
        {
            //S_NOT_STARTED,
            S_EXPORTING,
            S_READY,
            S_FAILED
        };

    public:

        GDataExporter(const Mesh& mesh, const String& filename);

	    virtual int operator() ();

        State getState() const { return mState; }

    protected:
        void makeIndices();

    protected:
        State mState;

        String mFilename;

        Mesh mMesh;
    };

    // No need in incapsulation
    class _3DAC_EXPORT Asset
    {
    public:

        const aiScene* _scene;

        std::vector<Mesh> meshes;

    public:

        
    };

    typedef boost::shared_ptr<Asset> AssetPtr;

    class _3DAC_EXPORT AssetLoader : public core::taskmanager::Task
    {
    public:

        enum State
        {
            //S_NOT_STARTED,
            S_LOADING,
            S_READY,
            S_FAILED
        };

    public:
        AssetLoader(const String& filename);

	    virtual int operator() ();

        State getState() const { return mState; }

        /// Returns valid assert only when state is S_READY, otherwise nullptr. \sa getState
        AssetPtr getAsset() { return mAsset; }

        String getSourceFilepath() const { return mFilepath; }

    protected:

        Assimp::Importer mImporter;

        State mState;

        String mFilepath;

        AssetPtr mAsset;
    };
} // namespace dac

#endif // #ifndef _3DAC_CONV_H