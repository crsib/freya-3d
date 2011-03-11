#ifndef _RENDERINGAPIFACTORY_H_
#define _RENDERINGAPIFACTORY_H_

#include "core/drivermodel/DriverFactory.h"
#include <map>
namespace core
{
class EngineCore;

namespace drivermodel
{
class DriverID;
}
}
namespace renderer
{
//! This class is used to create a RenderingAPI driver
class RenderingAPIFactory : public core::drivermodel::DriverFactory
{
	friend class core::EngineCore;
	RenderingAPIFactory();
	virtual ~RenderingAPIFactory();

public:
	//! Create driver identified by {name} string
	virtual core::drivermodel::Driver* 	createDriver(const EString& name);
	virtual void						registerDriver(core::drivermodel::DriverID* driverID);
	virtual EStringList	listDrivers() const;
private:
	std::map<EString,core::drivermodel::DriverID*,std::less<EString>, core::memory::MemoryAllocator<std::pair<const EString,core::drivermodel::DriverID*> > > m_Drivers;
}; //End of RenderingAPIFactory class

} //End of renderer namespace
#endif //End of _RENDERINGAPIFACTORY_H_
