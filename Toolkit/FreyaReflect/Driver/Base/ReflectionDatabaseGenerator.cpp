/* File         : FreyaReflectBinary: ReflectionDatabaseGenerator.cpp
 * Author       : Dmitry Vedenko
 * E-Mail       : dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifdef _MSC_VER
#	pragma warning(disable : 4005)
#endif

#include <stack>

#include "Base/ReflectionDatabaseGenerator.h"

#include "CppTree/CppNode.h"
#include "CppTree/CppTree.h"
#include "CppTree/CppType.h"

#include "Base/ReflectedScope.h"
#include "Base/ReflectedEnum.h"
#include "Base/ReflectedClass.h"

namespace base
{
	namespace
	{
		class RDG_Visitor : public CppNodeVisitor
		{
		public:
			reflected_scope_ptr					root_scope;
			std::stack<reflected_scope_ptr>		scope_stack;

			RDG_Visitor(CppNode* top)
			{
				top->acceptVisitor(*this);
			}

			virtual void	visit(CppNode* n)
			{
				if(n->getNodeFlag() > CppNode::NODE_FLAG_USED)
					return;

				reflected_element_ptr ptr(new ReflectedElement(n->getNodeName(),n));
				scope_stack.top()->addChild(ptr);
			}

			virtual void	visit(CppNodeScope* n)
			{
				// Nothing to do
			}

			virtual void	visit(CppNodeVariableDecl* n )
			{
				// Just insert the element
				visit(static_cast<CppNode*>(n));
			}

			virtual void	visit(CppNodeNamespace* n)
			{
				if(n->getNodeFlag() > CppNode::NODE_FLAG_USED)
					return;
				// Create a new scope
				reflected_scope_ptr ptr = reflected_scope_ptr(new ReflectedScope(n->getNodeName(),n));

				if(!root_scope)
					root_scope = ptr;
				else
					scope_stack.top()->addChild(ptr);

				scope_stack.push(ptr);

				std::clog << "Adding namespace " << ptr->getScopedName() << std::endl;

				for(CppNodeScope::node_array_iterator_t it = n->begin(), end = n->end(); it != end; ++it)
					(*it)->acceptVisitor(*this);

				scope_stack.pop();
			}

			virtual	void	visit(CppNodeEnum* n)
			{
				if(n->getNodeFlag() > CppNode::NODE_FLAG_USED)
					return;
				reflected_element_ptr ptr(new ReflectedEnum(n));
				scope_stack.top()->addChild(ptr);
			}

			virtual void    visit(CppNodeEnumValue* n)
			{
				//Nothing to do here
			}

			virtual void	visit(CppNodeFunctionProto* n)
			{
				// Just insert the element
				visit(static_cast<CppNode*>(n));
			}

			virtual void	visit(CppNodeFunction* n)
			{
				visit(static_cast<CppNodeFunctionProto*>(n));
			}

			virtual void	visit(CppNodeFunctionTemplateSpecialization* n)
			{
				visit(static_cast<CppNodeFunctionProto*>(n));
			}

			virtual void	visit(CppNodeGlobalVariable* n)
			{
				visit(static_cast<CppNodeVariableDecl*>(n));
			}

			virtual void	visit(CppNodeGlobalConstant* n)
			{
				visit(static_cast<CppNodeVariableDecl*>(n));
			}

			virtual	void	visit(CppNodeTypedef* n)
			{
				// Just insert the element
				visit(static_cast<CppNode*>(n));
			}

			virtual	void	visit(CppNodeClass* n)
			{
				if(n->getNodeFlag() > CppNode::NODE_FLAG_USED)
					return;

				reflected_scope_ptr ptr = reflected_scope_ptr(new ReflectedClass(n));


				scope_stack.top()->addChild(ptr);

				scope_stack.push(ptr);

				for(CppNodeScope::node_array_iterator_t it = n->begin(), end = n->end(); it != end; ++it)
					(*it)->acceptVisitor(*this);

				scope_stack.pop();
			}

			virtual	void	visit(CppNodeClassTemplateSpecialization* n)
			{
				visit(static_cast<CppNodeClass*>(n));
			}

			virtual	void	visit(CppNodeAnonymousStruct* n)
			{
				//visit(static_cast<CppNodeClass*>(n));
			}

			virtual	void	visit(CppNodeAnonymousUnion* n)
			{
				visit(static_cast<CppNodeUnion*>(n));
			}

			virtual	void	visit(CppNodeUnion* n)
			{
				// Just insert the element
				visit(static_cast<CppNode*>(n));
			}

			virtual	void	visit(CppNodeClassMethod* n)
			{
				// Nothing to do
			}

			virtual	void	visit(CppNodeClassConstructor* n)
			{
				// Nothing to do
			}

			virtual	void	visit(CppNodeClassCopyConstructor* n)
			{
				// Nothing to do
			}

			virtual	void	visit(CppNodeClassDestructor* n)
			{
				// Nothing to do
			}

			virtual	void	visit(CppNodeClassOperatorEqual* n)
			{
				// Nothing to do
			}

			virtual	void	visit(CppNodeClassMember* n)
			{
				// Nothing to do
			}

			virtual void	visit(CppNodeConversionOperator* n)
			{
				// Nothing to do
			}

			virtual void	visit(CppNodeClassMemberPointer* n)
			{
				// Nothing to do
			}

			virtual void	visit(CppNodePointer* n)
			{
				// Nothing to do
			}

			virtual void	visit(CppNodeReference* n)
			{
				// Nothing to do
			}

		}; // RDG_Visitor
	} // anon namespace

	ReflectionDatabaseGenerator::ReflectionDatabaseGenerator( CppTree* tree )
	{
		RDG_Visitor visitor(tree->getRootNode());
		m_RootScope = visitor.root_scope;
	} // ReflectionDatabaseGenerator::ReflectionDatabaseGenerator( CppTree* tree )


}// namespace base