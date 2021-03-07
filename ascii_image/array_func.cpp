#include"all.h"
#include"Array.h"
using namespace std;
Array a(2, 2), b(2, 2), c(2, 2), d(2, 2);//全局变量，方便测试矩阵加减乘除运算
void Array_menu()//菜单
{
	cout << "*********************************************************" << endl;
	cout << " *  1 初始化多维数组     2 矩阵加法     3 矩阵减法      *" << endl;
	cout << " *  4 矩阵点乘           5 矩阵点除     6 reshape操作   *" << endl;
	cout << " *  7 获取C风格元素      0 退出系统	                 *" << endl;
	cout << "*********************************************************" << endl;
	cout << "选择菜单项<0~7>:" << endl;
	return;
}
void init()//至少能初始化三个维度的数组，即该类至少需要支持三维索引
{
	Array e(3, 3, 3); //3x3x3
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
			{
				e[i][j][k] = i + j + k;
			}
	cout << "初始化后底层数据：\n";
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
			{
				cout << e[i][j][k] << " ";
			}
	cout << endl;
}
void print_ans()//打印结果，用于矩阵加减乘除
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
void matrixplus()//矩阵加法
{
	if (a.shape[0] == b.shape[0] && a.shape[0] == c.shape[0] && a.shape[0] == d.shape[0])//相同矩阵才能做加法
	{
		c = a + b;
		d = a + 2;
	}
	print_ans();//打印结果
}
void matrixsub()//矩阵减法
{
	if (a.shape[0] == b.shape[0] && a.shape[0] == c.shape[0] && a.shape[0] == d.shape[0])
	{	
		c = a - b;
		d = a - 2;
	}
	print_ans();
}
void matrixdotp()//矩阵点乘
{
	if (a.shape[0] == b.shape[0] && a.shape[0] == c.shape[0] && a.shape[0] == d.shape[0])
	{
		c = a * b;
		d = a * 2;
	}
	print_ans();
}
void matrixpointdiv()//矩阵点除,因为底层数据为int型，所以最后除法结果不是浮点数
{
	if (a.shape[0] == b.shape[0] && a.shape[0] == c.shape[0] && a.shape[0] == d.shape[0])
	{
		c = a / b;
		d = a / 2;
	}
	print_ans();
}
void martixreshape()//reshape操作
{
	Array f(16);
	for (int i = 0; i < 16; i++)
		f[i] = i;
	f.reshape(4, 4);
	cout << "reshape结果：\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << f[i][j] << " ";
		}
		cout << endl;
	}		
}
void getCstyle()//获取C风格元数据操作
{
	Array g(4);
	for (int i = 0; i < 4; i++)
		g[i] = i;
	int* h = g.get_content();//数据类型取决于你的实现
	cout << "获取的C风格元素：\n";
	for (int i = 0; i < 4; i++)
		cout << h[i] << ' ';
}
void Array_func()
{
	//为矩阵a,b赋值，用于矩阵加减乘除
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
	while (true) //注意该循环退出的条件
	{
		wait_for_enter();
		system("cls"); //清屏函数
		Array_menu(); //调用菜单显示函数
		cout << "按要求输入菜单选择项" << endl;
		cin >> choice;// 按要求输入菜单选择项choice
		if (choice == '0') //选择退出
		{
			cout << "\n确定退出吗?(Y or y)" << endl;
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
			cout << "\n输入错误，请重新输入" << endl;
			wait_for_enter();
		}
		cout << endl;
	}
	//使得a,b,c,d可以析构
	a.ischild = false;
	b.ischild = false;
	c.ischild = false;
	d.ischild = false;
	return;
}