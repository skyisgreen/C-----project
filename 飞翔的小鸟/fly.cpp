#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>


int high,width; 
int bird_x,bird_y; 
int bar1_y,bar1_xDown,bar1_xTop; 
int score; 
int bar_y,bar_xTop,bar_xDown; 

void gotoxy(int x,int y) 
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void startup()  
{
	high = 20;
	width = 20;
	bird_x = high/2;
	bird_y = 3;
	bar1_y = width;
	bar1_xDown = high/3;
	bar1_xTop = high/2;
	score = 0;
}

void show()  
{
	gotoxy(0,0);  	
	int i,j;
	
	for (i=0;i<high;i++)
	{
		for (j=0;j<width;j++)
		{
			if ((i==bird_x) && (j==bird_y))
				printf("东哥");  
			else if ((j==bar1_y) && ((i<bar1_xDown)||(i>bar1_xTop)) )
				printf("*");  
			else
				printf(" ");  
		}
		printf("\n");
	}
	printf("得分：%d\n",score);
}	

void updateWithoutInput() 
{
	bird_x ++;
	bar1_y --;
	if (bird_y==bar1_y)
	{
		if ((bird_x>=bar1_xDown)&&(bird_x<=bar1_xTop))
			score++;
		else
		{
			printf("游戏失败\n");
			system("pause");
			exit(0);
		}
	}
	if (bar1_y<=0)  
	{
		bar1_y = width;
		int temp = rand()%int(high*0.8);
		bar1_xDown = temp - high/10;
		bar1_xTop = temp + high/10;
	}
	
	Sleep(150);
}

void updateWithInput()  
{	
	char input;
	if(kbhit())  
	{
		input = getch();  
		if (input == ' ')  
			bird_x = bird_x - 2;
	}
}

int main()
{
	startup();  	
	while (1)  
	{
		show();  
		updateWithoutInput();  
		updateWithInput();    
	}
	return 0;
}   
