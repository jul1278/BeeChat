// AppMain.cpp

#include "BeeChatApp.h"
#include "UDPConnection.h"
#include "UDPServer.h"
#include "UDPClient.h"
#include <string>
#include "settings.h"
#include "BeeChatException.h"

void usage();

int main( int argc, char** argv )
{
    if (argc <= 1)
    {
        // no args
        usage();
        exit(4);
    }

    Settings& settings = Settings::get();

    try
    {
        try
        {
            settings.parse(argc, (const char **)argv);
        }

        catch(BeeChatException bce)
        {
            std::cerr << "An exception occurred parsing settings: " << bce.type()
                      << ": " << bce.message() << std::endl;
            usage();
            exit(1);
        }

        BeeChatApp* beeChatApp = new BeeChatApp( settings.username().c_str(), 0x01, settings.isServer());
        if(beeChatApp->quit) {return 1;}
        //debug code
        // {
        //     settings.dump();
        //     return 0;
        // }

        try
        {
            while ( beeChatApp->Run() )
            {

            }
        }

        catch(BeeChatException bce)
        {
            std::cerr << "An exception occurred operation during operation: " << bce.type()
                      << ": " << bce.message() << std::endl;
            usage();
            exit(5);
        }
    }

    catch(std::exception se)
    {
        std::cerr << "A std::exception occurred: " << se.what() << std::endl;
        usage();
        exit(2);
    }

    catch(...)
    {
        std::cerr << "An unknown exception occurred." << std::endl;
        usage();
        exit(3);
    }

    return 0;
}


void usage()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "\t./BeeChat -username=<user name> [-port=<port num>] "
              << "[-server] [-address=<server address>]" << std::endl;
    std::cout << std::endl;
}



