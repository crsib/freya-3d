#include "Output/XMLWriter.h"
#include "CppTree/CppTree.h"
#include "CppTree/CppType.h"

#include <boost/algorithm/string.hpp>

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

void XMLWriter::visit( CppNode* n )
{

}

void XMLWriter::visit( CppNodeScope* n )
{
	
}

void XMLWriter::visit( CppNodeVariableDecl* n )
{

}

void XMLWriter::visit( CppNodeNamespace* n )
{
	if(n->begin() == n->end())
		return;

	if(!n->getNodeName().empty())
		m_OutputStream << insertTabs() << "<namespace name=\"" << n->getNodeName() << "\">\n";
	else
		m_OutputStream << insertTabs() << "<namespace>\n";

	m_CurrentDepth++;

	for(CppNodeScope::node_array_iterator_t it = n->begin(), end = n->end(); it != end; ++it)
		if( ((*it)->getNodeFlag() <= CppNode::NODE_FLAG_USED) && ((*it)->getAccessType() != CppNode::ACCESS_TYPE_PRIVATE ) )
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

}

void XMLWriter::visit( CppNodeFunction* n )
{

}

void XMLWriter::visit( CppNodeFunctionTemplateSpecialization* n )
{

}

void XMLWriter::visit( CppNodeGlobalVariable* n )
{

}

void XMLWriter::visit( CppNodeGlobalConstant* n )
{

}

void XMLWriter::visit( CppNodeTypedef* n )
{

}

void XMLWriter::visit( CppNodeClass* n )
{
	m_OutputStream << insertTabs() << "<class name=\"" << n->getNodeName() << "\">\n";

	m_CurrentDepth++;

	//Write down bases
	if(n->baseClassCount())
	{
		m_OutputStream << insertTabs() << "<bases>\n";
		m_CurrentDepth++;
		for(CppNodeClass::base_type_list_iterator_t it = n->bases_begin(), end = n->bases_end(); it != end; ++it)
		{
			CppNodeClass::base_type_t& base = *it;
			m_TypesCache.insert(base.first.get());
			m_OutputStream << insertTabs() << "<base access=\"" << _access_str[base.second] << "\" type=\"" << makeValidXML(base.first->getQualifiedName()) << "\" />\n";
		}
		m_CurrentDepth--;
		m_OutputStream << insertTabs() << "</bases>\n";
	}

	for(CppNodeScope::node_array_iterator_t it = n->begin(), end = n->end(); it != end; ++ it)
		if( (*it)->getAccessType() != CppNode::ACCESS_TYPE_PRIVATE ) 
			(*it)->acceptVisitor(*this);

	m_CurrentDepth--;

	m_OutputStream << insertTabs() << "</class>\n";
}

void XMLWriter::visit( CppNodeClassTemplateSpecialization* n )
{

}

void XMLWriter::visit( CppNodeAnonymousStruct* n )
{

}

void XMLWriter::visit( CppNodeAnonymousUnion* n )
{

}

void XMLWriter::visit( CppNodeUnion* n )
{

}

void XMLWriter::visit( CppNodeClassMethod* n )
{

}

void XMLWriter::visit( CppNodeClassConstructor* n )
{

}

void XMLWriter::visit( CppNodeClassCopyConstructor* n )
{

}

void XMLWriter::visit( CppNodeClassDestructor* n )
{

}

void XMLWriter::visit( CppNodeClassOperatorEqual* n )
{

}

void XMLWriter::visit( CppNodeClassMember* n )
{

}

void XMLWriter::visit( CppNodeConversionOperator* n )
{

}

void XMLWriter::visit( CppNodeClassMemberPointer* n )
{

}

void XMLWriter::visit( CppNodePointer* n )
{

}

void XMLWriter::visit( CppNodeReference* n )
{

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