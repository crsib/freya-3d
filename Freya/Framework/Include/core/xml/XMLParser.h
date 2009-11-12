#ifndef _XMLPARSER_H_
#define _XMLPARSER_H_

#include "core/EngineSubsystem.h"
#include <xercesc/dom/DOM.hpp>
#include "core/xml/XMLStringWrap.h"

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

static const XMLCh		chLatin_0 = chDigit_0;
static const XMLCh		chLatin_1 = chDigit_1;
static const XMLCh		chLatin_2 = chDigit_2;
static const XMLCh		chLatin_3 = chDigit_3;
static const XMLCh		chLatin_4 = chDigit_4;
static const XMLCh		chLatin_5 = chDigit_5;
static const XMLCh		chLatin_6 = chDigit_6;
static const XMLCh		chLatin_7 = chDigit_7;
static const XMLCh		chLatin_8 = chDigit_8;
static const XMLCh		chLatin_9 = chDigit_9;

class XMLParser : public ::EngineSubsystem
{
	friend class core::EngineCore;
protected:
	XMLParser();
	virtual ~XMLParser();
public:
	xercesc::DOMDocument* parse(const EString& path);

void cleanup();

private:
	xerces::FreyaFileManager*		m_FileManager;
	xerces::FreyaMemoryManager*     m_MemoryManager;
	xerces::FreyaPanicHandler*      m_PanicHandler;

	xercesc::DOMImplementation *				m_DomImpl;
	xercesc::DOMLSParser       *				m_DomParser;
	xercesc::DOMConfiguration  *				m_DomConfig;
	xercesc::DOMErrorHandler   *				m_DomErrors;
}; //End of XMLParser class

} //End of xml namespace
} //End of core namespace
#endif //End of _XMLPARSER_H_
