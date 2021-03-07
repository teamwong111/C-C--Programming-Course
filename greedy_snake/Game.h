#pragma once		// 防止该头文件被多次调用
#include "Head.h"	// 初始化头文件
class Snake;
class Wall;
class Food;
class Info;
class Game;
//坐标属性
struct pos
{
	int x;
	int y;
};
//记录属性
struct info
{
	int level;//入门、进阶、高级
	char username[10];//用户名
	int score;//得分
	info* next;
};
//游戏
class Game
{
public:
	void game(Info B);//游戏入口，游戏开始界面，选择游戏模式
	void login();//登录
private:
	void primary();//入门
	void middle();//进阶
	void senior();//高级
	void putall();//绘制背景
	bool button(int a, int b, const wchar_t str[]);//放置按钮
	int putmessagebox(int x, int y, int wight, int hight, const wchar_t title[], const wchar_t* text[], int g_num, int var = MY_OK);//输出对话框
	void help();//帮助信息
	int keydown(int& direction);//按键
	void show(int level);//UI：游戏时间、得分、历史最高分
	bool end();//每次游戏结束后产生对话框
	char username[10];//用户名
	double times;//游戏时间
	char ch;//键盘消息
	MOUSEMSG m_msg;//鼠标消息
	int score;//得分
	int highestscore[3];//历史最高分
	friend class Info;
};
//蛇
class Snake
{
public:
	Snake();//构造函数
	void move();//移动
	int eatfood(Food &food);//吃食物
	bool kill_by_wall(Wall wall);//撞墙而死
	bool kill_by_snake();//撞蛇而死
	void draw();//画出蛇
	void becomewall(Wall& wall);//变成墙
	void becomefood(Food& food);//变成食物
	void create(Wall wall, Food food);//出现蛇
private:
	vector <pos> place;//每节坐标
	pos next;//为下一节预留的位置
	int length;//长度
	COLORREF color;//每节颜色
	int life;//生命数
	int direction;//方向
	friend class Food;
	friend class Game;
};
//墙
class Wall
{
public:
	Wall();//构造函数
	void draw();//画出墙
	bool full();//判断是否还有空间生成蛇
private:
	bool place[45][45];//墙位置
	friend class Snake;
};
//食物
class Food
{
public:
	Food();//构造函数
	void create(Snake snake,int n);//出现食物
	void draw();//画出食物，部分UI
	bool full();//判断是否还有空间生成蛇
private:
	int place[45][45];//食物位置及所占分数或不同食物
	int num;//食物总数
	friend class Snake;
};
//历史信息
class Info
{
public:
	void history(Game &A);//操作历史纪录入口
	void release();//释放内存
	void record(int level,char username[],int score);//每次游戏结束后记录
	void readin();//读入文件
private:
	void init();//初始化记录链表
	bool isContinue();//选择是否继续
	void menu();//操作历史纪录菜单
	void disp();//显示
	void searchbyUSER();//查找
	void delbyID();//删除
	void modibyID();//修改
	void add();//添加
	void gethighest(Game& A);//获取最高分
	info* head, * s, * the_end;//链表头指针、工作指针、尾指针
	int n;//总记录数
	friend class Game;
};