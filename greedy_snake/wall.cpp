#include "Game.h"
//���캯��
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
//����ǽ
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
//�ж��Ƿ��пռ�������
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