#include <iostream>
#include <conio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
void wait_for_enter()//�ȴ�����
{
	cout << endl << "���س�������";
	while (_getch() != '\r');
	cout << endl << endl;
}
void menu();
void matriplus();
void nummulti();
void matritrans();
void matrimulti();
void hadamulti();
void conv(int sel);
void demo();
void retain_ex();
void otsu();
int main()
{
	// ������ر���
	char  choice;
	char ch;
	while (true) //ע���ѭ���˳�������
	{
		wait_for_enter();
		system("cls"); //��������
		menu(); //���ò˵���ʾ���������в������
		cout << "��Ҫ������˵�ѡ����" << endl;
		//cin >> choice;// ��Ҫ������˵�ѡ����choice
		choice = _getch();
		if (choice == '0') //ѡ���˳�
		{
			cout << "\n ȷ���˳���?" << endl;
			cin >> ch;
			if (ch == 'y' || ch == 'Y')
				break;
			else
				continue;
		}
		switch (choice)
		{
		case '1':matriplus(); break;
		case '2':nummulti(); break;
		case '3':matritrans(); break;
		case '4':matrimulti(); break;
		case '5':hadamulti(); break;
		case '6':conv(0); break;
		case '7':demo(); break;
		case '8':otsu(); break;
		case '9':retain_ex(); break;
		default:
			cout << "\n �����������������" << endl;
			wait_for_enter();
		}
		cout << endl;
	}
	return 0;
}
