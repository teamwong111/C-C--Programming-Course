#include"all.h"
using namespace std;
void wait_for_enter()//�ȴ�����
{
	cout << endl << "���س�������";
	while (_getch() != '\r');
	cout << endl << endl;
}
void main_menu()//�˵�
{
	cout << "******************************" << endl;
	cout << "*     1 Array����ع��ܲ���  *" << endl;
	cout << "*     2 �ַ�ͼƬ���         *" << endl;
	cout << "*     3 �ַ���Ƶ���         *" << endl;
	cout << "*     0 �˳�ϵͳ             *" << endl;
	cout << "******************************" << endl;
	cout << "ѡ��˵���<0~3>:" << endl;
	return;
}
int main()
{
	cout << "����������ͣʱ���밴�س����Լ���\nͼƬ����Ƶ���ݿɸ���ע����Ϣ����\n";
	// ������ر���
	char choice;
	char ch;
	while (true) //ע���ѭ���˳�������
	{
		wait_for_enter();
		system("cls"); //��������
		main_menu(); //���ò˵���ʾ����
		cout << "��Ҫ������˵�ѡ����" << endl;
		cin >> choice;// ��Ҫ������˵�ѡ����choice
		if (choice == '0') //ѡ���˳�
		{
			cout << "\nȷ���˳���?��Y or y��" << endl;
			cin >> ch;
			if (ch == 'y' || ch == 'Y')
				break;
			else
				continue;
		}
		switch (choice)
		{
		case '1':Array_func(); break;
		case '2':Pic_output(); break;
		case '3':Video_output(); break;
		default:
			cout << "\n�����������������" << endl;
			wait_for_enter();
		}
		cout << endl;
	}
	return 0;
}