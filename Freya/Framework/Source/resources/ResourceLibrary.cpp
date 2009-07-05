/*
 * ResourceLibrary.cpp
 *
 *  Created on: 21.05.2009
 *      Author: vedenko
 */

#include "ResourceLibrary.h"

namespace resources
{

namespace __internal
{

ResourceLibrary::ResourceLibrary()
{
}

ResourceLibrary::~ResourceLibrary()
{
}

void		ResourceLibrary::add(const EString& ID,Resource* res)
{
	res->m_ResourceID = ID;
	m_Library[ID].first = res;
	m_Library[ID].second = 1;
}

void		ResourceLibrary::add(const EString& ID)
{
	m_Library[ID].second++;
}

bool		ResourceLibrary::remove(Resource* res)
{
	__ResourceLibrary::iterator	it = m_Library.find(res->m_ResourceID);
	if(it!=m_Library.end())
	{
		if((--(*it).second.second) > 0)
			return false;
		return true;
	}
	return false;
}

Resource*	ResourceLibrary::query(const EString& ID)
{
	__ResourceLibrary::iterator	it = m_Library.find(ID);
	if(it!=m_Library.end())
		return (*it).second.first;

	return NULL;
}

size_t		ResourceLibrary::count()
{
	return m_Library.size();
}

Resource*	ResourceLibrary::pop()
{
	Resource* res = m_Library.begin()->second.first;
	m_Library.erase(m_Library.begin());
	return res;
}

}

}
