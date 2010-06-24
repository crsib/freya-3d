#include "FreyaReflect.h"
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

#define checkLoc(obj) parsed_paths.find(std::string(source_loc_man->getFile(obj->getLoc()))) != parsed_paths.end()
#define checkLoc2(obj) parsed_paths.find(std::string(source_loc_man->getFile(obj->loc))) != parsed_paths.end()

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
			//std::cout << obj->nameAndParams->getDeclaratorId()->getName() << "\n";
			free_function_count++;
		}
		return false;
	}

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
				}
				break;
			}
		}
		return false;
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

				}
				break;
			}
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
		std::cout << path << std::endl;
#endif
		visitor.parsed_paths.insert(path);
	}
	visitor.source_loc_man = mgr;
	tree->traverse(visitor);

	std::clog << "Found functions: " << visitor.free_function_count << std::endl;
}