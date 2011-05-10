/* File		: core/Log.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef Core_Log_h__
#define Core_Log_h__

#include "FreyaSupportInternal.h"
#include "core/string.h"
#include "core/smart_ptr.h"
#include "atomic/atomic.h"
#include "containers/vector.h"
#include "integer.h"
#include "containers/policies/Policies.h"

#include "core/multithreading/spinlock.h"

#include "core/RefCountedBase.h"

namespace core
{
	class FREYA_SUPPORT_EXPORT LogOutputStream : public RefCountedBase
	{
	public:
		virtual ~LogOutputStream() {}
		virtual void	writeBuffer(const uint8_t * , size_t num_bytes) = 0;
	};

	typedef core::smart_ptr<LogOutputStream,policies::ownership::Intrusive> LogOutputStreamPtr;

	class FREYA_SUPPORT_EXPORT Log 
	{
		Log();
		~Log();
	public:
		static Log&    getInstance() { static Log __; return __; }

		enum	LogLevel
		{
			Info,
			Debug,
			Error,
			Critical
		};

		class FREYA_SUPPORT_EXPORT LogStream
		{
			friend class Log;
			LogStream(Log* parent, LogLevel level, bool writable, const char* file,  unsigned int line, const char* function, const char* fmt, va_list arglist);
		public:
			LogStream(const LogStream& rhs);
			LogStream& operator = (const LogStream& rhs);
			~LogStream();

			LogStream&	append(const core::string& str) 
			{ 
				FREYA_SUPPORT_ASSERT(m_RefCounter,"Appending to a flushed stream!"); 
				if(m_IsWritable) 
					m_Storage += str; 
				return *this; 
			}
		private:
			Log*		m_Parent;
			uint32_t*	m_RefCounter;
			LogLevel	m_LogLevel;
			bool		m_IsWritable;

			core::string m_Storage;
		};

		void	flush();

		LogStream	getStream(LogLevel level, const char* file,  unsigned int line, const char* function, const char* fmt = "", ...);

		void	setLogLevel(LogLevel level) { m_CurrentLogLevel = level; }
		LogLevel getLogLevel() const { return m_CurrentLogLevel; }

		void	 addOutputStream(const LogOutputStreamPtr& stream) { m_OutputStreams.push_back(stream); }
	private:
		LogLevel	m_CurrentLogLevel;

		struct buffer_storage
		{
			uint8_t*	buffer;
			uint32_t	first_not_flushed;
			uint32_t	current_position;

			static const uint32_t	buffer_size = 2048 - 1; //2 Kb per buffer

			buffer_storage();
			~buffer_storage();
			void reset(Log* parent) { parent->flush(); first_not_flushed = current_position = 0; }
		};

		buffer_storage	m_Storage[2];
		uint32_t		m_CurrentBuffer;

		containers::vector<LogOutputStreamPtr,containers::policies::memory::Malloc>	
			m_OutputStreams;

		multithreading::spinlock m_FlushMutex;
		multithreading::spinlock m_BufferMutex;

		void	write_string(const string& str);
	};

	FREYA_SUPPORT_EXPORT inline Log::LogStream& operator << (Log::LogStream& stream, const core::string& str) { stream.append(str); return stream; }
	FREYA_SUPPORT_EXPORT inline Log::LogStream& operator << (Log::LogStream& stream, int val) { stream.append(string::withFormat("%i",val)); return stream; }
	FREYA_SUPPORT_EXPORT inline Log::LogStream& operator << (Log::LogStream& stream, unsigned val) { stream.append(string::withFormat("%u",val)); return stream; }
	FREYA_SUPPORT_EXPORT inline Log::LogStream& operator << (Log::LogStream& stream, long val) { stream.append(string::withFormat("%li",val)); return stream; }
	FREYA_SUPPORT_EXPORT inline Log::LogStream& operator << (Log::LogStream& stream, unsigned long val) { stream.append(string::withFormat("%lu",val)); return stream; }
	FREYA_SUPPORT_EXPORT inline Log::LogStream& operator << (Log::LogStream& stream, long long val) { stream.append(string::withFormat("%lli",val)); return stream; }
	FREYA_SUPPORT_EXPORT inline Log::LogStream& operator << (Log::LogStream& stream, unsigned long long val) { stream.append(string::withFormat("%llu",val)); return stream; }
	FREYA_SUPPORT_EXPORT inline Log::LogStream& operator << (Log::LogStream& stream, void* val) { stream.append(string::withFormat("0x%X",val)); return stream; }
	FREYA_SUPPORT_EXPORT inline Log::LogStream& operator << (Log::LogStream& stream, char* val) { stream.append(string::withFormat("%s",val)); return stream; }
	FREYA_SUPPORT_EXPORT inline Log::LogStream& operator << (Log::LogStream& stream, const char* val) { stream.append(string::withFormat("%s",val)); return stream; }
	FREYA_SUPPORT_EXPORT inline Log::LogStream& operator << (Log::LogStream& stream, float val) { stream.append(string::withFormat("%f",val)); return stream; }
	FREYA_SUPPORT_EXPORT inline Log::LogStream& operator << (Log::LogStream& stream, double val) { stream.append(string::withFormat("%lf",val)); return stream; }
}

#if defined(__func__)
#	define __freya_func__ __func__
#else
#	define __freya_func__ __FUNCTION__
#endif

#define	InfoLog(...) core::Log::getInstance().getStream(core::Log::Info, __FILE__, __LINE__, __freya_func__, __VA_ARGS__)
#define	DebugLog(...) core::Log::getInstance().getStream(core::Log::Debug, __FILE__, __LINE__, __freya_func__, __VA_ARGS__)
#define	ErrorLog(...) core::Log::getInstance().getStream(core::Log::Error, __FILE__, __LINE__, __freya_func__, __VA_ARGS__)
#define	CriticalLog(...) core::Log::getInstance().getStream(core::Log::Critical, __FILE__, __LINE__, __freya_func__, __VA_ARGS__)

#endif // Core_Log_h__
