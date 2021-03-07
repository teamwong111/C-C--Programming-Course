/****************************************
GameEngine.cpp
Author: Root
Date: 2019/12/09
Description:
�����˳�����Ϸģ�飬��GameEngine�����ռ��ֹͬ����Ⱦ��������Ҫ��Ҫ�޸ĵ��ļ�
*****************************************/
#include "GameEngine.h"
#include "time.h"
#include <queue>
using namespace std;
namespace GameEngine {
	// �������������ռ�
	using namespace Graphic;
	using namespace Controller;

	size_t mapWidth = 0, mapHeight = 0;				 // ��ͼ��Ⱥ͸߶�
	UCHAR* mapCanvas = nullptr;						 // ��ͼ����ָ�룬�����������벻Ҫֱ�ӳ��Բ������ָ��
	COORD pos = { 0 }, posOld = { 0 };				 // ����λ��
	COORD posChoice = { 0 }, posChoiceOld = { 0 };	 // ѡ�е�ͼ�����λ��
	char key = '\0';								 // ���̵İ���
	bool gameFlag = false;							 // ��Ϸ����״̬
	size_t frame = 0;								 // ����Ⱦ֡��
	clock_t tic = clock();							 // ��Ϸ��ʼʱ��
	int operation = 0;								 // ִ�еĲ���
	bool isFirst = true;							 // �Ƿ�Ϊ��һ��
	UCHAR mapArray[10][10];							 // 10*10�ĵ�ͼ����
	// ��������¼ӵı�������������·���Ԥ�ñ���������
	queue<short> queBfs;                             // ����BFS�Ķ��У����λ��x,y
	int idx[100];                                    // �ж�ÿ��λ���Ƿ���й�BFS
	int mapArraytrue[100];							 // ʵ�ʲ���������
	int mineSum;                                     // ���׸���
	int timeStart;                                   // ��Ϸ��ʼʱ��
	int timeEnd;                                     // ��Ϸ����ʱ��
	int gameStart;                                   // �ж���Ϸ�Ƿ�ʼ
	int gameEnd;                                     // �ж���Ϸ�Ƿ����
	int randomCount;                                 // ������ɵĵ��׼�����
	int stepCount;                                   // ��Ϸ����������
	char strMine[32] = "";                             // ���ڴ�ӡ����
	char strStep[32] = "";                             // ���ڴ�ӡ����
	char strTime[32] = "";                             // ���ڴ�ӡʱ��
	int clickMouse = 0;                              // ���ڽ�����Ϸ
	int gameFail = 0;                                // �ж���Ϸ�Ƿ�ʧ��

	/****************************************
	Function:  renderMap()
	Parameter: None(void)
	Return:    None(void)
	Description:
	���Ƶ�ǰ��ͼ
	*****************************************/
	void renderMap() {
		// ���п�ʼ����
		for (size_t i = 0; i < mapHeight + 1; i++) {
			// �ƶ����������� ���������׵��ַ�
			MovePos(0, (SHORT)i * 2 + 3);
			if (i == 0) {
				PutString("�X");
			}
			else if (i == mapHeight) {
				PutString("�^");
			}
			else {
				PutString("�d");
			}

			// �����У����Ʊ߽�
			for (size_t j = 0; j < mapWidth; j++) {
				// �ƶ���ȷ�е����꣬���Ʒ���ı߽�
				MovePos(2 + (SHORT)j * 8, (SHORT)i * 2 + 3);
				if (i == 0) {
					if (j < mapWidth - 1) {
						PutString("�T�T�T�j");
					}
					else {
						PutString("�T�T�T�[");
					}
				}
				else if (i == mapHeight) {
					if (j < mapWidth - 1) {
						PutString("�T�T�T�m");
					}
					else {
						PutString("�T�T�T�a");
					}
				}
				else {
					if (j < mapWidth - 1) {
						PutString("�T�T�T�p");
					}
					else {
						PutString("�T�T�T�g");
					}
				}
			}

			// ���Ƶ��׵�ͼ
			if (i > 0 && i < mapHeight + 1) {
				// �ƶ������ף����Ʊ߽��ַ�
				MovePos(0, (SHORT)i * 2 + 2);
				PutString("�U");
				// ������ ���Ƶ���
				for (size_t j = 0; j < mapWidth; j++) {
					MovePos(2 + (SHORT)j * 5, (SHORT)i * 2 + 2);    // �ƶ���ȷ������
					const size_t mapIndex = (i - 1) * mapWidth + j; // ȷ����ͼ������±�
					char numMap[8] = "   ";							// ȷ�������ַ���
					numMap[1] = '0' + mapCanvas[mapIndex];			// ��mapCanvas[mapIndex]Ϊ1��8ʱ������ת�����ַ���
					switch (mapCanvas[mapIndex]) {
					case 0:
						// 0��ʱ����ÿհ�
						PutString("   ");
						break;
					case 1:
						// ��1��ʼ�������� ����ɫ
						PutStringWithColor(numMap, 30, 144, 255, 0, 0, 0);
						break;
					case 2:
						PutStringWithColor(numMap, 0, 255, 127, 0, 0, 0);
						break;
					case 3:
						PutStringWithColor(numMap, 255, 48, 48, 0, 0, 0);
						break;
					case 4:
						PutStringWithColor(numMap, 72, 61, 139, 0, 0, 0);
						break;
					case 5:
						PutStringWithColor(numMap, 255, 105, 180, 0, 0, 0);
						break;
					case 6:
						PutStringWithColor(numMap, 148, 0, 211, 0, 0, 0);
						break;
					case 7:
						PutStringWithColor(numMap, 139, 0, 0, 0, 0, 0);
						break;
					case 8:
						PutStringWithColor(numMap, 139, 34, 82, 0, 0, 0);
						break;
					case 9:
						// 9Ϊ����
						PutString(" �~");
						break;
					case 10:
						// ����Ǻţ����о�����;
						PutStringWithColor(" ��", 178, 34, 34, 0, 0, 0);
						break;
					case 11:
						// ����Ǻţ����о�����;
						PutStringWithColor(" ��", 255, 215, 0, 0, 0, 0);
						break;
					}

					MovePos(5 + (SHORT)j * 5, (SHORT)i * 2 + 2);
					PutString("�U");
				}
			}
		}
		Update(); // ����ͼ���µ���Ļ
	}

	/****************************************
	Function:  updateMap()
	Parameter: None(void)
	Return:    None(void)
	Description:
	����ά��������ݸ��Ƶ�һά������
	*****************************************/
	void updateMap() {
		memcpy_s(mapCanvas, mapWidth * mapHeight, mapArray, mapWidth * mapHeight);
	}

	/****************************************
	Function:  InitGame()
	Parameter: None(void)
	Return:    None(void)
	Description:
	��ʼ����Ϸ
	*****************************************/
	void InitGame() {
		ClearScreen();	// ����
		mapWidth = 10; mapHeight = 10;
		mapCanvas = new UCHAR[mapWidth * mapHeight]; // ��ʼ����������
		for (size_t i = 0; i < mapHeight; i++) {
			for (size_t j = 0; j < mapWidth; j++) {
				mapCanvas[i * 10 + j] = (i * mapWidth + j) % 12; // ���µ�ͼ���飬���γ��ָ��������ַ�
			}
		}
		updateMap();	// ���µ�ͼ
		renderMap();	// ���Ƶ�ͼ
	}

	/****************************************
	Function:  renderChoiceBackground(COORD choice)
	Parameter: COORD choice
	Return:    None(void)
	Description:
	����ѡ�еĵؿ�ı���
	*****************************************/
	void renderChoiceBackground(COORD choice) {
		const SHORT x = choice.X, y = choice.Y;
		const BYTE alpha = 255 - (BYTE)((frame % 50) * 5);        // ���屳����ɫ��ǰ����ɫֵ��ͨ������Ⱦ��֡���������㣨�˴�Ҳ���Ըĳ�ʹ��ʱ�䣩
		const size_t mapIndex = (size_t)y * mapWidth + (size_t)x; // ȷ����ͼ�±�

		MovePos(2 + x * 4, y * 2 + 3);

		// ��������ͬrenderMap�л��Ƶ��ײ�����ͬ������������
		char numMap[8] = "  ";
		numMap[0] = '0' + mapCanvas[mapIndex];
		switch (mapCanvas[mapIndex]) {
		case 0:
			PutStringWithColor("  ", 255, 255, 255, alpha, alpha, alpha);
			break;
		case 1:
			PutStringWithColor(numMap, 30, 144, 255, alpha, alpha, alpha);
			break;
		case 2:
			PutStringWithColor(numMap, 0, 255, 127, alpha, alpha, alpha);
			break;
		case 3:
			PutStringWithColor(numMap, 255, 48, 48, alpha, alpha, alpha);
			break;
		case 4:
			PutStringWithColor(numMap, 72, 61, 139, alpha, alpha, alpha);
			break;
		case 5:
			PutStringWithColor(numMap, 255, 105, 180, alpha, alpha, alpha);
			break;
		case 6:
			PutStringWithColor(numMap, 148, 0, 211, alpha, alpha, alpha);
			break;
		case 7:
			PutStringWithColor(numMap, 139, 0, 0, alpha, alpha, alpha);
			break;
		case 8:
			PutStringWithColor(numMap, 139, 34, 82, alpha, alpha, alpha);
			break;
		case 9:
			// 9Ϊ����
			PutString("�~");
			break;
		case 10:
			// ����Ǻţ����о�����;
			PutStringWithColor("��", 178, 34, 34, 0, 0, 0);
			break;
		case 11:
			// ����Ǻţ����о�����;
			PutStringWithColor("��", 255, 215, 0, 0, 0, 0);
			break;
		}
	}

	/****************************************
	Function:  clearChoiceBackground(COORD choice)
	Parameter: COORD choice
	Return:    None(void)
	Description:
	���choice��ָʾλ�õı���������ͬ�ϣ�����������
	*****************************************/
	void clearChoiceBackground(COORD choice) {
		const SHORT x = choice.X, y = choice.Y;
		const size_t mapIndex = (size_t)y * mapWidth + (size_t)x;

		MovePos(2 + x * 4, y * 2 + 3);

		char numMap[8] = "  ";
		numMap[0] = '0' + mapCanvas[mapIndex];
		switch (mapCanvas[mapIndex]) {
		case 0:
			PutStringWithColor("  ", 255, 255, 255, 0, 0, 0);
			break;
		case 1:
			PutStringWithColor(numMap, 30, 144, 255, 0, 0, 0);
			break;
		case 2:
			PutStringWithColor(numMap, 0, 255, 127, 0, 0, 0);
			break;
		case 3:
			PutStringWithColor(numMap, 255, 48, 48, 0, 0, 0);
			break;
		case 4:
			PutStringWithColor(numMap, 72, 61, 139, 0, 0, 0);
			break;
		case 5:
			PutStringWithColor(numMap, 255, 105, 180, 0, 0, 0);
			break;
		case 6:
			PutStringWithColor(numMap, 148, 0, 211, 0, 0, 0);
			break;
		case 7:
			PutStringWithColor(numMap, 139, 0, 0, 0, 0, 0);
			break;
		case 8:
			PutStringWithColor(numMap, 139, 34, 82, 0, 0, 0);
			break;
		case 9:
			// 9Ϊ����
			PutString("�~");
			break;
		case 10:
			// ����Ǻţ����о�����;
			PutStringWithColor("��", 178, 34, 34, 0, 0, 0);
			break;
		case 11:
			// ����Ǻţ����о�����;
			PutStringWithColor("��", 255, 215, 0, 0, 0, 0);
			break;
		}
	}

	/****************************************
	Function:  checkChoice()
	Parameter: None(void)
	Return:    None(void)
	Description:
	�������Ͳ�������������ر���
	*****************************************/
	void checkChoice() {
		FlushInput();							// ˢ�����뻺����
		pos = GetCursorPos();					// ��ȡ�������
		COORD hitLeftPos = GetCursorHitPos();	// ��ȡ�����������
		COORD hitRightPos = GetCursorHitPos(2);	// ��ȡ�Ҽ���������
		key = GetKeyHit();						// ��ȡ��������
		operation = 0;							// ��ǰ���� (0�޲�����1Ϊ�ڿ��ؿ飬2Ϊ��ֵ���ģ������Լ�ָ��)

		// ����������
		switch (key) {
		case VK_ESCAPE:
			// ESC��������Ϸ����״̬�÷����˳���Ϸ
			gameFlag = false;
			break;

			// �������Ҽ��ƶ�ѡ�е�����
		case VK_UP:
			if (posChoice.Y > 0)posChoice.Y--;
			break;
		case VK_RIGHT:
			if (posChoice.X < (SHORT)mapWidth - 1)posChoice.X++;
			break;
		case VK_DOWN:
			if (posChoice.Y < (SHORT)mapHeight - 1)posChoice.Y++;
			break;
		case VK_LEFT:
			if (posChoice.X > 0)posChoice.X--;
			break;

			// �س��Ϳո�ֱ��Ӧ����1��2
		case VK_RETURN:
			operation = 1;
			break;
		case VK_SPACE:
			operation = 2;
			break;
		}

		// ��������̨�������������ͼ����
		const size_t mouseY = (size_t)(pos.Y + 1) / 2 - 2;
		const size_t mouseX = (size_t)(pos.X - 1) / 4;
		if (mouseY < mapHeight && mouseX < mapWidth) {
			// ��û�г��߽磬����ѡ�������
			posChoice.X = (SHORT)mouseX;
			posChoice.Y = (SHORT)mouseY;
		}

		// ������Ҽ��ֱ��Ӧ����1��2
		if (hitLeftPos.X == pos.X && hitLeftPos.Y == pos.Y) {
			operation = 1;
		}
		else if (hitRightPos.X == pos.X && hitRightPos.Y == pos.Y) {
			operation = 2;
		}
	}

	/****************************************
	Function:  neighborBfs()
	Parameter: int i int j
	Return:    None(void)
	Description:
	�ҵ�ÿ��λ���ܱߵ�����
	*****************************************/
	void neighborBfs(int i, int j)
	{
		//��ǰλ�õ�����λ��������ǰλ�ü�1�������ͬ��
		if (i - 1 >= 0 && j - 1 >= 0 && mapArraytrue[(i - 1) * 10 + j - 1] == 9)
			mapArraytrue[i * 10 + j]++;
		if (i - 1 >= 0 && mapArraytrue[(i - 1) * 10 + j] == 9)
			mapArraytrue[i * 10 + j]++;
		if (j - 1 >= 0 && mapArraytrue[i * 10 + j - 1] == 9)
			mapArraytrue[i * 10 + j]++;
		if (i - 1 >= 0 && j + 1 <= 9 && mapArraytrue[(i - 1) * 10 + j + 1] == 9)
			mapArraytrue[i * 10 + j]++;
		if (i + 1 <= 9 && j - 1 >= 0 && mapArraytrue[(i + 1) * 10 + j - 1] == 9)
			mapArraytrue[i * 10 + j]++;
		if (i + 1 <= 9 && j + 1 <= 9 && mapArraytrue[(i + 1) * 10 + j + 1] == 9)
			mapArraytrue[i * 10 + j]++;
		if (i + 1 <= 9 && mapArraytrue[(i + 1) * 10 + j] == 9)
			mapArraytrue[i * 10 + j]++;
		if (j + 1 <= 9 && mapArraytrue[i * 10 + j + 1] == 9)
			mapArraytrue[i * 10 + j]++;
	}

	/****************************************
	Function:  initMap()
	Parameter: None(void)
	Return:    None(void)
	Description:
	��ʼ����ͼ
	*****************************************/
	void initMap() {
		//memset(mapArray, 0, sizeof(mapArray));     //mapArray����
		memset(mapCanvas, 0, sizeof(mapCanvas));     //mapArray����
		memset(mapArraytrue, 0, sizeof(mapArraytrue));  //mapArraytrue����
		srand(time(NULL));                       //ʱ��������
		randomCount = 0;                         //������ɵĵ�������ʼ��

		//���λ�����ɵ���
		for (int i = 0;; i++)
		{
			int x = rand() % 10;
			int y = rand() % 10;
			if ((x != posChoice.Y || y != posChoice.X) && mapArraytrue[x * 10 + y] == 0)
			{
				mapArraytrue[x * 10 + y] = 9;
				randomCount++;
			}
			if (randomCount == 10)
				break;
		}

		//Ϊ������ͼ��ʼ��
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
			{
				if (mapArraytrue[i * 10 + j] != 9)
					neighborBfs(i, j);
			}
	}

	/****************************************
	Function:  bfsNext()
	Parameter: short i short j
	Return:    None(void)
	Description:
	BFS�жϣ�i,j���İ������Ƿ�Ҫ������
	*****************************************/
	void bfsNext(short i, short j)
	{
		if (i < 0 || i>9 || j < 0 || j>9 || idx[i * 10 + j] != 0)//Խ������Ѿ����ʹ�
			return;
		else if (mapArraytrue[i * 10 + j] != 0)                     //��λ��Ϊ���ֵı߽�
		{
			mapCanvas[i * 10 + j] = mapArraytrue[i * 10 + j];
			idx[i * 10 + j] = 1;
		}
		else                                               //��λ��Ϊ�հ�
		{
			mapCanvas[i * 10 + j] = 10;
			queBfs.push(i);
			queBfs.push(j);
			idx[i * 10 + j] = 1;
		}
	}

	/****************************************
	Function:  bfsFirst()
	Parameter: short x short y
	Return:    None(void)
	Description:
	bfsNext�жϣ�i,j���Ƿ�Ϊ��
	*****************************************/
	void bfsFirst(short x, short y)
	{
		mapCanvas[x * 10 + y] = 10;
		queBfs.push(x);
		queBfs.push(y);
		idx[x * 10 + y] = 1;

		//�жϸ�λ�õİ�����
		while (!queBfs.empty())
		{
			short i = queBfs.front();
			queBfs.pop();
			short j = queBfs.front();
			queBfs.pop();
			bfsNext(i - 1, j - 1);
			bfsNext(i - 1, j);
			bfsNext(i - 1, j + 1);
			bfsNext(i, j - 1);
			bfsNext(i, j + 1);
			bfsNext(i + 1, j - 1);
			bfsNext(i + 1, j);
			bfsNext(i + 1, j + 1);
		}
	}

	/****************************************
	Function:  digBlock()
	Parameter: None(void)
	Return:    None(void)
	Description:
	��ʼ����ͼ�Լ�����ĳλ��
	*****************************************/
	void digBlock() {
		if (isFirst) {
			// ����ǵ�һ���ߣ����ȳ�ʼ����ͼ��ע�ⲻҪ���������һ������
			initMap();
			isFirst = false; // ����һ������Ϊ��
			memset(idx, 0, sizeof(idx));//idx��������
			if (mapArraytrue[posChoice.Y * 10 + posChoice.X] == 0)//�����λ��Ϊ�հ�
				bfsFirst(posChoice.Y, posChoice.X);
			else if (mapArraytrue[posChoice.Y * 10 + posChoice.X] > 0 && mapArraytrue[posChoice.Y * 10 + posChoice.X] < 9)//�����λ��Ϊ����
			{
				mapCanvas[posChoice.Y * 10 + posChoice.X] = mapArraytrue[posChoice.Y * 10 + posChoice.X];
				idx[posChoice.Y * 10 + posChoice.X] = 1;
			}
			//updateMap(); // ���µ�ͼ����
			renderMap(); // ���Ƶ�ǰ��ͼ
			gameStart = 1;//��Ϸ��ʼ
			timeStart = GetTickCount64();//��ʼ��ʱ
			mineSum = 10;//����Ϊ10
			stepCount = 1;//����Ϊ0
			return;
		}

		//���ǵ�һ��
		if (mapArraytrue[posChoice.Y * 10 + posChoice.X] == 9)//�����λ��Ϊ��
		{
			stepCount++;
			mapCanvas[posChoice.Y * 10 + posChoice.X] = 9;
			for (int i = 0; i < 10; i++)//��ʾȫ�����ף�������Ϸ
				for (int j = 0; j < 10; j++)
				{
					if (mapArraytrue[i * 10 + j] == 9)
						mapCanvas[i * 10 + j] = 9;
				}

			//updateMap(); // ���µ�ͼ����
			renderMap(); // ���Ƶ�ǰ��ͼ
			gameFail = 1;
		}
		else if (mapArraytrue[posChoice.Y * 10 + posChoice.X] > 0 && mapArraytrue[posChoice.Y * 10 + posChoice.X] < 9 && idx[posChoice.Y * 10 + posChoice.X] ==0)//�����λ��Ϊ����
		{
			stepCount++;
			mapCanvas[posChoice.Y * 10 + posChoice.X] = mapArraytrue[posChoice.Y * 10 + posChoice.X];
			idx[posChoice.Y * 10 + posChoice.X] = 1;
		}
		else if(mapArraytrue[posChoice.Y * 10 + posChoice.X] ==0 && idx[posChoice.Y * 10 + posChoice.X] == 0)//�����λ��Ϊ�հ�
		{
			stepCount++;
			bfsFirst(posChoice.Y, posChoice.X);
		}

		//
		//updateMap(); // ���µ�ͼ����
		renderMap(); // ���Ƶ�ǰ��ͼ
	}

	/****************************************
	Function:  flagBlock()
	Parameter: None(void)
	Return:    None(void)
	Description:
	Ϊ��λ�ñ�����ӻ򳷵�����
	*****************************************/
	void flagBlock() {
		//�����ӻ�������
		if (mineSum != 0 && mapCanvas[posChoice.Y * 10 + posChoice.X] == 0 || mapCanvas[posChoice.Y * 10 + posChoice.X] == 9)//�������û������
		{
			stepCount++;
			mapCanvas[posChoice.Y * 10 + posChoice.X] = 11;
			idx[posChoice.Y * 10 + posChoice.X] = 1;
			mineSum--;//������1
		}

		//�������������
		else if (mapCanvas[posChoice.Y * 10 + posChoice.X] == 11)
		{
			stepCount++;
			mapCanvas[posChoice.Y * 10 + posChoice.X] = 0;
			idx[posChoice.Y * 10 + posChoice.X] = 0;
			mineSum++;//������1
		}

		//
		//updateMap(); // ���µ�ͼ����
		renderMap(); // ���Ƶ�ǰ��ͼ
	}

	/****************************************
	Function:  checkMouse()
	Parameter: None(void)
	Return:    None(void)
	Description:
	����Ƿ�����굥��������������Ϸ
	*****************************************/
	void checkMouse()
	{
		clickMouse = 0;//û�е�����
		FlushInput();// ˢ�����뻺����
		pos = GetCursorPos();// ��ȡ�������
		COORD hitLeftPos = GetCursorHitPos();// ��ȡ��굥������
		if (hitLeftPos.X == pos.X && hitLeftPos.Y == pos.Y) {
			clickMouse = 1;//��ɵ������
		}
	}

	/****************************************
	Function:  endGame()
	Parameter: None(void)
	Return:    None(void)
	Description:
	ʤ��������Ϸ�ĺ�������
	*****************************************/
	void endGame()
	{
		ClearScreen();//����
		MovePos(14, 2); // �ƶ����굽 14,2
		PutString("��Ӯ�ˣ�");
		MovePos(14, 4); // �ƶ����굽 14,4
		PutString(strStep);
		MovePos(14, 6); // �ƶ����굽 14,6
		PutString(strTime);
		MovePos(14, 8); // �ƶ����굽 14,8
		PutString("�������������˵�");
		Update();// ����ͼ���µ���Ļ
		bool runFlag = true;//�ж���û�е�����
		while (runFlag) {
			checkMouse();  // �������
			if (clickMouse == 1)
				runFlag = false;
		}
	}

	/****************************************
	Function:  Play()
	Parameter: None(void)
	Return:    None(void)
	Description:
	��ʼ��Ϸ
	*****************************************/
	void Play() {
		//��Ҫ�����ĳ�ʼ��
		timeStart = 0;
		timeEnd = 0;
		gameFail = 0;
		stepCount = 0;
		gameStart = 0;
		isFirst = true;
		memset(strMine, 0, sizeof(strMine));
		memset(strStep, 0, sizeof(strStep));
		memset(strTime, 0, sizeof(strTime));

		//��Ϸ��ʼ
		gameFlag = true;
		while (gameFlag) {
			checkChoice(); // �������

			// �鿴��ǰ�����Ƿ���Ҫ���±���
			if (posChoice.X != posChoiceOld.X || posChoice.Y != posChoiceOld.Y) {
				clearChoiceBackground(posChoiceOld);
				posChoiceOld = posChoice;
			}
			renderChoiceBackground(posChoice);

			// ��0,0�����õ�ǰѡ��λ�õ��ַ�����ע���β�пո����ף�����˼��ΪʲôҪ����ô��ո�
			MovePos(0, 0);
			char str[32] = "";
			sprintf_s(str, "��ǰѡ��(%u, %u)", posChoice.X, posChoice.Y);
			PutString(str);
			// ִ����Ӧ����
			switch (operation) {
			case 1:
				// �����ؿ�
				digBlock();
				break;
			case 2:
				// ���Ϊ����
				flagBlock();
				break;
			}

			//��ʾ������������ʱ��
			if (gameStart == 1)
			{
				//��ʾʣ������
				MovePos(0, 0);
				sprintf_s(strMine, "ʣ������%d ", mineSum);
				PutString(strMine);

				//��ʾ���߲���
				MovePos(0, 0);
				sprintf_s(strStep, "����%d ", stepCount);
				PutString(strStep);

				//��ʾ��Ϸʱ��
				timeEnd = GetTickCount64();
				int mintue = (timeEnd - timeStart) / 60000;
				int second = ((timeEnd - timeStart) / 1000) % 60;
				int smallsecond = ((timeEnd - timeStart) / 10) % 100;
				MovePos(0, 0);
				//���ݷ��ӡ��롢�ٷ�֮һ���Ƿ����10��ȷ���Ƿ�Ҫ��ʾ��
				if (mintue < 10 && second < 10 && smallsecond < 10)
					sprintf_s(strTime, "ʱ��:0%d:0%d:0%d", mintue, second, smallsecond);
				else if (mintue < 10 && second < 10)
					sprintf_s(strTime, "ʱ��:0%d:0%d:%d", mintue, second, smallsecond);
				else if (mintue < 10 && smallsecond < 10)
					sprintf_s(strTime, "ʱ��:0%d:%d:0%d", mintue, second, smallsecond);
				else if (mintue < 10)
					sprintf_s(strTime, "ʱ��:0%d:%d:%d", mintue, second, smallsecond);
				else if (second < 10 && smallsecond < 10)
					sprintf_s(strTime, "ʱ��:%d:0%d:0%d", mintue, second, smallsecond);
				else if (second < 10)
					sprintf_s(strTime, "ʱ��:%d:0%d:%d", mintue, second, smallsecond);
				else if (smallsecond < 10)
					sprintf_s(strTime, "ʱ��:%d:%d:0%d", mintue, second, smallsecond);
				else
					sprintf_s(strTime, "ʱ��:%d:%d:%d", mintue, second, smallsecond);
				PutString(strTime);
			}

			//��Ϸ�Ƿ�ʧ��
			if (gameFail == 1)
			{
				MovePos(14, 2); // �ƶ����굽 14,2
				PutString("���ź���ʧ����"); // ������������һ��string
				MovePos(14, 4); // �ƶ����굽 14,4
				PutString("�������������˵�"); // ������������һ��string
				Update();// ����ͼ���µ���Ļ
				bool runFlag = true;//�ж���û�е�����
				while (runFlag) {
					checkMouse();  // �������
					if (clickMouse == 1)
						runFlag = false;
				}
				return;
			}

			//��Ϸ�Ƿ�ʤ������
			gameEnd = 0;
			if (operation != 0)
			{
				for (int i = 0; i < 10; i++)
					for (int j = 0; j < 10; j++)
					{
						if (mapCanvas[i * 10 + j] == 0)
							gameEnd = 1;
					}
				if (gameEnd == 0)//��Ϸ������
				{
					endGame();
					return;
				}

				else//��Ϸû����
				{
					gameEnd = 0;
				}
			}

			// �������ݲ������޸� ����ÿ֡������
			//updateMap(); // ���µ�ͼ����
			Update();    // ���²�����			
			frame++;  // ��Ⱦ֡������
			clock_t elapsed = 25 - (clock() - tic); // �����һ֡��Ⱦʱ�䣬��������25�Ĳ�ֵ
			Sleep(elapsed > 0 ? elapsed : 0);	    // ����ֵ�����㣬�����߸ò�ֵ�ĺ���������ȷ��ÿ֡��Ⱦ������50֡
			tic = clock();						    // ������һ�μ�¼��ʱ��
		}
	}

	/****************************************
	Function:  DestroyGame()
	Parameter: None(void)
	Return:    None(void)
	Description:
	������Ϸ�����ն�̬����ı���
	*****************************************/
	void DestroyGame() {
		delete[] mapCanvas;
	}
}