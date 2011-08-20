/* File         : FreyaReflectBinary: XMLReader.cpp
 * Author       : Dmitry Vedenko
 * E-Mail       : dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include "Input/XMLReader.h"

#include <cstdlib>
#include <cstdarg>
#include <cstdio>

#include <llvm/Support/CommandLine.h>
#include <iostream>

#include <boost/algorithm/string.hpp>

extern llvm::cl::opt<bool>			BeVerbose;

XMLReader::XMLReader( const std::string& str, CppTree* tree ) : m_ASTTree(tree)
{
	// Initialize all the handlers to the NULL
	memset(&m_SaxHandler,0,sizeof(xmlSAXHandler));

	m_SaxHandler.startDocument = startDocument;
	m_SaxHandler.endDocument   = endDocument;
	
	m_SaxHandler.startElement  = startElement;
	m_SaxHandler.endElement    = endElement;

	m_SaxHandler.getEntity     = getEntity;

	m_SaxHandler.warning       = warning;
	m_SaxHandler.error         = error;
	m_SaxHandler.fatalError    = fatalError;

	if(BeVerbose.getValue())
		std::clog << "Parsing " << str << std::endl;

	xmlSAXUserParseFile(&m_SaxHandler, this, str.c_str());
}

xmlEntityPtr XMLReader::getEntity( void *ctx, const xmlChar *name )
{
	return xmlGetPredefinedEntity(name);
}

void XMLReader::warning( void *user_data, const char *msg, ... )
{
	va_list list;

	va_start(list,msg);
	static char _buf[512];
	vsnprintf(_buf,sizeof(_buf),msg,list);
	va_end(list);

	printf("Warning: %i", _buf);
}

void XMLReader::error( void *user_data, const char *msg, ... )
{
	va_list list;

	va_start(list,msg);
	static char _buf[512];
	vsnprintf(_buf,sizeof(_buf),msg,list);
	va_end(list);

	printf("Error: %i", _buf);
}

void XMLReader::fatalError( void *user_data, const char *msg, ... )
{
	va_list list;

	va_start(list,msg);
	static char _buf[512];
	vsnprintf(_buf,sizeof(_buf),msg,list);
	va_end(list);

	printf("Fatal Error: %i", _buf);
}

void XMLReader::startDocument( void *ctx )
{

}

void XMLReader::endDocument( void *ctx )
{

}

void markElementDeserialized(CppNode* node)
{
	node->markDeserialized();

	if(node->getNodeType() & CppNode::NODE_TYPE_SCOPE)
	{
		CppNodeScope* scope = static_cast<CppNodeScope*>(node);
		for(CppNodeScope::node_array_iterator_t it = scope->begin(), end = scope->end(); it != end; ++it)
			markElementDeserialized(it->get());
	}
}

void XMLReader::startElement( void *ctx, const xmlChar *fullname, const xmlChar **atts )
{
	XMLReader* reader = reinterpret_cast<XMLReader*>(ctx);

	if(!strcmp((char*)fullname,"cpptree"))
	{
		reader->m_PopStack.push(false);
		reader->m_NeedsProcessing.push(true);
		return;
	}

	if(!reader->m_NeedsProcessing.top())
	{
		reader->m_PopStack.push(false);
		reader->m_NeedsProcessing.push(false);
		return;
	}

	if(!strcmp((char*)fullname,"astnodes"))
	{
		reader->m_PopStack.push(false);
		reader->m_NeedsProcessing.push(true);
		return;
	}

	if(!strcmp((char*)fullname, "namespace"))
	{
		if(reader->m_ScopeStack.empty())
		{
			reader->m_ScopeStack.push(static_cast<CppNodeScope*>(reader->m_ASTTree->getRootNode()));
			reader->m_NeedsProcessing.push(true);
			reader->m_PopStack.push(true);
			return;
		}
		else
		{
			char* name = NULL;
			while(*atts && strcmp((char*)*atts,"name"))
				atts += 2;
			
			if(atts)
				name = (char*)*(atts + 1);

			if(!name || name[0] == '0')
			{
				reader->m_PopStack.push(false);
				reader->m_NeedsProcessing.push(false);
				return;
			}

			// Try to get node
			CppNode* _node = reader->m_ScopeStack.top()->getChildByName(name).get();
			CppNodeScope* node = NULL;

			if(_node->getNodeType() & CppNode::NODE_TYPE_SCOPE)
				node = static_cast<CppNodeScope*>(_node);

			if(node)
			{
				reader->m_NeedsProcessing.push(true);
				reader->m_PopStack.push(true);
				reader->m_ScopeStack.push(node);
			}
			else
			{
				reader->m_PopStack.push(false);
				reader->m_NeedsProcessing.push(false);
			}
			return;
		} // Stack is not empty
	} // namespace node

	//Classes, enums, functions, typedefs and unions
	if(
		!strcmp((char*)fullname, "class") ||
		!strcmp((char*)fullname, "enum") ||
		!strcmp((char*)fullname, "function") ||
		!strcmp((char*)fullname, "typedef") ||
		!strcmp((char*)fullname, "global_variable") ||
		!strcmp((char*)fullname, "global_constant") ||
		!strcmp((char*)fullname, "union")
		)
	{
		// Extract name
		char* name = NULL;
		while(*atts && strcmp((char*)*atts,"name"))
			atts += 2;

		if(atts)
			name = (char*)*(atts + 1);

		if(!name || name[0] == '0')
		{
			reader->m_PopStack.push(false);
			reader->m_NeedsProcessing.push(false);
			return;
		}
		std::string _name(name);
		boost::replace_all(_name," < ","<");
		boost::replace_all(_name," > ",">");
		boost::replace_all(_name," & ","&");

		// Fine, name is extracted, retrieve the node
		CppNode* node = reader->m_ScopeStack.top()->getChildByName(_name).get();

		if(node)
			markElementDeserialized(node);
	}

	reader->m_PopStack.push(false);
	reader->m_NeedsProcessing.push(false);
}

void XMLReader::endElement( void *ctx, const xmlChar *name )
{
	XMLReader* reader = reinterpret_cast<XMLReader*>(ctx);

	if(reader->m_PopStack.top())
		reader->m_ScopeStack.pop();
	reader->m_PopStack.pop();
	reader->m_NeedsProcessing.pop();
}
