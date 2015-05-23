#include "settings.h"
#include "BeeChatException.h"


Settings Settings::_settings;

bool Settings::validateUsername(const std::string& username)
{
	if(username.empty())	//exit out if username is empty
	{
		throw BeeChatException(eET_empty_username, "Username empty, format: -username=<username>");
		return false;
	}

	if(username.size() > USERNAMELENGTH)	//do not allow usernames longer than max length
	{
		throw BeeChatException(eET_username_too_long, "Username is too long, must be <= 8 characters");
		return false;
	}

	for(size_t ii=0; ii<username.size(); ++ii)
	{
		if (!std::isalnum(username[ii]))	//check that all characters are alphanumeric
		{
			if(username[ii] != '_')	//allow underscore
			{
			throw BeeChatException(eET_invalid_username_characters,
						"Invalid username: username can only contain alphanumeric and underscore.");
				return false;	//no point check further if we find a non-alphanumeric
			}
		}
	}

	return true;	//username is valid
}


bool Settings::validateserverAddress(const std::string& serverAddress)
{
	//TODO: this
	return true;
}


bool Settings::validatePort(const unsigned short port)
{
	if(port <= 1024)
	{
		throw BeeChatException(eET_invalid_port, "Invalid port: must be above 1024");
	}

	return port > 1024;
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
	if(validateUsername(username))
	{
		_username = username;
	}

	else
	{
		//TODO: throw exception if not valid
	}

	return _username;
}


const std::string& Settings::serverAddress() const
{
	return _serverAddress;
}


const std::string& Settings::serverAddress(const std::string& serverAddress)
{
	if(validateserverAddress(serverAddress))
	{
		_serverAddress = serverAddress;
	}

	else
	{
		//TODO: throw exception if not valid
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
	if(validatePort(port))
	{
		_port = port;
	}

	else
	{
		//TODO: throw exception if not valid
	}

	return _port;
}











