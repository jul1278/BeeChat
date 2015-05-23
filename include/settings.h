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

	Settings(const std::string& username = "anon", const std::string& serverAddress = "127.0.0.1",
				const bool isServer = false, const unsigned short port = 6969)
	: _username(username),
	  _serverAddress(serverAddress),
	  _isServer(isServer),
	  _port(port)
	{
		//TODO: throw exception if username is invalide
			//too long
			//nonexistant
			//invalid characters
	}

	~Settings()	{}

	//ensure that username is composed of allowed characters only - alphanumeric or underscore
	static bool validateUsername(const std::string& username);
	//ensure the server address is composed of valid characters only - numbers, fullstop, valid dotted IP v4
	static bool validateserverAddress(const std::string& serverAddress);
	//ensure that the port is composed of valid characters only - none below 1024
	static bool validatePort(const unsigned short port);


public:

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

};


