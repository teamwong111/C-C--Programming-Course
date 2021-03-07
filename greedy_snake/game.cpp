#include "Game.h"
//��¼
void Game::login()
{
	cout << "������Ϊ̰���ߴ���ս���������˳�����£�\n";
	cout << "���ȵ�¼��Ȼ��ɲ�����ʷ��¼��Ȼ�������Ϸ����Ϸ��������ٴβ�����ʷ��¼��Ȼ�����\n";
	cout << "�ļ�������history.txt(�����в��ֳ�ʼ����)\n";
	cout << "��Ҫʵ�ּӷ��\n";
	cout << "1.����ͼ�λ�. ���ֲ�����ʷ��¼��һ���ֵĿؼ�̫������ͬʱ�����߼����أ�����û������¼����ʷ��¼��ͼ�λ�\n";
	cout << "2.�������Ϸ�߼�:������(�ϰ벿)������(�°벿)�������(��ɫ)�Ͷ��(��ɫ)\n";
	cout << "---------------------------------------------------------------\n";
	cout << "��ӭ����̰���ߴ���ս�����������˺�(����С��10)���е�¼\n\n�˺ţ�";
	cin >> username;
	cout << "\n��½�ɹ�\n";
}
//��Ϸ��ڣ���Ϸ��ʼ���棬ѡ����Ϸģʽ
void Game::game(Info B)
{
	cout << "���ڽ�����������Ϸ";
	Sleep(3000);
	initgraph(640, 450);
	setbkmode(TRANSPARENT);
	BeginBatchDraw();
	while (1)
	{
		times = 0;
		score = 0;

		if (_kbhit())//������Ϣ��ȡ
		{
			ch = _getch();
			if (ch == 27)//�� Esc �˳�
			{
				break;
			}
		}

		if (MouseHit())//�����Ϣ��ȡ
			m_msg = GetMouseMsg();

		putall();//���Ʊ���
		settextcolor(WHITE);
		settextstyle(70, 0, L"΢���ź�");
		outtextxy(235, 85, L"̰����");//�������
		if (button(280, 200, L"�����š�"))//�ؼ�
		{
			primary();//����
			B.record(1, username, score);//��¼��Ϸ��Ϣ
		}

		if (button(280, 250, L"�����ס�"))
		{
			middle();//����
			B.record(2, username, score);
		}

		if (button(280, 300, L"���߼���"))
		{
			senior();//�߼�
			B.record(3, username, score);
		}

		if (button(280, 350, L"��������"))
			help();//������Ϣ

		settextcolor(WHITE);
		outtextxy(249, 400, L"�� Esc �˳���Ϸ");

		FlushBatchDraw();
	}

	EndBatchDraw();
}
//���Ʊ���
void Game::putall()
{
	setbkcolor(RGB(50, 50, 50));
	cleardevice();
}
//���ð�ť
bool Game::button(int a, int b, const wchar_t str[])
{
	static int x, y;//�������																
	x = m_msg.x;//��ȡ����
	y = m_msg.y;

	setfillcolor(RGB(100, 100, 100));//���Ʊ߿�		
	solidrectangle(a - 25, b, a + 19 * wcslen(str) + 25, b + 30);																		
	if (x > a - 25 && (size_t)x < a + 19 * wcslen(str) + 25 && y > b && y < b + 30)//��ý�����ʾ
	{
		setfillcolor(RGB(150, 150, 150));
		solidrectangle(a - 25, b, a + 19 * wcslen(str) + 25, b + 30);
		if (m_msg.uMsg == WM_LBUTTONUP)
		{
			m_msg.uMsg = WM_MOUSEMOVE;
			return 1;
		}
	}
	settextstyle(25, 0, L"΢���ź�");//�������
	settextcolor(WHITE);
	outtextxy(a, b + 3, str);

	return 0;
}
//���ƶԻ���
int Game::putmessagebox(int x, int y, int wight, int hight, const wchar_t title[], const wchar_t* text[], int g_num, int var)
{
	setbkmode(TRANSPARENT);
	while (1)
	{
		if (_kbhit())//������Ϣ���								
			ch = _getch();

		if (MouseHit())
			m_msg = GetMouseMsg();//�����Ϣ��ȡ				

		setfillcolor(RGB(25, 25, 25));//���Ʊ߿�
		solidrectangle(x, y, x + wight, y + hight);

		settextstyle(30, 0, L"΢���ź�");//�������
		outtextxy(x + 20, y + 10, title);
		for (int i = 0; i < g_num; i++)				
		{
			settextstyle(18, 0, L"΢���ź�");
			outtextxy(x + 20, y + 45 + i * 20, text[i]);
		}

		if (var == MY_OK)//��ť����							
		{
			if (button(x + wight - 70, y + hight - 37, L"ȷ��"))
				return 0;
		}
		else if (var == MY_YESNO)
		{
			if (button(x + wight - 125, y + hight - 37, L"��"))
				return 1;

			if (button(x + wight - 50, y + hight - 37, L"��"))
				return 0;
		}
		FlushBatchDraw();
	}
	return 0;
}
//������Ϣ
void Game::help()
{
	while (1)
	{
		if (MouseHit())//�����Ϣ��ȡ							
			m_msg = GetMouseMsg();

		putall();//���Ʊ���								

		settextcolor(WHITE);//�������
		settextstyle(52, 0, L"����");
		outtextxy(250 + 3, 30 + 3, L"�� ��");		

		setfillcolor(RGB(100, 100, 100));//���Ʊ߿�
		setlinecolor(BLACK);
		setlinestyle(PS_SOLID, 5);
		fillrectangle(125, 120, 510, 360);			

		settextstyle(25, 0, L"΢���ź�");//��Ϣ���
		outtextxy(140, 130, L"��Ϸ��ʼѡ��ͬ�ؿ�");
		outtextxy(140, 170, L"�����֣�");
		outtextxy(140, 200, L"����");
		outtextxy(140, 230, L"����");
		outtextxy(140, 260, L"�߼�");
		outtextxy(140, 290, L"ѡ��󣬽�����Ϸ");
		outtextxy(140, 320, L"WSAD���������Ҳ���");	

		if (button(280, 400, L"�ص���ҳ"))//�ص���ҳ��ť					
			break;

		FlushBatchDraw();
	}
}
//����
int Game::keydown(int &direction)
{
	char userKey = _getch();
	if (userKey == 27)//��ǰ�˳���Ϸ������5�����
	{
		if (end())
			return 5;
		else
			return 0;
	}
	if (userKey == -32)
		userKey = -_getch();//��ȡ���巽��
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
//����UI��ʾ
void Game::show(int level)
{
	settextstyle(20, 0, L"΢���ź�");
	TCHAR s[10];
	outtextxy(480, 150, _T("����"));
	_stprintf_s(s, _T("%d"), score);
	outtextxy(550, 150, s);
	outtextxy(480, 200, _T("��ʷ��߷�"));

	if (score > highestscore[level-1])//�ж���߷�
		highestscore[level-1] = score;

	_stprintf_s(s, _T("%d"), highestscore[level-1]);
	outtextxy(550, 200, s);
	int second = int(times);
	int decimal = int((times * 100)) % 100;
	outtextxy(480, 250, _T("ʱ��"));
	_stprintf_s(s, _T("%d:"), second);
	outtextxy(550, 250, s);
	_stprintf_s(s, _T("%d"), decimal);
	if (second < 10 && second>0)
		outtextxy(565, 250, s);
	else if(second < 100 && second>10)
		outtextxy(575, 250, s);
	else if (second>100)
		outtextxy(585, 250, s);
	outtextxy(480, 300, _T("��ESC����ǰ������Ϸ"));
}
//ÿ����Ϸ����������Ի���
bool Game::end()
{
	wchar_t title[50];
	swprintf_s(title, L"��Ϸʱ�� %d s\0", int(times));
	while (1)
	{
		if (_kbhit())//������Ϣ��ȡ				
			ch = _getch();

		if (MouseHit())//�����Ϣ��ȡ
			m_msg = GetMouseMsg();	

		putall();//���Ʊ���				

		settextcolor(WHITE);//�������
		settextstyle(52, 0, L"����");
		outtextxy(140, 90, title);		

		if (button(273, 300, L"�ص���ҳ"))//�ص���ҳ��ť
		{
			const wchar_t* text[10];
			text[0] = L"��ȷ����Ҫ�ص���ҳ��\n";
			button(273, 300, L"�ص���ҳ");
			if (putmessagebox(120, 165, 400, 150, L"�ص���ҳ", text, 1, MY_YESNO))//�ص���ҳ�Ի���
			{
				return 1;
			}
		}
		FlushBatchDraw();
	}
	return 0;
}