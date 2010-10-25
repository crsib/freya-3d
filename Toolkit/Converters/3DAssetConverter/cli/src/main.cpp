/* 3DAC source */

#include "common.h"

void printHelp()
{
    std::cout << "Using: freya-3dac {command}" << std::endl;
    std::cout << "List of commands: " << std::endl;
    std::cout << "   list {filepath}" << std::endl;
    std::cout << "      Prints meshes information from file {filepath}" << std::endl;
    std::cout << "   convert {filepath} -nodes {node_name1} {node_name2} ... -o {out_file}" << std::endl;
    std::cout << "      Convert nodes and exports to {out_file}" << std::endl;
}

int main(int argc, char* argv[])
{
    po::Args args(argc, argv);

    freopen("3dac.log", "w", stdout);// Freya core log covers whole cmd screen :)

    if (args.num_args() > 0)
    {
        core::EngineCore core(argc, argv, "freya-3dac");

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

            // No sense until haven't got a mesh name
            for (size_t i = 0; i < asset->meshes.size(); ++i)
            {
                std::cout << "Mesh " << i << "; Has animation: " << asset->meshes[i].hasAnim << std::endl;
            }
        } 
        else if(args.num_arg(0) == "convert")
        {
            const po::Value* pathv;
            const po::Value* outFilepathv;

            DAC_ASSERT3((pathv = args.has_num_arg(1)) != nullptr, 
                "Expected second argument as path to source file!", printHelp(); return 1);

            DAC_ASSERT3((outFilepathv = args.has_key_arg_val("o")) != nullptr, 
                "Expected `-o {file_out}` argument - path to export file!", printHelp(); return 1);

            std::string path = pathv->as_string();

            dac::AssetLoader loader(path);
		    loader();

            dac::AssetPtr asset = loader.getAsset();

            DAC_ASSERT3(loader.getState() == dac::AssetLoader::S_READY && 
                asset.get() != nullptr, "Wasn't loaded!", return 1);

            const po::Values* nodes = args.has_key_arg_arr("nodes");

            std::vector<dac::Mesh> exportMeshes;

            // Export all nodes
            if (nodes == nullptr || (nodes->is_single() && (*nodes)[0].as_string() == "*"))
            {
                std::cout << "Exporting all meshes" << std::endl;
                exportMeshes = asset->meshes;
            }
            else // Select nodes
            {
                for (size_t nodesIter = 0; nodesIter < nodes->count(); ++nodesIter)
                {
                    std::string nodeName = (*nodes)[nodesIter].as_string();
                    aiNode* nodePtr = asset->_scene->mRootNode->FindNode(nodeName);

                    if (nodePtr)
                    {
                        for (unsigned int meshesIter = 0; meshesIter < nodePtr->mNumMeshes; ++meshesIter)
                            exportMeshes.push_back(asset->meshes[nodePtr->mMeshes[meshesIter]]);
                    }
                    else
                        DAC_ERROR("No such node `" << nodeName << "` to export !");                  
                }
            }

            dac::GDataExporter exporter(exportMeshes, outFilepathv->as_string());
            exporter();
            DAC_ASSERT2(exporter.getState() == dac::GDataExporter::S_READY, "Wasn't exported!");
        }
        else //"switch"
            printHelp();
    }
    else //if (args.num_args() > 0)
        printHelp();

    return 0;
}
