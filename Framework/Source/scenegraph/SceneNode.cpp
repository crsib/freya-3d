#include "scenegraph/SceneNode.h"
#include <sstream>

#include <algorithm>

#include "scenegraph/World.h"
namespace scenegraph
{

SceneNode::SceneNode(unsigned id, const EString& name)
:m_NodeId(id),m_NodeName(name)
 {
	m_Type = NODE_TYPE_BASE;
	{
		std::ostringstream		stream;
		stream << "SceneNode ( " << (void*)this << ", " << m_NodeId << ", " << m_NodeName << " )";
		m_FullName = stream.str();
	}
	m_ReferenceCount = 1;
	m_NodeReadyForRendering = false;
 }

SceneNode::~SceneNode()
{

}

void SceneNode::update(float dt)
{
	SceneNodeControllerMap::iterator it = m_SceneNodeControllers.begin();
	for( ; it != m_SceneNodeControllers.end(); it++)
	{
		it->second->operator ()(this,dt);
	}
}

SceneNode*					SceneNode::getParent(unsigned idx)
{
	if(idx < m_Parents.size())
	{
		return m_Parents[idx];
	}
	else
		return NULL;
}

SceneNode*					SceneNode::getChild(unsigned idx)
{
	if(idx < m_Children.size())
	{
		return m_Children[idx];
	}
	else
		return NULL;
}

void						SceneNode::detach(SceneNode* parent,DETACH_MODE mode)
{
	SceneNodeList::iterator pit = std::find(m_Parents.begin(),m_Parents.end(),parent);
	if(pit == m_Parents.end())
		return;
	if(m_Children.size())
	{
		switch(mode)
		{
			case DETACH_MODE_DETACH_CHILDREN:
			{
				size_t child_count = m_Children.size();
				for(size_t i = 0; i < child_count; i++)
				{
					SceneNode* node = m_Children[i];
					node->detach(this,DETACH_MODE_DETACH_CHILDREN);
				}
			} // DETACH_MODE_DESTROY_CHILDREN
			break;
			case DETACH_MODE_REATTACH_CHILDREN:
			{
				size_t child_count = m_Children.size();
				for(size_t i = 0; i < child_count; i++)
				{
					SceneNode* node = m_Children[i];
					parent->addChild(node);
					SceneNodeList::iterator it = std::find(node->m_Parents.begin(),node->m_Parents.end(),this);
					node->m_Parents.erase(it);
					node->m_ReferenceCount--;
				}
			} // DETACH_MODE_REATTACH_CHILDREN
			break;
		} // switch(mode)
	}//if(m_Children.size())
	//Drop connection with parent
	m_Parents.erase(pit);
	SceneNodeList::iterator it = std::find(parent->m_Children.begin(),parent->m_Children.end(),this);
	parent->m_Children.erase(it);

	m_ReferenceCount--;
	if(m_ReferenceCount <= 1)
	{
		World::getInstance()->destroyNode(this);
	}

}

math::matrix4x4
SceneNode::getWorldTransform(unsigned forParentIdx) const
{
	return math::matrix4x4::identity;
}

AABB
SceneNode::getBoundingBox(unsigned forParentTransformIdx) const
{
	return m_BoundingBox;
}

void						SceneNode::attachController(unsigned priority,SceneNodeController* controller)
{
	m_SceneNodeControllers.insert(std::make_pair(priority,controller));
}

void						SceneNode::detachController(SceneNodeController* controller)
{
	SceneNodeControllerMap::iterator it = m_SceneNodeControllers.begin();
	for( ; it != m_SceneNodeControllers.end(); it++)
	{
		if(it->second == controller)
		{
			//Class does not take controller ownership
			m_SceneNodeControllers.erase(it);
			return;
		}
	}
}

void						SceneNode::preloadData()
{
	//Just a stub method here )
}

void						SceneNode::addChild(SceneNode* node)
{
	node->addParent(this);
	m_Children.push_back(node);
}

void						SceneNode::addParent(SceneNode* node)
{
	//Increase reference count
	m_ReferenceCount++;
	//Add to a parent node
	m_Parents.push_back(node);
}

void						SceneNode::reaattach(SceneNode* from, SceneNode* to)
{
	//Search for parent
	SceneNodeList::iterator it = std::find(m_Parents.begin(),m_Parents.end(),from);
	(*it) = to;
	to->m_Children.push_back(this);
	it = std::find(from->m_Children.begin(),from->m_Children.end(),this);
	from->m_Children.erase(it);
}

}


