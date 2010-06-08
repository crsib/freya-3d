#include "FreyaReflect.h"

#include <iostream>

void NodePrinter(CppNode* root,int depth)
{
	for(int i = 0; i < depth; i++)
		std::cout << "\t";
	std::cout << root->getShortName() << " ( " << root->getQualifiedName() << " )" << std::endl;
	for(NodeListIterator it = root->begin(); it != root->end(); ++it)
		NodePrinter(*it,depth+1);
}

int main(int argc, char* argv[])
{
	//TESTS
	FreyaReflect		reflector;

	reflector.addDefinition("_SHARED_BUILD");
	reflector.addDefinition("EXPORT=");
#ifdef _MSC_VER
	reflector.addDefinition("_MSC_VER=1600");
#else
	reflector.addDefinition("__GNUC__=");
#endif
	reflector.addDirectory("D:\\Devel\\Projects\\Freya3D\\Freya\\Framework\\Include\\core");

	reflector.parse();
	//Print all nodes
	NodePrinter(reflector.root(),0);

	system("pause");
	
	return 0;
}