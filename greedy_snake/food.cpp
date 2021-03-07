#include "Game.h"
//构造函数
Food::Food()
{
	num = 0;
	memset(place, 0, sizeof(place));
}
//出现食物
void Food::create(Snake snake,int n)
{
	int devilnum = 0;//恶魔果数
	for (int i = 0; i < 45; i++)
	{
		for (int j = 0; j < 45; j++)
		{
			if (place[i][j] == 7)
				devilnum++;
		}
	}

	int newnum = 0;//新加的食物数
	if (num == 0||num==devilnum||n==2||n==3)//没有食物、只有恶魔果、进阶:重新出现食物、高级:重新出现食物
	{
		newnum = rand() % 5 + 1;
		if (n == 2)//进阶:重新出现食物
		{
			num = 0;
			memset(place, 0, sizeof(place));
		}	
		int i = num; 
		while (i < num+newnum)//产生食物
		{
			int x = rand() % 43 + 1;
			int y = rand() % 43 + 1;
			for (int j = 0; j < snake.length; j++)
			{
				if (snake.place[j].y==y&&snake.place[j].x==x||place[y][x]!=0)//有蛇或其他食物
				{
					continue;
				}
			}
			place[y][x] = rand() % 7 + 1;
			i++;
		}
		num += newnum;
	}
}
//画出食物
void Food::draw()
{
	for (int i = 0; i < 45; i++)
	{
		for (int j = 0; j < 45; j++)
		{
			if (place[i][j] != 0)
			{
				if(place[i][j]==6)
					setfillcolor(RGB(255, 255, 255));
				else if(place[i][j] == 7)
					setfillcolor(RGB(0, 0, 0));
				else
					setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
				fillrectangle(j * 10, i * 10, j * 10 + 10, i * 10 + 10);
			}
		}
	}
}
//判断是否还有空间生成蛇
bool Food::full()
{
	if (num > 2000)
		return true;
	return false;
}
