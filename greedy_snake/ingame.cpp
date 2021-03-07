#include "Game.h"	
//����
void Game::primary()
{
	Snake snake;
	Food food;
	Wall wall;
	food.create(snake,1);//��������ʳ��
	while (1)
	{
		putall();//���Ʊ���
		if (snake.place[0].y > 22)//���ּ��١�������
		{
			Sleep(150);
			times += 0.15;//�ۼ�ʱ��
		}
		else
		{
			Sleep(100);
			times += 0.1;
		}
		setfillcolor(RGB(100, 100, 100));//������Ϸ��
		solidrectangle(0, 0, 450, 450);
		
		ch = '#';// ������Ϣ���
		if (_kbhit())// ������Ϣ��ȡ
			if (keydown(snake.direction) == 5)//���������߷�����Ƿ���ǰ�˳�
				break;
		if (MouseHit())//�����Ϣ��ȡ
			m_msg = GetMouseMsg();

		snake.move();//���ƶ�
		int foodlevel = snake.eatfood(food);//��ʳ��
		if (foodlevel>0&& foodlevel <6)//һ��ʳ��
		{
			score += foodlevel*10;
		}
		else if(foodlevel==6)//������ӷ�
		{
			score += 100;
		}
		else if (foodlevel == 7)//��ħ������
		{
			break;
		}
		food.create(snake,1);//��������ʳ��
		if (snake.kill_by_wall(wall) || snake.kill_by_snake())//�ж�ײǽ��ײ��
			break;

		wall.draw();//��ͼ��UIչʾ
		snake.draw();
		food.draw();
		show(1);

		FlushBatchDraw();
	}
	Sleep(3000);
	if (end())//ÿ����Ϸ����������Ի���
		return;
}
//����
void Game::middle()
{
	Snake snake;
	Food food;
	Wall wall;
	food.create(snake,1);
	while (1)
	{
		putall();
		if (snake.place[0].y > 22)
		{
			Sleep(150);
			times += 0.15;
		}
		else
		{
			Sleep(100);
			times += 0.1;
		}
		setfillcolor(RGB(100, 100, 100));
		solidrectangle(0, 0, 450, 450);
		
		ch = '#';
		if (_kbhit())
			if (keydown(snake.direction) == 5)
				break;
		if (MouseHit())
			m_msg = GetMouseMsg();

		snake.move();
		int foodlevel = snake.eatfood(food);
		if (foodlevel > 0 && foodlevel < 6)
		{
			score += foodlevel * 10;
		}
		else if (foodlevel == 6)
		{
			score += 100;
		}
		else if (foodlevel == 7)
		{
			break;
		}
		food.create(snake,1);
		if (snake.kill_by_wall(wall) || snake.kill_by_snake())//�ؼ���ͬ
		{
			Sleep(2000);
			snake.becomewall(wall);//�߱��ǽ
			if (wall.full())//ǽռ���ռ�
				break;
			else
			{
				snake.create(wall,food);
				food.create(snake,2);//���³���ʳ��
			}
		}

		wall.draw();
		snake.draw();
		food.draw();
		show(2);

		FlushBatchDraw();
	}
	Sleep(3000);
	if (end())
		return;
}
//�߼�
void Game::senior()
{
	Snake snake;
	Food food;
	Wall wall;
	snake.life = 5;
	food.create(snake,1);
	while (1)
	{
		putall();// ���Ʊ���
		if (snake.place[0].y > 22)
		{
			Sleep(150);
			times += 0.15;
		}
		else
		{
			Sleep(100);
			times += 0.1;
		}
		setfillcolor(RGB(100, 100, 100));
		solidrectangle(0, 0, 450, 450);
		
		ch = '#';
		if (_kbhit())
			if (keydown(snake.direction) == 5)
				return;
		if (MouseHit())
			m_msg = GetMouseMsg();

		snake.move();
		int foodlevel = snake.eatfood(food);
		if (foodlevel > 0 && foodlevel < 6)
		{
			score += foodlevel * 10;
		}
		else if (foodlevel == 6)
		{
			score += 100;
		}
		else if (foodlevel == 7)
		{
			break;
		}
		food.create(snake,1);
		if (snake.kill_by_wall(wall) || snake.kill_by_snake())//�ؼ���ͬ
		{
			Sleep(2000);
			snake.becomefood(food);//�߱��ʳ��
			if (food.full())//ʳ��ռ���ռ�
				break;
			else
			{
				snake.create(wall,food);
				food.create(snake, 3);//���³���ʳ��
				snake.life--;
			}
		}
		if (snake.life == 0)//��������Ϊ0
			break;

		wall.draw();
		snake.draw();
		food.draw();
		show(3);

		FlushBatchDraw();
	}
	Sleep(3000);
	if (end())
		return;
}