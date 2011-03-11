#include <iostream>
#include <fstream>
#include <streambuf>

namespace core
{
	
namespace __internal
{

template <class charT, class traits = std::char_traits<charT> >
class basic_freya_buf : public std::basic_streambuf<charT, traits>
{
public:
    typedef charT char_type;
    typedef typename traits::int_type int_type;
    typedef typename traits::pos_type pos_type;
    typedef typename traits::off_type off_type;
    typedef traits traits_type;
    typedef std::basic_streambuf<charT, traits> streambuf_type;

private:
    streambuf_type *m_sbuf1;
    streambuf_type *m_sbuf2;
	streambuf_type *m_sbuf3;
    char_type *m_buffer;

    enum {BUFFER_SIZE = 8192 / sizeof(char_type)};

public:
    basic_freya_buf(streambuf_type *sbuf1, streambuf_type *sbuf2,streambuf_type *sbuf3)
        : m_sbuf1(sbuf1), m_sbuf2(sbuf2),m_sbuf3(sbuf3), m_buffer(new char_type[BUFFER_SIZE])
    {
        setp(m_buffer, m_buffer + BUFFER_SIZE);
    }//constructor

    ~basic_freya_buf()
    {
        this->pubsync();
        delete[] m_buffer;
    }//destructor

protected:
    virtual int_type overflow(int_type c = traits_type::eof())
    {
        // empty our buffer into m_sbuf1 and m_sbuf2
        std::streamsize n = static_cast<std::streamsize>(this->pptr() - this->pbase());
        std::streamsize size1 = m_sbuf1->sputn(this->pbase(), n);
        std::streamsize size2 = m_sbuf2->sputn(this->pbase(), n);
		std::streamsize size3 = m_sbuf3->sputn(this->pbase(), n);
        if (size1 != n || size2 != n || size3 != n)
            return traits_type::eof();

        // reset our buffer
        setp(m_buffer, m_buffer + BUFFER_SIZE);

        // write the passed character if necessary
        if (!traits_type::eq_int_type(c, traits_type::eof()))
        {
            traits_type::assign(*(this->pptr()), traits_type::to_char_type(c));
            this->pbump(1);
        }//if

        return traits_type::not_eof(c);
    }//overflow

    virtual int sync()
    {
        // flush our buffer into m_sbuf1 and m_sbuf2
        int_type c = overflow(traits_type::eof());

        // checking return for eof.
        if (traits_type::eq_int_type(c, traits_type::eof()))
            return -1;

        // flush m_sbuf1 and m_sbuf2
        if (m_sbuf1->pubsync() == -1 || m_sbuf2->pubsync() == -1)
            return -1;

        return 0;
    }//sync
};//basic_teebuf

typedef basic_freya_buf<char>    freya_buf;

}
}