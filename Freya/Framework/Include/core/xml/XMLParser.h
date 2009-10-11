#ifndef _XMLPARSER_H_
#define _XMLPARSER_H_

#include "core/EngineSubsystem.h"
#include <xercesc/dom/DOM.hpp>
#include <core/xml/XMLStringWrap.h>

namespace core
{
class EngineCore;
namespace xml
{

namespace xerces
{
class FreyaFile;
class FreyaFileManager;
class FreyaMemoryManager;
class FreyaPanicHandler;
}

using namespace xercesc;

class XMLParser : public ::EngineSubsystem
{
	friend class core::EngineCore;
protected:
	XMLParser();
	virtual ~XMLParser();
public:
DOMDocument* parse(const EString& path);

void freeDocument(DOMDocument* doc);

private:
	xerces::FreyaFileManager*		m_FileManager;
	xerces::FreyaMemoryManager*     m_MemoryManager;
	xerces::FreyaPanicHandler*      m_PanicHandler;

	DOMImplementation *				m_DomImpl;
	DOMLSParser       *				m_DomParser;
	DOMConfiguration  *				m_DomConfig;
	DOMErrorHandler   *				m_DomErrors;
}; //End of XMLParser class

} //End of xml namespace
} //End of core namespace
#endif //End of _XMLPARSER_H_
