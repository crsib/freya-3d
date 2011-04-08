// This file is a part of Freya 3D Engine


#include "core/string.h"

#if FREYA_USE_ICU
#include <unicode/utypes.h>
#include <unicode/stringpiece.h>
#include <unicode/utf8.h>
#include <unicode/uchar.h>
#endif

#include <utf8.h>


namespace core
{
	core::string string::to_upper() const
	{
		size_t length = this->length();
		if(length == 0)
			return *this;

		uint32_t * utf32_str = memory::alloc<uint32_t>(length);

		utf8::utf8to32(m_BufferPtr.ptr(), m_BufferPtr.ptr() + m_BufferPtr.get_range().length(), utf32_str);

		for(size_t i = 0; i < length; ++i)
#if FREYA_USE_ICU
			utf32_str[i] = u_toupper(utf32_str[i]);
#else
		{}
#endif

		string out(m_BufferPtr.get_range().length());

		// It is safe to use const_cast here, despite it is ugly
		// We do guarantee, that the hash will be recalculated correctly
		utf8::utf32to8(utf32_str, utf32_str + length, const_cast<char*>(out.m_BufferPtr.ptr()));

		memory::dealloc(utf32_str);
		return out;
	}

	core::string string::to_lower() const
	{
		size_t length = this->length();
		if(length == 0)
			return *this;

		uint32_t * utf32_str = memory::alloc<uint32_t>(length);

		utf8::utf8to32(m_BufferPtr.ptr(), m_BufferPtr.ptr() + m_BufferPtr.get_range().length(), utf32_str);

		for(size_t i = 0; i < length; ++i)
#if FREYA_USE_ICU
			utf32_str[i] = u_tolower(utf32_str[i]);
#else
		{}
#endif
		string out(m_BufferPtr.get_range().length());

		// It is safe to use const_cast here, despite it is ugly
		// We do guarantee, that the hash will be recalculated correctly
		utf8::utf32to8(utf32_str, utf32_str + length, const_cast<char*>(out.m_BufferPtr.ptr()));

		memory::dealloc(utf32_str);
		return out;
	}

	core::string string::replace( const range& r, const string& str ) const
	{
		if(r.empty())
			return *this;
		
		FREYA_SUPPORT_ASSERT(r.length() <= m_BufferPtr.get_range().length(),"Invalid range");

		range r_before ( 0,  r.begin() );
		range r_after  ( r.end(), m_BufferPtr.get_range().length());

		// Calculate amount of memory to use
		size_t str_size = str.m_BufferPtr.get_range().length();

		size_t bytes_used = r_before.length() + str_size + r_after.length();

		string	out(bytes_used);

		if(!r_before.empty())
			out.m_BufferPtr.write_buffer(substr(r_before).m_BufferPtr.ptr(),0,r_before.length());

		out.m_BufferPtr.write_buffer(str.m_BufferPtr.ptr(),r_before.length(), str_size);

		if(!r_after.empty())
			out.m_BufferPtr.write_buffer(substr(r_after).m_BufferPtr.ptr(), r_before.length() + str_size, r_after.length());

		return out;
	}

} // namespace core