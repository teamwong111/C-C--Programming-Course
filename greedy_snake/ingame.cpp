#include "Game.h"	
//入门
void Game::primary()
{
	Snake snake;
	Food food;
	Wall wall;
	food.create(snake,1);//正常出现食物
	while (1)
	{
		putall();//绘制背景
		if (snake.place[0].y > 22)//划分加速、减速区
		{
			Sleep(150);
			times += 0.15;//累加时间
		}
		else
		{
			Sleep(100);
			times += 0.1;
		}
		setfillcolor(RGB(100, 100, 100));//绘制游戏区
		solidrectangle(0, 0, 450, 450);
		
		ch = '#';// 键盘消息清空
		if (_kbhit())// 键盘消息获取
			if (keydown(snake.direction) == 5)//按键决定蛇方向和是否提前退出
				break;
		if (MouseHit())//鼠标消息获取
			m_msg = GetMouseMsg();

		snake.move();//蛇移动
		int foodlevel = snake.eatfood(food);//吃食物
		if (foodlevel>0&& foodlevel <6)//一般食物
		{
			score += foodlevel*10;
		}
		else if(foodlevel==6)//精灵果加分
		{
			score += 100;
		}
		else if (foodlevel == 7)//恶魔果死亡
		{
			break;
		}
		food.create(snake,1);//正常出现食物
		if (snake.kill_by_wall(wall) || snake.kill_by_snake())//判断撞墙、撞蛇
			break;

		wall.draw();//绘图及UI展示
		snake.draw();
		food.draw();
		show(1);

		FlushBatchDraw();
	}
	Sleep(3000);
	if (end())//每次游戏结束后产生对话框
		return;
}
//进阶
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
		if (snake.kill_by_wall(wall) || snake.kill_by_snake())//关键不同
		{
			Sleep(2000);
			snake.becomewall(wall);//蛇变成墙
			if (wall.full())//墙占满空间
				break;
			else
			{
				snake.create(wall,food);
				food.create(snake,2);//重新出现食物
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
//高级
void Game::senior()
{
	Snake snake;
	Food food;
	Wall wall;
	snake.life = 5;
	food.create(snake,1);
	while (1)
	{
		putall();// 绘制背景
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
		if (snake.kill_by_wall(wall) || snake.kill_by_snake())//关键不同
		{
			Sleep(2000);
			snake.becomefood(food);//蛇变成食物
			if (food.full())//食物占满空间
				break;
			else
			{
				snake.create(wall,food);
				food.create(snake, 3);//重新出现食物
				snake.life--;
			}
		}
		if (snake.life == 0)//蛇生命数为0
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