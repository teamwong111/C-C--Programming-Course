#include "Game.h"
//构造函数
Wall::Wall()
{
	memset(place, 0, sizeof(place));	
	for (int i = 0; i < 45; i++)
	{
		place[0][i] = 1;
		place[44][i] = 1;
		place[i][0] = 1;
		place[i][44] = 1;
	}
}
//画出墙
void Wall::draw()
{
	setfillcolor(RGB(255,215,0));
	for (int i = 0; i < 45; i++)
	{
		for (int j = 0; j < 45; j++)
		{
			if(place[i][j] == 1)
				fillrectangle(j * 10, i * 10, j * 10 + 10, i * 10 + 10);
		}
	}
}
//判断是否还有空间生成蛇
bool Wall::full()
{
	int num = 0;
	for (int i = 0; i < 45; i++)
	{
		for (int j = 0; j < 45; j++)
		{
			if (place[i][j] == 1)
				num++;
		}
	}
	if (num > 2000)
		return true;
	return false;
}