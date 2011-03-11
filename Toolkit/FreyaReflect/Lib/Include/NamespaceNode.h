#ifndef _NAMESPACE_NODE_H_
#define _NAMESPACE_NODE_H_

#include "CppNode.h"

class EXPORT NamespaceNode : public CppNode
{
public:
	NamespaceNode(const std::string& namespace_name, CppNode* parent) : CppNode(NODE_TYPE_NAMESPACE,parent,namespace_name){ }
	virtual ~NamespaceNode(){}

private:

};

#endif