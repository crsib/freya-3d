/*
 * StaticGeometryNode.cpp
 *
 *  Created on: Jan 4, 2010
 *      Author: crsib
 */

#include "../../Include/scenegraph/StaticGeometryNode.h"
#include <sstream>

namespace scenegraph
{

StaticGeometryNode::StaticGeometryNode(unsigned id,const EString& name)
:SceneNode(id,name)
 {
	m_Type = NODE_TYPE_STATIC_GEOMETRY;
	{
		std::ostringstream		stream;
		stream << "StaticGeometryNode ( " << (void*)this << ", " << m_NodeId << ", " << m_NodeName << " )";
		m_FullName = stream.str();
	}
 }

StaticGeometryNode::~StaticGeometryNode( )
{

}

}
