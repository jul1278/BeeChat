/* shapetest.cpp
 * ENB241 Portfolio 2
 *
 * Shape inheritance demonstration
 *
 */

#include "GUI.h"
#include <stdlib.h>
#include <iostream>
using namespace std;




int main(int argc, char *argv[])
{
    int ch = 'a';
    GUI Gooey;
    Gooey.initScreen();
    Gooey.initWindows();
    Gooey.Routine();

    // mainWindow.win_0 = newwin(10, 20, 3, 5);
    // mainWindow.win_1 = newwin(10, 20, 8, 15);


    while(1);
    // wgetch(mainWindow.info_scr);
    endwin();
    return 0;
}
