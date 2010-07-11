/* 3DAC header */

#ifndef _3DAC_CONV_H
#define _3DAC_CONV_H

#include "common.h"

namespace dac 
{
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

        /// Can be nullptr :)
        AssetPtr getAsset() { return mAsset; }

    protected:
        static Assimp::Importer mImporter;

        State mState;

        String mFilename;

        AssetPtr mAsset;
    };
} // namespace dac

#endif // #ifndef _3DAC_CONV_H