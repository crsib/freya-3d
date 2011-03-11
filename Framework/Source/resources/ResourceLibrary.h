/*
 * ResourceLibrary.h
 *
 *  Created on: 21.05.2009
 *      Author: vedenko
 */

#ifndef RESOURCELIBRARY_H_
#define RESOURCELIBRARY_H_

/*
 *
 */
#include "core/EngineSubsystem.h"
#include "resources/Resource.h"
#include "core/EString.h"
#include "core/memory/MemoryAllocator.h"

#include <map>

namespace resources
{
class ResourceManager;
namespace __internal
{

class ResourceLibrary : virtual public ::EngineSubsystem
{
	friend class resources::ResourceManager;
private:
	ResourceLibrary();
	virtual ~ResourceLibrary();
public:
	void		add(const EString& ID,Resource* res);
	void		add(const EString& ID);
	//Return true if resource is not needed anymore
	bool		remove(Resource* res);
	Resource*	query(const EString& ID);
	size_t		count();
	Resource*	pop();
private:
	typedef std::pair<Resource*,size_t> __ResourceRef;
	typedef std::map<EString,__ResourceRef,std::less<EString>,core::memory::MemoryAllocator<std::pair<const EString,__ResourceRef> > > __ResourceLibrary;
	__ResourceLibrary	m_Library;
};

}
}

#endif /* RESOURCELIBRARY_H_ */
