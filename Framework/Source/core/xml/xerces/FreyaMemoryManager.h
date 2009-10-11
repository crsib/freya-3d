#ifndef _FREYAMEMORYMANAGER_H_
#define _FREYAMEMORYMANAGER_H_

#include "core/EngineSubsystem.h"
#include <xercesc/framework/MemoryManager.hpp>

namespace core
{
namespace xml
{
class XMLParser;
namespace xerces
{

class FreyaMemoryManager : public ::EngineSubsystem, public xercesc::MemoryManager
{
	friend class xml::XMLParser;
protected:
	FreyaMemoryManager();
public:

	//returns this
	virtual xercesc::MemoryManager* getExceptionMemoryManager();

	//Allocates a memory block of size sz
	virtual void* allocate(XMLSize_t sz);

	//Frees memory block
	virtual void deallocate(void* p);


}; //End of FreyaMemoryManager class

} //End of xerces namespace
} //End of xml namespace
} //End of core namespace
#endif //End of _FREYAMEMORYMANAGER_H_
