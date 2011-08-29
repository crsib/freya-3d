/* File         : FreyaReflectBinary: TreeMarker.cpp
 * Author       : Dmitry Vedenko
 * E-Mail       : dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include "CppTree/TreeMarker.h"
#include "CppTree/CppType.h"

#include <iostream>

namespace
{
	void mark_down( CppNode* node, int& used_counter )
	{
		if(node && node->getParent() && node->getParent()->getNodeFlag() > CppNode::NODE_FLAG_USED)
		{
			used_counter++;
			node->getParent()->setNodeFlag(CppNode::NODE_FLAG_USED);
			mark_down(node->getParent(),used_counter);
		}
	}

	void  mark_type( const CppTypePtr& type, TreeMarker& this_marker )
	{
		if(type && type->getUserType() && type->getUserType()->getNodeFlag() > CppNode::NODE_FLAG_USED)
			type->getUserType()->acceptVisitor(this_marker);
	}
}

void TreeMarker::visit( CppNodeNamespace* n )
{
	for(CppNodeScope::node_array_iterator_t it = n->begin(), end = n->end(); it != end; ++it )
	{
		CppNodePtr node = *it;
		if( node->getNodeFlag() == CppNode::NODE_FLAG_USER_SUPPLIED )
		{
			//UserSuppliedNodes++;
			node->acceptVisitor(*this);
		}
	}
}

void TreeMarker::visit( CppNodeFunctionProto* n )
{
	markNode(n);

	mark_type(n->getReturnValue(),*this);

	for( CppNodeFunctionProto::argument_list_iterator_t it = n->args_begin(), end = n->args_end(); it != end; ++it )
		mark_type(it->get()->Type,*this);
}

void TreeMarker::visit( CppNodeVariableDecl* n )
{
	markNode(n);
	mark_type(n->getCppType(),*this);
}

void TreeMarker::visit( CppNodeTypedef* n )
{
	markNode(n);
	mark_type(n->getAliasType(),*this);
}

void TreeMarker::visit( CppNodeClass* n )
{
	if(!n->isClassWasDefined())
	{
		n->setNodeFlag(CppNode::NODE_FLAG_EXTERNAL);
		return;
	}
	
	markNode(n);

	//Mark bases
	for(CppNodeClass::base_type_list_iterator_t it = n->bases_begin(), end = n->bases_end(); it != end; ++it)
	{
		CppNodeClass::base_type_t& base = *it;
		if( base.second != CppNode::ACCESS_TYPE_PRIVATE )
			mark_type(base.first,*this);
	}

	//Mark methods
	for( CppNodeClass::member_list_iterator_t it = n->members_begin(), end = n->members_end(); it != end; ++it )
		if((*it)->getAccessType() != CppNode::ACCESS_TYPE_PRIVATE)
			(*it)->acceptVisitor(*this);

	for( CppNodeClass::method_list_iterator_t it = n->methods_begin(), end = n->methods_end(); it != end; ++it )
		if((*it)->getAccessType() != CppNode::ACCESS_TYPE_PRIVATE)
			(*it)->acceptVisitor(*this);

	for(CppNodeScope::node_array_iterator_t it = n->begin(), end = n->end(); it != end; ++it )
		if((*it)->getAccessType() != CppNode::ACCESS_TYPE_PRIVATE)
			(*it)->acceptVisitor(*this);
}

void TreeMarker::visit( CppNodeUnion* n )
{
	markNode(n);
	for(CppNodeScope::node_array_iterator_t it = n->begin(), end = n->end(); it != end; ++it )
		(*it)->acceptVisitor(*this);
}

void TreeMarker::visit( CppNodeConversionOperator* n )
{
	markNode(n);
	mark_type(n->getConversionResultType(),*this);
}

void TreeMarker::visit( CppNodeClassMemberPointer* n )
{
	markNode(n);
	mark_type(n->getPointeeType(),*this);
	if(n->getClass() && n->getClass()->getNodeFlag() > CppNode::NODE_FLAG_USED)
		n->getClass()->acceptVisitor(*this);
}

void TreeMarker::visit( CppNodePointer* n )
{
	markNode(n);
	mark_type(n->getPointeeType(),*this);
}

void TreeMarker::visit( CppNodeReference* n )
{
	markNode(n);
	mark_type(n->getReferencedType(),*this);
}

void TreeMarker::visit( CppNodeClassTemplateSpecialization* n )
{
	for(CppNodeClassTemplateSpecialization::template_argument_list_iterator_t it = n->targs_begin(), end = n->targs_end(); it != end; ++it)
	{
		if((*it)->getType() == CppNodeClassTemplateSpecialization::TemplateArgument::CPP_TYPE)
			mark_type((*it)->getCppNode(), *this);
	}

	visit(static_cast<CppNodeClass*>(n));
}


void TreeMarker::markNode( CppNode* n )
{
	if(n->getNodeFlag() == CppNode::NODE_FLAG_USER_SUPPLIED)
		UserSuppliedNodes++;
	if( n->getNodeFlag() > CppNode::NODE_FLAG_USED )
	{
		UsedNodes++;
		n->setNodeFlag(CppNode::NODE_FLAG_USED);
		mark_down(n, UsedNodes);
	}
}
