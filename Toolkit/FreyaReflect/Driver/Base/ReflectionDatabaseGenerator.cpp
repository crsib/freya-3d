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
				// Never to be called
			}

			virtual void	visit(CppNodeScope* n)
			{

			}

			virtual void	visit(CppNodeVariableDecl* n )
			{

			}

			virtual void	visit(CppNodeNamespace* n)
			{
				if(n->getNodeFlag() > CppNode::NODE_FLAG_USED)
					return;
				// Create a new scope
				reflected_scope_ptr ptr = reflected_scope_ptr(new ReflectedScope(n->getNodeName()));

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

			}

			virtual void    visit(CppNodeEnumValue* n)
			{

			}

			virtual void	visit(CppNodeFunctionProto* n)
			{

			}

			virtual void	visit(CppNodeFunction* n)
			{

			}

			virtual void	visit(CppNodeFunctionTemplateSpecialization* n)
			{

			}

			virtual void	visit(CppNodeGlobalVariable* n)
			{

			}

			virtual void	visit(CppNodeGlobalConstant* n)
			{

			}

			virtual	void	visit(CppNodeTypedef* n)
			{

			}

			virtual	void	visit(CppNodeClass* n)
			{

			}

			virtual	void	visit(CppNodeClassTemplateSpecialization* n)
			{

			}

			virtual	void	visit(CppNodeAnonymousStruct* n)
			{

			}

			virtual	void	visit(CppNodeAnonymousUnion* n)
			{

			}

			virtual	void	visit(CppNodeUnion* n)
			{

			}

			virtual	void	visit(CppNodeClassMethod* n)
			{

			}

			virtual	void	visit(CppNodeClassConstructor* n)
			{

			}

			virtual	void	visit(CppNodeClassCopyConstructor* n)
			{

			}

			virtual	void	visit(CppNodeClassDestructor* n)
			{

			}

			virtual	void	visit(CppNodeClassOperatorEqual* n)
			{

			}

			virtual	void	visit(CppNodeClassMember* n)
			{

			}

			virtual void	visit(CppNodeConversionOperator* n)
			{

			}

			virtual void	visit(CppNodeClassMemberPointer* n)
			{

			}

			virtual void	visit(CppNodePointer* n)
			{

			}

			virtual void	visit(CppNodeReference* n)
			{

			}

		}; // RDG_Visitor
	} // anon namespace

	ReflectionDatabaseGenerator::ReflectionDatabaseGenerator( CppTree* tree )
	{
		RDG_Visitor visitor(tree->getRootNode());
		m_RootScope = visitor.root_scope;
	} // ReflectionDatabaseGenerator::ReflectionDatabaseGenerator( CppTree* tree )


}// namespace base