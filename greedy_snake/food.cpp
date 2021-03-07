#include "Game.h"
//���캯��
Food::Food()
{
	num = 0;
	memset(place, 0, sizeof(place));
}
//����ʳ��
void Food::create(Snake snake,int n)
{
	int devilnum = 0;//��ħ����
	for (int i = 0; i < 45; i++)
	{
		for (int j = 0; j < 45; j++)
		{
			if (place[i][j] == 7)
				devilnum++;
		}
	}

	int newnum = 0;//�¼ӵ�ʳ����
	if (num == 0||num==devilnum||n==2||n==3)//û��ʳ�ֻ�ж�ħ��������:���³���ʳ��߼�:���³���ʳ��
	{
		newnum = rand() % 5 + 1;
		if (n == 2)//����:���³���ʳ��
		{
			num = 0;
			memset(place, 0, sizeof(place));
		}	
		int i = num; 
		while (i < num+newnum)//����ʳ��
		{
			int x = rand() % 43 + 1;
			int y = rand() % 43 + 1;
			for (int j = 0; j < snake.length; j++)
			{
				if (snake.place[j].y==y&&snake.place[j].x==x||place[y][x]!=0)//���߻�����ʳ��
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
//����ʳ��
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
//�ж��Ƿ��пռ�������
bool Food::full()
{
	if (num > 2000)
		return true;
	return false;
}
