#include "resources/ResourceFactory.h"

namespace resources
{

namespace __internal
{

void					destroyResource(resources::Resource* res)
{
	delete res;
}

void					finalizeResource(resources::Resource* res)
{
	res->m_Ready = true;
}

}

}
