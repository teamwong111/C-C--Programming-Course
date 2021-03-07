#include <iostream>
#include <conio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
void wait_for_enter()//等待输入
{
	cout << endl << "按回车键继续";
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
	// 定义相关变量
	char  choice;
	char ch;
	while (true) //注意该循环退出的条件
	{
		wait_for_enter();
		system("cls"); //清屏函数
		menu(); //调用菜单显示函数，自行补充完成
		cout << "按要求输入菜单选择项" << endl;
		//cin >> choice;// 按要求输入菜单选择项choice
		choice = _getch();
		if (choice == '0') //选择退出
		{
			cout << "\n 确定退出吗?" << endl;
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
			cout << "\n 输入错误，请重新输入" << endl;
			wait_for_enter();
		}
		cout << endl;
	}
	return 0;
}
