#include "FreyaReflect.h"

#include <iostream>

void NodePrinter(CppNode* root,int depth)
{
	for(NodeListIterator it = root->begin(); it != root->end(); ++it)
		NodePrinter(*it,depth+1);
	for(int i = 0; i < depth; i++)
		std::cout << "\t";
	std::cout << root->getShortName() << " ( " << root->getQualifiedName() << " )" << std::endl;
}

int main(int argc, char* argv[])
{
	//TESTS
	FreyaReflect		reflector;

	reflector.addDefinition("FREYA_SHARED");
	reflector.addDirectory("D:\\Devel\\Projects\\Freya3D\\Freya\\Framework\\Include\\renderer");
	reflector.addDirectory("D:\\Devel\\Projects\\Freya3D\\Freya\\Framework\\Include",false);
	reflector.addFile("D:\\Devel\\Projects\\Freya3D\\Freya\\Framework\\Include\\windowmanager\\WindowManagerDriver.h");

	reflector.parse();
	//Print all nodes
	NodePrinter(reflector.root(),0);

	system("pause");
	
	return 0;
}