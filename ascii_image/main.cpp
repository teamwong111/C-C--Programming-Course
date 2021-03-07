#include"all.h"
using namespace std;
void wait_for_enter()//等待输入
{
	cout << endl << "按回车键继续";
	while (_getch() != '\r');
	cout << endl << endl;
}
void main_menu()//菜单
{
	cout << "******************************" << endl;
	cout << "*     1 Array类相关功能测试  *" << endl;
	cout << "*     2 字符图片输出         *" << endl;
	cout << "*     3 字符视频输出         *" << endl;
	cout << "*     0 退出系统             *" << endl;
	cout << "******************************" << endl;
	cout << "选择菜单项<0~3>:" << endl;
	return;
}
int main()
{
	cout << "当程序画面暂停时，请按回车键以继续\n图片和视频内容可根据注释信息更换\n";
	// 定义相关变量
	char choice;
	char ch;
	while (true) //注意该循环退出的条件
	{
		wait_for_enter();
		system("cls"); //清屏函数
		main_menu(); //调用菜单显示函数
		cout << "按要求输入菜单选择项" << endl;
		cin >> choice;// 按要求输入菜单选择项choice
		if (choice == '0') //选择退出
		{
			cout << "\n确定退出吗?（Y or y）" << endl;
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
			cout << "\n输入错误，请重新输入" << endl;
			wait_for_enter();
		}
		cout << endl;
	}
	return 0;
}