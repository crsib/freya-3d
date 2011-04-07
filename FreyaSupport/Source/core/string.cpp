// This file is a part of Freya 3D Engine

#include "core/string.h"

#include <utf8.h>

#include <wctype.h>

namespace core
{
	core::string string::to_upper() const
	{
		size_t length = this->length();
		if(length == 0)
			return *this;

		uint16_t*	utf16_str = reinterpret_cast<uint16_t*>(memory::alloc( ( length + 1 )*sizeof( uint16_t ) ) );

		utf8::utf8to16(m_BufferPtr.ptr(), m_BufferPtr.ptr() + m_BufferPtr.get_range().length(), utf16_str);

		for(size_t i = 0; i < length; ++i)
			utf16_str[i] = towupper(utf16_str[i]);

		string out(m_BufferPtr.get_range().length());

		// It is safe to use const_cast here, despite it is ugly
		// We do guarantee, that the hash will be recalculated correctly
		utf8::utf16to8(utf16_str, utf16_str + length, const_cast<char*>(out.m_BufferPtr.ptr()));

		memory::dealloc(utf16_str);
		return out;
	}

	core::string string::to_lower() const
	{
		size_t length = this->length();
		if(length == 0)
			return *this;

		uint16_t*	utf16_str = reinterpret_cast<uint16_t*>(memory::alloc( ( length + 1 )*sizeof( uint16_t ) ) );

		utf8::utf8to16(m_BufferPtr.ptr(), m_BufferPtr.ptr() + m_BufferPtr.get_range().length(), utf16_str);

		for(size_t i = 0; i < length; ++i)
			utf16_str[i] = towlower(utf16_str[i]);

		string out(m_BufferPtr.get_range().length());

		// It is safe to use const_cast here, despite it is ugly
		// We do guarantee, that the hash will be recalculated correctly
		utf8::utf16to8(utf16_str, utf16_str + length, const_cast<char*>(out.m_BufferPtr.ptr()));

		memory::dealloc(utf16_str);
		return out;
	}
} // namespace core