// Created on A.R.M1111

#include <iostream>
//conio.h for getch and detection of pressing any key
#include <conio.h>

#define maxx	30
#define maxy	50
#define minx	0
#define miny	0
using namespace std;

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
     	screen[i][0]='|';
    	screen[i][49]='|';
    }
    screen[25][10]='i';
    screen[25][11]='m';
    screen[25][12]=' ';
    screen[25][13]='h';
    screen[25][14]='e';
    screen[25][15]='r';
    screen[25][16]='e';
    screen[25][17]='!';
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

int main()
{

    print_screen();

    char pressed_key ;
    while (1)
    {
        pressed_key=getch();
        if (pressed_key == 'd')
        {
            cout<<"right!"<<endl;
        }
        else if (pressed_key =='a')
        {
            cout<<"left!"<<endl;
        }

    }
    
    return 0;
}
