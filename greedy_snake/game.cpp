#include "Game.h"
//登录
void Game::login()
{
	cout << "本程序为贪吃蛇大作战，程序进行顺序如下：\n";
	cout << "首先登录，然后可操作历史记录，然后进入游戏，游戏结束后可再次操作历史纪录，然后结束\n";
	cout << "文件保存在history.txt(里面有部分初始数据)\n";
	cout << "主要实现加分项：\n";
	cout << "1.部分图形化. 发现操作历史纪录这一部分的控件太难做，同时考虑逻辑因素，所以没有做登录和历史纪录的图形化\n";
	cout << "2.更多的游戏逻辑:加速区(上半部)减速区(下半部)、精灵果(白色)和恶果(黑色)\n";
	cout << "---------------------------------------------------------------\n";
	cout << "欢迎来到贪吃蛇大作战，请先输入账号(长度小于10)进行登录\n\n账号：";
	cin >> username;
	cout << "\n登陆成功\n";
}
//游戏入口，游戏开始界面，选择游戏模式
void Game::game(Info B)
{
	cout << "现在进入真正的游戏";
	Sleep(3000);
	initgraph(640, 450);
	setbkmode(TRANSPARENT);
	BeginBatchDraw();
	while (1)
	{
		times = 0;
		score = 0;

		if (_kbhit())//键盘消息获取
		{
			ch = _getch();
			if (ch == 27)//按 Esc 退出
			{
				break;
			}
		}

		if (MouseHit())//鼠标消息获取
			m_msg = GetMouseMsg();

		putall();//绘制背景
		settextcolor(WHITE);
		settextstyle(70, 0, L"微软雅黑");
		outtextxy(235, 85, L"贪吃蛇");//标题输出
		if (button(280, 200, L"　入门　"))//控件
		{
			primary();//入门
			B.record(1, username, score);//记录游戏信息
		}

		if (button(280, 250, L"　进阶　"))
		{
			middle();//进阶
			B.record(2, username, score);
		}

		if (button(280, 300, L"　高级　"))
		{
			senior();//高级
			B.record(3, username, score);
		}

		if (button(280, 350, L"　帮助　"))
			help();//帮助信息

		settextcolor(WHITE);
		outtextxy(249, 400, L"按 Esc 退出游戏");

		FlushBatchDraw();
	}

	EndBatchDraw();
}
//绘制背景
void Game::putall()
{
	setbkcolor(RGB(50, 50, 50));
	cleardevice();
}
//放置按钮
bool Game::button(int a, int b, const wchar_t str[])
{
	static int x, y;//鼠标坐标																
	x = m_msg.x;//获取坐标
	y = m_msg.y;

	setfillcolor(RGB(100, 100, 100));//绘制边框		
	solidrectangle(a - 25, b, a + 19 * wcslen(str) + 25, b + 30);																		
	if (x > a - 25 && (size_t)x < a + 19 * wcslen(str) + 25 && y > b && y < b + 30)//获得焦点显示
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a - 25, b, a + 19 * wcslen(str) + 25, b + 30);
		if (m_msg.uMsg == WM_LBUTTONUP)
		{
			m_msg.uMsg = WM_MOUSEMOVE;
			return 1;
		}
	}
	settextstyle(25, 0, L"微软雅黑");//输出文字
	settextcolor(WHITE);
	outtextxy(a, b + 3, str);

	return 0;
}
//绘制对话框
int Game::putmessagebox(int x, int y, int wight, int hight, const wchar_t title[], const wchar_t* text[], int g_num, int var)
{
	setbkmode(TRANSPARENT);
	while (1)
	{
		if (_kbhit())//键盘消息清空								
			ch = _getch();

		if (MouseHit())
			m_msg = GetMouseMsg();//鼠标消息获取				

		setfillcolor(RGB(25, 25, 25));//绘制边框
		solidrectangle(x, y, x + wight, y + hight);

		settextstyle(30, 0, L"微软雅黑");//输出标题
		outtextxy(x + 20, y + 10, title);
		for (int i = 0; i < g_num; i++)				
		{
			settextstyle(18, 0, L"微软雅黑");
			outtextxy(x + 20, y + 45 + i * 20, text[i]);
		}

		if (var == MY_OK)//按钮放置							
		{
			if (button(x + wight - 70, y + hight - 37, L"确定"))
				return 0;
		}
		else if (var == MY_YESNO)
		{
			if (button(x + wight - 125, y + hight - 37, L"是"))
				return 1;

			if (button(x + wight - 50, y + hight - 37, L"否"))
				return 0;
		}
		FlushBatchDraw();
	}
	return 0;
}
//帮助信息
void Game::help()
{
	while (1)
	{
		if (MouseHit())//鼠标消息获取							
			m_msg = GetMouseMsg();

		putall();//绘制背景								

		settextcolor(WHITE);//标题输出
		settextstyle(52, 0, L"黑体");
		outtextxy(250 + 3, 30 + 3, L"帮 助");		

		setfillcolor(RGB(100, 100, 100));//绘制边框
		setlinecolor(BLACK);
		setlinestyle(PS_SOLID, 5);
		fillrectangle(125, 120, 510, 360);			

		settextstyle(25, 0, L"微软雅黑");//信息输出
		outtextxy(140, 130, L"游戏开始选择不同关卡");
		outtextxy(140, 170, L"有三种：");
		outtextxy(140, 200, L"入门");
		outtextxy(140, 230, L"进阶");
		outtextxy(140, 260, L"高级");
		outtextxy(140, 290, L"选择后，进入游戏");
		outtextxy(140, 320, L"WSAD或上下左右操作");	

		if (button(280, 400, L"回到主页"))//回到主页按钮					
			break;

		FlushBatchDraw();
	}
}
//按键
int Game::keydown(int &direction)
{
	char userKey = _getch();
	if (userKey == 27)//提前退出游戏，返回5则结束
	{
		if (end())
			return 5;
		else
			return 0;
	}
	if (userKey == -32)
		userKey = -_getch();//获取具体方向
	switch (userKey)
	{
	case 'w':
	case 'W':
	case -72:
		if (direction != down)
			direction = up;
		break;
	case 's':
	case 'S':
	case -80:
		if (direction != up)
			direction = down;
		break;
	case 'a':
	case 'A':
	case -75:
		if (direction != Right)
			direction = Left;
		break;
	case 'd':
	case 'D':
	case -77:
		if (direction != Left)
			direction = Right;
		break;
	}
	return direction;
}
//部分UI显示
void Game::show(int level)
{
	settextstyle(20, 0, L"微软雅黑");
	TCHAR s[10];
	outtextxy(480, 150, _T("分数"));
	_stprintf_s(s, _T("%d"), score);
	outtextxy(550, 150, s);
	outtextxy(480, 200, _T("历史最高分"));

	if (score > highestscore[level-1])//判定最高分
		highestscore[level-1] = score;

	_stprintf_s(s, _T("%d"), highestscore[level-1]);
	outtextxy(550, 200, s);
	int second = int(times);
	int decimal = int((times * 100)) % 100;
	outtextxy(480, 250, _T("时间"));
	_stprintf_s(s, _T("%d:"), second);
	outtextxy(550, 250, s);
	_stprintf_s(s, _T("%d"), decimal);
	if (second < 10 && second>0)
		outtextxy(565, 250, s);
	else if(second < 100 && second>10)
		outtextxy(575, 250, s);
	else if (second>100)
		outtextxy(585, 250, s);
	outtextxy(480, 300, _T("按ESC可提前结束游戏"));
}
//每次游戏结束后产生对话框
bool Game::end()
{
	wchar_t title[50];
	swprintf_s(title, L"游戏时长 %d s\0", int(times));
	while (1)
	{
		if (_kbhit())//键盘消息获取				
			ch = _getch();

		if (MouseHit())//鼠标消息获取
			m_msg = GetMouseMsg();	

		putall();//绘制背景				

		settextcolor(WHITE);//标题输出
		settextstyle(52, 0, L"黑体");
		outtextxy(140, 90, title);		

		if (button(273, 300, L"回到主页"))//回到主页按钮
		{
			const wchar_t* text[10];
			text[0] = L"你确定你要回到主页吗？\n";
			button(273, 300, L"回到主页");
			if (putmessagebox(120, 165, 400, 150, L"回到主页", text, 1, MY_YESNO))//回到主页对话框
			{
				return 1;
			}
		}
		FlushBatchDraw();
	}
	return 0;
}