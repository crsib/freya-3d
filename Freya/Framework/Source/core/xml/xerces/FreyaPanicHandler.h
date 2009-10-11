#ifndef _FREYAPANICHANDLER_H_
#define _FREYAPANICHANDLER_H_

#include "core/EngineSubsystem.h"

#include <xercesc/util/PanicHandler.hpp>

namespace core
{
namespace xml
{
class XMLParser;
namespace xerces
{

class FreyaPanicHandler : public xercesc::PanicHandler
{
	friend class xml::XMLParser;
protected:
	FreyaPanicHandler();
public:
	//This function throws an exception, when xerces library needs to throw it))
	virtual void panic(const xercesc::PanicHandler::PanicReasons reason);
}; //End of FreyaPanicHandler class

} //End of xerces namespace
} //End of xml namespace
} //End of core namespace
#endif //End of _FREYAPANICHANDLER_H_
