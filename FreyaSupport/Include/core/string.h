/* File		: core/string.h
 * Author	: Dmitry Vedenko
 * E-Mail	: dmitry.vedenko@freya3d.org
 *
 * This file is a part of Freya3D Engine.
 */

#ifndef string_h__
#define string_h__

#include "core/memory/MemoryArena.h"
#include "atomic/atomic.h"
#include "integer.h"

namespace core
{
	//! This class encapsulates futures, required for easy and efficient manipulation with string data
	/*!
	 * This class provides various methods, that are usefull with strings. 
	 * The implementation of this class is targeting efficient memory management,
	 * which leads to low footprint, almost free copy operators and rather expensive 
	 * modification of strings, as most modifications lead to memory allocation and copying.
	 * For this reason, most of string class methods (except operator = / operator +=) are 
	 * constant and return the copy of the string.
	 * Second design limitation is that string assumes, that it's data is represented in normalized
	 * UTF-8 encoding. For this reason the iterator concept from STL was replaced with range concept, 
	 * as one char could be expressed in up to 4 bytes. Also, for performance reasons, 
	 * internal implementation does not check
	 * UTF-8 correctness and assumes, that the string is normalized form (i.e. the shortest representation
	 * for the character is preferred). For convenience, string provides UTF-32 iterator.
	 */

	class FREYA_SUPPORT_EXPORT string
	{
	public:
		//! Not a valid position in string
		static const size_t npos = -1;
		//! This class represents a range within a string
		/*! 
		 * This class is kind of analogue of STL string iterator with the following exceptions, despite
		 * it does not provide direct access to string data. More over, it simultaneously provides access for
		 * both begin and end of the corresponding interval.
		 */
		class FREYA_SUPPORT_EXPORT range
		{
			size_t	m_Begin;
			size_t	m_End;
		public:
			//! Constructs an empty range
			range() throw(): m_Begin(0), m_End(0) {}
			//! Construct a range
			/*! 
			 * Construct not empty range
			 * \param begin is a first index of the range
			 * \param end is an one-past-last index of the range
			 */
			range(size_t begin, size_t end) throw() : m_Begin(begin), m_End(end) { FREYA_SUPPORT_ASSERT(begin < end || (begin == 0 && end == 0),"wrong parameters list"); }
			//! Copy constructor
			range(const range& rhs) throw() : m_Begin(rhs.m_Begin), m_End(rhs.m_End) {}
			//! operator =
			range& operator = (const range& rhs) { m_Begin = rhs.m_Begin; m_End = rhs.m_End; return *this;}

			bool operator == (const range& rhs ) const { return m_Begin == rhs.m_Begin && m_End == rhs.m_End; }
			bool operator != (const range& rhs ) const { return m_Begin != rhs.m_Begin || m_End != rhs.m_End; }

			size_t begin() const { return m_Begin; }
			size_t end() const { return m_End; }
			//! Length of the range
			size_t  length() const { return m_End - m_Begin; }
			//! Check, if range is empty
			bool	empty() const { return m_Begin == m_End; }
		};

		//! Default constructor
		/*! 
		 * Constructs an empty string
		 */
		string() {}
		//! Destructor
		~string() {}
		//! Copy constructor
		string(const string& rhs) : m_BufferPtr(rhs.m_BufferPtr) {}
		//! Construct a substring
		string(const string& rhs, const range& r) : m_BufferPtr(rhs.m_BufferPtr) 
		{
			FREYA_SUPPORT_ASSERT(r.begin() < m_BufferPtr.get_range().end(),"Invalid range");
			FREYA_SUPPORT_ASSERT(r.end() <= m_BufferPtr.get_range().end(),"Invalid range");
			m_BufferPtr.set_range(r);
		}
		//! Construct from a C-string
		string(const char* c_str) : m_BufferPtr(data_buffer_ptr(c_str)) {}
		//! Construct from a C-string with a given hash value
		string(const char* c_str, uint32_t hash_value) : m_BufferPtr(data_buffer_ptr(c_str, hash_value)) {}
		string& operator = (const string& rhs) { m_BufferPtr = rhs.m_BufferPtr; return *this;}

		//! Get the corresponding data. (Possibly not 0 terminated)
		const char*		data() const { return m_BufferPtr.ptr(); }
		//! Get corresponding zero terminated string
		const char*		c_str() const  { return m_BufferPtr.null_terminated_string(); }
		//! Get the strings length with respect of UTF8
		size_t			length() const 
		{ 
			size_t l = 0;
			if(m_BufferPtr.get_range().length() == 0)
				return l;
			for( size_t i = m_BufferPtr.get_range().begin(); i < m_BufferPtr.get_range().end(); ++i )
				if( (m_BufferPtr[i] & 0xC0) != 0x80 )
					++l;
			return l; 
		}
		//! Check, if the string is empty
		bool			empty() const { return m_BufferPtr.get_range().empty(); }

		//! Get the string hash value
		uint32_t		hash() const { return m_BufferPtr.hash(); }

		//Comparison operators

		//! Check, if two strings are equal
		bool			operator == (const string& rhs) const 
		{ return m_BufferPtr.equals(rhs.m_BufferPtr); }
		//! Check, if the string is equal to the c-string
		bool			operator == (const char* rhs) const { return *this == string(rhs); }
		//! Check, if two strings are not equal
		bool			operator != (const string& rhs) const
		{ return !m_BufferPtr.equals(rhs.m_BufferPtr); }
		//! Check, if string differs from given c-string
		bool			operator != (const char* rhs) const { return * this != string(rhs); }
		//! Check, if the first string is lexicographically less, then a second string
		bool			operator < (const string& rhs) const { return m_BufferPtr.compare(rhs.m_BufferPtr) == -1; }
		//! Check, if the string is lexicographically less, then a c-string
		bool			operator < (const char* rhs) const { return *this < string(rhs); }
		//! Check, if the first string is lexicographically greater, then the second
		bool			operator > (const string& rhs) const { return rhs < *this; }
		//! Check, if the string is lexicographically greater, then a c-string
		bool			operator > (const char* rhs ) const { return string(rhs) < *this; }

		//! Check, if the first string is lexicographically not less, then a second string
		bool			operator <= (const string& rhs) const { return m_BufferPtr.compare(rhs.m_BufferPtr) != 1; }
		//! Check, if the string is lexicographically not less, then a c-string
		bool			operator <= (const char* rhs) const { return *this <= string(rhs); }
		//! Check, if the first string is lexicographically not greater, then the second
		bool			operator >= (const string& rhs) const { return rhs <= *this; }
		//! Check, if the string is lexicographically not greater, then a c-string
		bool			operator >= (const char* rhs ) const { return string(rhs) <= *this; }

		// String concatenation
		//! Concatenate two strings
		string			operator + (const string& rhs) const
		{
			size_t lhs_len = m_BufferPtr.get_range().length(), rhs_len = rhs.m_BufferPtr.get_range().length();
			string res( lhs_len + rhs_len);
			res.m_BufferPtr.write_buffer(m_BufferPtr.ptr(),0,lhs_len);
			res.m_BufferPtr.write_buffer(rhs.m_BufferPtr.ptr(),lhs_len,rhs_len);
			return res;
		}
		//! Concatenate two strings
		string&			operator += (const string& rhs) { return (*this = (*this + rhs));}
		//! Concatenate two strings
		string			operator + (const char* rhs) const {return *this + string(rhs); }
		//! Concatenate two strings
		string&			operator += (const char* rhs) { return (*this = (*this + string(rhs)));}

		// Substrings
		//! Get a substring of string
		string			substr(const range& r) const
		{
			FREYA_SUPPORT_ASSERT(r.length() <= m_BufferPtr.get_range().length(),"Invalid range");

			string out(*this);
			out.m_BufferPtr.set_range(range(r.begin() + m_BufferPtr.get_range().begin(), r.end() + m_BufferPtr.get_range().begin()));
			return out;
		}
		//! Get a substring of string starting from idx
		string			substr(size_t idx) const 
		{
			FREYA_SUPPORT_ASSERT(idx < m_BufferPtr.get_range().end() - m_BufferPtr.get_range().begin(), "Invalid idx");
			return substr(range(idx, m_BufferPtr.get_range().end()));
		}
		//! Get a substring of string
		string			substr(size_t s, size_t e) const
		{
			return substr(range(s,e));
		}

		//! Search for the first occurrence specific sub string
		/*!
		 * Search for the first occurrence of specific sub string in a string in [from, end)
		 * \param substring is a sub string to search
		 * \param from is the position to start the search from
		 * \return range in intial string such as this->substr(range) == substring or an empty range, if substring was not found
		 */
		range			find(const string& substring, size_t from = 0) const
		{
			return m_BufferPtr.find(substring.m_BufferPtr, from);
		}

		//! Search for the first occurrence specific sub string
		/*!
		 * Search for the first occurrence of specific sub string in a string in [from, end)
		 * \param substring is a sub string to search
		 * \param from is the position to start the search from
		 * \return range in intial string such as this->substr(range) == substring or an empty range, if substring was not found
		 */
		range			find(const char* substring, size_t from = 0) const
		{
			return find(string(substring),from);
		}

		//! Search for the last occurrence of specific sub string
		/*!
		 * Search for the last occurrence of specific sub string in a string in [begin, from)
		 * \param substring is a sub string to search
		 * \param from is the position to start the search up to
		 * \return range in intial string such as this->substr(range) == substring or an empty range, if substring was not found
		 */
		range			rfind(const string& substring, size_t from = npos) const
		{
			return m_BufferPtr.rfind(substring.m_BufferPtr, from == npos ? 0 : m_BufferPtr.get_range().length() - from - 1);
		}

		//! Search for the last occurrence of specific sub string
		/*!
		 * Search for the last occurrence of specific sub string in a string in [begin, from)
		 * \param substring is a sub string to search
		 * \param from is the position to start the search up to
		 * \return range in intial string such as this->substr(range) == substring or an empty range, if substring was not found
		 */
		range			rfind(const char* substring, size_t from = npos) const
		{
			return rfind(string(substring),from);
		}
		
		//! Replace a range in the string
		/*!
		 * Replace a range in the string with given substring
		 * \param r range to replace
		 * \param str string to replace with
		 * \return modified string
		 */
		string			replace(const range& r, const string& str) const;
		
		//! Replace a range in the string
		/*!
		 * Replace a range in the string with given substring
		 * \param r range to replace
		 * \param str string to replace with
		 * \return modified string
		 */
		string			replace(const range& r, const char* str) const
		{ return replace(r, string(str)); }

		//! Search for a substring and replace it
		/*! 
		 * Search for a substring and replace it with a given substring
		 * \param search_for is a substring to search for
		 * \param replace_with is a substring to replace with
		 * \return modified string
		 */
		string			replace(const string& search_for, const string& replace_with) const
		{
			return replace(find(search_for), replace_with);
		}

		//! Search for a substring and replace it
		/*! 
		 * Search for a substring and replace it with a given substring
		 * \param search_for is a substring to search for
		 * \param replace_with is a substring to replace with
		 * \return modified string
		 */
		string			replace(const char* search_for, const char* replace_with) const
		{
			return replace(find(search_for), replace_with);
		}

		//! Search for a substring and replace it
		/*! 
		 * Search for a substring and replace it with a given substring
		 * \param search_for is a substring to search for
		 * \param replace_with is a substring to replace with
		 * \return modified string
		 */
		string			replace(const string& search_for, const char* replace_with) const
		{
			return replace(find(search_for), replace_with);
		}

		//! Search for a substring and replace it
		/*! 
		 * Search for a substring and replace it with a given substring
		 * \param search_for is a substring to search for
		 * \param replace_with is a substring to replace with
		 * \return modified string
		 */
		string			replace(const char* search_for, const string& replace_with) const
		{
			return replace(find(search_for), replace_with);
		}

		//! Convert string to uppercase
		/*!
		 * Retrieve UPPER CASE version of the string. This methods has significant runtime overhead,
		 * as it requires the string to be converted into UTF-32 for correct localization support
		 */
		string			to_upper() const;
		//! Convert string to lowercase
		/*!
		 * Retrieve lower case version of the string. This methods has significant runtime overhead,
		 * as it requires the string to be converted into UTF-32 for correct localization support
		 */
		string			to_lower() const;

		//Memory management routines 
		//! Overloaded new operator
		static void* operator new(size_t sz) { return memory::alloc(sz,memory::CLASS_POOL); }
		//! Overloaded new [] operator
		static void* operator new [] (size_t sz) { return memory::alloc(sz,memory::CLASS_POOL); }
		//! Overloaded delete operator
		static void	 operator delete(void* p) { memory::dealloc(p, memory::CLASS_POOL); }
		//! Overloaded delete [] operator
		static void  operator delete[] (void* p) { memory::dealloc(p, memory::CLASS_POOL); }
	private:
		string(size_t sz) : m_BufferPtr(sz) {}

		static uint32_t		calculate_hash(const uint8_t* str, size_t max_l, size_t& l)
		{
			l = 0;
			//Seed value is taken from Sergey Makeyevs reflection source code
			uint32_t hash = 1315423911;
			const uint8_t * char_ptr = str;
			while (*char_ptr && (l < max_l))
			{
				uint8_t c = *char_ptr++;
				hash ^= ((hash << 5) + c + (hash >> 2));
				l++;
			}
			return hash;
		}
		// Data buffer structure
		struct	FREYA_SUPPORT_EXPORT data_buffer 
		{
			// Pointer to the buffer structure
			uint8_t*	data_ptr;
			// Size of the buffer in bytes
			// Size of 0 means, that the buffer is not owned by the object
			size_t		buffer_size;
			// Use count of the buffer
			atomic::atomic<uint32_t> use_count;
			// Hash value for the string
			mutable uint32_t	hash; // Initialized to 0
			// Hashed length
			mutable uint32_t	hashed_length;

			data_buffer() throw() : data_ptr(NULL), buffer_size(0), use_count(0), hash(0), hashed_length(0)
			{ }

			data_buffer(size_t size) throw() : buffer_size(size), use_count(1), hash(0), hashed_length(0)
			{ data_ptr = reinterpret_cast<uint8_t*>( memory::alloc( size, memory::STL_POOL ) ); data_ptr[size - 1] = 0; }

			data_buffer(const char* ptr) : 
			data_ptr(reinterpret_cast<uint8_t*>(const_cast<char*>(ptr))), buffer_size(0), use_count(1), hash(0), hashed_length(0)
			{ }
			
			data_buffer(const char* ptr, uint32_t hash_val, size_t l) : 
			data_ptr(reinterpret_cast<uint8_t*>(const_cast<char*>(ptr))), buffer_size(0), use_count(1), hash(hash_val), hashed_length(l)
			{ }

			~data_buffer() throw()
			{ 
				if( buffer_size && data_ptr)
				{
					FREYA_SUPPORT_ASSERT( use_count == 0,"Data is still owned by some class" );
					memory::dealloc(data_ptr, memory::STL_POOL);
					data_ptr = NULL;
					buffer_size = 0;
					use_count = 0;
				}
			}

			static void* operator new(size_t sz) { return memory::alloc(sz,memory::STL_POOL); }
			static void	 operator delete(void* p) { memory::dealloc(p, memory::STL_POOL); }

			uint32_t	get_hash() const
			{
				if(data_ptr)
				{
					if(hash == 0)
					{
						hash = calculate_hash(data_ptr,buffer_size,hashed_length);
					}

					return hash;
				}
				return 0;
			}

			void		write_buffer(const char* source, size_t offset, size_t sz) 
			{
				FREYA_SUPPORT_ASSERT(source, "source should not be empty");
				FREYA_SUPPORT_ASSERT((sz + offset) <= reinterpret_cast<size_t>(data_ptr + buffer_size), "source is larger the the buffer size");
				FREYA_SUPPORT_ASSERT(use_count == 1, "source is not uniquely owned");
				if(sz == 0)
					return;
				memcpy(data_ptr + offset, source, sz);
				hash = 0; //mark to rehash
			}

			data_buffer* clone_and_resize(const range& r)
			{
				FREYA_SUPPORT_ASSERT(buffer_size == 0 || use_count.load() > 1, "Could not clone uniquely owned buffer");
				FREYA_SUPPORT_ASSERT(buffer_size <= r.begin(), "Invalid range");
				FREYA_SUPPORT_ASSERT(r.length(), "Empty range");
			
				data_buffer* new_buffer = new data_buffer(r.length() + 1);

				size_t copy_size;
				if(data_ptr + buffer_size >= data_ptr + r.end())
					copy_size = r.length();
				else
					copy_size = buffer_size - r.begin();

				memcpy(new_buffer->data_ptr, data_ptr + r.begin(), copy_size);

				if(r.begin() == 0 && buffer_size <= r.length())
					new_buffer->hash = hash;

				--use_count;
				return new_buffer;
			}
		private:
			data_buffer& operator = (data_buffer const &);
			data_buffer(data_buffer const &);
		}; // struct data_buffer
		// Wrapper, emulating intrusive "shared pointer"

		class	FREYA_SUPPORT_EXPORT data_buffer_ptr
		{
			range			r;
			data_buffer*	buffer;
			mutable uint32_t		hash_value;
		public:
			data_buffer_ptr() throw() : buffer (NULL),hash_value(0) {}
			data_buffer_ptr(size_t sz) throw() : r(0,sz),buffer(new data_buffer(sz + 1)),hash_value(0) {}
			data_buffer_ptr(const char* ptr) throw() 
				: r(0,strlen(ptr)),buffer(new data_buffer(ptr) ),hash_value(0) {}
			data_buffer_ptr(const char* ptr, uint32_t hash_val) throw() 
				: r(0,strlen(ptr)), buffer(new data_buffer(ptr,hash_val,r.length()) ),hash_value(hash_val) {}
			data_buffer_ptr(const data_buffer_ptr& rhs) : r(rhs.r),buffer(rhs.buffer), hash_value(rhs.hash_value)
			{
				if(buffer)
				{
					++buffer->use_count;
				}
			}
			data_buffer_ptr& operator = (const data_buffer_ptr& rhs)
			{
				if(buffer)
				{
					--buffer->use_count;
					if(buffer->use_count == 0)
						delete buffer;
				}

				buffer = rhs.buffer;
				r = rhs.r;
				hash_value = rhs.hash_value;
				if(buffer)
				{
					++buffer->use_count;
				}
				return *this;
			}

			~data_buffer_ptr()
			{
				if(buffer)
				{
					--buffer->use_count;
					if(buffer->use_count == 0)
						delete buffer;
				}
			}

			void	clone_and_resize(const range& _r) 
			{
				if(buffer && buffer->use_count.load() > 1)
				{
					if(r != _r)
						hash_value = 0;
					buffer = buffer->clone_and_resize(_r);
					r = range(0,r.length());
				}
			}

			void	write_buffer(const char* source, size_t offset, size_t sz) 
			{
				if(buffer && buffer->data_ptr)
				{
					if(buffer->buffer_size && buffer->use_count != 1)
						clone_and_resize(r);
					buffer->write_buffer(source,offset + r.begin(),sz);
				}
			}

			void			set_range(const range& _r) { if(r != _r) {r = _r; hash_value = 0;} }
			const range&	get_range() const { return r; }

			uint8_t	operator [] (size_t i) const 
			{
				if(buffer && buffer->data_ptr)
				{
					FREYA_SUPPORT_ASSERT(i < r.length(),"Invalid index");
					return buffer->data_ptr[i + r.begin()];
				}
				return 0;
			}

			uint32_t	hash() const
			{
				if(hash_value == 0)
				{
					if(buffer && buffer->data_ptr && r.length())
					{
						size_t tmp;
						if(r.begin() == 0 && r.length() == buffer->hashed_length)
							return (hash_value = buffer->get_hash());
						else if(hash_value == 0)
						{
							if(r.begin() == 0)
							{
								hash_value = buffer->get_hash();
								if(r.length() == buffer->hashed_length)
									return hash_value;
							}
							hash_value = calculate_hash(buffer->data_ptr + r.begin(), r.length(),tmp);
						}
					}
				}
				return hash_value;
			} // uint32_t hash()

			const char*		ptr() const
			{
				static const size_t __ = 0;
				if(buffer && buffer->data_ptr)
					return reinterpret_cast<char*>(buffer->data_ptr + r.begin());
				else
					return reinterpret_cast<const char*>(&__);
			}

			const char*		null_terminated_string() const
			{
				if(buffer && buffer->data_ptr )
				{
					if( buffer->data_ptr[r.end()] == 0 )
						return reinterpret_cast<char*>(buffer->data_ptr + r.begin());
					else
					{	
						//This looks bad, but we do not actually change the string
						//We just create a deep copy of it internal representation
						const_cast<data_buffer_ptr*>(this)->clone_and_resize(r); //This will zero terminate the string without actually changing it
						return reinterpret_cast<char*>(buffer->data_ptr + r.begin());
					}
				}
				return ptr();
			} // const char* null_terminated string

			bool		equals(const data_buffer_ptr& rhs) const
			{
				if((r == rhs.r && buffer == rhs.buffer) || (r.length() == 0 && rhs.r.length() == 0)) 
					return true;

				if(buffer == NULL || buffer->data_ptr == NULL || rhs.buffer == NULL || rhs.buffer->data_ptr == NULL)
					return false;

				//if(buffer->data_ptr == rhs.buffer->data_ptr)
				//	return true;
				
				if((r.length() == rhs.r.length()) && (hash() == rhs.hash()))
					return (
					strncmp(
					reinterpret_cast<char*>(buffer->data_ptr + r.begin()),
					reinterpret_cast<char*>(rhs.buffer->data_ptr + rhs.r.begin()),
					r.length() < rhs.r.length() ? r.length() : rhs.r.length()) == 0);
				else 
					return false;
			} //bool equals

			int	compare(const data_buffer_ptr& rhs) const //Acts as strcmp
			{
				if(buffer == rhs.buffer || (r.length() == 0 && rhs.r.length() == 0)) 
					return 0;
				else if((buffer == NULL || buffer->data_ptr == NULL) && (rhs.buffer && rhs.buffer->data_ptr && rhs.r.length())) //Lhs is empty
					return -1;
				else if(buffer && buffer->data_ptr && rhs.buffer && rhs.buffer->data_ptr) //Neither are empty
					return strncmp(
					reinterpret_cast<char*>(buffer->data_ptr + r.begin()),
					reinterpret_cast<char*>(rhs.buffer->data_ptr + rhs.r.begin()),
					r.length() < rhs.r.length() ? r.length() : rhs.r.length());
				else //Rhs is empty
					return 1;

			} // int compare

			range		find(const data_buffer_ptr& other, size_t starting_from) const //
			{
				if(other.r.length() > r.length() || other.r.length() == 0 || r.length() == 0)  //Substr is longer then search string or some of the ops are empty
					return range();
				
				if(other.r.length() == r.length() && starting_from == 0) //Strings are equal
					return equals(other) ? r : range();

				FREYA_SUPPORT_ASSERT(starting_from < r.length(), "Invalid search start position");
				
				const uint8_t* first1 = buffer->data_ptr + r.begin() + starting_from; 
				const uint8_t* start_it = first1;
				const uint8_t* last1  = buffer->data_ptr + r.end() - other.r.length() + 1;

				const uint8_t* first2 = other.buffer->data_ptr + other.r.begin();
				const uint8_t* last2  = other.buffer->data_ptr + other.r.end();

				while(first1 != last1)
				{
					const uint8_t* it1 = first1, *it2 = first2;
					while(*it1 == *it2)
					{
						++it1; ++it2;
						if(it2 == last2)
							return range(first1 - start_it, it1 - start_it);
					}
					++first1;
				}
				return range();
			} // range find()

			range		rfind(const data_buffer_ptr& other, size_t starting_from) const //
			{
				if(other.r.length() > r.length() || other.r.length() == 0 || r.length() == 0)  //Substr is longer then search string or some of the ops are empty
					return range();

				if(other.r.length() == r.length() && starting_from == 0) //Strings are equal
					return equals(other) ? r : range();

				FREYA_SUPPORT_ASSERT(starting_from < r.length(), "Invalid search start position");

				

				const uint8_t* first1 = buffer->data_ptr + r.end() - starting_from - 1 - other.r.length(); 
				//const uint8_t* start_it = first1;
				const uint8_t* last1  = buffer->data_ptr + r.begin();

				const uint8_t* first2 = other.buffer->data_ptr + other.r.begin();
				const uint8_t* last2  = other.buffer->data_ptr + other.r.end();

				while(first1 >= last1)
				{
					const uint8_t* it1 = first1, *it2 = first2;
					while(*it1 == *it2)
					{
						++it1; ++it2;
						if(it2 == last2)
							return range(first1 - last1, it1 - last1);
					}
					--first1;
				}
				return range();
			}// range rfind
		}; // data_buffer_ptr

		data_buffer_ptr	m_BufferPtr;
	};
} // namespace core

#endif // string_h__
