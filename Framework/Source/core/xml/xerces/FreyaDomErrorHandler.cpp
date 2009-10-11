/*
 * FreyaDomErrorHandler.cpp
 *
 *  Created on: 11.02.2009
 *      Author: vedenko
 */

#include "FreyaDomErrorHandler.h"
#include <iostream>
#include "core/xml/XMLStringWrap.h"
#include "core/xml/XMLParserException.h"
namespace core
{

namespace xml
{

namespace xerces
{

FreyaDomErrorHandler::FreyaDomErrorHandler()
{
	m_ParseOK = true;
}

FreyaDomErrorHandler::~FreyaDomErrorHandler()
{
}

bool FreyaDomErrorHandler::handleError  	(const xercesc::DOMError & domError)
{

	//TODO replace it with normal logging
	using xercesc::DOMError;
	if (domError.getSeverity() == DOMError::DOM_SEVERITY_WARNING)
	        std::cout << "\nWarning at file ";
	    else if (domError.getSeverity() == DOMError::DOM_SEVERITY_ERROR)
	        std::cout << "\nError at file ";
	    else
	        std::cout << "\nFatal Error at file ";

	    std::cout << core::xml::XMLStringWrap(domError.getLocation()->getURI())
	         << ", line " << domError.getLocation()->getLineNumber()
	         << ", char " << domError.getLocation()->getColumnNumber()
	         << "\n  Message: " << core::xml::XMLStringWrap(domError.getMessage()) << std::endl;
	    if ((domError.getSeverity() == DOMError::DOM_SEVERITY_ERROR) || (domError.getSeverity() == DOMError::DOM_SEVERITY_FATAL_ERROR ))
	    	//throw core::xml::XMLParserException("Error occurred while parsing xml document");
	    	m_ParseOK = false;
	    return true;
}

}

}

}
