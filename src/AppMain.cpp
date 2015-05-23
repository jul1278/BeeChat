// AppMain.cpp

#include "BeeChatApp.h"
#include "UDPConnection.h"
#include "UDPServer.h"
#include "UDPClient.h"
#include <string>
#include "settings.h"
#include "BeeChatException.h"

void getSettings(int argc, char** argv);
//void dumpSettings();    //for debug testing

void usage();

int main( int argc, char** argv )
{
    if (argc <= 1)
    {
        usage();
        exit(4);
    }

    try
    {
        getSettings(argc,argv);
    }

    catch(std::exception se)
    {
        std::cerr << "A std::exception occurred: " << se.what() << std::endl;
        exit(2);
    }

    catch(...)
    {
        std::cerr << "An unknown exception occurred." << std::endl;
        exit(3);
    }

    Settings& settings = Settings::get();

	BeeChatApp* beeChatApp = new BeeChatApp( settings.username().c_str(), 0x01, settings.isServer());

    //debug code
        //dumpSettings();
        //return 0;

    while ( beeChatApp->Run() ) {
    }

	return 0;
}



//pass in a switch=value string and return the value
const std::string getArgValue(const std::string& arg)
{
    size_t pos = arg.find("=");

    if (pos == std::string::npos)
    {
        return arg;
    }

    std::string value(arg.substr(pos+1));

    return value;
}



//loop through command line arguments and extract settings
void getSettings(int argc, char** argv)
{
    bool hasUserName = false;   //assume user hasn't entered a username

    Settings& settings = Settings::get();    //get a reference to the settings (singleton)

    //loops through arguments, reads in each argument and decides what to do with it
    for(int ii = 0; ii < argc; ++ii)
    {
        std::string arg(argv[ii]);

        std::cerr << "parse arg: " << arg << std::endl;

        if (arg[0] != '-')
        {
            continue;   //not a switch, skip it
        }

        if(arg.find("-username=") == 0)     //are we setting username?
        {
            std::string username(getArgValue(arg));
            //TODO: move this to a try/catch once exceptions are implemented
            settings.username(username);    //set and validate requested username
            //
            hasUserName = true;     //user has entered a valid username
        }

        else if (arg.find("-address=") == 0)    //are we setting a server IP?
        {
            std::string serverAddress(getArgValue(arg));
            //TODO: move this to a try/catch once exceptions are implemented
            settings.serverAddress(serverAddress);    //set and validate requested server address
            //
        }

        else if(arg.find("-server") == 0)
        {
            settings.isServer(true);    //reuest to bee a server
        }

        else if(arg.find("-port=") == 0)
        {
            std::string port(getArgValue(arg));
            try
            {
                settings.port((unsigned short)atoi(port.c_str()));    //set and validate requested port
            }
            catch(BeeChatException e)
            {
                std::cerr << "Could not set port: " << e.type() << ":" << e.message() << std::endl;
                exit(1);
            }
        }

        else
        {
            std::cerr << "unknown argument: " << arg << std::endl;
        }
    }

    if(!hasUserName)
    {
        std::cerr << "no username supplied" << std::endl << std::endl;
        usage();
        exit(1);
    }

}

void dumpSettings()
{
    Settings& settings = Settings::get();
    std::cout << "Settings: " << std::endl;
    std::cout << "username: " << settings.username() << std::endl;
    std::cout << "address: " << settings.serverAddress() << std::endl;
    std::cout << "server?: " << (settings.isServer() ? "true":"false") << std::endl;
    std::cout << "port: " << settings.port() << std::endl;

}


void usage()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "\t./BeeChat -username=<user name> [-port=<port num>] "
              << "[-server] [-address=<server address>]" << std::endl;
    std::cout << std::endl;
}



