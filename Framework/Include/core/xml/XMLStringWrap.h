/*
 * XMLString.h
 *
 *  Created on: 06.02.2009
 *      Author: vedenko
 */

#ifndef XMLSTRINGWRAP_H_
#define XMLSTRINGWRAP_H_

/*
 *
 */
#include "core/EngineSubsystem.h"
#include <xercesc/util/XMLString.hpp>
#include "core/EString.h"
#include <iostream>

#define XML(str) core::xml::XMLStringWrap( str )

namespace core
{

namespace xml
{

class XMLStringWrap: public EngineSubsystem
{
public:
	XMLStringWrap()
	{
		m_XMLStr = NULL;
	}
	virtual ~XMLStringWrap()
	{
		if(m_XMLStr)
			xercesc::XMLString::release(&m_XMLStr);
	}

	explicit XMLStringWrap(const char* const ascii )
	{
		m_XMLStr = xercesc::XMLString::transcode(ascii);
	}

	explicit XMLStringWrap(const EString& str)
	{
		m_XMLStr = xercesc::XMLString::transcode(str.c_str());
	}

	explicit XMLStringWrap(const XMLCh* const utf16)
	{
		m_XMLStr = xercesc::XMLString::replicate(utf16);
	}

	XMLStringWrap(const XMLStringWrap& other)
	{
		m_XMLStr = xercesc::XMLString::replicate(other.m_XMLStr);
	}

	XMLStringWrap& operator =(const XMLStringWrap& other)
	{
		if(m_XMLStr)
			xercesc::XMLString::release(&m_XMLStr);
		m_XMLStr = xercesc::XMLString::replicate(other.m_XMLStr);
		return *this;
	}

	XMLStringWrap& operator =(const EString& other)
	{
		if(m_XMLStr)
			xercesc::XMLString::release(&m_XMLStr);
		m_XMLStr = xercesc::XMLString::transcode(other.c_str());
		return *this;
	}

	XMLStringWrap& operator =(const char* const other)
	{
		if(m_XMLStr)
			xercesc::XMLString::release(&m_XMLStr);
		m_XMLStr = xercesc::XMLString::transcode(other);
		return *this;
	}

	XMLStringWrap& operator =(const XMLCh* const other)
	{
		if(m_XMLStr)
			xercesc::XMLString::release(&m_XMLStr);
		m_XMLStr = xercesc::XMLString::replicate(other);
		return *this;
	}

	operator EString()
	{
		char* ch = xercesc::XMLString::transcode(m_XMLStr);
		EString str(ch);
		xercesc::XMLString::release(&ch);
		return str;
	}

	operator char*()
	{
		return xercesc::XMLString::transcode(m_XMLStr);
	}

	operator XMLCh* ()
	{
		return m_XMLStr;
	}

	operator EString() const
	{
		char* ch = xercesc::XMLString::transcode(m_XMLStr);
		EString str(ch);
		xercesc::XMLString::release(&ch);
		return str;
	}

	operator char*() const
	{
		return xercesc::XMLString::transcode(m_XMLStr);
	}

	operator XMLCh* () const
	{
		return m_XMLStr;
	}

	operator const char*() const
	{
		return xercesc::XMLString::transcode(m_XMLStr);
	}
private:
	XMLCh* m_XMLStr;
};

}

}

inline std::ostream& operator<<(std::ostream& target, const core::xml::XMLStringWrap& toDump)
{
    target << (const char *)toDump;
    return target;
}

#endif /* XMLSTRING_H_ */
