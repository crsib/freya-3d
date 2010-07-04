#ifndef ClassNodes_h__
#define ClassNodes_h__

#include "CppNode.h"

//Class node itself
class EXPORT ClassNode : public CppNode
{
public:
	ClassNode(const std::string& namespace_name, CppNode* parent) : CppNode(NODE_TYPE_CLASS,parent,namespace_name)
	{}
	virtual ~ClassNode(){}


};

#endif // ClassNodes_h__