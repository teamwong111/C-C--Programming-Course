#include "Game.h"		// ��Ϸͷ�ļ�
bool Info::isContinue()
{
	cout << "�Ƿ����?(y/n): \n";
	char tmp;
	cin >> tmp;
	if (tmp == 'Y' || tmp == 'y')
		return true;
	return false;
}
////������ʷ��¼�˵�
void Info::menu()
{
	cout << endl;
	for (int i = 0; i < 57; i++)
	{
		cout << '*';
	}
	cout << endl;
	cout << "\t1 ���Ҽ�¼\t2 ɾ����¼\t3 �޸ļ�¼\n";
	cout << "\t4 ��Ӽ�¼\t5 ��ʾ��¼\t0 �˳�����\n";
	for (int i = 0; i < 57; i++)
	{
		cout << '*';
	}
	cout << endl;
}
//��ʼ����¼����
void Info::init()
{
	ifstream fin("history.txt");
	if (!fin)
	{
		cerr << "�ļ��򲻿�" << endl;
		exit(-1);
	}
	fin >> n;
	info* s = new(nothrow)info;//β�巨��������
	if (s == NULL)
	{
		cout << "û���ڴ�" << endl;
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
				cout << "û���ڴ�" << endl;
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
//��ʾ
void Info::disp()
{
	info* q = head;
	while (q != the_end)
	{
		cout << "�汾��";
		if (q->level == 1)
			cout << "���Ű�";
		else if (q->level == 2)
			cout << "���װ�";
		else
			cout << "�߼���";
		cout << " �û���" << q->username << " �÷֣�" << q->score << endl;
		q = q->next;
	}
}
//����
void Info::searchbyUSER()
{
	cout << "�������û���" << endl;
	char username[10];
	cin >> username;
	info* q = head;
	while (q != the_end)
	{
		if (!strcmp(q->username, username))
		{
			cout << "�汾��";
			if (q->level == 1)
				cout << "���Ű�";
			else if (q->level == 2)
				cout << "���װ�";
			else
				cout << "�߼���";
			cout << " �û���" << q->username << " �÷֣�" << q->score << endl;
		}
		q = q->next;
	}
}
//ɾ��
void Info::delbyID()
{
	while (1)
	{
		int new_no;
		cout << "���������(���������û���ȫ����¼�����У�����ʹ����ʾ��¼��ʾ)" << endl;
		cin >> new_no;
		if (new_no > n)
			cout << "������" << endl;
		else if (head == NULL)
			cout << "û�м�¼" << endl;
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
//�޸�
void Info::modibyID()
{
	while (1)
	{
		int new_no;
		cout << "���������(���������û���ȫ����¼�����У�����ʹ����ʾ��¼��ʾ)" << endl;
		cin >> new_no;
		if (new_no > n)
			cout << "������" << endl;
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
					cout << "������Ҫ�޸ĵ��û���" << endl;
					cin >> username;
					strcpy_s(q->username, username);
				}
			}
		}
		if (!isContinue())
			break;
	}
}
//���
void Info::add()
{
	while (1)
	{
		cout << "������汾(����1�������ţ�2������ף�3����߼�)���û����͵÷�" << endl;
		cin >> the_end->level >> the_end->username >> the_end->score;
		s = new(nothrow)info;
		if (s == NULL)
		{
			cout << "û���ڴ�" << endl;
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
//�ڴ��ͷ�
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
//��ȡ��߷�
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
//ÿ����Ϸ�������¼
void Info::record(int level,char username[],int score)
{
	the_end->level = level;
	strcpy_s(the_end->username,username);
	the_end->score = score;
	s = new(nothrow)info;
	if (s == NULL)
	{
		cout << "û���ڴ�" << endl;
		exit(1);
	}
	else
	{
		the_end->next = s;
		the_end = s;
		s->next = NULL;
	}
}
//�����ļ�
void Info::readin()
{
	ofstream fout("history.txt");
	if (!fout)
	{
		cerr << "�ļ��򲻿�" << endl;
		exit(-1);
	}
	info* q = head;
	int num = 0;//�ȵõ��ܼ�¼��
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
//������ʷ��¼���
void Info::history(Game& A)
{
	cout << endl << "���ڿɶ���ʷ��¼������ɾ�Ĳ�" << endl;
	menu();//�˵�
	init();//��ʼ������
	gethighest(A);//��ȡ��߷�
	int choice;
	char c;
	while (1)
	{
		cout << "ѡ��˵���(0~5):";
		cin >> choice;
		if (choice == 0)       //ѡ���˳�
		{
			cout << "ȷ���˳���?(y/n)" << endl;
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
			cout << "����������������" << endl;
		}
	}
}