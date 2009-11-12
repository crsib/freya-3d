#include "framework/World.h"

#include "core/EngineCore.h"
#include "core/filesystem/Filesystem.h"
#include "resources/ResourceManager.h"

#include "resources/Resource.h"

#include "XMLStaticStrings.h"
#include "core/xml/XMLStringWrap.h"

#include <iostream>

namespace framework
{

World*		World::m_Instance = NULL;

World*		World::loadFromXML(const EString& path)
{
	core::xml::DOMDocument*	doc = core::EngineCore::getXMLParser()->parse(path);

	try
	{
		m_Instance = new World(doc->getDocumentElement());
	}
	catch(...)
	{
		core::EngineCore::getXMLParser()->cleanup();
		throw;
	}
	core::EngineCore::getXMLParser()->cleanup();
}

World::World(core::xml::DOMNode* doc_root)
{
	using namespace core::xml;
	if(XMLString::equals(doc_root->getNodeName(),XMLS(world)))
	{
		//Parsing started
		std::cout << "Parsing of world document started!" << std::endl;


		DOMNodeList*	nodes = doc_root->getChildNodes();
		for(size_t node_it = 0; node_it < nodes->getLength(); node_it ++)
		{
			DOMNode* node = nodes->item(node_it);
			if(XMLString::equals(node->getNodeName(),XMLS(cell_size)))
			{
				m_CellWidth = m_CellHeight = 0;
				std::cout << "Parsing cell_size tag" << std::endl;
				DOMNamedNodeMap*  map = node->getAttributes();
				if(DOMNode* nd = map->getNamedItem(XMLS(width)))
				{
					char* val = XMLStringWrap(nd->getNodeValue());
					m_CellWidth = ::atoi(val);
				}
				if(DOMNode* nd = map->getNamedItem(XMLS(height)))
				{
					char* val = XMLStringWrap(nd->getNodeValue());
					m_CellHeight = ::atoi(val);
				}

				if(!m_CellWidth || !m_CellHeight)
					throw ::EngineException();
				std::cout << "World: cell_width: " << m_CellWidth << " cell_height " << m_CellHeight << std::endl;
			}//cell_size
			else if(XMLString::equals(node->getNodeName(),XMLS(world_size)))
			{
				m_WorldWidth = m_WorldHeight = 0;
				std::cout << "Parsing cell_size tag" << std::endl;
				DOMNamedNodeMap*  map = node->getAttributes();
				if(DOMNode* nd = map->getNamedItem(XMLS(horizontal)))
				{
					char* val = XMLStringWrap(nd->getNodeValue());
					m_WorldWidth = ::atoi(val);
				}
				if(DOMNode* nd = map->getNamedItem(XMLS(vertical)))
				{
					char* val = XMLStringWrap(nd->getNodeValue());
					m_WorldHeight = ::atoi(val);
				}

				if(!m_WorldWidth || !m_WorldHeight)
					throw ::EngineException();
				std::cout << "World: cell_width: " << m_WorldWidth << " cell_height " << m_WorldHeight << std::endl;

			}
		}
	}
	else
		throw ::EngineException();
}

World::~World()
{

}

}
