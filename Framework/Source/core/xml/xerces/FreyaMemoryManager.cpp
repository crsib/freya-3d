#include "core/xml/xerces/FreyaMemoryManager.h"
#include "core/EngineCore.h"
namespace core
{
namespace xml
{
namespace xerces
{
//============================== Default constructor==============================

FreyaMemoryManager::FreyaMemoryManager()
{
	//TODO: Constructor stub
}

//==============================~Default constructor==============================


//============================== Method: getExceptionMemoryManager==============================

/******************************************************************************************
* returns this
******************************************************************************************/

xercesc::MemoryManager*		FreyaMemoryManager::getExceptionMemoryManager()
{
	return this;
}

//==============================~Method: getExceptionMemoryManager==============================

//============================== Method: allocate==============================

/*************************************************************************
* Allocates a memory block of size sz
*************************************************************************/

void*		FreyaMemoryManager::allocate(XMLSize_t sz)
{
	return core::memory::Allocate(sz,core::memory::XML_POOL);
}

//==============================~Method: allocate==============================

//============================== Method: deallocate==============================

/***************************************************************************
* Frees memory block
***************************************************************************/

void		FreyaMemoryManager::deallocate(void* p)
{
	core::memory::Free(p,core::memory::XML_POOL);
}

//==============================~Method: deallocate==============================

} //End of xerces namespace
} //End of xml namespace
} //End of core namespace

