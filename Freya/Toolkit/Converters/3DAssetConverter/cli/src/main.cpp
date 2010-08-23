/* 3DAC source */

#include "common.h"

void printHelp()
{
    std::cout << "Using: freya-3dac {command}" << std::endl;
    std::cout << "List of commands: " << std::endl;
    std::cout << "    list {filepath} - path to supported asset." << std::endl;
}

// No sense until haven't got a mesh name
void printMesh(const dac::Mesh& mesh, std::ostream& stream)
{
}

int main(int argc, char* argv[])
{
    po::Args args(argc, argv);

    freopen("3dac.log", "w", stdout);// Freya core log covers full cmd screen :)

    if (args.num_args() > 0)
    {
        core::EngineCore core(argc,argv, "freya-3dac-cli");

        core::filesystem::Filesystem* fs = core::EngineCore::getFilesystem();
		fs->mount("pwd");

        if (args.num_arg(0) == "list")
        {
            const po::Value* pathv;

            DAC_ASSERT3((pathv = args.has_num_arg(1)) != nullptr, 
                "Expected second argument as path to file!", printHelp(); return 1);

            std::string path = pathv->as_string();

            DAC_ASSERT3(fs->fileExists(path), 
                "Requested file wasn't not found in engine filesystem!", return 0);

            dac::AssetLoader loader(path);
		    loader();

            dac::AssetPtr asset = loader.getAsset();

            DAC_ASSERT3(loader.getState() == dac::AssetLoader::S_READY && 
                asset.get() != nullptr, "Wasn't loaded!", return 1);

            //for (size_t i = 0; i < asset->meshes.size(); ++i)
            //    printMesh(asset->meshes[i], std::cout);

        } 
        else if(args.num_arg(0) == "convert")
        {
            const po::Value* pathv;

            DAC_ASSERT3((pathv = args.has_num_arg(1)) != nullptr, 
                "Expected second argument as path to file!", printHelp(); return 1);

            std::string path = pathv->as_string();

            dac::AssetLoader loader(path);
		    loader();

            dac::AssetPtr asset = loader.getAsset();

            DAC_ASSERT3(loader.getState() == dac::AssetLoader::S_READY && 
                asset.get() != nullptr, "Wasn't loaded!", return 1);

            const po::Values* nodes = args.has_key_arg_arr("nodes");

            // FIXME. Tiny copy-paste
            if (nodes == nullptr || (nodes->is_single() && (*nodes)[0].as_string() == "*"))
            {
                std::cout << "Exporting all meshes" << std::endl;
                for (size_t meshesIter = 0; meshesIter < asset->meshes.size(); ++meshesIter)
                {
                    std::ostringstream exportName;
                    exportName << "mesh" << meshesIter << ".vdata";

                    dac::GDataExporter exporter(asset->meshes[meshesIter], exportName.str());
                    exporter();
                    DAC_ASSERT2(exporter.getState() == dac::GDataExporter::S_READY, "Wasn't exported!");
                    std::cout << "Mesh exported to '" << exportName.str() << "'" << std::endl;
                }
            }
            else
            {
                for (size_t nodesIter = 0; nodesIter < nodes->count(); ++nodesIter)
                {
                    std::string nodeName = (*nodes)[nodesIter].as_string();
                    aiNode* nodePtr = asset->_scene->mRootNode->FindNode(nodeName);

                    std::cout << "Exporting '" << nodePtr->mName.data << "' node" << std::endl;

                    for (unsigned int meshesIter = 0; meshesIter < nodePtr->mNumMeshes; ++meshesIter)
                    {
                        aiMesh* aiMesh = asset->_scene->mMeshes[nodePtr->mMeshes[meshesIter]];

                        std::ostringstream exportName;
                        exportName << nodePtr->mName.data << meshesIter << ".vdata";

                        dac::Mesh dacMesh;
                        dacMesh._mesh = aiMesh;

                        dac::GDataExporter exporter(dacMesh, exportName.str());
                        exporter();
                        DAC_ASSERT2(exporter.getState() == dac::GDataExporter::S_READY, "Wasn't exported!");
                        std::cout << "  Mesh exported to '" << exportName.str() << "'" << std::endl;
                    }
                }//for (size_t nodesIter = 0; nodesIter < nodes->count(); ++nodesIter)
            }//if (nodes->is_single() && (*nodes)[0].as_string() == "*")
        }
        else
            printHelp();
    }
    else
        printHelp();

    return 0;
}