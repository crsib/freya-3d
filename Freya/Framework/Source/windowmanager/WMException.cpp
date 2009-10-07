
#ifdef _FREYA_SHARED_PLUGIN
#include <cstdlib>
namespace core
{
namespace memory
{
	extern void* (*Allocate)(size_t,unsigned);
	extern void  (*Free)(void*,unsigned);
}
}
#endif
#include "windowmanager/WMException.h"


namespace windowmanager
{
//============================== Default constructor==============================

WMException::WMException()
{
	m_Msg = "Unknown window manager exception";
}

//==============================~Default constructor==============================

//============================== Derived constructors==============================

//==============================~Derived constructors==============================

//============================== Destructor==============================

WMException::~WMException()
{
}

//==============================~Destructor==============================

//============================== Method: message==============================

EString		WMException::message() const
{
	return m_Msg;
}

//==============================~Method: message==============================

} //End of windowmanager namespace

