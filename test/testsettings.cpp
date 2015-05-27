#include <iostream>
#include <string>

#include <BeeChatException.h>
#include <settings.h>

#include "testmain.h"


namespace testDefaults
{
    inline void test()
    {
        std::stringstream cerrBuf;
        TestUtils::ErrRedirect_t redir(cerrBuf);
        std::cout << "Settings (\"" << Settings::DEFAULT_USERNAME << "\", \""
                  << Settings::DEFAULT_ADDRESS << "\", "
                  << TestUtils::torf(Settings::DEFAULT_ISSERVER) << ", "
                  << Settings::DEFAULT_PORT << "): " << std::endl;
        try
        {
            Settings &settings = Settings::get();

            std::string uname = settings.username();
            std::cout << "  username: " << uname << " ";
            TestUtils::report(std::string(Settings::DEFAULT_USERNAME), uname, cerrBuf);

            std::string address = settings.serverAddress();
            std::cout << "   address: " << address << " ";
            TestUtils::report(std::string(Settings::DEFAULT_ADDRESS), address, cerrBuf);

            bool isSvr = settings.isServer();
            std::cout << "   server?: " << TestUtils::torf(isSvr) << " ";
            TestUtils::report(Settings::DEFAULT_ISSERVER, isSvr, cerrBuf);

            unsigned short port = settings.port();
            std::cout << "      port: " << address << " ";
            TestUtils::report(Settings::DEFAULT_PORT, port, cerrBuf);
        }
        catch (...)
        {
            std::cout << RED << "FAIL: Unhandled exception" << DEFAULT << std::endl;
        }
    }

    // pass in a switch=value string and return the value
    void run()
    {
        std::cout << YELLOW << "Settings::Settings(...)" << DEFAULT << std::endl;
        test();
        std::cout << std::endl;
    }
};

namespace testGetArgValue
{
    inline void test(const std::string &arg, const std::string &expected)
    {
        std::stringstream cerrBuf;
        TestUtils::ErrRedirect_t redir(cerrBuf);
        std::cout << "Parse Arg Value (" << arg << "): ";
        try
        {
            std::string result = Settings::getArgValue(arg);
            std::cout << result << " ";
            TestUtils::report(expected, result, cerrBuf);
        }
        catch (...)
        {
            std::cout << RED << "FAIL: Unhandled exception" << DEFAULT << std::endl;
        }
    }


    struct TestPair
    {
        TestPair(const std::string& _arg, const std::string& _expected)
        : arg(_arg), expected(_expected) {}

        std::string arg, expected;
    };

    // pass in a switch=value string and return the value
    void run()
    {
        std::cout << YELLOW << "Settings::getArgValue" << DEFAULT << std::endl;
        TestPair tests[] = {
            TestPair("-test1=result1", "result1"),
            TestPair("-test2:result2", "-test2:result2"),
            TestPair("test3", "test3"),
            TestPair("", ""),
        };
        const size_t numTests = sizeof(tests)/sizeof(TestPair);

        for (int ii = 0; ii < numTests; ++ii)
        {
            const TestPair& testPair(tests[ii]);
            test(testPair.arg, testPair.expected);
        }
        std::cout << std::endl;
    }
};


namespace testValidateUsername
{
    inline void test(const std::string &arg, const ExceptionType eType)
    {
        std::stringstream cerrBuf;
        TestUtils::ErrRedirect_t redir(cerrBuf);
        std::cout << "validateUsername (" << arg << "): ";
        try
        {
            ExceptionType result = eET_none;
            try
            {
                Settings::validateUsername(arg);
            }
            catch (BeeChatException bce)
            {
                // do we expect a failure AND is it the right one
                result = bce.type();
            }
            std::cout << (unsigned int)result << " ";
            TestUtils::report((unsigned int)eType, (unsigned int)result, cerrBuf);
        }
        catch (...)
        {
            std::cout << RED << "FAIL: Unhandled exception" << DEFAULT << std::endl;
        }
    }


    struct TestData
    {
        TestData(const std::string& _arg, const ExceptionType _type)
        : arg(_arg), type(_type) {}

        std::string arg;
        ExceptionType type;
    };

    // ensure that username is composed of allowed characters only - alphanumeric or underscore
    void run()
    {
        std::cout << YELLOW << "Settings::validateUsername" << DEFAULT << std::endl;
        TestData tests[] = {
            TestData("bob", eET_none),          // short name
            TestData("12345678", eET_none),     // max length
            TestData("bill_bo", eET_none),      // underscore
            TestData("DaveM1k3", eET_none),     // upper, lower and numbers

            TestData("", eET_empty_username),            // empty name
            TestData("too_long_name", eET_username_too_long),   // too long
            TestData("bad-char1", eET_username_too_long),
            TestData("bad-ch1", eET_invalid_username_characters),
        };
        const size_t numTests = sizeof(tests)/sizeof(TestData);

        for (int ii = 0; ii < numTests; ++ii)
        {
            const TestData& testData(tests[ii]);
            test(testData.arg, testData.type);
        }
        std::cout << std::endl;
    }
};


    // //ensure the server address is composed of valid characters only - numbers, fullstop, valid dotted IPv4
    // static void validateserverAddress(const std::string& serverAddress);


namespace testValidatePort
{
    inline void test(const unsigned short port, const ExceptionType eType)
    {
        std::stringstream cerrBuf;
        TestUtils::ErrRedirect_t redir(cerrBuf);
        std::cout << "validatePort (" << port << "): ";
        try
        {
            ExceptionType result = eET_none;
            try
            {
                Settings::validatePort(port);
            }
            catch (BeeChatException bce)
            {
                // do we expect a failure AND is it the right one
                result = bce.type();
            }
            std::cout << (unsigned int)result << " ";
            TestUtils::report((unsigned int)eType, (unsigned int)result, cerrBuf);
        }
        catch (...)
        {
            std::cout << RED << "FAIL: Unhandled exception" << DEFAULT << std::endl;
        }
    }


    struct TestData
    {
        TestData(const unsigned short _port, const ExceptionType _type)
        : port(_port), type(_type) {}

        unsigned short port;
        ExceptionType type;
    };

    // ensure that the port is composed of valid characters only - none below 1024
    void run()
    {
        std::cout << YELLOW << "Settings::validatePort" << DEFAULT << std::endl;
        TestData tests[] = {
            TestData(1025, eET_none),          // short name
            TestData(4444, eET_none),     // max length
            TestData(65535, eET_none),      // underscore

            TestData(0, eET_invalid_port),            // empty name
            TestData(1024, eET_invalid_port),   // too long
            TestData(80, eET_invalid_port),
        };
        const size_t numTests = sizeof(tests)/sizeof(TestData);

        for (int ii = 0; ii < numTests; ++ii)
        {
            const TestData& testData(tests[ii]);
            test(testData.port, testData.type);
        }
        std::cout << std::endl;
    }
};



namespace testParse
{
    struct ExpectedResult
    {
        ExpectedResult(const std::string& _uname, const std::string& _addr,
                       bool _svr, const unsigned short _port)
        : username(_uname), address(_addr), isSvr(_svr), port(_port) {}

        ExpectedResult(const ExpectedResult &orig)
        : username(orig.username), address(orig.address), isSvr(orig.isSvr), port(orig.port) {}

        std::string username;
        std::string address;
        bool isSvr;
        unsigned short port;

        friend std::ostream& operator<< (std::ostream& os, const ExpectedResult& results);
    };

    std::ostream& operator<< (std::ostream& os, const ExpectedResult& results)
    {
        std::stringstream ss;
        ss << "[[" << results.username << ", " << results.address << ", ";
        ss << TestUtils::torf(results.isSvr) << ", " << results.port << "]]";
        return os << ss;
    }

    // we need a different output format to display the settings after changes
    const std::string dumpSettings(const Settings& settings)
    {
        std::stringstream ss;
        ss << "[[" << settings.username() << ", " << settings.serverAddress() << ", ";
        ss << TestUtils::torf(settings.isServer()) << ", " << settings.port() << "]]";
        return ss.str();
    }

    struct TestData
    {
        TestData(const int _numArgs, const char *_args[], const ExpectedResult _result, const ExceptionType _type)
        : numArgs(_numArgs), args(_args), result(_result), type(_type) {}

        int numArgs;
        const char ** args;
        ExpectedResult result;
        ExceptionType type;
    };

    inline void test(const TestData &data)
    {
        std::stringstream cerrBuf;
        TestUtils::ErrRedirect_t redir(cerrBuf);
        std::cout << "parse (" << data.numArgs << ", " << TestUtils::dumpArgs(data.numArgs, data.args) << "): " << std::endl;

        try
        {
            Settings& settings = Settings::get();

            ExceptionType result = eET_none;
            try
            {
                settings.parse(data.numArgs, data.args);
            }
            catch (BeeChatException bce)
            {
                // do we expect a failure AND is it the right one
                result = bce.type();
            }
            std::cout << dumpSettings(settings) << std::endl;
            std::cout << "  expected exception: " << (unsigned int)data.type << " ";
            TestUtils::report((unsigned int)data.type, (unsigned int)result, cerrBuf);
            std::cout << "        username: " << data.result.username << " ";
            TestUtils::report(data.result.username, settings.username(), cerrBuf);
            std::cout << "  server address: " << data.result.address << " ";
            TestUtils::report(data.result.address, settings.serverAddress(), cerrBuf);
            std::cout << "     is a server: " << TestUtils::torf(data.result.isSvr) << " ";
            TestUtils::report(data.result.isSvr, settings.isServer(), cerrBuf);
            std::cout << "            port: " << data.result.port << " ";
            TestUtils::report(data.result.port, settings.port(), cerrBuf);
            std::cout << DGREY << "-- end parse test --" << DEFAULT << std::endl;
        }
        catch (...)
        {
            std::cout << RED << "FAIL: Unhandled exception" << DEFAULT << std::endl;
        }
    }

    // Parse settings from command line args
    // ensure that username is composed of allowed characters only - alphanumeric or underscore
    void run()
    {
        std::cout << YELLOW << "Settings::parse" << DEFAULT;
        std::cout << " --> Start settings = " << MAGENTA << dumpSettings(Settings::get()) << DEFAULT << std::endl;

        const char * args1[] = {"-username=bob"};
        const char * args2[] = {"-username=anne", "-address=10.11.12.13"};
        const char * args3[] = {"-username=mark", "-server"};
        const char * args4[] = {"-username=jen", "-port=23456"};

        // IMPORTANT!!!!!!
        // NOTE: The Setttings object is a singleton, so these tests need to allow for the result of the previous test
        TestData tests[] = {
            TestData(1, args1, ExpectedResult("bob", "127.0.0.1", false, 6969), eET_none),
            TestData(2, args2, ExpectedResult("anne", "10.11.12.13", false, 6969), eET_none),
            TestData(2, args3, ExpectedResult("mark", "10.11.12.13", true, 6969), eET_none),
            TestData(2, args4, ExpectedResult("jen", "10.11.12.13", true, 23456), eET_none),
        };
        const size_t numTests = sizeof(tests)/sizeof(TestData);

        for (int ii = 0; ii < numTests; ++ii)
        {
            const TestData& testData(tests[ii]);
            test(testData);
        }

        std::cout << std::endl;

        // these defaults should probably be created rather than hardcoded, but meh...
        const char * defaultArgs[] = {"-username=anon", "-address=127.0.0.1", "-port=6969"};
        // restore to defaults
        Settings::get().parse(3, defaultArgs);
        Settings::get().isServer(false);
        std::cout << "           --> Restore settings = " << MAGENTA << dumpSettings(Settings::get()) << DEFAULT << std::endl;
        std::cout << std::endl;
    }
};
/*
    const std::string& username() const;
    const std::string& username(const std::string& username);

    const std::string& serverAddress() const;
    const std::string& serverAddress(const std::string& serverAddress);

    const bool isServer() const;
    const bool isServer(const bool isServer);

    const unsigned short port() const;
    const unsigned short port(const unsigned short port);
*/

void testSettings()
{
    std::cout << CYAN << "Setting tests:" << DEFAULT << std::endl;

    testDefaults::run();
    testGetArgValue::run();
    testValidateUsername::run();
    testValidatePort::run();
    testParse::run();
}
