#include <iostream>
//conio.h for getch and detection of pressing any key
#include <conio.h>
#include <unistd.h>   //for defining sleep
#include <windows.h>  //for defining gotoxy
#include <stdlib.h>  //for exiting when losing

#define maxx	40
#define maxy	30
#define minx	0
#define miny	0

#define silder_length	10
#define slider_start_x	16
#define slider_y		28
#define slider_speed 3

#define ball_start_x 20
#define ball_start_y 27

#define north_east 1
#define north_west 2
#define south_west 3
#define south_east 4

#define bricks_length	3
#define bricks_width	2
#define bricks_number	9
#define bricks_row1		5
#define bricks_culomn1	10
#define bricks_row2		10
#define bricks_culomn2	20
#define bricks_row3		15
#define bricks_culomn3	30
int bricks = bricks_number;

#define ball_number		1

int x_changes	=	2;
int y_changes	=	1;
using namespace std;

//defing the array
char screen[maxy][maxx];


//struct of slider
struct cordinate
{
	int x=slider_start_x;

}slider;

//struct of bricks
struct bricks
{
	int x;
	int y;
	bool visibility=true;
	bool del=false; 
}brick[bricks_number];

//struct of ball
struct ball
{
    int heading = north_east;
    bool visible = true;
    int pos_x = ball_start_x; //index of posision of ball , in the middle bottom for defualt (higher than slider)
    int pos_y = ball_start_y; 
    char c = 'O';
    
}target_ball[ball_number];

//move_ball moves the ball according to it's heading
void move_ball(void)
{
	for(int i=0;i<ball_number;i++)
	{
		switch (target_ball[i].heading)
   		{
	        case north_east: 
        	    target_ball[i].pos_x +=x_changes ;
	           	target_ball[i].pos_y -=y_changes ;
    	        break;
        	
	        case north_west:
        	    target_ball[i].pos_x -=x_changes ;
	            target_ball[i].pos_y -=y_changes ;
    	        break;
        	
 	       case south_west:
  	            target_ball[i].pos_x -=x_changes ;
  	            target_ball[i].pos_y +=y_changes ;
         	    break;
       		
	        case south_east:
  	          	target_ball[i].pos_x +=x_changes ;
           		target_ball[i].pos_y +=y_changes ;
         	    break;
      		
   		}
	}
}

void print_bricks()
{
	for(int i=0;i<bricks_number;i++)
	{
		if (brick[i].visibility)
		{
			for(int j=0;j<bricks_length;j++)
			{
				for(int k=0;k<bricks_width;k++)
					screen[brick[i].y+k][brick[i].x+j]='#';
			}
		}
	}
}

bool border_collision(void)
{
	for(int i=0;i<ball_number;i++)
	{	
		//barkhord ba divar rast	
		if(target_ball[i].heading==north_east && target_ball[i].pos_x +x_changes>= maxx)
			target_ball[i].heading=north_west;
		else if(target_ball[i].heading==south_east && target_ball[i].pos_x +x_changes>= maxx)
			target_ball[i].heading=south_west;

		//barkhord ba divar bala
		else if(target_ball[i].heading==north_west && target_ball[i].pos_y-y_changes<=miny)
			target_ball[i].heading=south_west;
		else if(target_ball[i].heading==north_east && target_ball[i].pos_y-y_changes<=miny)
			target_ball[i].heading=south_east;

		//barkhord ba divar chap
		else if(target_ball[i].heading==south_west && target_ball[i].pos_x -x_changes<= minx )
			target_ball[i].heading=south_east;
		else if(target_ball[i].heading==north_west && target_ball[i].pos_x -x_changes<= minx )
			target_ball[i].heading=north_east;
		
		//barkhord be payin
		else if(target_ball[i].pos_y >= maxy)
		{
			//reset the ball !
			target_ball[i].pos_x = ball_start_x;
			target_ball[i].pos_y = ball_start_y;
			target_ball[i].heading = north_east;
		}
	}
	return true;	
}

void brick_collision(void)
{	
		for (int i = 0; i < ball_number; i++)
		{
			for (int j = 0; j < bricks_number; j++)
			{
				if (brick[j].visibility)
				{
					if (brick[j].x <= target_ball[i].pos_x && brick[j].x + bricks_length >= target_ball[i].pos_x )
					{	
						if (brick[j].y <= target_ball[i].pos_y &&  brick[j].y + bricks_width >= target_ball[i].pos_y)
						{
							switch (target_ball[i].heading)
							{
								case north_east:
									if(target_ball[i].pos_x == bricks_culomn1 || target_ball[i].pos_x == bricks_culomn2 || target_ball[i].pos_x == bricks_culomn3)
										target_ball[i].heading=north_west;
									else
										target_ball[i].heading=south_east;								
									break;
								case north_west:
									if(target_ball[i].pos_x == (bricks_culomn1+(bricks_length-1)) || target_ball[i].pos_x == (bricks_culomn2+(bricks_length-1)) || target_ball[i].pos_x == (bricks_culomn3+(bricks_length-1)))
										target_ball[i].heading=north_east;
									else
										target_ball[i].heading=south_west;									
									break;
								case south_east:
									if(target_ball[i].pos_x == bricks_culomn1 || target_ball[i].pos_x == bricks_culomn2 || target_ball[i].pos_x == bricks_culomn3)
										target_ball[i].heading=north_west;
									else
										target_ball[i].heading=north_east;
									break;
								case south_west:
									if(target_ball[i].pos_x == (bricks_culomn1+(bricks_length-1)) || target_ball[i].pos_x == (bricks_culomn2+(bricks_length-1)) || target_ball[i].pos_x == (bricks_culomn3+(bricks_length-1)))
										target_ball[i].heading=south_east;
									else
										target_ball[i].heading=north_west;
									break;
								
							}
						}
					}
				}
			}	
		}	
}
bool slider_collision(void)
{
	for (int i = 0; i < ball_number; i++)
	{
		if (target_ball[i].pos_y >=slider_y && target_ball[i].pos_x >= slider.x && target_ball[i].pos_x <= slider.x + silder_length)
		{
			if (target_ball[i].heading == south_east )
			{
				target_ball[i].heading = north_east;
			}
			if (target_ball[i].heading == south_west)
			{
				target_ball[i].heading = north_west;
			}
		}
	}
	return true;
}

bool brick_del (void)
{
	static int cnt=0;
	for (int i = 0; i < bricks_number; i++)
		if(brick[i].del == true)
		{			
			if(cnt==1)
			{
				brick[i].visibility = false;
				cnt=0;	
			}
			cnt++;			
		}
	for (int i = 0; i < bricks_number; i++)
	{
		for (int j = 0; j < ball_number; j++)
		{
			if (brick[i].visibility)
			{
				if (brick[i].x <= target_ball[j].pos_x && brick[i].x + bricks_length >= target_ball[j].pos_x )
				{
					
					if (brick[i].y <= target_ball[j].pos_y &&  brick[i].y + bricks_width >= target_ball[j].pos_y)
					{
						brick[i].del = true;
						bricks--;
					}
				}
			}
		}
	}
	return true;
}

bool print_screen (void)
{
	system("cls");
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
    for (int i=miny+1;i<maxy;i++)
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
    screen[target_ball[0].pos_y][target_ball[0].pos_x] = target_ball[0].c;
    
    print_bricks();

    //printing the array
    for (int i = miny; i < maxy; i++)
    {
    	
        for (int j = minx; j < maxx; j++)
        {
            cout<<screen[i][j];
        }
        cout<<'\n';
    }
    cout<<endl<<endl<<target_ball[0].pos_x<<","<<target_ball[0].pos_y;
    
    	
    return true;
}

void check_left_chafe()
{
	for (int  i = 0; i < ball_number; i++)
	{
		if (target_ball[i].pos_y==slider_y && target_ball[i].pos_x >= slider.x && target_ball[i].pos_x <= slider.x + silder_length)
		{
			x_changes+=1;
		}	
	}
}
void check_right_chafe()
{
	for (int  i = 0; i < ball_number; i++)
	{
		if (target_ball[i].pos_y==slider_y && target_ball[i].pos_x >= slider.x && target_ball[i].pos_x <= slider.x + silder_length)
		{
			x_changes+=1;
		}	
	}
}

int slider_move(void)
{
	if(kbhit())
		switch(getch())
		{
			case 'a':
			case 'A':
				if((slider.x-slider_speed)<minx )
					return 0;
				slider.x -= slider_speed;
				check_left_chafe();
				break;
			case 'd':
			case 'D':
				if((slider.x+silder_length+slider_speed)>maxx)
					return 0;
				slider.x += slider_speed;
				check_right_chafe();
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
void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput,scrn);
}

void welcome_page(void) 
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
    for (int i=miny+1;i<maxy;i++)
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
    gotoxy(8,8);
    cout<<"Welcome to BRICK BREAKER";
	sleep(1);
    gotoxy(15,16);
    cout<<"Producers:";
	sleep(1);
    gotoxy(14,17);
    cout<<"Hadi Firoozi";
	sleep(1);
    gotoxy(14,18);
    cout<<"Sanaz Motie";
	sleep(1);
    gotoxy(12,19);
    cout<<"Alireza Mikaeili";
      sleep(5);
	for (int i=3; i>0; i--){
	gotoxy(20,21);
    cout<<i;
      	sleep(1);
	}
	system("cls");
   	break;
   }
}
int start(void)
{
	char ch;
	slider.x=slider_start_x;
	target_ball[0].pos_x=ball_start_x;
	target_ball[0].pos_y=ball_start_y;
	target_ball[0].heading=north_east;
	system("cls");
	print_screen();
	gotoxy(4,18);
        cout<<"For moving right press 'D' button";
    gotoxy(4,20);
        cout<<"For moving left press 'A' button";
	gotoxy(10,22);
	sleep(1);
	cout<<"Press Space to start";
	while(1)
	{
		if (kbhit)
		{
			ch = getch();
			if (int(ch) == 32)
			return 0;
		}
		else
			system("cls");		
	}
}
void losing(int &lose)   //call by reference
{
	cout<<"You lost!"<<'\t';
	sleep(2);
	if(lose<3) 
	{
		cout<<"Remain chances="<<3-lose;
		lose++;
		sleep(3);
		start();
	}
	else
	{
		cout<<"You can try again later";
		sleep(3);
		exit(0);
	}
}
void winning()
{
	system("cls");
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
    for (int i=miny+1;i<maxy;i++)
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
	sleep(1);
	gotoxy(13,8);
        cout<<"BRICK BREAKER";
		sleep(2);
	gotoxy(12,12);
        cout<<"Congratulations";
	sleep(1);
	 gotoxy(15,14);
        cout<<"You won!";
		sleep(5);
		gotoxy(2,31);
		exit (0);	
}
int main()
{
    welcome_page();
    initialize();

    //adding a ball

	int lose =1;
	start();
	while(1)
	{		
		print_screen();	
		move_ball();
        border_collision();
        brick_collision();
		slider_collision();
		brick_del();
		slider_move();        
        usleep(100000);
		if(bricks==0)
			winning();
		for(int i=0;i<ball_number;i++)
			if(target_ball[i].pos_y==maxy-1) 
				losing(lose);			
	}
    return 0;
}
