
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

        dac::AssetLoader loader("/3DAC/pyramob.3ds");
		loader();

        dac::AssetPtr asset = loader.getAsset();

        DAC_ASSERT3(loader.getState() == dac::AssetLoader::S_READY 
            && asset.get() != nullptr, "Wasn't load!", return 1);

        size_t qq = asset->meshes.size();
        DAC_ASSERT3(asset->meshes.size() > 0, "No meshes to export", return 0);
        dac::GDataExporter exporter(asset->meshes[0], "mesh0.vdata");
        exporter();

        DAC_ASSERT2(exporter.getState() == dac::GDataExporter::S_READY, "Wasn't exported!");

        /*typedef std::list<dac::GDataExporter> Exporters;
        Exporters exporters;

        for (size_t i = 0; i < asset->meshes.size(); ++i)
        {
            std::ostringstream filename;
            filename << "mesh" << i << ".vdata";
            dac::GDataExporter exporter(asset->meshes[i], filename.str());
            exporters.push_back(exporter);
        }

        for (Exporters::iterator i = exporters.begin(); i != exporters.end(); ++i)
            core::EngineCore::getTaskManager()->addAsynchronousTask(&(*i));

        while(true)
        {
            Exporters::iterator i = exporters.begin();
            for (; i != exporters.end(); ++i)
                if (i->getState() == dac::GDataExporter::S_EXPORTING)
                    break;

            if (i == exporters.end())
                break;
        }*/

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