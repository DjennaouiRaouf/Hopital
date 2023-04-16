#include <windows.h>
#include <tchar.h>
#include <stdio.h>

void textcolor(int flags)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,(WORD)flags);
}

void gotoxy(int x,int y)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD C;
    C.X=(SHORT)x;
    C.Y=(SHORT)y;
    SetConsoleCursorPosition(H,C);
}




