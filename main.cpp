// Created on A.R.M1111

#include <iostream>
//conio.h for getch and detection of pressing any key
#include <conio.h>

#define maxx	30
#define maxy	50
#define minx	0
#define miny	0

#define silder_length	10
#define slider_start_y	20
#define slider_x		27
using namespace std;

struct cordinate
{
	int y=slider_start_y;

}slider;
bool print_screen ()
{
    //defing the array
    char screen[maxx][maxy];
    
    for (int i = minx; i < maxx; i++)
    {
        if (i==(maxx-1) || i==minx)
        {
            for (int j = miny; j < maxy; j++)
            {
                screen[i][j]= '_';
            }
        }
        else
		{
            for (int j = miny; j < maxy; j++)
            {
                screen[i][j]= ' ';
            }
        }
    }
    for (int i=minx;i<maxx;i++)
    {
     	screen[i][miny]='|';
    	screen[i][maxy-1]='|';
    }
    
    for(int j= slider.y;j<(silder_length+slider.y);j++)
    {
    	screen[slider_x][j]='=';    	
	}
	
    //printing the array
    for (int i = minx; i < maxx; i++)
    {
    	
        for (int j = miny; j < maxy; j++)
        {
            cout<<screen[i][j];
        }
        cout<<'\n';
    }
    
    	
    return true;
}
int slider_move(void)
{
	if(kbhit())
		switch(getch())
		{
			case 'a':
			case 'A':
				slider.y--;
				break;
			case 'd':
			case 'D':
				slider.y++;
				break;
			default:
				return 0;
		}
	return 0;
}
int main()
{
	while(1)
	{
		system("cls");
		print_screen();
		slider_move();	
	}
    
    return 0;
}
