#include <string>

#define USERNAMELENGTH 8

class Settings
{

private:

	std::string _username;
	std::string _serverAddress;
	bool _isServer;
	unsigned short _port;

	static Settings _settings;

    Settings(const std::string& username = DEFAULT_USERNAME,
             const std::string& serverAddress = DEFAULT_ADDRESS,
             const bool isServer = DEFAULT_ISSERVER,
             const unsigned short port = DEFAULT_PORT);
    ~Settings();


public:
    static const char * DEFAULT_USERNAME;
    static const char * DEFAULT_ADDRESS;
    static const bool DEFAULT_ISSERVER;
    static const unsigned short DEFAULT_PORT;

    //get the static instance of settings
    static Settings& get();

    const std::string& username() const;
    const std::string& username(const std::string& username);

    const std::string& serverAddress() const;
    const std::string& serverAddress(const std::string& serverAddress);

    const bool isServer() const;
    const bool isServer(const bool isServer);

    const unsigned short port() const;
    const unsigned short port(const unsigned short port);

    const std::string dump() const;

    // Parse settings from command line args
    void parse(const int argc, const char** argv);

    //pass in a switch=value string and return the value
    static const std::string getArgValue(const std::string& arg);

    //ensure that username is composed of allowed characters only - alphanumeric or underscore
    static void validateUsername(const std::string& username);
	
    //ensure the server address is composed of valid characters only - numbers, fullstop, valid dotted IPv4
    static void validateserverAddress(const std::string& serverAddress);
    
	//ensure that the port is composed of valid characters only - none below 1024
    static void validatePort(const unsigned short port);
};


