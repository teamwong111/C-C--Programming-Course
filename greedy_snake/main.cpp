#include "Game.h"	
// ����������
int main()
{
	srand((int)time(0));
	Game *A=new Game();
	A->login();//��¼
	Info B;
	B.history(*A);//������ʷ��¼���
	A->game(B);//��ʼ��Ϸ						
	closegraph();//��Ϸ����
	B.readin();//�����н��е���Ϸ��¼�����ļ�
	B.release();//�ͷ��ڴ�
	B.history(*A);//������ʷ��¼���
	delete A;
	B.release();//�ͷ��ڴ�
	return 0;							
}