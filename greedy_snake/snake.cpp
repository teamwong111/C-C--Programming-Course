#include "Game.h"
//���캯��
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
//������
void Snake::create(Wall wall,Food food)
{
	place.clear();//���
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
//���ƶ�
void Snake::move()
{
	next = place[length - 1];
	for (int i =length-1;i>0;i--)//������ͷ����Ľ��ƶ�������ǰ��һ��
		place[i] = place[i - 1];
	switch (direction)//���ݵ�ǰ�ƶ������ƶ���ͷ
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
// ��ʳ��
int Snake::eatfood(Food &food)
{
	int level = food.place[place[0].y][place[0].x];//�Ե�ʳ��ļ���0û�Ե���1��5������6�������7��ħ��
	if (level!=0)
	{
		length++;
		place.push_back(next);//����һ���ڵ�Ԥ��λ��
		food.num--;
		food.place[place[0].y][place[0].x] = 0;
		return level;
	}
	return 0;
}
//ײǽ
bool Snake::kill_by_wall(Wall wall)
{
	if (wall.place[place[0].y][place[0].x] == 1)
	{
		for (int i = 0; i <= length - 2; i++)//���ص�ײǽ֮ǰ��״̬
			place[i] = place[i + 1];
		place[length - 1] = next;
		return true;		
	}
	return false;
}
//ײ����
bool Snake::kill_by_snake()
{
	for (int i = 1; i < length; i++)
	{
		if (place[i].x == place[0].x && place[i].y == place[0].y)
			return true;
	}
	return false;
}
// ���ߣ�����UI
void Snake::draw()
{
	for (int i = 0; i < length; i++)
	{
		setfillcolor(color);
		fillrectangle(place[i].x*10, place[i].y*10, place[i].x*10 + 10, place[i].y*10 + 10);
	}

	settextstyle(20, 0, L"΢���ź�");
	settextcolor(WHITE);
	TCHAR s[10];
	outtextxy(480, 50, _T("����"));	
	_stprintf_s(s, _T("%d"), length);
	outtextxy(550, 50, s);
	outtextxy(480, 100, _T("����"));	
	_stprintf_s(s, _T("%d"), life);
	outtextxy(550, 100, s);	
}
//�߱��ǽ
void Snake::becomewall(Wall &wall)
{
	for (int i = 0; i < length; i++)
	{
		wall.place[place[i].y][place[i].x] = 1;
	}
}
//�߱��ʳ��
void Snake::becomefood(Food& food)
{
	for (int i = 0; i < length; i++)
	{
		food.place[place[i].y][place[i].x] = rand() % 5 + 1;;
	}
	food.num += length;
}