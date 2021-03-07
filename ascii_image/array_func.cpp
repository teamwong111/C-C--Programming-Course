#include"all.h"
#include"Array.h"
using namespace std;
Array a(2, 2), b(2, 2), c(2, 2), d(2, 2);//ȫ�ֱ�����������Ծ���Ӽ��˳�����
void Array_menu()//�˵�
{
	cout << "*********************************************************" << endl;
	cout << " *  1 ��ʼ����ά����     2 ����ӷ�     3 �������      *" << endl;
	cout << " *  4 ������           5 ������     6 reshape����   *" << endl;
	cout << " *  7 ��ȡC���Ԫ��      0 �˳�ϵͳ	                 *" << endl;
	cout << "*********************************************************" << endl;
	cout << "ѡ��˵���<0~7>:" << endl;
	return;
}
void init()//�����ܳ�ʼ������ά�ȵ����飬������������Ҫ֧����ά����
{
	Array e(3, 3, 3); //3x3x3
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
			{
				e[i][j][k] = i + j + k;
			}
	cout << "��ʼ����ײ����ݣ�\n";
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
			{
				cout << e[i][j][k] << " ";
			}
	cout << endl;
}
void print_ans()//��ӡ��������ھ���Ӽ��˳�
{
	cout << "c:\n";
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cout << c[i][j] << " ";
		}
		cout << endl;
	}
	cout << "d:\n";
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cout << d[i][j] << " ";
		}
		cout << endl;
	}
}
void matrixplus()//����ӷ�
{
	if (a.shape[0] == b.shape[0] && a.shape[0] == c.shape[0] && a.shape[0] == d.shape[0])//��ͬ����������ӷ�
	{
		c = a + b;
		d = a + 2;
	}
	print_ans();//��ӡ���
}
void matrixsub()//�������
{
	if (a.shape[0] == b.shape[0] && a.shape[0] == c.shape[0] && a.shape[0] == d.shape[0])
	{	
		c = a - b;
		d = a - 2;
	}
	print_ans();
}
void matrixdotp()//������
{
	if (a.shape[0] == b.shape[0] && a.shape[0] == c.shape[0] && a.shape[0] == d.shape[0])
	{
		c = a * b;
		d = a * 2;
	}
	print_ans();
}
void matrixpointdiv()//������,��Ϊ�ײ�����Ϊint�ͣ�����������������Ǹ�����
{
	if (a.shape[0] == b.shape[0] && a.shape[0] == c.shape[0] && a.shape[0] == d.shape[0])
	{
		c = a / b;
		d = a / 2;
	}
	print_ans();
}
void martixreshape()//reshape����
{
	Array f(16);
	for (int i = 0; i < 16; i++)
		f[i] = i;
	f.reshape(4, 4);
	cout << "reshape�����\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << f[i][j] << " ";
		}
		cout << endl;
	}		
}
void getCstyle()//��ȡC���Ԫ���ݲ���
{
	Array g(4);
	for (int i = 0; i < 4; i++)
		g[i] = i;
	int* h = g.get_content();//��������ȡ�������ʵ��
	cout << "��ȡ��C���Ԫ�أ�\n";
	for (int i = 0; i < 4; i++)
		cout << h[i] << ' ';
}
void Array_func()
{
	//Ϊ����a,b��ֵ�����ھ���Ӽ��˳�
	int cnt = 1;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
		{
			a[i][j] = cnt;
			b[i][j] = cnt;
			cnt++;
		}

	char choice;
	char ch;
	while (true) //ע���ѭ���˳�������
	{
		wait_for_enter();
		system("cls"); //��������
		Array_menu(); //���ò˵���ʾ����
		cout << "��Ҫ������˵�ѡ����" << endl;
		cin >> choice;// ��Ҫ������˵�ѡ����choice
		if (choice == '0') //ѡ���˳�
		{
			cout << "\nȷ���˳���?(Y or y)" << endl;
			cin >> ch;
			if (ch == 'y' || ch == 'Y')
				break;
			else
				continue;
		}
		switch (choice)
		{
		case '1':init(); break;
		case '2':matrixplus(); break;
		case '3':matrixsub(); break;
		case '4':matrixdotp(); break;
		case '5':matrixpointdiv(); break;
		case '6':martixreshape(); break;
		case '7':getCstyle(); break;
		default:
			cout << "\n�����������������" << endl;
			wait_for_enter();
		}
		cout << endl;
	}
	//ʹ��a,b,c,d��������
	a.ischild = false;
	b.ischild = false;
	c.ischild = false;
	d.ischild = false;
	return;
}