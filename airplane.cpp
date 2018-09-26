#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#define H 20  
#define W 30
#define DJNum 4
int post_x,post_y; 
int dj_x[DJNum],dj_y[DJNum]; 
int book[H][W] = {0};                       
int score; 
int BulletW; 
int DJMoveSpeed; 

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
	post_x = H-1;
	post_y = W/2;
	book[post_x][post_y] = 1;	
	int k;
	for (k=0;k<DJNum;k++)
	{
		dj_x[k] = rand()%2;
		dj_y[k] = rand()%W;
		book[dj_x[k]][dj_y[k]] = 3;
	}
	score = 0;
	BulletW = 0;
	DJMoveSpeed = 20;
}

void show()  
{
	gotoxy(0,0);  
	int i,j;
	for (i=0;i<H;i++)
	{
		for (j=0;j<W;j++)
		{
			if (book[i][j]==0)
				printf(" ");   
			else if (book[i][j]==1)
				printf("**");   
			else if (book[i][j]==2)
				printf("|");   
			else if (book[i][j]==3)
				printf("&\n");
			
		}
		printf("\n");
	}
	printf("得分：%d\n",score);
	Sleep(20);
}	

void updateWithoutInput()  // 与用户输入无关的更新
{
	int i,j,k;
	for (i=0;i<H;i++)
	{
		for (j=0;j<W;j++)
		{
			if (book[i][j]==2) 
			{
				for (k=0;k<DJNum;k++)
				{
					if ((i==dj_x[k]) && (j==dj_y[k]))  // 子弹打中敌机
					{
						score++;                // 加分
						if (score%5==0 && DJMoveSpeed>4)   							                     DJMoveSpeed--;
						if (score%5==0)   
							BulletW++;
						book[dj_x[k]][dj_y[k]] = 0;
						dj_x[k] = rand()%2;           						
dj_y[k] = rand()%W;
						book[dj_x[k]][dj_y[k]] = 3;
						book[i][j] = 0;    					}
				}
				// 子弹向上移动
				book[i][j] = 0;
				if (i>0)
					book[i-1][j] = 2;
			}
		}
	}

	static int speed = 0;  
	if (speed<DJMoveSpeed)
		speed++;

	for (k=0;k<DJNum;k++)
	{
		if ((post_x==dj_x[k]) && (post_y==dj_y[k]))  // 敌机撞本机
		{
			printf("游戏失败啦！\n");
			Sleep(3000);
			system("pause");
			exit(0);
		}

		if (dj_x[k]>H)   // 敌机跑出显示屏幕
		{
			book[dj_x[k]][dj_y[k]] = 0;
			dj_x[k] = rand()%2;           // 产生新的飞机
			dj_y[k] = rand()%W;
			book[dj_x[k]][dj_y[k]] = 3;
			score--;  // 减分
		}

		if (speed ==DJMoveSpeed)
		{
			// 敌机下落
			for (k=0;k<DJNum;k++)
			{
				book[dj_x[k]][dj_y[k]] = 0;
				dj_x[k]++;			
				speed = 0;
				book[dj_x[k]][dj_y[k]] = 3;
			}
		}
	}
}

void updateWithInput()  
{
	char input;
	if(kbhit())  
	{
		input = getch();  
		if (input == 'a' && post_y>0) 
		{
			book[post_x][post_y] = 0;
			post_y--;  // 位置左移
			book[post_x][post_y] = 1;
		}
		else if (input == 'd' && post_y<W-1)
		{
			book[post_x][post_y] = 0;
			post_y++;  // 位置右移
		book[post_x][post_y] = 1;
		}
		else if (input == 'w')
		{
			book[post_x][post_y] = 0;
			post_x--;  // 位置上移
			book[post_x][post_y] = 1;
		}
		else if (input == 's')
		{
			book[post_x][post_y] = 0;
			post_x++;  // 位置下移
			book[post_x][post_y] = 1;
		}
		else if (input == ' ')  // 发射子弹
		{
			int left = post_y-BulletW;
			int right = post_y+BulletW;
			if (left<0)
				left = 0;
			if (right>W-1)
				right = W-1;
			int k;
			for (k=left;k<=right;k++) 
				book[post_x-1][k] = 2;		}		
	}
}

int main()
{
	startup();  	
	while (1) //  游戏循环执行
	{
		show();  // 显示画面
		updateWithoutInput();  
		updateWithInput();  
	}
	return 0;
}

