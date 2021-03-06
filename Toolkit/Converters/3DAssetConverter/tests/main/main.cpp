
#include "freya-3dac/conv.h"
#include <list>
#include <sstream>

int main(int argc, char* argv[])
{
    try
	{
		core::EngineCore core(argc,argv, "3DAC.Tests.Main");

        core::filesystem::Filesystem* fs = core::EngineCore::getFilesystem();
		fs->mount("pwd");

        dac::AssetLoader loader("/3DAC/jeep1.3ds");
		loader();

        dac::AssetPtr asset = loader.getAsset();

        DAC_ASSERT3(loader.getState() == dac::AssetLoader::S_READY && 
            asset.get() != nullptr, "Wasn't loaded!", return 1);

        DAC_ASSERT3(asset->meshes.size() > 0, "No meshes to export!", return 0);
        dac::GDataExporter exporter(asset->meshes, "meshes.vdata");
        exporter();

        DAC_ASSERT2(exporter.getState() == dac::GDataExporter::S_READY, "Wasn't exported!");

		std::cout << "Done. Exit." << std::endl;
	}
	catch(EngineException& ex)
	{
		//Something failed. Ansi c++ standart gurantees that all stack object will be release at this point.
		std::cout << "[ENGINE]: "<< ex.message() << std::endl;
	}
	catch(std::exception& ex)
	{
		std::cout << "[STD]: "<< ex.what() << std::endl;
	}
	catch(...)
	{
		std::cout << "Unknown exception" << std::endl;
	}

    return 0;
}