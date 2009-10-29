#include "freya/FreyaResourceProvider.h"
#include "core/EngineCore.h"
#include "core/filesystem/Filesystem.h"
#include "CEGUIExceptions.h"

#include <cstdlib>

namespace CEGUI
{

namespace freya
{
FreyaResourceProvider::FreyaResourceProvider()
{

}

FreyaResourceProvider::~FreyaResourceProvider()
{

}

void 	FreyaResourceProvider::loadRawDataContainer(const String& filename, RawDataContainer& output,
		const String& resourceGroup)
{
	String resGrp;
	if(resourceGroup.empty() )
		resGrp = d_defaultResourceGroup.empty() ? "default" : d_defaultResourceGroup;
	else
		resGrp = resourceGroup;


	EString path = getGroupPath(resGrp) + filename.c_str();

	std::cout << "[CEGUI::ResourceProvider]: Trying to load " << path << std::endl;
	if(core::EngineCore::getFilesystem()->fileExists(path))
	{
		size_t sz  = core::EngineCore::getFilesystem()->fileSize(path);
		void* data = core::EngineCore::getFilesystem()->read(path);
		output.setData(reinterpret_cast<uint8*>(data));
		output.setSize(sz);
	}
	else
	{
		throw InvalidRequestException(
				"FreyaResourceProvider::loadRawDataContainer: Unable to open "
				"resource file '" + filename + "' in resource group '" + resGrp +
				"'.");
	}
	std::cout << "[CEGUI::ResourceProvider]: Resource successfully loaded" << std::endl;
}

void 	FreyaResourceProvider::unloadRawDataContainer(RawDataContainer& output)
{
	if(output.getDataPtr())
	{
		core::memory::Free(output.getDataPtr(),core::memory::GENERIC_POOL);
		output.setData(NULL);
		output.setSize(0);
	}
}
//Algorithm from http://xoomer.virgilio.it/acantato/dev/wildcard/wildmatch.html
bool szWildMatch8(const char* pat, const char* str) {
	const char* s, *p;
	bool star = false;

	loopStart:
	for (s = str, p = pat; *s; ++s, ++p) {
		switch (*p) {
			case '?':
				if (*s == '.') goto starCheck;
				break;
			case '*':
				star = true;
				str = s, pat = p;
				if (!*++pat) return true;
				goto loopStart;
			default:
				if (toupper(*s) != toupper(*p))
					goto starCheck;
				break;
		} /* endswitch */
	} /* endfor */
	if (*p == '*') ++p;
	return (!*p);

	starCheck:
	if (!star) return false;
	str++;
	goto loopStart;
}

size_t 	FreyaResourceProvider::getResourceGroupFileNames(std::vector<String>& out_vec,
		const String& file_pattern,
		const String& resource_group)
{
	const char* match = (getGroupPath(resource_group) + file_pattern.c_str()).c_str();
	size_t rgps = getGroupPath(resource_group).length() + 1;
	EStringList lst = core::EngineCore::getFilesystem()->list();
	size_t entr = 0;
	for(unsigned i = 0; i < lst.size(); i++)
	{
		if(szWildMatch8(match,lst[i].c_str()))
		{
			EString tmp = lst[i];
			tmp = tmp.erase(0,rgps);
			out_vec.push_back(String(tmp.c_str()));
			entr ++;
		}
	}
	return entr;
}

void	FreyaResourceProvider::setResourceGroupDirectory(const String& group, const EString& path)
{
	m_Groups[group] = path;
}

EString		FreyaResourceProvider::getGroupPath(const String& str)
{
	EString t = m_Groups[str];
	if(t.empty())
	{
		return  "/";
	}
	if(t[t.length() - 1] != '/')
		t += '/';
	return t;
}

}

}
