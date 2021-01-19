

#include <iostream>
//conio.h for getch and detection of pressing any key
#include <conio.h>
#include <unistd.h>

#define maxx	40
#define maxy	30
#define minx	0
#define miny	0

#define silder_length	10
#define slider_start_x	20
#define slider_y		28

#define north_east 1
#define north_west 2
#define south_east 3
#define south_west 4

#define bricks_length	3
#define bricks_width	2
#define bricks_number	9
#define bricks_row1		5
#define bricks_culomn1	10
#define bricks_row2		10
#define bricks_culomn2	20
#define bricks_row3		15
#define bricks_culomn3	30
using namespace std;
//struct of slider
struct cordinate
{
	int x=slider_start_x;

}slider;

struct bricks
{
	int x;
	int y;
	bool visibility=true;
}brick[bricks_number];
//struct of ball

struct ball
{
    int heading=north_east; // 1= up-right 2=up-left 3=down-left 4=down-right
    bool visible = true;
    int pos_x = ((maxx/2) -1); //index of posision of ball , in the middle bottom for defualt (higher than slider)
    int pos_y = maxy-2; 
    char c = 'o';
};

//add_ball adds a new ball to the screen
ball add_ball (char **screen)
{
    ball new_ball;
    screen[new_ball.pos_y][new_ball.pos_x] = new_ball.c;
    return new_ball;
}

//move_ball moves the ball according to it's heading
ball move_ball(ball target_ball,char **screen)
{
    switch (target_ball.heading)
    {
        case north_east: 
        {
            screen[target_ball.pos_y][target_ball.pos_x] = ' ';
            screen[target_ball.pos_y - 1][target_ball.pos_x + 1] = target_ball.c;
            target_ball.pos_x++;
            target_ball.pos_y--;
        }
        case north_west:
        {
            screen[target_ball.pos_y][target_ball.pos_x] = ' ';
            screen[target_ball.pos_y - 1][target_ball.pos_x - 1] = target_ball.c;
            target_ball.pos_x--;
            target_ball.pos_y--;
        }
        case south_west:
        {
            screen[target_ball.pos_y][target_ball.pos_x] = ' ';
            screen[target_ball.pos_y + 1][target_ball.pos_x - 1] = target_ball.c;
            target_ball.pos_x++;
            target_ball.pos_y++;
        }
        case south_east:
        {
            screen[target_ball.pos_y][target_ball.pos_x] = ' ';
            screen[target_ball.pos_y + 1][target_ball.pos_x + 1] = target_ball.c;
            target_ball.pos_x--;
            target_ball.pos_y++;
        }
    }
    return target_ball;
}

void print_bricks(char **screen)
{
	for(int i=0;(i<bricks_number) && (brick[i].visibility == true);i++)
	{
		for(int j=0;j<bricks_length;j++)
		{
			for(int k=0;k<bricks_width;k++)
				screen[brick[i].y+k][brick[i].x+j]='#';
		}
	}
}
bool print_screen ()
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
    
    for(int j= slider.x;j<(silder_length+slider.x);j++)
    {
    	screen[slider_y][j]='=';    	
	}
	//print_bricks(screen);
	for(int i=0;(i<bricks_number) && (brick[i].visibility == true);i++)
	{
		for(int j=0;j<bricks_length;j++)
		{
			for(int k=0;k<bricks_width;k++)
				screen[brick[i].y+k][brick[i].x+j]='#';
		}
	}
	
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
void initialize(void)
{
	brick[0].x=bricks_culomn1;
	brick[0].y=bricks_row1;
	brick[1].x=bricks_culomn2;
	brick[1].y=bricks_row1;
	brick[2].x=bricks_culomn3;
	brick[2].y=bricks_row1;
	
	brick[3].x=bricks_culomn1;
	brick[3].y=bricks_row2;
	brick[4].x=bricks_culomn2;
	brick[4].y=bricks_row2;
	brick[5].x=bricks_culomn3;
	brick[5].y=bricks_row2;
	
	brick[6].x=bricks_culomn1;
	brick[6].y=bricks_row3;
	brick[7].x=bricks_culomn2;
	brick[7].y=bricks_row3;
	brick[8].x=bricks_culomn3;
	brick[8].y=bricks_row3;
}
int main()
{
	initialize();
	while(1)
	{
		
		print_screen();
		slider_move();
        usleep(100000);
        system("cls");
        	
	}
    return 0;
}
