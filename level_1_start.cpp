#include <iostream>
#include <windows.h>
#include <unistd.h>
#define maxx	40
#define maxy	30
#define minx	0
#define miny	0
using namespace std;
char screen[maxy][maxx];
void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput,scrn);
}

void level_1_start(void) 
{
   while (true)
   {
    for (int i = miny; i < maxy; i++)
    {
        if (i==(maxy-1) || i==miny)
        {
            for (int j = minx; j < maxx; j++)
            {
                screen[i][j]= '_';
            }
        }
    }
    for (int i=miny;i<maxy;i++)
    {
     	screen[i][minx]='|';
    	screen[i][maxx-1]='|';
    }
     for (int i = miny; i < maxy; i++)
    {
    	
        for (int j = minx; j < maxx; j++)
        {
            cout<<screen[i][j];
        }
        cout<<'\n';
    }
    gotoxy(16,8);
        cout<<"Level 1";
    gotoxy(13,12);
        cout<<"Are you ready?";
        sleep(5);
    gotoxy(15,17);
        cout<<"Let's go!";
        sleep(1);
        system("cls");
   			break;
   }
}


int main()
{
    level_1_start();
    return 0;
}