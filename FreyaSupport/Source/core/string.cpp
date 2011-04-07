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
			utf32_str[i] = u_toupper(utf32_str[i]);

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
			utf32_str[i] = u_tolower(utf32_str[i]);

		string out(m_BufferPtr.get_range().length());

		// It is safe to use const_cast here, despite it is ugly
		// We do guarantee, that the hash will be recalculated correctly
		utf8::utf32to8(utf32_str, utf32_str + length, const_cast<char*>(out.m_BufferPtr.ptr()));

		memory::dealloc(utf32_str);
		return out;
	}
} // namespace core