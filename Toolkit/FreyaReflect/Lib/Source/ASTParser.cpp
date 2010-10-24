#include "FreyaReflect.h"

#include "NamespaceNode.h"
#include "ClassNodes.h"
#include "EnumNodes.h"

#include <exception>
#include <string>

#include <iostream>

#include "cc.ast.gen.h"
#include "srcloc.h"

#include <stack>
#include <hash_set>

class	ASTException : public std::exception
{
public:
	ASTException(const std::string& msg) : m_What(std::string("[ASTParser]: ") + msg) {}
	virtual  ~ASTException(){}
	virtual const char *  what() const
	{
		return m_What.c_str();
	}
private:
	std::string		m_What;
};

#define checkLoc(obj) (parsed_paths.find(std::string(source_loc_man->getFile(obj->getLoc()))) != parsed_paths.end())
#define checkLoc2(obj) (parsed_paths.find(std::string(source_loc_man->getFile(obj->loc))) != parsed_paths.end())

class FASTVisitior : public ASTVisitor
{
public:
	FASTVisitior()
	{
		free_function_count = 0;
		class_count = 0;
		namespace_count = 0;
		enum_count = 0;
	}

	virtual bool visitFunction(Function *obj)
	{
		//std::cout << source_loc_man->getFile(obj->getLoc()) << std::endl;
		if(checkLoc(obj))
		{
			//obj->nameAndParams->
		//	std::cout << obj->nameAndParams->getDeclaratorId()->getName() << "\n";
			//Get the top node 
			CppNode* top = node_stack.top();
			if(top->getNodeType() == CppNode::NODE_TYPE_NAMESPACE)
			{
				if(obj->nameAndParams && (obj->nameAndParams->var->flags & DF_MEMBER) ) //Still a member
					return false;
				std::cout << obj->nameAndParams->getDeclaratorId()->toString() << "\n";

				free_function_count++;
			}// Belongs to namespace - a free function
			else //if(top->getNodeType() != CppNode::NODE_TYPE_NAMESPACE)
			{
				//Is a class member
				//if(obj->dflags & DF_IMPLICIT)
				//	return false;
				//Ok, lets create a member class. We believe, that it was never created
				ClassMethod*	n = new ClassMethod(obj->nameAndParams->getDeclaratorId()->getName(),
					(static_cast<D_func*>(obj->nameAndParams->decl))->cv & CV_CONST, obj->dflags & DF_VIRTUAL, obj->dflags & DF_STATIC,node_stack.top());
				node_stack.top()->addNode(n);
			}//if(top->getNodeType() != CppNode::NODE_TYPE_NAMESPACE)
		}
		return false;
	}

	virtual bool visitDeclaration(Declaration *decl)
	{
		if(!checkLoc2(decl->spec))
			return false;
		switch(decl->spec->kind())
		{
		case TypeSpecifier::TS_CLASSSPEC:
			{
				//We are parsing a class declaration now
				TS_classSpec* class_spec = static_cast<TS_classSpec*>(decl->spec);
				if(class_spec->keyword == TI_CLASS || class_spec->keyword == TI_STRUCT)
				{
					if(class_spec->name == NULL)//It must be an unnamed struct
					{
						class_count++;
						AnonymousStructNode* n = new AnonymousStructNode(node_stack.top());
						node_stack.top()->addNode(n);
						node_stack.push(n);
						//return true;
					}
					if(node_stack.top()->getNodeNamed(class_spec->name->getName()))
						return false;
					else
					{
						class_count++;
						//Create a new class node
						ClassNode* n = new ClassNode(class_spec->name->getName(),node_stack.top());
						node_stack.top()->addNode(n);
						node_stack.push(n);
						//return true; //Recursively pass the class structure down 
					}
					//Load the base classes

					//Ok, parse down the class members
					//0 means private, 1 means protected, 2 means public
					//We do not parse private data
					int access = class_spec->keyword == TI_CLASS ? 0 : 2;
					
					node_stack.pop();
					return false;
				} //Truly a class or a struct if(class_spec->keyword == TI_CLASS || class_spec->keyword == TI_STRUCT)
			}//TS_CLASSSPEC
			break;
		case TypeSpecifier::TS_ENUMSPEC:
			{
				TS_enumSpec* enum_spec = static_cast<TS_enumSpec*>(decl->spec);
				std::string ename = enum_spec->name ? enum_spec->name : "";
				if(node_stack.top()->getNodeNamed(ename))
					return false;
				EnumNode* n = new EnumNode(ename, node_stack.top());
				node_stack.top()->addNode(n);

				FAKELIST_FOREACH(Enumerator,enum_spec->elts,enumerator)
				{
					n->addNode(new EnumValueNode(enumerator->name,enumerator->enumValue,n));
				}

				return false;
			}
		}//switch(decl->spec->kind())
		return true;
	}

	virtual void postvisitDeclaration(Declaration *decl)
	{
		if(checkLoc2(decl->spec))
		{
			switch(decl->spec->kind())
			{
			case TypeSpecifier::TS_CLASSSPEC:
				{
					CppNode* top = node_stack.top();
					if(
						(top->getNodeType() == ClassNode::NODE_TYPE_CLASS) 
						&& 
						static_cast<TS_classSpec*>(decl->spec)->name
						&&
						(top->getShortName() == static_cast<TS_classSpec*>(decl->spec)->name->getName())
						)
						node_stack.pop();//Pop the node out
					else if(
						top->getNodeType() == ClassNode::NODE_TYPE_ANONYMOUS_STRUCT
						)
						node_stack.pop();
				} //TS_CLASSSPEC
				break;
			}//switch
		}
	}

	//======================= Template declaration parsing =================================================
	virtual bool visitTemplateDeclaration(TemplateDeclaration *obj)
	{
		//Ok, the location will be checked using first template parameter
		if(obj->kind() == TemplateDeclaration::TD_DECL)
		{

			return true;
		}
		else if(obj->kind() == TemplateDeclaration::TD_FUNC)
		{

			return true;
		}
		return false;
	}

	virtual void postvisitTemplateDeclaration(TemplateDeclaration *obj)
	{
		if(obj->kind() == TemplateDeclaration::TD_DECL)
		{

		}
	}

	//TopForm is basically anything on the top of namespace
	virtual bool visitTopForm(TopForm *obj)
	{
		if(checkLoc2(obj))
		{
			switch(obj->kind())
			{
			case TopForm::TF_NAMESPACEDEFN:
				{

					TF_namespaceDefn*	defn = static_cast<TF_namespaceDefn*>(obj);
					if(defn->name == std::string("__internal"))
						return false;
					CppNode* nd = node_stack.top();
					CppNode* n = NULL;
					if(n = nd->getNodeNamed(defn->name))
					{
						node_stack.push(n);
					}
					else
					{
						n = new NamespaceNode(defn->name,node_stack.top());
						node_stack.push(n);
						nd->addNode(n);
					}

					return true;
				} //TF_NAMESPACEDEFN
				break;
			case TopForm::TF_DECL:
			case TopForm::TF_EXPLICITINST:
			case TopForm::TF_TEMPLATE:
			case TopForm::TF_ONE_LINKAGE:
				return true;
			}//switch
		} // correct location
		return true;
	}

	virtual void postvisitTopForm(TopForm *obj)
	{
		if(checkLoc2(obj))
		{
			switch(obj->kind())
			{
			case TopForm::TF_NAMESPACEDEFN:
				{

					TF_namespaceDefn*	defn = static_cast<TF_namespaceDefn*>(obj);
					if(defn->name == std::string("__internal"))
						return;
					node_stack.pop();

				} //TF_NAMESPACEDEFN
				break;
			}// switch
		}
	}


public:
	size_t free_function_count;
	size_t namespace_count;
	size_t class_count;
	size_t enum_count;

	std::stack<CppNode*> node_stack;
	std::hash_set<std::string> parsed_paths;
	SourceLocManager*		source_loc_man;
};

void	regenerateAST(CppNode* top, TranslationUnit* tree, const FreyaReflect::IncludePaths& paths,SourceLocManager* mgr)
{
	FASTVisitior visitor;
	visitor.node_stack.push(static_cast<NamespaceNode*>(top));
	for(size_t i = 0; i < paths.size(); i++)
	{
		std::string path = paths[i];
#ifdef _MSC_VER
		//We need to replace \\ to "\"
		size_t pos = path.find("\\") ;
		while(pos != std::string::npos)
		{
			path.replace(pos,1, "\\\\");
			pos = path.find("\\",pos+3);		
		}
		//std::cout << path << std::endl;
#endif
		visitor.parsed_paths.insert(path);
	}
	visitor.source_loc_man = mgr;
	tree->traverse(visitor);

	std::clog << "Found functions: " << visitor.free_function_count << std::endl;
}