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
	//! \defgroup grpLogging Freya 3D Engine logging support

	//! Output stream for a log
	/*!
	 * This interface should be overridden by classes in order to create custom output log.
	 * Thread safety is guaranteed by the Log class itself
	 * \ingroup grpLogging
	 */
	class FREYA_SUPPORT_EXPORT LogOutputStream : public RefCountedBase
	{
	public:
		//!Default constructor
		LogOutputStream() : m_Suppressed (false) {}
		//! Virtual destructor
		virtual ~LogOutputStream() {}
		//! Write \a num_bytes of data to the output stream. Implement this method to suit your needs
		virtual void	writeBuffer(const uint8_t * , size_t num_bytes) = 0;
		//! Set, whether to suppress data output to the stream
		void			suppressBuffer(bool suppress) { m_Suppressed = suppress; }
	protected:
		bool			m_Suppressed;
	};

	//! Smart pointer to the output stream
	// \ingroup grpLogging

	typedef core::smart_ptr<LogOutputStream,policies::ownership::Intrusive> LogOutputStreamPtr;
	//! Main logger class
	/*!
	 * This class provides following functionality: 
	 * - Log levels
	 * - Custom output streams
	 * - Both C and C++ variants of writing custom data to log (i.e. format string and operator <<)
	 * - Thread safe logging
	 *
	 * Internally, class is a Mayers singleton and will be early instantiated from FreyaReflect subsystem (still later, than memory manager).
	 * Basic implementation has overloaded versions of operator << for builtin types. It could be extended by overloading operator << for any types
	 * requred by using core::Log::LogStream::append method. The log will be flushed to the output streams when the following conditions are met:
	 * - internal buffer overflow (about 4kb of data)
	 * - message with Level not least than core::Log::Error is written
	 * - core::Log::flush is explicitly called
	 * - on core::Log destruction
	 *
	 * The current implementation could not handle log messages larger than 4kb. New line is appended automatically.
	 * There are for macro defined to ease access to logger:
	 * - \b InfoLog() prints a message at core::Log::Info
	 * - \b DebugLog() prints a message at core::Log::Debug
	 * - \b ErrorLog() prints a message at core::Log::Error
	 * - \b CriticalLog() prints a message at core::Log::Critical
	 *
	 * This macros can be used at any of the following ways and their combinations:
	 * - InfoLog("Info message") will log "Info message"
	 * - InfoLog("Formatted message %i", 1) will log "Formatted message 1"
	 * - InfoLog() << "Foo" will log "Foo"
	 * - InfoLog("Message ") << " from log" will log "Message from log". Spaces are \b not automatically inserted between calls to operator <<
	 *
	 * By default, log will have core::Log::Info as default level in debug and core::Log::Error in release.
	 * \ingroup grpLogging
	 */
	class FREYA_SUPPORT_EXPORT Log 
	{
		Log();
		~Log();
	public:
		//! Retrieve the Log instance
		static Log&    GetInstance() { static Log __; return __; }

		//! Log levels
		enum	LogLevel
		{
			Info, //!< Least important messages 
			Debug,//!< Debug messages
			Error,//!< Error messages
			Critical//!< Critical error messages
		};
		//! Log stream
		/*! 
		 * Log stream is a core concept of the logger. It provides non thread safe, RAII controlled stream (in C++ terms)
		 * which will be flushed to the logger buffer when the last copy is destructed. This stream should be used for single event only 
		 * and should be never copied across threads. Use *Log() macro to simplify stream management
		 * \ingroup grpLogging
		 */
		class FREYA_SUPPORT_EXPORT LogStream
		{
			friend class Log;
			LogStream(Log* parent, LogLevel level, bool writable, const char* file,  unsigned int line, const char* function, const char* fmt, va_list arglist);
		public:
			//! Copy constructor
			LogStream(const LogStream& rhs);
			//! Assignment operator
			LogStream& operator = (const LogStream& rhs);
			//! Destructor
			~LogStream();
			//! Append a string to the stream
			LogStream&	append(const core::string& str) 
			{ 
				FREYA_SUPPORT_ASSERT(m_RefCounter,"Appending to a flushed stream!"); 
				if(m_IsWritable) 
					m_Storage += str; 
				return *this; 
			}
			//! Get the reference to the stream.append This is required due to odd GCC behavior
			LogStream& 	getRef() { return *this; } //Strange GCC behavior without it

		private:
			Log*		m_Parent;
			uint32_t*	m_RefCounter;
			LogLevel	m_LogLevel;
			bool		m_IsWritable;

			core::string m_Storage;
		};
		//! Forcibly flush the log data to the output streams
		void	flush();
		//! Get the logger stream. Use *Log macros instead
		LogStream	getStream(LogLevel level, const char* file,  unsigned int line, const char* function, const char* fmt = "", ...);
		//! Set the logger level
		void	setLogLevel(LogLevel level) { m_CurrentLogLevel = level; }
		//! Retrieve the current logger level
		LogLevel getLogLevel() const { return m_CurrentLogLevel; }
		//! Add new output stream to the logger
		void	 addOutputStream(const LogOutputStreamPtr& stream) { m_OutputStreams.push_back(stream); }
		//! Suppress stdout output
		void	 suppressStdoutOutput(bool suppress) { m_OutputStreams[0]->suppressBuffer(suppress); }
	private:
		LogLevel	m_CurrentLogLevel;

		struct buffer_storage
		{
			uint8_t*	buffer;
			uint32_t	first_not_flushed;
			uint32_t	current_position;

			static const uint32_t	buffer_size = 4096 - 1; //4096 Kb per buffer

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
	//! \cond
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
	//! \endcond
}
//! \cond
#if defined(__func__)
#	define __freya_func__ __func__
#else
#	define __freya_func__ __FUNCTION__
#endif

#define	InfoLog(...) core::Log::GetInstance().getStream(core::Log::Info, __FILE__, __LINE__, __freya_func__, ##__VA_ARGS__).getRef()
#define	DebugLog(...) core::Log::GetInstance().getStream(core::Log::Debug, __FILE__, __LINE__, __freya_func__, ##__VA_ARGS__).getRef()
#define	ErrorLog(...) core::Log::GetInstance().getStream(core::Log::Error, __FILE__, __LINE__, __freya_func__, ##__VA_ARGS__).getRef()
#define	CriticalLog(...) core::Log::GetInstance().getStream(core::Log::Critical, __FILE__, __LINE__, __freya_func__, ##__VA_ARGS__).getRef()
//! \endcond
#endif // Core_Log_h__
