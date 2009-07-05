#include "renderer/RenderingAPIFactory.h"

#include "renderer/Drivers/OpenGL_GLSL/SM4_Full/OpenGL_GLSL_SM4_Full.h"
#include "renderer/Drivers/OpenGL_GLSL/SM4_NoDS/OpenGL_GLSL_SM4_NoDS.h"
#include "renderer/Drivers/OpenGL_GLSL/SM4_NoMRT/OpenGL_GLSL_SM4_NoMRT.h"
#include "renderer/Drivers/OpenGL_GLSL/SM4_NoMRTDS/OpenGL_GLSL_SM4_NoMRTDS.h"

#include "renderer/Drivers/OpenGL_GLSL/SM3_Full/OpenGL_GLSL_SM3_Full.h"
#include "renderer/Drivers/OpenGL_GLSL/SM3_NoDS/OpenGL_GLSL_SM3_NoDS.h"
#include "renderer/Drivers/OpenGL_GLSL/SM3_NoMRT/OpenGL_GLSL_SM3_NoMRT.h"
#include "renderer/Drivers/OpenGL_GLSL/SM3_NoMRTDS/OpenGL_GLSL_SM3_NoMRTDS.h"
#include "renderer/Drivers/OpenGL_GLSL/SM3_Simple/OpenGL_GLSL_SM3_Simple.h"

#include "core/drivermodel/DriverException.h"
namespace renderer
{
//============================== Derived constructors==============================
RenderingAPIFactory::RenderingAPIFactory()
{
	registerDriver(new renderer::drivers::ids::OpenGL_GLSL_SM4_FULL());
	registerDriver(new renderer::drivers::ids::OpenGL_GLSL_SM4_NODS());
	registerDriver(new renderer::drivers::ids::OpenGL_GLSL_SM4_NOMRT());
	registerDriver(new renderer::drivers::ids::OpenGL_GLSL_SM4_NOMRTDS());

	registerDriver(new renderer::drivers::ids::OpenGL_GLSL_SM3_FULL());
	registerDriver(new renderer::drivers::ids::OpenGL_GLSL_SM3_NODS());
	registerDriver(new renderer::drivers::ids::OpenGL_GLSL_SM3_NOMRT());
	registerDriver(new renderer::drivers::ids::OpenGL_GLSL_SM3_NOMRTDS());

	registerDriver(new renderer::drivers::ids::OpenGL_GLSL_SM3_SIMPLE());
}
//==============================~Derived constructors==============================

//============================== Destructor==============================

RenderingAPIFactory::~RenderingAPIFactory()
{
	typedef std::map<EString,core::drivermodel::DriverID*,std::less<EString>, core::memory::MemoryAllocator<std::pair<const EString,core::drivermodel::DriverID*> > >::iterator __iterator;
	for(__iterator it = m_Drivers.begin();it != m_Drivers.end();it++)
		delete it->second;
}

//==============================~Destructor==============================

//============================== Method: createDriver==============================

core::drivermodel::Driver*		RenderingAPIFactory::createDriver(const EString& name)
{
	if(m_Drivers[name])
		return m_Drivers[name]->create();
	throw core::drivermodel::DriverException(EString("Failed to create rendering driver - ") + name + ": driver not found");
}

//==============================~Method: createDriver==============================

void							RenderingAPIFactory::registerDriver(core::drivermodel::DriverID* driverID)
{
	m_Drivers[driverID->id()] = driverID;
}

EStringList	RenderingAPIFactory::listDrivers() const
{
	EStringList		lst;
	typedef std::map<EString,core::drivermodel::DriverID*,std::less<EString>, core::memory::MemoryAllocator<std::pair<const EString,core::drivermodel::DriverID*> > >::const_iterator __iterator;
	for(__iterator it = m_Drivers.begin();it != m_Drivers.end();it++)
		lst.push_back(it->first);
	return lst;
}

} //End of renderer namespace

