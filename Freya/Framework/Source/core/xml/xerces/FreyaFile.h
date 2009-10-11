#ifndef _FREYAFILE_H_
#define _FREYAFILE_H_

#include "core/EngineSubsystem.h"
#include "core/EString.h"
namespace core
{
namespace xml
{
namespace xerces
{

class FreyaFile : public ::EngineSubsystem
{
	friend class FreyaFileManager;
protected:
	FreyaFile();
public:

	//Opens file from freya fs and reads it to memory
void open(const EString& path, bool toWrite);

	//Frees memory allocated for file
void close();

size_t read(size_t count, void* buf);

void write(size_t count, const void*  );

size_t pos();

size_t size();

void reset();

private:
	bool m_ForWrite;
	EString m_Path;
	size_t m_Pos;
	size_t m_Size;
	void*	m_Buffer;
	size_t	m_Allocated;
}; //End of FreyaFile class

} //End of xerces namespace
} //End of xml namespace
} //End of core namespace
#endif //End of _FREYAFILE_H_
