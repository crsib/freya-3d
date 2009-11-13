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

void World::destroy()
{
	delete m_Instance;
	m_Instance = 0;
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
				//Now create and setup cells
				m_Cells = new WorldCell[m_WorldWidth*m_WorldHeight];
				size_t centerX = -(m_WorldWidth *m_CellWidth) >> 1;
				size_t centerY = -(m_WorldHeight *m_CellHeight) >> 1;
				for(size_t i = 0; i < m_WorldWidth; i++)
					for(size_t j = 0; j < m_WorldHeight; j++)
					{
						WorldCell* cell 	= m_Cells + i*m_WorldHeight + j;
						cell->tile.left 	= centerX + i*m_CellWidth;
						cell->tile.right	= centerX + (i+1)*m_CellWidth;
						cell->tile.top		= centerY + j*m_CellHeight;
						cell->tile.bottom	= centerY + (j+1)*m_CellWidth;
						if((i > 0 && i < (m_WorldWidth - 1))&& j > 0 && j < (m_WorldHeight - 1))
						{
							cell->neighbours[WorldCell::Top] = m_Cells + i*m_WorldHeight + (j - 1);
							cell->neighbours[WorldCell::TopLeft] = m_Cells + (i - 1)*m_WorldHeight + (j - 1);
							cell->neighbours[WorldCell::Left] = m_Cells + (i - 1)*m_WorldHeight + j;
							cell->neighbours[WorldCell::BottomLeft] = m_Cells + (i - 1)*m_WorldHeight + (j + 1);
							cell->neighbours[WorldCell::Bottom] = m_Cells + i*m_WorldHeight + (j + 1);
							cell->neighbours[WorldCell::BottomRight] = m_Cells + (i + 1)*m_WorldHeight + (j + 1);
							cell->neighbours[WorldCell::Right] = m_Cells + (i + 1)*m_WorldHeight + j;
							cell->neighbours[WorldCell::TopRight] = m_Cells + (i + 1)*m_WorldHeight + (j - 1);
						}
						else
						{
							if(i == 0)
							{
								if(1 == m_WorldWidth ) //m_WorldWidth == 1
								{
									if(j > 0) //connect to top
									{
										cell->neighbours[WorldCell::Top] = m_Cells + (j - 1);
									}
									if((j + 1) < m_WorldHeight) // connect bottom
									{
										cell->neighbours[WorldCell::Bottom] = m_Cells + (j + 1);
									}
								}
								else
								{
									cell->neighbours[WorldCell::Right] = m_Cells + (i + 1)*m_WorldHeight + j;
									if(j > 0) //connect to top
									{
										cell->neighbours[WorldCell::Top] = m_Cells + (j - 1);
										cell->neighbours[WorldCell::TopRight] = m_Cells + (i + 1)*m_WorldHeight + j - 1;
									}
									if((j + 1) < m_WorldHeight) // connect bottom
									{
										cell->neighbours[WorldCell::Bottom] = m_Cells + (j + 1);
										cell->neighbours[WorldCell::BottomRight] = m_Cells + (i + 1)*m_WorldHeight + j + 1;
									}
								}
							}
							else
							{
								cell->neighbours[WorldCell::Left] = m_Cells + (i - 1)*m_WorldHeight + j;
								if(j > 0) //connect to top
								{
									cell->neighbours[WorldCell::Top] = m_Cells + (j - 1);
									cell->neighbours[WorldCell::TopLeft] = m_Cells + (i - 1)*m_WorldHeight + j - 1;
								}
								if((j + 1) < m_WorldHeight) // connect bottom
								{
									cell->neighbours[WorldCell::Bottom] = m_Cells + (j + 1);
									cell->neighbours[WorldCell::BottomLeft] = m_Cells + (i - 1)*m_WorldHeight + j + 1;

								}
							}
						}
					}//for cycle
			}//World size
		}
	}
	else
		throw ::EngineException();
}

World::~World()
{
	delete [] m_Cells;
}

}
