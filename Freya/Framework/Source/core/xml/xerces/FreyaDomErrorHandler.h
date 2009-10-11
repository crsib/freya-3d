/*
 * FreyaDomErrorHandler.h
 *
 *  Created on: 11.02.2009
 *      Author: vedenko
 */

#ifndef FREYADOMERRORHANDLER_H_
#define FREYADOMERRORHANDLER_H_

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMError.hpp>
/*
 *
 */
namespace core
{

namespace xml
{
class XMLParser;

namespace xerces
{

class FreyaDomErrorHandler: public xercesc::DOMErrorHandler
{
	friend class core::xml::XMLParser;
protected:
	FreyaDomErrorHandler();
public:
	virtual ~FreyaDomErrorHandler();

	virtual bool handleError  	(const xercesc::DOMError & domError);
    void reset()
    {
    	m_ParseOK = true;
    }

    bool isOk()
    {
    	return m_ParseOK;
    }
private:
	bool	m_ParseOK;
};

}

}

}

#endif /* FREYADOMERRORHANDLER_H_ */
