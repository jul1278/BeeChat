#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <cstdio>
#include <stdarg.h>

#include "testmain.h"


//-----------------------------------------------------------------------------
#if defined(_WIN32) && !defined(__FORCE_ANSI__)
const char* DEFAULT = "";
const char* BLACK   = "";
const char* RED     = "";
const char* GREEN   = "";
const char* YELLOW  = "";
const char* BLUE    = "";
const char* MAGENTA = "";
const char* CYAN    = "";

const char* DGREY   = "";
const char* BRED    = "";
#else
// ANSI colour codes
//   These strings are interpreted by the terminal as a change colour command
const char* DEFAULT = "\033[0m";
const char* BLACK   = "\033[30m";
const char* RED     = "\033[31m";
const char* GREEN   = "\033[32m";
const char* YELLOW  = "\033[33m";
const char* BLUE    = "\033[34m";
const char* MAGENTA = "\033[35m";
const char* CYAN    = "\033[36m";

const char* DGREY   = "\033[1;30m";
const char* BRED    = "\033[1;31m";
#endif

const size_t CSTR_BUF_SIZE = 1024;


const std::string formatString(const char *fmt, ...)
{
    char buf[CSTR_BUF_SIZE+1];
    memset(buf, 0, CSTR_BUF_SIZE+1);

    std::string result("FAILED");
    if (fmt)
    {
        va_list argptr;
        va_start(argptr, fmt);
        result = formatString(fmt, argptr);
        va_end(argptr);
    }

    return result;
}


const std::string formatString(const char *fmt, va_list args)
{
    char buf[CSTR_BUF_SIZE+1];
    memset(buf, 0, CSTR_BUF_SIZE+1);

    if (fmt)
    {
        int rc = std::vsnprintf(buf, CSTR_BUF_SIZE, fmt, args);
        if (rc <= 0)
        {
            strncpy(buf, "FAILED", CSTR_BUF_SIZE);
        }
        else if (rc >= CSTR_BUF_SIZE)
        {
            // it was oversize
            strncpy(buf + (CSTR_BUF_SIZE - 3), "...", 3);
        }
    }
    else
    {
        return std::string("");
    }

    return std::string(buf);
}

/*
inline std::ostream& operator<< (std::ostream& os, const bool val) {
    return os << (val ? "true" : "false");
}
*/
const std::string TestUtils::dumpArgs(const int num, const char *args[])
{
    if (num < 1)
    {
        return std::string("");
    }

    std::stringstream ss;
    ss << "{";
    for (int ii = 0; ii < num; ++ii)
    {
        if (ii > 0)
        {
            ss << ", ";
        }
        ss << "\"" << args[ii] << "\"";
    }
    ss << "}";

    return ss.str();
}
