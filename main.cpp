// Created on A.R.M1111

#include <iostream>
//conio.h for getch and detection of pressing any key
#include <conio.h>
#include <unistd.h>

#define maxx	30
#define maxy	30
#define minx	0
#define miny	0

#define silder_length	10
#define slider_start_x	20
#define slider_y		28

#define ball_start_x 14
#define ball_start_y 27

#define north_east 1
#define north_west 2
#define south_west 3
#define south_east 4
using namespace std;

struct cordinate
{
	int x=slider_start_x;

}slider;

//struct of ball

struct ball
{
    int heading = north_east;
    bool visible = true;
    int pos_x = ball_start_x; //index of posision of ball , in the middle bottom for defualt (higher than slider)
    int pos_y = ball_start_y; 
    char c = 'o';
};


//move_ball moves the ball according to it's heading
void move_ball(ball *target_ball)
{
    switch (target_ball->heading)
    {
        case north_east: 
        {
            target_ball->pos_x ++ ;
            target_ball->pos_y -- ;
            break;
        }
        case north_west:
        {
            target_ball->pos_x -- ;
            target_ball->pos_y -- ;
            break;
        }
        case south_west:
        {
            target_ball->pos_x ++ ;
            target_ball->pos_y ++ ;
            break;
        }
        case south_east:
        {
            target_ball->pos_x -- ;
            target_ball->pos_y ++ ;
            break;
        }
    }
}


bool print_screen (ball& target_ball)
{
    //defing the array
    char screen[maxy][maxx];
    
    for (int i = miny; i < maxy; i++)
    {
        if (i==(maxy-1) || i==miny)
        {
            for (int j = minx; j < maxx; j++)
            {
                screen[i][j]= '_';
            }
        }
        else
		{
            for (int j = minx; j < maxx; j++)
            {
                screen[i][j]= ' ';
            }
        }
    }
    for (int i=miny;i<maxy;i++)
    {
     	screen[i][minx]='|';
    	screen[i][maxx-1]='|';
    }

    //adding the slider
    for(int j= slider.x;j<(silder_length+slider.x);j++)
    {
    	screen[slider_y][j] = '=';    	
	}

    //adding the ball(s)
     screen[target_ball.pos_y][target_ball.pos_x] = target_ball.c;
    
    

	
    //printing the array
    for (int i = miny; i < maxy; i++)
    {
    	
        for (int j = minx; j < maxx; j++)
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
				slider.x--;
				break;
			case 'd':
			case 'D':
				slider.x++;
				break;
			default:
				return 0;
		}
	return 0;
}
int main()
{
    

    //adding a ball
    ball ball_no_1;

	while(1)
	{
		print_screen(ball_no_1);
		slider_move();
        move_ball(&ball_no_1);
        usleep(100000);
        system("cls");
	}
    return 0;
}
