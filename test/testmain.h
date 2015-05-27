
#ifndef __ENB241__TESTMAIN_H__
#define __ENB241__TESTMAIN_H__

#include <string>
#include <string.h>
#include <cstdlib>
#include <sstream>
#include <stdarg.h>

extern const char* DEFAULT;
extern const char* BLACK;
extern const char* RED;
extern const char* GREEN;
extern const char* YELLOW;
extern const char* BLUE;
extern const char* MAGENTA;
extern const char* CYAN;

extern const char* DGREY;

extern const char* BRED;

extern const size_t CSTR_BUF_SIZE;

extern const std::string formatString(const char *fmt, ...);
extern const std::string formatString(const char *fmt, va_list args);


//-----------------------------------------------------------------------------
void testMessages();
void testSettings();


namespace TestUtils
{
    class ErrRedirect_t
    {
    public:
        ErrRedirect_t(std::stringstream &ss)
        : m_pOldBuf(std::cerr.rdbuf(ss.rdbuf()))
        { }

        ErrRedirect_t(std::streambuf * new_buffer)
        : m_pOldBuf(std::cerr.rdbuf(new_buffer))
        { }

        ~ErrRedirect_t()
        {
            std::cerr.rdbuf(m_pOldBuf);
        }

    private:
        std::streambuf *m_pOldBuf;
    };


    inline bool dispPass(bool pass)
    {
        if (pass) std::cout << GREEN << "PASS" << DEFAULT;
        else      std::cout << RED   << "FAIL" << DEFAULT;
        return pass;
    }


    inline const char * torf(const bool val)
    {
        static const char *tStr = "true";
        static const char *fStr = "false";

        return (val ? tStr : fStr);
    }

    const std::string dumpArgs(const int num, const char *args[]);

    template <typename T>
    inline void report(const T &expected, const T &got, const std::stringstream &errBuf)
    {
        if (!dispPass(got == expected))
        {
            std::cout << std::flush << "\tExpected: [" << YELLOW << expected << DEFAULT << "], "
                      << "got [" << YELLOW << got << DEFAULT << "]";
            if (!errBuf.str().empty())
            {
                std::cout << "\tErr buf: " << RED << errBuf.str() << DEFAULT;
            }
        }
        std::cout << std::endl << std::flush;
    }
};

#endif  // __ENB241__TESTMAIN_H__
