#ifndef ClassNodes_h__
#define ClassNodes_h__

#include "CppNode.h"

//Class node itself
class EXPORT ClassNode : public CppNode
{
public:
	ClassNode(const std::string& class_name, CppNode* parent) : CppNode(NODE_TYPE_CLASS,parent,class_name)
	{}
	virtual ~ClassNode(){}


};

class EXPORT AnonymousStructNode : public CppNode
{
public:
	AnonymousStructNode(CppNode* parent) : CppNode(NODE_TYPE_ANONYMOUS_STRUCT,parent,"")
	{}
	virtual ~AnonymousStructNode(){}


};

#endif // ClassNodes_h__