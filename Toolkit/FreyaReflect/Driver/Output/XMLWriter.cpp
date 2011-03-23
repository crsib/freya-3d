#include "Output/XMLWriter.h"
#include "CppTree/CppTree.h"
#include "CppTree/CppType.h"

#include <boost/algorithm/string.hpp>

namespace
{

	std::string		makeValidXML(const std::string& input)
	{
		std::string output(input);
	
		boost::replace_all(output, "&", " &amp; ");
		boost::replace_all(output,"<"," &lt; ");
		boost::replace_all(output,">"," &gt; ");
	
		return output;
	}

	static const char* _access_str[] = {
		"public",
		"protected",
		"private"
	};
}
void XMLWriter::visit( CppNode* n )
{
	//This method will be never called
}

void XMLWriter::visit( CppNodeScope* n )
{
	//This method will be never called
}

void XMLWriter::visit( CppNodeVariableDecl* n )
{
	if( n->getCppType() )
	{
		m_OutputStream << insertTabs() << "<variable type=\"" << makeValidXML(n->getCppType()->getQualifiedName()) << "\" name=\"" << makeValidXML(n->getNodeName()) 
			<< "\" has_value=\"" << static_cast<int>(n->hasValue()) << "\" />\n";
		m_TypesCache.insert(n->getCppType().get());
	}
}

void XMLWriter::visit( CppNodeNamespace* n )
{
	if(n->begin() == n->end())
		return;

	m_OutputStream << insertTabs() << "<namespace name=\"" << n->getNodeName() << "\">\n";

	m_CurrentDepth++;

	for(CppNodeScope::node_array_iterator_t it = n->begin(), end = n->end(); it != end; ++it)
		if( ((*it)->getNodeFlag() <= CppNode::NODE_FLAG_USED) )
			(*it)->acceptVisitor(*this);

	m_CurrentDepth--;

	m_OutputStream << insertTabs() << "</namespace>\n";
}

void XMLWriter::visit( CppNodeEnum* n )
{
	m_OutputStream << insertTabs() << "<enum name=\"" << n->getNodeName() << "\">\n";
	
	m_CurrentDepth++;
	for(CppNodeScope::node_array_iterator_t it = n->begin(), end = n->end(); it != end; ++ it)
		(*it)->acceptVisitor(*this);
	m_CurrentDepth--;

	m_OutputStream << insertTabs() << "</enum>\n";
}

void XMLWriter::visit( CppNodeEnumValue* n )
{
	m_OutputStream << insertTabs() << "<enum_value name=\"" << n->getNodeName() << "\" value=\"" <<
		n->getValue() << "\" />\n";
}

void XMLWriter::visit( CppNodeFunctionProto* n )
{
	m_OutputStream << insertTabs() << "<function_prototype op_type=\"" << n->getOverloadedOperatorKind() << "\" overloaded_operator=\"" << static_cast<int>(n->isOverloadedOperator()) << "\" >\n";
	m_CurrentDepth++;
	//Write return value
	if( n->getReturnValue() )
	{
		m_OutputStream << insertTabs() << "<return_type type=\"" << makeValidXML(n->getReturnValue()->getQualifiedName()) << "\" />\n";
		m_TypesCache.insert(n->getReturnValue().get());
	}
	else
		m_OutputStream << insertTabs() << "<return_type type=\"void\" />\n";

	if( n->argumentsCount() )
	{
		m_OutputStream << insertTabs() << "<arguments>\n";
		m_CurrentDepth++;
		int arg_c = 0;
		for(CppNodeFunctionProto::argument_list_iterator_t it = n->args_begin(), end = n->args_end(); it != end; ++it)
		{
			CppNodeFunctionProto::argument_ptr_t arg = *it;
			m_OutputStream << insertTabs() << "<argument type=\"" << makeValidXML(arg->Type->getQualifiedName()) << "\" has_default_value=\"" << static_cast<int>(arg->HasDefaultVal) <<
				"\" idx=\"" << arg_c++ << "\" />\n";
			m_TypesCache.insert(arg->Type.get());
		}
		m_CurrentDepth--;
		m_OutputStream << insertTabs() << "</arguments>\n";
	}

	m_CurrentDepth--;
	m_OutputStream << insertTabs() << "</function_prototype>\n";
}

void XMLWriter::visit( CppNodeFunction* n )
{
	m_OutputStream << insertTabs() << "<function name=\"" << makeValidXML(n->getFunctionName()) << "\" >\n";
	m_CurrentDepth++;
	visit(static_cast<CppNodeFunctionProto*>(n));
	m_CurrentDepth--;
	m_OutputStream << insertTabs() << "</function>\n";

}

void XMLWriter::visit( CppNodeFunctionTemplateSpecialization* n )
{
	//Currently incorrect, just pass down to the function handler
	visit(static_cast<CppNodeFunction*>(n));
}

void XMLWriter::visit( CppNodeGlobalVariable* n )
{
	if( n->getCppType() )
	{
		m_OutputStream << insertTabs() << "<global_variable type=\"" << makeValidXML(n->getCppType()->getQualifiedName()) << "\" name=\"" << makeValidXML(n->getNodeName()) 
			<< "\" has_value=\"" << static_cast<int>(n->hasValue()) << "\" />\n";
		m_TypesCache.insert(n->getCppType().get());
	}
}

void XMLWriter::visit( CppNodeGlobalConstant* n )
{
	if( n->getCppType() )
	{
		m_OutputStream << insertTabs() << "<global_constant type=\"" << makeValidXML(n->getCppType()->getQualifiedName()) << "\" name=\"" << makeValidXML(n->getNodeName()) 
			<< "\" has_value=\"" << static_cast<int>(n->hasValue()) << "\" />\n";
		m_TypesCache.insert(n->getCppType().get());
	}
}

void XMLWriter::visit( CppNodeTypedef* n )
{
	if(n->getAliasType())
	{
		m_OutputStream << insertTabs() << "<typedef name=\"" << n->getNodeName() << "\" type=\"" << makeValidXML(n->getAliasType()->getQualifiedName()) << "\" />\n";
		m_TypesCache.insert(n->getAliasType().get());
	}
}

void XMLWriter::visit( CppNodeClass* n )
{
	m_OutputStream << insertTabs() << "<class name=\"" << makeValidXML(n->getNodeName()) << "\">\n";

	m_CurrentDepth++;

	//Write down template parameters, if we have to
	if( n->getNodeType() & CppNode::NODE_TYPE_CLASS_TEMPLATE_SPECIALIZATION )
	{
		CppNodeClassTemplateSpecialization* spec = static_cast<CppNodeClassTemplateSpecialization*>(n);
		if(spec->targs_begin() != spec->targs_end())
		{
			m_OutputStream << insertTabs() << "<template_args>\n";
			m_CurrentDepth++;
			for(CppNodeClassTemplateSpecialization::template_argument_list_iterator_t it = spec->targs_begin(), end = spec->targs_end();
				it != end; ++it)
			{
				CppNodeClassTemplateSpecialization::TemplateArgumentPtr arg = *it;
				m_OutputStream << insertTabs() << "<arg type=\"" << static_cast<int>(arg->getType()) << "\" ";

				switch (arg->getType())
				{
				case CppNodeClassTemplateSpecialization::TemplateArgument::CPP_TYPE:
					m_OutputStream << "cpp_type=\"" << makeValidXML(arg->getCppNode()->getQualifiedName()) << "\" />\n";
					m_TypesCache.insert(arg->getCppNode().get());
					break;
				case CppNodeClassTemplateSpecialization::TemplateArgument::INTEGER:
					m_OutputStream << "integer_value=\"" << arg->getIntValue() << "\" />\n";
					break;
				case CppNodeClassTemplateSpecialization::TemplateArgument::TEMPLATE:
					m_OutputStream << "template=\"" << makeValidXML(arg->getTemplateName()) << "\" />\n";
					break;
				}

			}
			m_CurrentDepth--;
			m_OutputStream << insertTabs() << "</template_args>\n";
		}
	}

	//Write down bases
	if(n->baseClassCount())
	{
		m_OutputStream << insertTabs() << "<bases>\n";
		m_CurrentDepth++;
		//Read bases
		for(CppNodeClass::base_type_list_iterator_t it = n->bases_begin(), end = n->bases_end(); it != end; ++it)
		{
			CppNodeClass::base_type_t& base = *it;
			
			if(base.second == CppNodeClass::ACCESS_TYPE_PRIVATE)
				continue;

			m_TypesCache.insert(base.first.get());
			m_OutputStream << insertTabs() << "<base access=\"" << _access_str[base.second] << "\" type=\"" << makeValidXML(base.first->getQualifiedName()) << "\" />\n";
		}
		m_CurrentDepth--;
		m_OutputStream << insertTabs() << "</bases>\n";
	}
	//Read ast nodes, scoped within class
	if( n->begin() != n->end() )
	{
		m_OutputStream << insertTabs() << "<astnodes>\n";
		m_CurrentDepth++;
		for(CppNodeScope::node_array_iterator_t it = n->begin(), end = n->end(); it != end; ++ it)
			if( (*it)->getAccessType() != CppNode::ACCESS_TYPE_PRIVATE ) 
				(*it)->acceptVisitor(*this);
		m_CurrentDepth--;
		m_OutputStream << insertTabs() << "</astnodes>\n";
	}
	//Read class methods
	if( n->methods_begin() != n->methods_end() )
	{
		m_OutputStream << insertTabs() << "<methods>\n";
		m_CurrentDepth++;
		for( CppNodeClass::method_list_iterator_t it = n->methods_begin(), end = n->methods_end(); it != end; ++it )
			if((*it)->getAccessType() != CppNode::ACCESS_TYPE_PRIVATE)
				(*it)->acceptVisitor(*this);
		m_CurrentDepth--;
		m_OutputStream << insertTabs() << "</methods>";
	}
	//Read class members
	if( n->members_begin() != n->members_end() )
	{
		m_OutputStream << insertTabs() << "<members>\n";
		m_CurrentDepth++;
		for( CppNodeClass::member_list_iterator_t it = n->members_begin(), end = n->members_end(); it != end; ++it )
			if((*it)->getAccessType() != CppNode::ACCESS_TYPE_PRIVATE)
				(*it)->acceptVisitor(*this);
		m_CurrentDepth--;
		m_OutputStream << insertTabs() << "</members>";
	}

	m_CurrentDepth--;

	m_OutputStream << insertTabs() << "</class>\n";
}

void XMLWriter::visit( CppNodeClassTemplateSpecialization* n )
{
	visit( static_cast<CppNodeClass*>( n ) );
}

void XMLWriter::visit( CppNodeAnonymousStruct* n )
{
	visit( static_cast<CppNodeClass*>( n ) );
}

void XMLWriter::visit( CppNodeAnonymousUnion* n )
{
	visit( static_cast<CppNodeUnion*>( n ) );
}

void XMLWriter::visit( CppNodeUnion* n )
{
	m_OutputStream << insertTabs() << "<union name=\"" << n->getNodeName() << "\" >\n";
	m_CurrentDepth++;
	//Read ast nodes, scoped within union
	if( n->begin() != n->end() )
	{
		m_OutputStream << insertTabs() << "<astnodes>\n";
		m_CurrentDepth++;
		for(CppNodeScope::node_array_iterator_t it = n->begin(), end = n->end(); it != end; ++ it)
			(*it)->acceptVisitor(*this);
		m_CurrentDepth--;
		m_OutputStream << insertTabs() << "</astnodes>\n";
	}
	m_CurrentDepth--;
	m_OutputStream << insertTabs() << "</union>\n";
}

void XMLWriter::visit( CppNodeClassMethod* n )
{
	m_OutputStream << insertTabs() << "<method name=\"" << makeValidXML(n->getFunctionName()) 
		<< "\" virtual=\"" << static_cast<int>(n->isVirtual())
		<< "\" abstract=\"" << static_cast<int>(n->isAbstract()) 
		<< "\" static=\"" << static_cast<int>(n->isStatic())  
		<< "\" access=\"" << _access_str[n->getAccessType()] << "\" >\n";
	m_CurrentDepth++;
	visit(static_cast<CppNodeFunctionProto*>(n));
	m_CurrentDepth--;
	m_OutputStream << insertTabs() << "</method>\n";
}

void XMLWriter::visit( CppNodeClassConstructor* n )
{
	m_OutputStream << insertTabs() << "<constructor access=\"" << _access_str[n->getAccessType()] << "\" >\n";
	m_CurrentDepth++;
	visit(static_cast<CppNodeFunctionProto*>(n));
	m_CurrentDepth--;
	m_OutputStream << insertTabs() << "</constructor>\n";
}

void XMLWriter::visit( CppNodeClassCopyConstructor* n )
{
	m_OutputStream << insertTabs() << "<copy_constructor access=\"" << _access_str[n->getAccessType()] << "\" >\n";
	m_CurrentDepth++;
	visit(static_cast<CppNodeFunctionProto*>(n));
	m_CurrentDepth--;
	m_OutputStream << insertTabs() << "</copy_constructor>\n";
}

void XMLWriter::visit( CppNodeClassDestructor* n )
{
	m_OutputStream << insertTabs() << "<destructor virtual=\"" << static_cast<int>(n->isVirtual()) << "\" access=\"" << _access_str[n->getAccessType()] << "\" >\n";
	m_CurrentDepth++;
	visit(static_cast<CppNodeFunctionProto*>(n));
	m_CurrentDepth--;
	m_OutputStream << insertTabs() << "</destructor>\n";
}

void XMLWriter::visit( CppNodeClassOperatorEqual* n )
{
	visit(static_cast<CppNodeClassMethod*>(n));
}

void XMLWriter::visit( CppNodeClassMember* n )
{
	if( n->getCppType() )
	{
		m_OutputStream << insertTabs() << "<member type=\"" << makeValidXML(n->getCppType()->getQualifiedName()) << "\" name=\"" << makeValidXML(n->getNodeName()) 
			<< "\" has_value=\"" << static_cast<int>(n->hasValue()) << "\" access=\"" << _access_str[n->getAccessType()] << "\" />\n";
		m_TypesCache.insert(n->getCppType().get());
	}
}

void XMLWriter::visit( CppNodeConversionOperator* n )
{
	if( n->getConversionResultType() )
	{
		m_OutputStream << insertTabs() << "<conversion type=\"" << makeValidXML(n->getConversionResultType()->getQualifiedName()) << "\" />\n";
		m_TypesCache.insert(n->getConversionResultType().get());
	}
}

void XMLWriter::visit( CppNodeClassMemberPointer* n )
{
	if( n->getClass() && n->getPointeeType() )
	{
		m_TypesCache.insert(n->getPointeeType().get());
		m_OutputStream << "<member_pointer ast_node=\"" << makeValidXML( n->getClass()->getScopedName() ) << "\" pointee_type=\"" << makeValidXML( n->getPointeeType()->getQualifiedName() ) << "\" />\n";
	}
}

void XMLWriter::visit( CppNodePointer* n )
{
	if( n->getPointeeType() )
	{
		m_TypesCache.insert(n->getPointeeType().get());
		m_OutputStream << "<pointer type=\"" << makeValidXML(n->getPointeeType()->getQualifiedName()) << "\" declared_as_array=\"" << static_cast<int>(n->isDeclaredAsArray()) << "\" />\n"; 
	}
}

void XMLWriter::visit( CppNodeReference* n )
{
	if( n->getReferencedType() )
	{
		m_TypesCache.insert(n->getReferencedType().get());
		m_OutputStream << "<reference type=\"" << makeValidXML(n->getReferencedType()->getQualifiedName()) << "\" lvalue=\"" 
			<< static_cast<int>(n->getReferenceType() == CppNodeReference::REFERENCE_TYPE_LVALUE) << "\" />\n"; 
	}
}

std::string XMLWriter::insertTabs()
{
	if(m_CurrentDepth)
		return std::string(m_CurrentDepth,'\t');
	return std::string();
}

XMLWriter::XMLWriter( CppNode* tree_top, const std::string& _path )
	: m_CurrentDepth(2), m_TreeTop(tree_top), m_OutputStream( _path, std::ios_base::out )
{
	if(m_OutputStream.bad())
		throw std::exception("Failed to open output stream for writing");

	m_OutputStream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n<cpptree>\n\t<astnodes>\n";
}

XMLWriter::~XMLWriter()
{
	if(m_OutputStream.good())
	{
		m_OutputStream << "\t</astnodes>\n";
		if(m_TypesCache.size())
		{
			m_OutputStream << "\t<types>\n";
			for(std::set<CppType*>::iterator it = m_TypesCache.begin(), end = m_TypesCache.end(); it != end; ++it)
			{
				m_OutputStream 
					<< "\t\t<type qualified_name=\"" << makeValidXML((*it)->getQualifiedName())
					<< "\" bitmask=\"" << (*it)->getTypeHeader().mask << "\" ";

				if((*it)->getUserType())
					m_OutputStream << "astnode=\"" << makeValidXML((*it)->getUserType()->getScopedName()) << "\" ";
				m_OutputStream << " />\n";
			}
			m_OutputStream << "\t</types>\n";
		}
		m_OutputStream << "</cpptree>" << std::endl;
		m_OutputStream.close();
	}
}