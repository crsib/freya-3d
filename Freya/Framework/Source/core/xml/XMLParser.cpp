#include "core/xml/XMLParser.h"
#include <xercesc/util/PlatformUtils.hpp>

#include "core/xml/xerces/FreyaFileManager.h"
#include "core/xml/xerces/FreyaMemoryManager.h"
#include "core/xml/xerces/FreyaPanicHandler.h"
#include "core/xml/XMLStringWrap.h"
#include "core/xml/xerces/FreyaDomErrorHandler.h"
#include "core/xml/XMLParserException.h"

#include <iostream>
namespace core
{
namespace xml
{
//============================== Default constructor==============================

XMLParser::XMLParser()
{
	m_MemoryManager = new xerces::FreyaMemoryManager();
	m_PanicHandler = new xerces::FreyaPanicHandler();
	try
	{
		xercesc::XMLPlatformUtils::Initialize(XMLUni::fgXercescDefaultLocale,0,m_PanicHandler,m_MemoryManager);
		XMLPlatformUtils::fgFileMgr = m_FileManager = new xerces::FreyaFileManager();
	}
	catch(const core::xml::XMLParserException& ex)
	{
		throw;
	}
	catch(...)
	{
		throw core::xml::XMLParserException();
	}
	//Create parser now
	static const XMLCh LS[] = { chLatin_L, chLatin_S, chNull };
	m_DomImpl = DOMImplementationRegistry::getDOMImplementation(LS);
	m_DomParser = reinterpret_cast<DOMImplementationLS*>(m_DomImpl)->createLSParser(DOMImplementationLS::MODE_SYNCHRONOUS,0);
	m_DomConfig = m_DomParser->getDomConfig();

	//m_DomConfig->setParameter(XMLUni::fgDOMNamespaces, true);
	//m_DomConfig->setParameter(XMLUni::fgDOMValidateIfSchema, true);

	m_DomErrors = new core::xml::xerces::FreyaDomErrorHandler();
	m_DomConfig->setParameter(XMLUni::fgDOMErrorHandler, m_DomErrors);
	std::cout << "I m here" << std::endl;
	try
	{
		//m_DomConfig->setParameter(XMLUni::fgEncodingString,(XMLCh*)XMLStringWrap("UTF8"));
	}
	catch(const core::xml::XMLParserException& ex)
	{
		throw;
	}
	catch(...)
	{
		throw core::xml::XMLParserException();
	}
}

//==============================~Default constructor==============================

//============================== Derived constructors==============================

//==============================~Derived constructors==============================

//============================== Destructor==============================

XMLParser::~XMLParser()
{
	m_DomParser->release();
	//delete m_DomImpl;
	XMLPlatformUtils::Terminate();
	delete m_PanicHandler;
	delete m_MemoryManager;
}

//==============================~Destructor==============================

//============================== Method: parse==============================

xercesc::DOMDocument*		XMLParser::parse(const EString& path)
{
	xercesc::DOMDocument* doc;
	try
	{
		reinterpret_cast<core::xml::xerces::FreyaDomErrorHandler*>(m_DomErrors)->reset();
		doc = m_DomParser->parseURI(path.c_str());
		if(!reinterpret_cast<core::xml::xerces::FreyaDomErrorHandler*>(m_DomErrors)->isOk())
			throw core::xml::XMLParserException("Errors occurred while parsing");
	}
	catch(const core::xml::XMLParserException& ex)
	{
		throw;
	}
	catch(...)
	{
		throw core::xml::XMLParserException();
	}
	return doc;
}

//==============================~Method: parse==============================

//============================== Method: freeDocument==============================

void		XMLParser::freeDocument(xercesc::DOMDocument* doc)
{
	doc->release();
}

//==============================~Method: freeDocument==============================

} //End of xml namespace
} //End of core namespace


