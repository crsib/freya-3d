#include "framework/SceneNode.h"
#include "XMLStaticStrings.h"
namespace framework
{

__Camera::__Camera(core::xml::DOMNode* root)
{
	using namespace core::xml;
	if(XMLString::equals(root->getNodeName(),XMLS(camera)))
	{

	}
	else
		throw ::EngineException();
}

SceneNode::SceneNode( core::xml::DOMNode*	root)
{

}

SceneNode::~SceneNode( )
{

}

}
