#include <sstream>
#include <cstdlib>
#include "settings.h"
#include "BeeChatException.h"


Settings Settings::_settings;


const char * Settings::DEFAULT_USERNAME = "anon";
const char * Settings::DEFAULT_ADDRESS = "127.0.0.1";
const bool Settings::DEFAULT_ISSERVER = false;
const unsigned short Settings::DEFAULT_PORT = 6969;


Settings::Settings(const std::string& username /*= DEFAULT_USERNAME*/,
                   const std::string& serverAddress /*= DEFAULT_ADDRESS*/,
                   const bool isServer /*= DEFAULT_ISSERVER*/,
                   const unsigned short port /*= DEFAULT_PORT*/)
: _username(username),
  _serverAddress(serverAddress),
  _isServer(isServer),
  _port(port)
{
    // try
    // {
    //     validateUsername(_username);
    //     validateserverAddress(_serverAddress);
    //     validatePort(_port);
    // }
    // catch (BeeChatException bce)
    // {
    //     throw;
    // }
}

Settings::~Settings()
{
    // Nothing much to do
}


void Settings::validateUsername(const std::string& username)
{
    if(username.empty())	//exit out if username is empty
    {
        throw BeeChatException(eET_empty_username, "Username empty, format: -username=<username>");
    }

    if(username.size() > USERNAMELENGTH)	//do not allow usernames longer than max length
    {
        throw BeeChatException(eET_username_too_long, "Username is too long, must be <= 8 characters");
    }

    for(size_t ii=0; ii<username.size(); ++ii)
    {
        if (!std::isalnum(username[ii]))	//check that all characters are alphanumeric
        {
            if(username[ii] != '_')			//allow underscore
            {
                throw BeeChatException(eET_invalid_username_characters,
                        "Invalid username: username can only contain alphanumeric and underscore.");
            }
        }
    }
}


void Settings::validateserverAddress(const std::string& serverAddress)
{
    //TODO: this
}


void Settings::validatePort(const unsigned short port)
{
    if(port <= 1024)
    {
        throw BeeChatException(eET_invalid_port, "Invalid port: must be above 1024");
    }
}


Settings& Settings::get()
{
    return _settings;
}


const std::string& Settings::username() const
{
    return _username;
}


const std::string& Settings::username(const std::string& username)
{
    try
    {
        validateUsername(username);
        _username = username;
    }
    catch (BeeChatException bce)
    {
        throw;	// rethrow
    }

    return _username;
}


const std::string& Settings::serverAddress() const
{
    return _serverAddress;
}


const std::string& Settings::serverAddress(const std::string& serverAddress)
{
    try
    {
        validateserverAddress(serverAddress);
        _serverAddress = serverAddress;
    }
    catch (BeeChatException bce)
    {
        throw;	// rethrow
    }

    return _serverAddress;

}


const bool Settings::isServer() const
{
    return _isServer;
}


const bool Settings::isServer(const bool isServer)
{
    _isServer = isServer;
    return _isServer;
}

const unsigned short Settings::port() const
{
    return _port;
}


const unsigned short Settings::port(const unsigned short port)
{
    try
    {
        validatePort(port);
        _port = port;
    }
    catch (BeeChatException bce)
    {
        throw;	// rethrow
    }

    return _port;
}


//loop through command line arguments and extract settings
void Settings::parse(const int argc, const char** argv)
{
    bool hasUserName = false;   //assume user hasn't entered a username

    //loops through arguments, reads in each argument and decides what to do with it
    for(int ii = 0; ii < argc; ++ii)
    {
        std::string arg(argv[ii]);

        if (arg[0] != '-')
        {
            continue;   //not a switch, skip it
        }

        if(arg.find("-username=") == 0)     //are we setting username?
        {
            std::string uname(getArgValue(arg));
            try {
                (void)username(uname);    //set and validate requested username
            }
            catch (BeeChatException bce)
            {
                throw;    //rethrow the same exception
            }
            hasUserName = true;     //user has entered a valid username
        }

        else if (arg.find("-address=") == 0)    //are we setting a server IP?
        {
            std::string address(getArgValue(arg));
            try
            {
                (void)serverAddress(address);    //set and validate requested server address
            }
            catch (BeeChatException bce)
            {
                throw;    //rethrow the same exception
            }
        }

        else if(arg.find("-server") == 0)
        {
            (void)isServer(true);    //request to bee a server
        }

        else if(arg.find("-port=") == 0)
        {
            std::string portStr(getArgValue(arg));
            try
            {
                (void)port((unsigned short)atoi(portStr.c_str()));    //set and validate requested port
            }
            catch(BeeChatException e)
            {
                std::stringstream ss;
                ss << "Could not set port: " << e.type() << ":" << e.message();
                throw BeeChatException(eET_invalid_port, ss.str());
            }
        }

        else
        {
            std::stringstream ss;
            ss << "Unknown argument: " << arg;
            throw BeeChatException(eET_unknown_arg, ss.str());
        }
    }

    if(!hasUserName)
    {
        throw BeeChatException(eET_empty_username, "No username supplied");
    }

}


const std::string Settings::dump() const
{
    std::stringstream ss;
    ss << "Settings: " << std::endl;
    ss << "\tusername: " << username() << std::endl;
    ss << "\t address: " << serverAddress() << std::endl;
    ss << "\t server?: " << (isServer() ? "true":"false") << std::endl;
    ss << "\t    port: " << port() << std::endl;

    return ss.str();
}

    //pass in a switch=value string and return the value
const std::string Settings::getArgValue(const std::string& arg)
{
    size_t pos = arg.find("=");

    if (pos == std::string::npos)
    {
        return arg;
    }

    std::string value(arg.substr(pos+1));

    return value;
}
