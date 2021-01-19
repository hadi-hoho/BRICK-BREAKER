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

<<<<<<< HEAD
struct cordinate
{
	int y=slider_start_y;

}slider;
=======
//struct of ball

struct ball
{
    int heading=1; // 1= up-right 2=up-left 3=down-left 4=down-right
    bool visible = true;
    int pos_x = maxx/2 -1; //index of posision of ball , in the middle bottom for defualt (higher than slider)
    int pos_y = maxy-2; 
    char c = 'o';
};

//add_ball adds a new ball to the screen
ball add_ball (char **screen)
{
    ball new_ball;
    screen[new_ball.pos_x][new_ball.pos_y] = new_ball.c;
    return new_ball;
}

//move_ball moves the ball according to it's heading
ball move_ball(ball target_ball,char **screen)
{
    if (target_ball.heading==1)
    {
        screen[target_ball.pos_x][target_ball.pos_y] = ' ';
        screen[target_ball.pos_x+1][target_ball.pos_y-1] = target_ball.c;
        target_ball.pos_x++;
        target_ball.pos_y--;
    }
    if (target_ball.heading==2)
    {
        screen[target_ball.pos_x][target_ball.pos_y] = ' ';
        screen[target_ball.pos_x-1][target_ball.pos_y-1] = target_ball.c;
        target_ball.pos_x--;
        target_ball.pos_y--;
    }
    if (target_ball.heading==3)
    {
        screen[target_ball.pos_x][target_ball.pos_y] = ' ';
        screen[target_ball.pos_x-1][target_ball.pos_y+1] = target_ball.c;
        target_ball.pos_x--;
        target_ball.pos_y++;
    }
    if (target_ball.heading==4)
    {
        screen[target_ball.pos_x][target_ball.pos_y] = ' ';
        screen[target_ball.pos_x+1][target_ball.pos_y+1] = target_ball.c;
        target_ball.pos_x++;
        target_ball.pos_y++;
    }
    return target_ball;
}

>>>>>>> 3fb469c0e1694262de562088f3e1b9fd41ef9ad9
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
