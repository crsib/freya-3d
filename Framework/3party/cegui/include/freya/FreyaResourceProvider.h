/*
 * FreyaResourceProvider.h
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Oct 28, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef FREYARESOURCEPROVIDER_H_
#define FREYARESOURCEPROVIDER_H_

/*
 *
 */
#include "CEGUIResourceProvider.h"
#include "CEGUIMemory.h"

#include <map>
#include <core/memory/MemoryAllocator.h>
#include "core/EString.h"

namespace CEGUI
{

namespace freya
{

class FreyaResourceProvider : public CEGUI::ResourceProvider, public virtual CEGUI::CEGUIMemory
{
public:
	FreyaResourceProvider( );
	virtual ~FreyaResourceProvider( );

	virtual void loadRawDataContainer(const String& filename, RawDataContainer& output,
			const String& resourceGroup);
	virtual void unloadRawDataContainer(RawDataContainer& output);
	virtual size_t getResourceGroupFileNames(std::vector<String>& out_vec,
			const String& file_pattern,
			const String& resource_group);

	void	setResourceGroupDirectory(const String& group, const EString& path);

private:
	typedef std::map<String,EString,std::less<String>, core::memory::MemoryAllocator< std::pair<const String,EString> > > Groups;
	Groups	m_Groups;
	EString		getGroupPath(const String& str);
};

}

}

#endif /* FREYARESOURCEPROVIDER_H_ */
