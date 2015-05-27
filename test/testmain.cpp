#include <iostream>
#include <string.h> // needed for memset
#include <stdarg.h>

#include <cstdio>
#include <string>

#include "testmain.h"


int main(int argc, char* argv[])
{
    std::cout << "Run Tests" << std::endl << std::endl;

    testSettings();
    std::cout << std::endl;

    testMessages();
    std::cout << std::endl << std::endl;

    return 0;
}
