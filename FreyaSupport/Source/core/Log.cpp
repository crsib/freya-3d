/* File		: core/Log.cpp
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#include "core/Log.h"
#include "date_time/date_time_string.h"
#include "core/multithreading/synchronize.h"
#include "core/multithreading/thread_self.h"
#include "date_time/date_time_string.h"
#include <cstdio>

namespace core
{
	namespace details
	{
		class	StdOutOutputStream : public LogOutputStream
		{
		public:
			void	writeBuffer(const uint8_t * p, size_t num_bytes)
			{
				fwrite( p, sizeof(uint8_t), num_bytes, stdout);
			}
		};
	}

	Log::Log()
	{
		m_CurrentLogLevel = Info;
		m_CurrentBuffer = 0;

		m_OutputStreams.push_back(LogOutputStreamPtr(new details::StdOutOutputStream));
	}

	Log::~Log()
	{
		flush();
	}

	void Log::flush()
	{
		synchronize(&m_FlushMutex)
		{
			buffer_storage& current_buffer = m_Storage[m_CurrentBuffer];
		
			uint8_t * ptr = current_buffer.buffer + current_buffer.first_not_flushed;
			size_t    sz  = current_buffer.current_position - current_buffer.first_not_flushed;

			for( size_t i = 0, count = m_OutputStreams.size(); i < count; ++i )
				m_OutputStreams[i]->writeBuffer(ptr, sz);

			current_buffer.first_not_flushed = current_buffer.current_position;
		}
	}

	Log::LogStream Log::getStream( LogLevel level, const char* file, unsigned int line, const char* function, const char* fmt, ... )
	{
		va_list list;
		va_start(list, fmt);
		LogStream stream( this, level, level >= m_CurrentLogLevel,file, line, function, fmt, list);
		va_end(list);
		return stream;
	}

	void Log::write_string(const string& s)
	{
		synchronize(&m_BufferMutex)
		{
			// Check out, if we have sufficient space for storing the string data
			size_t storage_required = s.least_storage_size();

			if( ( buffer_storage::buffer_size - m_Storage[m_CurrentBuffer].current_position ) < storage_required )
			{
				m_Storage[m_CurrentBuffer].reset(this);
				m_CurrentBuffer ^= 1;
			}

			::memcpy( m_Storage[m_CurrentBuffer].buffer + m_Storage[m_CurrentBuffer].current_position, s.data(), storage_required );

			m_Storage[m_CurrentBuffer].current_position += storage_required;
		}
	}

	Log::buffer_storage::buffer_storage()
	{
		current_position = first_not_flushed = 0;
		buffer = reinterpret_cast<uint8_t*>(::malloc(buffer_size + 1));
	}

	Log::buffer_storage::~buffer_storage()
	{
		free(buffer);
	}



	Log::LogStream::LogStream( Log* parent, LogLevel level, bool writable, const char* file, unsigned int line, const char* function, const char* fmt, va_list arglist)
	{
		m_Parent = parent;
		m_RefCounter = core::memory::alloc<uint32_t>(1);
		*m_RefCounter = 1;
		m_IsWritable = writable;

		string level_str;

		if(writable)
		{
			switch(level)
			{
			case Info:
				level_str += "Info:";
				break;
			case Debug:
				level_str += "Debug:";
				break;
			case Error:
				level_str += "Error:";
				break;
			case Critical:
				level_str += "Critical:";
				break;
			}

			m_Storage = string::withFormat("[%s][%s %s, %s:%u, thread %u]: %s",date_time::date_time_string("%c").c_str(),level_str.c_str(),function,file,line, multithreading::thread_self::get_freya_id(), string::withVAList(fmt,arglist).c_str());
		}
	}

	Log::LogStream::LogStream( const LogStream& rhs )
	{
		FREYA_SUPPORT_ASSERT(m_RefCounter, "Copying flushed stream");
		m_RefCounter = rhs.m_RefCounter;
		++*m_RefCounter;
		m_Parent = rhs.m_Parent;
		m_LogLevel = rhs.m_LogLevel;
		m_IsWritable = rhs.m_IsWritable;
		m_Storage = rhs.m_Storage;
	}

	Log::LogStream::~LogStream()
	{
		if(*m_RefCounter)
			--*m_RefCounter;
		if( !*m_RefCounter )
		{
			memory::dealloc(m_RefCounter);
			m_RefCounter = NULL;
			
			if(  m_IsWritable )
			{
				m_Parent->write_string(m_Storage + "\n");
				if( m_LogLevel >= Error )
					m_Parent->flush();
			}
		}
	}

	Log::LogStream& Log::LogStream::operator= ( const LogStream& rhs )
	{
		FREYA_SUPPORT_ASSERT(m_RefCounter, "Copying flushed stream");
		m_RefCounter = rhs.m_RefCounter;
		++*m_RefCounter;
		m_LogLevel = rhs.m_LogLevel;
		m_Parent = rhs.m_Parent;
		m_IsWritable = rhs.m_IsWritable;
		m_Storage = rhs.m_Storage;
		return *this;
	}

}