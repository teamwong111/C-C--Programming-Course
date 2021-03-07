#include "Game.h"
//构造函数
Snake::Snake()
{
	pos xy;
	xy = { 4,2 };
	place.push_back(xy);
	length = 1;
	color = RGB(100,149,237);
	direction = Right;
	next = { 0,0 };
	life = 1;
}
//生成蛇
void Snake::create(Wall wall,Food food)
{
	place.clear();//清空
	pos xy;
	while (1)
	{
		xy.x = rand() % 43 + 1;
		xy.y = rand() % 43 + 1;
		if (wall.place[xy.y][xy.x] == 0&&food.place[xy.y][xy.x]==0)
		{
			place.push_back(xy);
			break;
		}
	}
	length = 1;
	color = RGB(100, 149, 237);
	direction = rand() % 4 + 1;
	next = { 0,0 };
}
//蛇移动
void Snake::move()
{
	next = place[length - 1];
	for (int i =length-1;i>0;i--)//将除蛇头以外的节移动到它的前面一节
		place[i] = place[i - 1];
	switch (direction)//根据当前移动方向移动蛇头
	{
	case Right:
		place[0].x += 1;
		break;
	case Left:
		place[0].x -= 1;
		break;
	case up:
		place[0].y -= 1;
		break;
	case down:
		place[0].y += 1;
	}
}
// 吃食物
int Snake::eatfood(Food &food)
{
	int level = food.place[place[0].y][place[0].x];//吃到食物的级别：0没吃到，1到5正常，6精灵果，7恶魔果
	if (level!=0)
	{
		length++;
		place.push_back(next);//新增一个节到预留位置
		food.num--;
		food.place[place[0].y][place[0].x] = 0;
		return level;
	}
	return 0;
}
//撞墙
bool Snake::kill_by_wall(Wall wall)
{
	if (wall.place[place[0].y][place[0].x] == 1)
	{
		for (int i = 0; i <= length - 2; i++)//返回到撞墙之前的状态
			place[i] = place[i + 1];
		place[length - 1] = next;
		return true;		
	}
	return false;
}
//撞到蛇
bool Snake::kill_by_snake()
{
	for (int i = 1; i < length; i++)
	{
		if (place[i].x == place[0].x && place[i].y == place[0].y)
			return true;
	}
	return false;
}
// 画蛇，部分UI
void Snake::draw()
{
	for (int i = 0; i < length; i++)
	{
		setfillcolor(color);
		fillrectangle(place[i].x*10, place[i].y*10, place[i].x*10 + 10, place[i].y*10 + 10);
	}

	settextstyle(20, 0, L"微软雅黑");
	settextcolor(WHITE);
	TCHAR s[10];
	outtextxy(480, 50, _T("长度"));	
	_stprintf_s(s, _T("%d"), length);
	outtextxy(550, 50, s);
	outtextxy(480, 100, _T("生命"));	
	_stprintf_s(s, _T("%d"), life);
	outtextxy(550, 100, s);	
}
//蛇变成墙
void Snake::becomewall(Wall &wall)
{
	for (int i = 0; i < length; i++)
	{
		wall.place[place[i].y][place[i].x] = 1;
	}
}
//蛇变成食物
void Snake::becomefood(Food& food)
{
	for (int i = 0; i < length; i++)
	{
		food.place[place[i].y][place[i].x] = rand() % 5 + 1;;
	}
	food.num += length;
}