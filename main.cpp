#include <iostream>
#include <conio.h>    //for getch and detection of pressing any key
#include <unistd.h>   //for defining sleep
#include <windows.h>  //for defining gotoxy
#include <stdlib.h>   //for exiting when losing
#include <fstream>
//TODO : /adding level 1:6 , 2:6+3 , 3:6+3 2toop / changing bricks /
//TODO : /adding timer / adding menu=>OK /
//TODO : /slider move to left and right before start / changing ball heading before start /

#define level_numbers 3
int current_level = 1;
#define maxx	40
#define maxy	30
#define minx	0
#define miny	0

#define silder_length	10
#define slider_start_x	16
#define slider_y		28
#define slider_speed 3
#define slider_left 1
#define slider_right 2

#define x_chafe_rate 1

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

#define max_ball_number		2

#define x_changes_default	2
#define y_changes_default	1
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
	int health = 1;
	char ch = '#';

}brick[bricks_number];

//struct of ball
struct ball
{
    int heading = 0;
    bool visible = true;
    int pos_x = ball_start_x; //index of posision of ball , in the middle bottom for defualt (higher than slider)
    int pos_y = ball_start_y;
	int x_changes = x_changes_default;
	int y_changes = y_changes_default;
    char c = 'O';
    bool active = false;
}target_ball[max_ball_number];

/*********************functions***************/

void move_ball(void);
void print_bricks(void);
bool border_collision(void);
void brick_collision(void);
int slider_collision(void);
bool brick_del (void);
bool print_screen (void);
void left_chafe(int);
void right_chafe(int);
int slider_move(void);
void initialize(void);
void gotoxy(int xpos, int ypos);
void welcome_page(void);
int start(void);
int menu(void);
void pause(void);
void losing(int ball_index);
void winning(void);
void level_start(void);
void Timer(void);
void check_chafe(int slider_moved , int slider_hit);
void set_level(int level);
void print_array(void);
void print_border(void);
/************************/

int main()
{
    welcome_page();
    menu();
    initialize();
	set_level(current_level);
	start();
	while(1)
	{		
		print_screen();
		Timer();
		move_ball();
		int slider_moved =slider_move(); 
		border_collision();
		brick_collision();
		brick_del();
		int slider_hit =slider_collision();
		check_chafe(slider_moved , slider_hit);
		usleep(100000);
		if(bricks==0)
			winning();			
	}
    return 0;
}
//move_ball moves the ball according to it's heading
void move_ball(void)
{
	for(int i=0;i<max_ball_number;i++)
	{
		if (target_ball[i].active)
		{
			switch (target_ball[i].heading)
			{
				case north_east: 
					target_ball[i].pos_x +=target_ball[i].x_changes ;
					target_ball[i].pos_y -=target_ball[i].y_changes ;
					break;
				
				case north_west:
					target_ball[i].pos_x -=target_ball[i].x_changes ;
					target_ball[i].pos_y -=target_ball[i].y_changes ;
					break;
				
			case south_west:
					target_ball[i].pos_x -=target_ball[i].x_changes ;
					target_ball[i].pos_y +=target_ball[i].y_changes ;
					break;
				
				case south_east:
					target_ball[i].pos_x +=target_ball[i].x_changes ;
					target_ball[i].pos_y +=target_ball[i].y_changes ;
					break;
				
			}
		}
		
		
	}
}

void print_bricks(void)
{
	for(int i=0;i<bricks_number;i++)
	{
		if (brick[i].visibility)
		{
			for(int j=0;j<bricks_length;j++)
			{
				for(int k=0;k<bricks_width;k++)
					screen[brick[i].y+k][brick[i].x+j]=brick[i].ch;
			}
		}
	}
}

bool border_collision(void)
{
	for(int i=0;i<max_ball_number;i++)
	{	
		if (target_ball[i].active)
		{
			//barkhord ba divar rast	
			if(target_ball[i].heading==north_east && target_ball[i].pos_x +target_ball[i].x_changes>= maxx)
				target_ball[i].heading=north_west;
			else if(target_ball[i].heading==south_east && target_ball[i].pos_x +target_ball[i].x_changes>= maxx)
				target_ball[i].heading=south_west;

			//barkhord ba divar bala
			else if(target_ball[i].heading==north_west && target_ball[i].pos_y-target_ball[i].y_changes<=miny)
				target_ball[i].heading=south_west;
			else if(target_ball[i].heading==north_east && target_ball[i].pos_y-target_ball[i].y_changes<=miny)
				target_ball[i].heading=south_east;

			//barkhord ba divar chap
			else if(target_ball[i].heading==south_west && target_ball[i].pos_x -target_ball[i].x_changes<= minx )
				target_ball[i].heading=south_east;
			else if(target_ball[i].heading==north_west && target_ball[i].pos_x -target_ball[i].x_changes<= minx )
				target_ball[i].heading=north_east;
			
			//barkhord be payin
			else if(target_ball[i].pos_y >= maxy)
			{
				losing(i);
			}
		}
	}
	return true;	
}

void brick_collision(void)
{	
	for (int i = 0; i < max_ball_number; i++)
	{
		if (target_ball[i].active)
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
}

//if ball(s) hit the slider this func will change the heading of it and return the index of that ball
int slider_collision(void)
{
	for (int i = 0; i < max_ball_number; i++)
	{
		if (target_ball[i].active)
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
				return i;
			}
		}
	}	
	return -1;
}

bool brick_del (void)
{	
	for (int i = 0; i < bricks_number; i++)
	{
		if (brick[i].visibility)
		{
			for (int j = 0; j < max_ball_number; j++)
			{
				if (target_ball[j].active)
				{
					
					if (brick[i].x <= target_ball[j].pos_x && brick[i].x + bricks_length >= target_ball[j].pos_x )
					{
						
						if (brick[i].y <= target_ball[j].pos_y &&  brick[i].y + bricks_width >= target_ball[j].pos_y)
						{
							if (brick[i].health == 1)
							{
								brick[i].visibility = false;
								bricks--;
							}
							else 
							{
								brick[i].ch = '#';
								brick[i].health --;
							}
						}
					}
				}
			}
		}
	}
	return true;
}
void print_border(void)
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
}
void print_array(void)
{
	for (int i = miny; i < maxy; i++)
    {
    	
        for (int j = minx; j < maxx; j++)
        {
            cout<<screen[i][j];
        }
        cout<<'\n';
    }
}
bool print_screen (void)
{
	system("cls");
    
	print_border();
    //adding the slider
    for(int j= slider.x;j<(silder_length+slider.x);j++)
    {
    	screen[slider_y][j] = '=';    	
	}

    //adding the ball(s)
	for (int i = 0; i < max_ball_number; i++)
	{
		if (target_ball[i].active)
		{
			screen[target_ball[i].pos_y][target_ball[i].pos_x] = target_ball[i].c;
		}
	}
    print_bricks();

    //printing the array
    print_array();
    	
    return true;
}
void level_start(void) 
{
	system("cls");
   while (true)
   {
    print_border();
    print_array();
	sleep(2);
	gotoxy(13,8);
        cout<<"BRICK BREAKER";
		sleep(1);
    gotoxy(16,10);
        cout<<"Level "<<current_level;
    sleep(1);
		if (current_level>1)
		{
			gotoxy(3,12);
			cout<<"'$' bricks should be broken twice!";
			if (current_level>2)
			{
			gotoxy(8,14);
			cout<<"Now, there are 2 balls!";
			gotoxy(6,15);
			cout<<"Start moving them separately";
			gotoxy(8,17);
			cout<<"You have only 2 minutes!";
			}
		}
	gotoxy(13,20);
        cout<<"Are you ready?";
        sleep(4);
    gotoxy(15,22);
        cout<<"Let's go!";
        sleep(1);
        system("cls");
   			break;
   }
}
void Timer(void)
{
	if(current_level!=3)
	{
	static int sec=0;
	static int min=0;
	static int temp=0;
	static int last_level = current_level;
	if(last_level != current_level)
	{
		min=0;
		sec=0;
		last_level=current_level;
	}
	temp++;
	if (temp == 3)
	{
		sec++;
		temp=0;
	}
	if (sec==60)
	{
		min++;
		sec=0;
	}
	gotoxy(8,32);
	cout << "-------------------------\n";
	gotoxy(8,33);
	cout << "| "<< min << " Minutes | "<<  sec << " Seconds |" << endl;  
	gotoxy(8,34);
	cout << "-------------------------\n";
	}
	else
	{
	static int sec=60;
	static int min=1;
	static int temp=0;
	temp++;
	if (temp == 3)
	{
		sec--;
		temp=0;
	}
	if (sec==-1)
	{
		min--;
		sec=59;
	}
	if(min==0 && sec==0)
	{
		sleep(2);
		cout<<"You lost!\t";
		sleep(1);
		cout<<"You can try again later";
		sleep(3);
		exit(0);
	}
	gotoxy(8,32);
	cout << "-------------------------\n";
	gotoxy(8,33);
	cout << "| "<< min << " Minutes | "<<  sec << " Seconds |" << endl;  
	gotoxy(8,34);
	cout << "-------------------------\n";
	}
}

//check_chafe 
void check_chafe(int slider_moved , int slider_hit)
{
	if (slider_moved != 0 && slider_hit !=-1)
	{
		switch  (slider_moved)
		{
		case slider_right:
			right_chafe(slider_hit);
			break;
		
		case slider_left :
			left_chafe(slider_hit);
		}
	}
	
}


// left_chafe and right_chafe will change the speed of given ball 
void left_chafe(int ball_index)
{
	switch (target_ball[ball_index].heading)
	{
	case north_east:
	case south_east:
		target_ball[ball_index].x_changes -= x_chafe_rate;
		break;
	case north_west:
	case south_west:
		target_ball[ball_index].x_changes += x_chafe_rate;
		break;
	}
}
void right_chafe(int ball_index)
{
	switch (target_ball[ball_index].heading)
	{
	case north_east:
	case south_east:
		target_ball[ball_index].x_changes += x_chafe_rate;
		break;
	case north_west:
	case south_west:
		target_ball[ball_index].x_changes -= x_chafe_rate;
		break;
	}
}

void pause(void)
{
	if (kbhit())
		{
			char pause = getch();
			if (int(pause) == 27)
			{
			cout<<"\n \tPress Enter to continue";
			cin.get();
			}
		}
}

int slider_move(void)
{
	if(kbhit())
	{
		char key = getch();
		if(current_level != 3)
		switch(int(key))
		{
			case 'a':
			case 'A':
				if((slider.x-slider_speed)<minx )
					return 0;
				slider.x -= slider_speed;
				return slider_left;
				break;
			case 'd':
			case 'D':
				if((slider.x+silder_length+slider_speed)>maxx)
					return 0;
				slider.x += slider_speed;
				return slider_right;
				break;
			case 27 :
				cout<<"\n \tPress Enter to continue";
				cin.get();
				break;
			default:
				return 0;
		}
		else
			switch(int(key))
			{
			case 'a':
			case 'A':
				if((slider.x-slider_speed)<minx )
					break;
				slider.x -= slider_speed;
				target_ball[1].pos_x-= slider_speed;
				print_screen();	
				break;
			case 'd':
			case 'D':
				if((slider.x+silder_length+slider_speed)>maxx)
					break;
				slider.x += slider_speed;
				target_ball[1].pos_x += slider_speed;
				print_screen();	
				break;
			case 'e':
			case 'E':
				target_ball[1].heading=north_east;
				print_screen();
				return 0;
				break;
			case 'q':
			case 'Q':
				target_ball[1].heading=north_west;
				print_screen();
				return 0;
				break;					
			}
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

void set_level (int level)
{
	if (level == 1)
	{
		bricks = 6;
		for (int i = 0; i < 9; i++)
		{
			if (i>=3 && i<6)
			{
				brick[i].visibility = false;
				brick[i].del = true;
			}
			else
			{
				brick[i].del = false;
				brick[i].visibility = true;
			}
		}
		target_ball[0].active = true;
	}
	else if (level == 2)
	{
		bricks = 9;
		for (int i = 0; i < 9; i++)
		{
			if (i>=3 && i<6)
			{

				brick[i].health = 2;
				brick[i].ch = '$';
			}
			brick[i].del = false;
			brick[i].visibility = true;
			
		}
		target_ball[0].active = true;
		target_ball[0].x_changes=x_changes_default;
		target_ball[0].y_changes=y_changes_default;
	}
	else if (level == 3)
	{
		bricks = 9;
		for (int i = 0; i < 9; i++)
		{
			if (i>=3 && i<6)
			{
				brick[i].health = 2;
				brick[i].ch = '$';
			}
			brick[i].visibility = true;
			brick[i].del = false;
		}

		for(int i=0;i<max_ball_number;i++)
		{
			target_ball[i].active = true;
			target_ball[i].x_changes=x_changes_default;
			target_ball[i].y_changes=y_changes_default;
		}
	}
	
}

void welcome_page(void) 
{
   while (true)
   {
    print_border();
    print_array();
    
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
      sleep(3);
	for (int i=3; i>0; i--){
	gotoxy(19,21);
    cout<<i;
      	sleep(1);
	}
	system("cls");
   	break;
   }
}

int start(void)
{
	
	level_start();
	slider.x=slider_start_x;
	for(int i=0;i<max_ball_number;i++)
	{
		if(target_ball[i].active)
		{
			target_ball[i].pos_x=ball_start_x;
			target_ball[i].pos_y=ball_start_y;
		}
	}
	//target_ball[0].heading=north_east;
	system("cls");
	print_screen();
	gotoxy(10,22);
	sleep(1);
	while(1)
	{
		if(kbhit)
		{
			char key = getch();
			switch(int(key))
			{
			case 'a':
			case 'A':
				if((slider.x-slider_speed)<minx )
					break;
				slider.x -= slider_speed;
				for(int i=0;i<max_ball_number;i++)
					if(target_ball[i].active)
						target_ball[i].pos_x-= slider_speed;
				print_screen();	
				break;
			case 'd':
			case 'D':
				if((slider.x+silder_length+slider_speed)>maxx)
					break;
				slider.x += slider_speed;
				for(int i=0;i<max_ball_number;i++)
					if(target_ball[i].active)
						target_ball[i].pos_x+= slider_speed;
				print_screen();	
				break;
			case 'e':
			case 'E':
				target_ball[0].heading=north_east;
				print_screen();
				//if(current_level == 3)
				//	target_ball[1].pos_x = target_ball[0].pos_x;
				return 0;
				break;
			case 'q':
			case 'Q':
				target_ball[0].heading=north_west;
				print_screen();
				//if(current_level == 3)
				//	target_ball[1].pos_x = target_ball[0].pos_x;
				return 0;
				break;					
			}	
		}
	}   
}

void instructions(void)
{
	system("cls");
    print_border();
    print_array();
    gotoxy(14,8);
    cout<<"BRICK BREAKER";
	sleep(1);
    gotoxy(14,11);
    cout<<"Instructions";
	sleep(1);
	gotoxy(12,16);
        cout<<"Moving right: 'D'";
    gotoxy(12,18);
        cout<<"Moving left: 'A'";
    gotoxy(10,20);
        cout<<"Heading top right: 'E'";
	gotoxy(10,22);
		cout<<"Heading top left: 'Q'";
	sleep(1);
    gotoxy(6,24);
    cout<<"Press 'Esc' to go back to menu";
      while(1)
	{
		if (kbhit)
		{
		char ch;
		ch = getch();
		if (int(ch) == 27)
		break;	
		}
	}
  menu();
} 

int menu(void)
{
	system("cls");
   while (true)
   {
   
    print_border();
    print_array();
    
    gotoxy(14,8);
    cout<<"BRICK BREAKER";
	sleep(1);
    gotoxy(18,11);
    cout<<"MENU";
	sleep(1);
    gotoxy(7,16);
    cout<<"Press 'S' to start new game";
	sleep(1);
    gotoxy(6,18);
    cout<<"Press 'R' to resume last game";
	sleep(1);
	gotoxy(6,20);
    cout<<"Press 'I' to see instructions";
	sleep(1);
    gotoxy(10,22);
    cout<<"Press 'Esc' to exit";
      while(1)
	{
		if (kbhit)
		{
			char ch;
			ch = getch();
			if (int(ch) == 83 || int(ch) == 115)
			return 0;
			else if (int(ch) == 73 || int(ch) == 105)
			instructions();
			else if (int(ch) == 27)
			{
			gotoxy(1,31);
			exit(0);	
			}
		}	
		else
			system("cls");
	}
   }
} 

void losing(int ball_index)  
{
	static int lose=1;
	if(current_level ==3 )
	{
		target_ball[ball_index].active = false;
		if(target_ball[0].active == false && target_ball[1].active == false)
			lose=3;
		else
			return;	
	}
	
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

void winning(void)
{
	system("cls");
    print_border();
    print_array();
	sleep(1);
	gotoxy(13,8);
        cout<<"BRICK BREAKER";
		sleep(2);
	gotoxy(12,12);
        cout<<"Congratulations";
	sleep(1);
	 gotoxy(15,14);
        cout<<"You won!";
		sleep(3);
		gotoxy(2,31);
	if (current_level != level_numbers)
	{
		current_level ++;
		cout<<"moving to level "<<current_level;
		sleep(2);
		set_level(current_level);
		start();
	}
	else
	{
		exit(0);
	}
}
