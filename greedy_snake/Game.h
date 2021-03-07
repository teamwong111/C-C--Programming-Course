#pragma once		// ��ֹ��ͷ�ļ�����ε���
#include "Head.h"	// ��ʼ��ͷ�ļ�
class Snake;
class Wall;
class Food;
class Info;
class Game;
//��������
struct pos
{
	int x;
	int y;
};
//��¼����
struct info
{
	int level;//���š����ס��߼�
	char username[10];//�û���
	int score;//�÷�
	info* next;
};
//��Ϸ
class Game
{
public:
	void game(Info B);//��Ϸ��ڣ���Ϸ��ʼ���棬ѡ����Ϸģʽ
	void login();//��¼
private:
	void primary();//����
	void middle();//����
	void senior();//�߼�
	void putall();//���Ʊ���
	bool button(int a, int b, const wchar_t str[]);//���ð�ť
	int putmessagebox(int x, int y, int wight, int hight, const wchar_t title[], const wchar_t* text[], int g_num, int var = MY_OK);//����Ի���
	void help();//������Ϣ
	int keydown(int& direction);//����
	void show(int level);//UI����Ϸʱ�䡢�÷֡���ʷ��߷�
	bool end();//ÿ����Ϸ����������Ի���
	char username[10];//�û���
	double times;//��Ϸʱ��
	char ch;//������Ϣ
	MOUSEMSG m_msg;//�����Ϣ
	int score;//�÷�
	int highestscore[3];//��ʷ��߷�
	friend class Info;
};
//��
class Snake
{
public:
	Snake();//���캯��
	void move();//�ƶ�
	int eatfood(Food &food);//��ʳ��
	bool kill_by_wall(Wall wall);//ײǽ����
	bool kill_by_snake();//ײ�߶���
	void draw();//������
	void becomewall(Wall& wall);//���ǽ
	void becomefood(Food& food);//���ʳ��
	void create(Wall wall, Food food);//������
private:
	vector <pos> place;//ÿ������
	pos next;//Ϊ��һ��Ԥ����λ��
	int length;//����
	COLORREF color;//ÿ����ɫ
	int life;//������
	int direction;//����
	friend class Food;
	friend class Game;
};
//ǽ
class Wall
{
public:
	Wall();//���캯��
	void draw();//����ǽ
	bool full();//�ж��Ƿ��пռ�������
private:
	bool place[45][45];//ǽλ��
	friend class Snake;
};
//ʳ��
class Food
{
public:
	Food();//���캯��
	void create(Snake snake,int n);//����ʳ��
	void draw();//����ʳ�����UI
	bool full();//�ж��Ƿ��пռ�������
private:
	int place[45][45];//ʳ��λ�ü���ռ������ͬʳ��
	int num;//ʳ������
	friend class Snake;
};
//��ʷ��Ϣ
class Info
{
public:
	void history(Game &A);//������ʷ��¼���
	void release();//�ͷ��ڴ�
	void record(int level,char username[],int score);//ÿ����Ϸ�������¼
	void readin();//�����ļ�
private:
	void init();//��ʼ����¼����
	bool isContinue();//ѡ���Ƿ����
	void menu();//������ʷ��¼�˵�
	void disp();//��ʾ
	void searchbyUSER();//����
	void delbyID();//ɾ��
	void modibyID();//�޸�
	void add();//���
	void gethighest(Game& A);//��ȡ��߷�
	info* head, * s, * the_end;//����ͷָ�롢����ָ�롢βָ��
	int n;//�ܼ�¼��
	friend class Game;
};