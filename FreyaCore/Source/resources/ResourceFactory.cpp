#include "resources/ResourceFactory.h"
#include "internal.h"
namespace resources
{

namespace __internal
{

EXPORT void					destroyResource(resources::Resource* res)
{
	delete res;
}

EXPORT void					finalizeResource(resources::Resource* res)
{
	res->m_Ready = true;
}

}

}
