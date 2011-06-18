/* File         : FreyaReflectBinary: XMLReader.h
 * Author       : Dmitry Vedenko
 * E-Mail       : dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include <libxml/parser.h>

#include <string>
#include <stack>

#include "CppTree/CppTree.h"
#include "CppTree/CppNode.h"

#ifndef XMLReader_h__
#define XMLReader_h__

class XMLReader
{
public:
	XMLReader(const std::string& str, CppTree* tree);

private:
	CppTree*           m_ASTTree;

	typedef std::stack<CppNodeScope*>  scope_stack_t;
	typedef std::stack<bool>           bool_stack_t;

	scope_stack_t      m_ScopeStack;
	bool_stack_t       m_PopStack;
	bool_stack_t       m_NeedsProcessing;

	xmlSAXHandler      m_SaxHandler;

	static void startDocument(void *ctx);
	static void endDocument(void *ctx);

	static void startElement(void *ctx, const xmlChar *fullname, const xmlChar **atts);
	static void endElement(void *ctx, const xmlChar *name);

	static xmlEntityPtr getEntity(void *ctx, const xmlChar *name);

	static void warning(void *user_data, const char *msg, ...);
	static void error(void *user_data, const char *msg, ...);
	static void fatalError(void *user_data, const char *msg, ...);

};

#endif // XMLReader_h__