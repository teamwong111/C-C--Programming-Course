#include "Game.h"	
// 程序主函数
int main()
{
	srand((int)time(0));
	Game *A=new Game();
	A->login();//登录
	Info B;
	B.history(*A);//操作历史纪录入口
	A->game(B);//开始游戏						
	closegraph();//游戏结束
	B.readin();//将所有进行的游戏记录读入文件
	B.release();//释放内存
	B.history(*A);//操作历史纪录入口
	delete A;
	B.release();//释放内存
	return 0;							
}