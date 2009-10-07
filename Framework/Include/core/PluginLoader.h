#ifndef PLUGIN_LOADER_H_
#define PLUGIN_LOADER_H_

#include "core/EngineSubsystem.h"
#include "core/EString.h"

namespace core
{	
	namespace drivermodel
	{
		class Driver;
	}
class EngineCore;
class PluginLoader : public EngineSubsystem
{
	friend class core::EngineCore;
private:
	PluginLoader(int arcC,char** argV);
	virtual ~PluginLoader();
public:
};
}

#endif // PLUGIN_LOADER_H_