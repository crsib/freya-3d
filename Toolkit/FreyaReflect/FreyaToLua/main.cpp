#include "FreyaReflect.h"

#include <iostream>

void NodePrinter(CppNode* root,int depth)
{
	for(int i = 0; i < depth; i++)
		std::cout << "\t";
	std::string type;
	switch(root->getNodeType())
	{
	case CppNode::NODE_TYPE_CLASS:
		type = "class ";
		break;
	case CppNode::NODE_TYPE_NAMESPACE:
		type = "namespace ";
		break;
	case CppNode::NODE_TYPE_ENUM:
		type = "enum ";
		break;
	}
	std::cout << type << root->getShortName() << " ( " << root->getQualifiedName() << " )" << std::endl;
	for(NodeListIterator it = root->begin(); it != root->end(); ++it)
		NodePrinter(*it,depth+1);
}

int main(int argc, char* argv[])
{
	//TESTS
	FreyaReflect		reflector;

	reflector.addDefinition("_SHARED_BUILD");
	reflector.addDefinition("EXPORT=");
	reflector.addDirectory("D:\\Devel\\Projects\\Freya3D\\Freya\\Framework\\Include");
	reflector.addIncludeDirectory("D:\\Devel\\Projects\\Freya3D\\Freya\\Framework\\Include");
	reflector.addIncludeDirectory("D:/Devel/Projects/Freya3D/Freya_MSVC10/include/");
	reflector.addIncludeDirectory("D:/Devel/Projects/Freya3D/Freya_MSVC10/include/stlport");
	//reflector.addIncludeDirectory("");
	reflector.addIncludeDirectory("D:/Devel/Projects/Freya3D/Freya_MSVC10/include/boost-1_43");
	reflector.addIncludeDirectory("D:/Devel/Projects/Freya3D/Freya/Build/Intermediate");
	reflector.parse();
	//Print all nodes
	NodePrinter(reflector.root(),0);

	system("pause");
	
	return 0;
}