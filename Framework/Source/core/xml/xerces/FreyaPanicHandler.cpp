#include "core/xml/xerces/FreyaPanicHandler.h"
#include "core/xml/XMLParserException.h"
namespace core
{
namespace xml
{
namespace xerces
{
//============================== Default constructor==============================

FreyaPanicHandler::FreyaPanicHandler()
{
}

//============================== Method: panic==============================

/**********************************************************************
/* This function throws an exception, when xerces library needs to throw it))
**********************************************************************/

void		FreyaPanicHandler::panic(const PanicHandler::PanicReasons reason)
{
	throw xml::XMLParserException(EString("XML error: xerces-c++ reported: ") + PanicHandler::getPanicReasonString(reason));
}

//==============================~Method: panic==============================

} //End of xerces namespace
} //End of xml namespace
} //End of core namespace

