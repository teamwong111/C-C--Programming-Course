#include "Game.h"		// 游戏头文件
bool Info::isContinue()
{
	cout << "是否继续?(y/n): \n";
	char tmp;
	cin >> tmp;
	if (tmp == 'Y' || tmp == 'y')
		return true;
	return false;
}
////操作历史纪录菜单
void Info::menu()
{
	cout << endl;
	for (int i = 0; i < 57; i++)
	{
		cout << '*';
	}
	cout << endl;
	cout << "\t1 查找记录\t2 删除记录\t3 修改记录\n";
	cout << "\t4 添加记录\t5 显示记录\t0 退出操作\n";
	for (int i = 0; i < 57; i++)
	{
		cout << '*';
	}
	cout << endl;
}
//初始化记录链表
void Info::init()
{
	ifstream fin("history.txt");
	if (!fin)
	{
		cerr << "文件打不开" << endl;
		exit(-1);
	}
	fin >> n;
	info* s = new(nothrow)info;//尾插法建立链表
	if (s == NULL)
	{
		cout << "没有内存" << endl;
		exit(1);
	}
	else
	{
		head = the_end = s;
		for (int i = 0; i < n; i++)
		{
			fin >> s->level >> s->username >> s->score;
			s = new(nothrow)info;
			if (s == NULL)
			{
				cout << "没有内存" << endl;
				exit(1);
			}
			else
			{
				the_end->next = s;
				the_end = s;
				s->next = NULL;
			}
		}
	}
	fin.close();
}
//显示
void Info::disp()
{
	info* q = head;
	while (q != the_end)
	{
		cout << "版本：";
		if (q->level == 1)
			cout << "入门版";
		else if (q->level == 2)
			cout << "进阶版";
		else
			cout << "高级版";
		cout << " 用户：" << q->username << " 得分：" << q->score << endl;
		q = q->next;
	}
}
//查找
void Info::searchbyUSER()
{
	cout << "请输入用户名" << endl;
	char username[10];
	cin >> username;
	info* q = head;
	while (q != the_end)
	{
		if (!strcmp(q->username, username))
		{
			cout << "版本：";
			if (q->level == 1)
				cout << "入门版";
			else if (q->level == 2)
				cout << "进阶版";
			else
				cout << "高级版";
			cout << " 用户：" << q->username << " 得分：" << q->score << endl;
		}
		q = q->next;
	}
}
//删除
void Info::delbyID()
{
	while (1)
	{
		int new_no;
		cout << "请输入序号(根据所有用户的全部记录的序列，可先使用显示记录显示)" << endl;
		cin >> new_no;
		if (new_no > n)
			cout << "不存在" << endl;
		else if (head == NULL)
			cout << "没有记录" << endl;
		else
		{
			n--;
			info* p = head, * q = p;
			int i = 1;
			while (p != the_end && i!= new_no)
			{
				i++;
				q = p;
				p = p->next;
			}
			if (p == head)
			{
				head = p->next;
				delete p;
			}
			else if (p != the_end)
			{
				q->next = p->next;
				delete p;
			}
		}
		if (!isContinue())
			break;
	}
}
//修改
void Info::modibyID()
{
	while (1)
	{
		int new_no;
		cout << "请输入序号(根据所有用户的全部记录的序列，可先使用显示记录显示)" << endl;
		cin >> new_no;
		if (new_no > n)
			cout << "不存在" << endl;
		else
		{
			info* q;
			int i=0;
			char username[10];
			for (q = head; q != the_end; q = q->next)
			{
				i++;
				if (i == new_no)
				{
					cout << "请输入要修改的用户名" << endl;
					cin >> username;
					strcpy_s(q->username, username);
				}
			}
		}
		if (!isContinue())
			break;
	}
}
//添加
void Info::add()
{
	while (1)
	{
		cout << "请输入版本(输入1代表入门，2代表进阶，3代表高级)、用户名和得分" << endl;
		cin >> the_end->level >> the_end->username >> the_end->score;
		s = new(nothrow)info;
		if (s == NULL)
		{
			cout << "没有内存" << endl;
			exit(1);
		}
		else
		{
			n++;
			the_end->next = s;
			the_end = s;
			s->next = NULL;
		}
		if (!isContinue())
			break;
	}
}
//内存释放
void Info::release()
{
	info* q = head, * p;
	while (q != the_end)
	{
		p = q;
		q = q->next;
		delete p;
	}
	delete q;
}
//获取最高分
void Info::gethighest(Game& A)
{
	info* q = head;
	for(int i=0;i<3;i++)
		A.highestscore[i] = 0;
	while (q != the_end)
	{
		if (!strcmp(q->username, A.username))
		{
			if (A.highestscore[q->level-1] < q->score)
				A.highestscore[q->level-1] = q->score;
		}
		q = q->next;
	}
}
//每次游戏结束后记录
void Info::record(int level,char username[],int score)
{
	the_end->level = level;
	strcpy_s(the_end->username,username);
	the_end->score = score;
	s = new(nothrow)info;
	if (s == NULL)
	{
		cout << "没有内存" << endl;
		exit(1);
	}
	else
	{
		the_end->next = s;
		the_end = s;
		s->next = NULL;
	}
}
//读入文件
void Info::readin()
{
	ofstream fout("history.txt");
	if (!fout)
	{
		cerr << "文件打不开" << endl;
		exit(-1);
	}
	info* q = head;
	int num = 0;//先得到总记录数
	while (q->next != NULL)
	{
		num++;
		q = q->next;
	}
	fout << num << endl;
	q = head;
	while (q->next != NULL)
	{
		fout << q->level << " " << q->username << " " << q->score << endl;
		q = q->next;
	}
	fout.close();
}
//操作历史纪录入口
void Info::history(Game& A)
{
	cout << endl << "现在可对历史纪录进行增删改查" << endl;
	menu();//菜单
	init();//初始化链表
	gethighest(A);//获取最高分
	int choice;
	char c;
	while (1)
	{
		cout << "选择菜单项(0~5):";
		cin >> choice;
		if (choice == 0)       //选择退出
		{
			cout << "确定退出吗?(y/n)" << endl;
			cin >> c;
			if (c == 'y' || c == 'Y')
			{
				break;
			}
			else
				continue;
		}
		switch (choice)
		{
		case 1: searchbyUSER(); break;
		case 2: delbyID(); break;
		case 3: modibyID(); break;
		case 4: add(); break;
		case 5: disp(); break;
		default:
			cout << "输入错误，请从新输入" << endl;
		}
	}
}