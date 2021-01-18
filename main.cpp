#include <iostream>
using namespace std;

bool print_screen ()
{
    //defing the array
    char screen[30][50];
    for (int i = 0; i < 30; i++)
    {
        if (i==29 || i==0)
        {
            for (int j = 0; j < 50; j++)
            {
                screen[i][j]= '_';
            }
        }
        else{
            for (int j = 0; j < 50; j++)
            {
                screen[i][j]= ' ';
            }
        }
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
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            cout<<screen[i][j];
        }
        cout<<'\n';
    }
    return true;
}

int main()
{
    int a;
    print_screen();
    cin>>a;
}