#include "FreyaReflect.h"
#include <exception>
#include <string>

#include <iostream>

#include "translation_unit_parser.h"

template<class T>
lexed_token_type::string_type get_value_of_it(const T& it)
{
	if(it->value.begin() != it->value.end())
		return it->value.begin()->get_value();
	return "";
}


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

void	eval_expression(CppNode* __default_namespace, ast_const_tree_iterator const& it,  translation_unit_grammar::rule_map_type& rule_map, int depth);

void	parse_ast(NamespaceNode* __default_namespace, const ast_result_type& __ast, translation_unit_grammar::rule_map_type& rule_map)
{
	ast_const_tree_iterator  it  = __ast.trees.begin();
	ast_const_tree_iterator  end = __ast.trees.end();
	for(;it != end; ++it)
		eval_expression(__default_namespace,it,rule_map,0);
}

void	eval_expression(CppNode* node, ast_const_tree_iterator const& it, translation_unit_grammar::rule_map_type& rule_map, int depth)
{
	using namespace std;
	//for(int i = 0; i < depth; ++i) cout << "\t";
	//cout << "In eval_expression. values = "; 
	//for(auto mit = it->value.begin(); mit != it->value.end(); ++mit)
	//	cout	<<	mit->get_value() << ", ";
	//cout << " i->children.size() = " << it->children.size() << " id " << rule_map[it->value.id()] << endl;
	ast_const_tree_iterator  child_it  = it->children.begin();
	ast_const_tree_iterator  end = it->children.end();

	//Ok, cache up some values
	boost::spirit::classic::parser_id	node_id = it->value.id();
	//ast_tree_match::parse_node_t::const_iterator_t node_val_it_begin = it->value.begin(), node_val_it_end = it->value.end(), node_val_it = node_val_it_begin;
	//size_t	values_count = std::distance(node_val_it_begin,node_val_it_end);

	//Now, parse fuck out the type of current node
	std::string id_name = rule_map[node_id];
	CppNode*		new_node = node;
	if(id_name == "original_namespace_definition")
	{
		std::cout << "Current node is namespace node: ";
		//Check the root node to be namespace
		if(node->getNodeType() != CppNode::NODE_TYPE_NAMESPACE)
			throw ASTException("Incorrect parent node for \"namespace\"");
		//Ok, lets check, that namespace does not exists
		//First child must be "namespace"
		if(get_value_of_it(child_it) != "namespace")
			throw ASTException("Parse node \"original_namespace_definition\": incorrect first child");
		//Second child is namespace name
		lexed_token_type::string_type namespace_name = get_value_of_it(++child_it);
		std::cout << namespace_name << std::endl;
		//Get the namespace
		if(NULL == (new_node = node->getNodeNamed(namespace_name.c_str())))
		{
			new_node = new NamespaceNode(namespace_name.c_str(),node);
			node->addNode(new_node);
			cout << "Added namespace " << new_node->getQualifiedName() << endl;
		}
		//Third child must be "{". Otherwise, treat this as forward declaration
		if(get_value_of_it(++child_it) != "{")
			return; //boil out
		//Now, the fourth child must be either simple declaration, either compound declaration. But we will check only that the next node is not }
		if(get_value_of_it(++child_it) != "}")
		{
			//for(ast_const_tree_iterator c_it = child_it->children.begin(); c_it != child_it->children.end(); ++c_it)
				eval_expression(new_node,child_it,rule_map,depth + 1);
		}

	} // original_namespace_definition
	else if(id_name == "declaration_seq")
	{
		for(ast_const_tree_iterator c_it = child_it; c_it != end; ++c_it)
			eval_expression(node,c_it,rule_map,depth + 1);
	} // declaration_seq
	else if(id_name == "simple_declaration")
	{
		if(child_it != end)
			eval_expression(node,child_it,rule_map,depth + 1);
	}// simple_declaration
}