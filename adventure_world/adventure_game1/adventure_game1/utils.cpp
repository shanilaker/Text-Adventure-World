#include "utils.h"
#include <iostream>
#include <windows.h> // Required for Windows API console functions
#include <cstdlib>

// Used from tirgul with Amir Kirsh
// Puts cursor on required (x,y) on the screen 
void gotoxy(int x, int y) {
    std::cout.flush();
    COORD coord;
    coord.X = (SHORT)x;
    coord.Y = (SHORT)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Used from tirgul with Amir Kirsh
// Hides the cursor from the screen
void hideCursor()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(hStdOut, &curInfo);
    curInfo.bVisible = FALSE; // Set to TRUE to make it visible
    SetConsoleCursorInfo(hStdOut, &curInfo);
}

//Clears the screen
void cls() {
    system("cls");
}