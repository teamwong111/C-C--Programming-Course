/****************************************
GameEngine.cpp
Author: Root
Date: 2019/12/09
Description:
定义了程序游戏模块，用GameEngine命名空间防止同名污染，是你主要需要修改的文件
*****************************************/
#include "GameEngine.h"
#include "time.h"
#include <queue>
using namespace std;
namespace GameEngine {
	// 引入两个命名空间
	using namespace Graphic;
	using namespace Controller;

	size_t mapWidth = 0, mapHeight = 0;				 // 地图宽度和高度
	UCHAR* mapCanvas = nullptr;						 // 地图数组指针，若做基础项请不要直接尝试操作这个指针
	COORD pos = { 0 }, posOld = { 0 };				 // 鼠标的位置
	COORD posChoice = { 0 }, posChoiceOld = { 0 };	 // 选中地图坐标的位置
	char key = '\0';								 // 键盘的按键
	bool gameFlag = false;							 // 游戏运行状态
	size_t frame = 0;								 // 已渲染帧数
	clock_t tic = clock();							 // 游戏开始时刻
	int operation = 0;								 // 执行的操作
	bool isFirst = true;							 // 是否为第一步
	UCHAR mapArray[10][10];							 // 10*10的地图数组
	// 如果你有新加的变量，建议加在下方和预置变量做区别
	queue<short> queBfs;                             // 用于BFS的队列，存放位置x,y
	int idx[100];                                    // 判断每个位置是否进行过BFS
	int mapArraytrue[100];							 // 实际操作的数组
	int mineSum;                                     // 地雷个数
	int timeStart;                                   // 游戏开始时间
	int timeEnd;                                     // 游戏结束时间
	int gameStart;                                   // 判断游戏是否开始
	int gameEnd;                                     // 判断游戏是否结束
	int randomCount;                                 // 随机生成的地雷计数器
	int stepCount;                                   // 游戏步数计数器
	char strMine[32] = "";                             // 用于打印雷数
	char strStep[32] = "";                             // 用于打印步数
	char strTime[32] = "";                             // 用于打印时间
	int clickMouse = 0;                              // 用于结束游戏
	int gameFail = 0;                                // 判断游戏是否失败

	/****************************************
	Function:  renderMap()
	Parameter: None(void)
	Return:    None(void)
	Description:
	绘制当前地图
	*****************************************/
	void renderMap() {
		// 从行开始遍历
		for (size_t i = 0; i < mapHeight + 1; i++) {
			// 移动坐标至行首 并绘制行首的字符
			MovePos(0, (SHORT)i * 2 + 3);
			if (i == 0) {
				PutString("╔");
			}
			else if (i == mapHeight) {
				PutString("╚");
			}
			else {
				PutString("╠");
			}

			// 遍历列，绘制边界
			for (size_t j = 0; j < mapWidth; j++) {
				// 移动至确切的坐标，绘制方格的边界
				MovePos(2 + (SHORT)j * 8, (SHORT)i * 2 + 3);
				if (i == 0) {
					if (j < mapWidth - 1) {
						PutString("═══╦");
					}
					else {
						PutString("═══╗");
					}
				}
				else if (i == mapHeight) {
					if (j < mapWidth - 1) {
						PutString("═══╩");
					}
					else {
						PutString("═══╝");
					}
				}
				else {
					if (j < mapWidth - 1) {
						PutString("═══╬");
					}
					else {
						PutString("═══╣");
					}
				}
			}

			// 绘制地雷地图
			if (i > 0 && i < mapHeight + 1) {
				// 移动至行首，绘制边界字符
				MovePos(0, (SHORT)i * 2 + 2);
				PutString("║");
				// 遍历列 绘制地雷
				for (size_t j = 0; j < mapWidth; j++) {
					MovePos(2 + (SHORT)j * 5, (SHORT)i * 2 + 2);    // 移动至确切坐标
					const size_t mapIndex = (i - 1) * mapWidth + j; // 确定地图数组的下标
					char numMap[8] = "   ";							// 确定数字字符串
					numMap[1] = '0' + mapCanvas[mapIndex];			// 当mapCanvas[mapIndex]为1到8时，将其转换成字符串
					switch (mapCanvas[mapIndex]) {
					case 0:
						// 0的时候放置空白
						PutString("   ");
						break;
					case 1:
						// 从1开始绘制数字 带颜色
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
						// 9为地雷
						PutString(" ▇");
						break;
					case 10:
						// 特殊记号，自行决定用途
						PutStringWithColor(" ☆", 178, 34, 34, 0, 0, 0);
						break;
					case 11:
						// 特殊记号，自行决定用途
						PutStringWithColor(" ⊙", 255, 215, 0, 0, 0, 0);
						break;
					}

					MovePos(5 + (SHORT)j * 5, (SHORT)i * 2 + 2);
					PutString("║");
				}
			}
		}
		Update(); // 将地图更新到屏幕
	}

	/****************************************
	Function:  updateMap()
	Parameter: None(void)
	Return:    None(void)
	Description:
	将二维数组的数据复制到一维数组中
	*****************************************/
	void updateMap() {
		memcpy_s(mapCanvas, mapWidth * mapHeight, mapArray, mapWidth * mapHeight);
	}

	/****************************************
	Function:  InitGame()
	Parameter: None(void)
	Return:    None(void)
	Description:
	初始化游戏
	*****************************************/
	void InitGame() {
		ClearScreen();	// 清屏
		mapWidth = 10; mapHeight = 10;
		mapCanvas = new UCHAR[mapWidth * mapHeight]; // 初始化画板数组
		for (size_t i = 0; i < mapHeight; i++) {
			for (size_t j = 0; j < mapWidth; j++) {
				mapCanvas[i * 10 + j] = (i * mapWidth + j) % 12; // 更新地图数组，依次出现各个特殊字符
			}
		}
		updateMap();	// 更新地图
		renderMap();	// 绘制地图
	}

	/****************************************
	Function:  renderChoiceBackground(COORD choice)
	Parameter: COORD choice
	Return:    None(void)
	Description:
	绘制选中的地块的背景
	*****************************************/
	void renderChoiceBackground(COORD choice) {
		const SHORT x = choice.X, y = choice.Y;
		const BYTE alpha = 255 - (BYTE)((frame % 50) * 5);        // 定义背景白色当前的颜色值，通过已渲染的帧数进行运算（此处也可以改成使用时间）
		const size_t mapIndex = (size_t)y * mapWidth + (size_t)x; // 确定地图下标

		MovePos(2 + x * 4, y * 2 + 3);

		// 以下内容同renderMap中绘制地雷部分相同，不详做介绍
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
			// 9为地雷
			PutString("▇");
			break;
		case 10:
			// 特殊记号，自行决定用途
			PutStringWithColor("☆", 178, 34, 34, 0, 0, 0);
			break;
		case 11:
			// 特殊记号，自行决定用途
			PutStringWithColor("⊙", 255, 215, 0, 0, 0, 0);
			break;
		}
	}

	/****************************************
	Function:  clearChoiceBackground(COORD choice)
	Parameter: COORD choice
	Return:    None(void)
	Description:
	清除choice中指示位置的背景，功能同上，不详做介绍
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
			// 9为地雷
			PutString("▇");
			break;
		case 10:
			// 特殊记号，自行决定用途
			PutStringWithColor("☆", 178, 34, 34, 0, 0, 0);
			break;
		case 11:
			// 特殊记号，自行决定用途
			PutStringWithColor("⊙", 255, 215, 0, 0, 0, 0);
			break;
		}
	}

	/****************************************
	Function:  checkChoice()
	Parameter: None(void)
	Return:    None(void)
	Description:
	检查输入和操作，并设置相关变量
	*****************************************/
	void checkChoice() {
		FlushInput();							// 刷新输入缓冲区
		pos = GetCursorPos();					// 获取鼠标坐标
		COORD hitLeftPos = GetCursorHitPos();	// 获取左键单击坐标
		COORD hitRightPos = GetCursorHitPos(2);	// 获取右键单击坐标
		key = GetKeyHit();						// 获取键盘输入
		operation = 0;							// 当前操作 (0无操作，1为挖开地块，2为标值旗帜，或者自己指定)

		// 检查键盘输入
		switch (key) {
		case VK_ESCAPE:
			// ESC键，将游戏运行状态置否以退出游戏
			gameFlag = false;
			break;

			// 上下左右键移动选中的坐标
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

			// 回车和空格分别对应操作1和2
		case VK_RETURN:
			operation = 1;
			break;
		case VK_SPACE:
			operation = 2;
			break;
		}

		// 将鼠标控制台的坐标放缩至地图坐标
		const size_t mouseY = (size_t)(pos.Y + 1) / 2 - 2;
		const size_t mouseX = (size_t)(pos.X - 1) / 4;
		if (mouseY < mapHeight && mouseX < mapWidth) {
			// 若没有超边界，更新选择的坐标
			posChoice.X = (SHORT)mouseX;
			posChoice.Y = (SHORT)mouseY;
		}

		// 左键和右键分别对应操作1和2
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
	找到每个位置周边的雷数
	*****************************************/
	void neighborBfs(int i, int j)
	{
		//当前位置的左上位置有雷则当前位置加1，下面的同理
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
	初始化地图
	*****************************************/
	void initMap() {
		//memset(mapArray, 0, sizeof(mapArray));     //mapArray清零
		memset(mapCanvas, 0, sizeof(mapCanvas));     //mapArray清零
		memset(mapArraytrue, 0, sizeof(mapArraytrue));  //mapArraytrue清零
		srand(time(NULL));                       //时间做种子
		randomCount = 0;                         //随机生成的地雷数初始化

		//随机位置生成地雷
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

		//为整个地图初始化
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
	BFS判断（i,j）的八邻域是否要被翻开
	*****************************************/
	void bfsNext(short i, short j)
	{
		if (i < 0 || i>9 || j < 0 || j>9 || idx[i * 10 + j] != 0)//越界或者已经访问过
			return;
		else if (mapArraytrue[i * 10 + j] != 0)                     //该位置为数字的边界
		{
			mapCanvas[i * 10 + j] = mapArraytrue[i * 10 + j];
			idx[i * 10 + j] = 1;
		}
		else                                               //该位置为空白
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
	bfsNext判断（i,j）是否为雷
	*****************************************/
	void bfsFirst(short x, short y)
	{
		mapCanvas[x * 10 + y] = 10;
		queBfs.push(x);
		queBfs.push(y);
		idx[x * 10 + y] = 1;

		//判断该位置的八邻域
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
	初始化地图以及翻开某位置
	*****************************************/
	void digBlock() {
		if (isFirst) {
			// 如果是第一步走，则先初始化地图，注意不要在落点设置一个地雷
			initMap();
			isFirst = false; // 将第一步设置为否
			memset(idx, 0, sizeof(idx));//idx数组清零
			if (mapArraytrue[posChoice.Y * 10 + posChoice.X] == 0)//如果该位置为空白
				bfsFirst(posChoice.Y, posChoice.X);
			else if (mapArraytrue[posChoice.Y * 10 + posChoice.X] > 0 && mapArraytrue[posChoice.Y * 10 + posChoice.X] < 9)//如果该位置为数字
			{
				mapCanvas[posChoice.Y * 10 + posChoice.X] = mapArraytrue[posChoice.Y * 10 + posChoice.X];
				idx[posChoice.Y * 10 + posChoice.X] = 1;
			}
			//updateMap(); // 更新地图画板
			renderMap(); // 绘制当前地图
			gameStart = 1;//游戏开始
			timeStart = GetTickCount64();//开始计时
			mineSum = 10;//雷数为10
			stepCount = 1;//步数为0
			return;
		}

		//不是第一步
		if (mapArraytrue[posChoice.Y * 10 + posChoice.X] == 9)//如果该位置为雷
		{
			stepCount++;
			mapCanvas[posChoice.Y * 10 + posChoice.X] = 9;
			for (int i = 0; i < 10; i++)//显示全部的雷，结束游戏
				for (int j = 0; j < 10; j++)
				{
					if (mapArraytrue[i * 10 + j] == 9)
						mapCanvas[i * 10 + j] = 9;
				}

			//updateMap(); // 更新地图画板
			renderMap(); // 绘制当前地图
			gameFail = 1;
		}
		else if (mapArraytrue[posChoice.Y * 10 + posChoice.X] > 0 && mapArraytrue[posChoice.Y * 10 + posChoice.X] < 9 && idx[posChoice.Y * 10 + posChoice.X] ==0)//如果该位置为数字
		{
			stepCount++;
			mapCanvas[posChoice.Y * 10 + posChoice.X] = mapArraytrue[posChoice.Y * 10 + posChoice.X];
			idx[posChoice.Y * 10 + posChoice.X] = 1;
		}
		else if(mapArraytrue[posChoice.Y * 10 + posChoice.X] ==0 && idx[posChoice.Y * 10 + posChoice.X] == 0)//如果该位置为空白
		{
			stepCount++;
			bfsFirst(posChoice.Y, posChoice.X);
		}

		//
		//updateMap(); // 更新地图画板
		renderMap(); // 绘制当前地图
	}

	/****************************************
	Function:  flagBlock()
	Parameter: None(void)
	Return:    None(void)
	Description:
	为该位置标记旗子或撤掉旗子
	*****************************************/
	void flagBlock() {
		//插旗子或撤销旗子
		if (mineSum != 0 && mapCanvas[posChoice.Y * 10 + posChoice.X] == 0 || mapCanvas[posChoice.Y * 10 + posChoice.X] == 9)//如果这里没有旗子
		{
			stepCount++;
			mapCanvas[posChoice.Y * 10 + posChoice.X] = 11;
			idx[posChoice.Y * 10 + posChoice.X] = 1;
			mineSum--;//雷数减1
		}

		//如果这里有旗子
		else if (mapCanvas[posChoice.Y * 10 + posChoice.X] == 11)
		{
			stepCount++;
			mapCanvas[posChoice.Y * 10 + posChoice.X] = 0;
			idx[posChoice.Y * 10 + posChoice.X] = 0;
			mineSum++;//雷数加1
		}

		//
		//updateMap(); // 更新地图画板
		renderMap(); // 绘制当前地图
	}

	/****************************************
	Function:  checkMouse()
	Parameter: None(void)
	Return:    None(void)
	Description:
	检查是否有鼠标单击，用来结束游戏
	*****************************************/
	void checkMouse()
	{
		clickMouse = 0;//没有点击鼠标
		FlushInput();// 刷新输入缓冲区
		pos = GetCursorPos();// 获取鼠标输入
		COORD hitLeftPos = GetCursorHitPos();// 获取鼠标单击输入
		if (hitLeftPos.X == pos.X && hitLeftPos.Y == pos.Y) {
			clickMouse = 1;//完成单击鼠标
		}
	}

	/****************************************
	Function:  endGame()
	Parameter: None(void)
	Return:    None(void)
	Description:
	胜利结束游戏的后续处理
	*****************************************/
	void endGame()
	{
		ClearScreen();//清屏
		MovePos(14, 2); // 移动坐标到 14,2
		PutString("你赢了！");
		MovePos(14, 4); // 移动坐标到 14,4
		PutString(strStep);
		MovePos(14, 6); // 移动坐标到 14,6
		PutString(strTime);
		MovePos(14, 8); // 移动坐标到 14,8
		PutString("鼠标左击返回主菜单");
		Update();// 将地图更新到屏幕
		bool runFlag = true;//判断有没有点击鼠标
		while (runFlag) {
			checkMouse();  // 检查输入
			if (clickMouse == 1)
				runFlag = false;
		}
	}

	/****************************************
	Function:  Play()
	Parameter: None(void)
	Return:    None(void)
	Description:
	开始游戏
	*****************************************/
	void Play() {
		//主要变量的初始化
		timeStart = 0;
		timeEnd = 0;
		gameFail = 0;
		stepCount = 0;
		gameStart = 0;
		isFirst = true;
		memset(strMine, 0, sizeof(strMine));
		memset(strStep, 0, sizeof(strStep));
		memset(strTime, 0, sizeof(strTime));

		//游戏开始
		gameFlag = true;
		while (gameFlag) {
			checkChoice(); // 检查输入

			// 查看当前坐标是否需要更新背景
			if (posChoice.X != posChoiceOld.X || posChoice.Y != posChoiceOld.Y) {
				clearChoiceBackground(posChoiceOld);
				posChoiceOld = posChoice;
			}
			renderChoiceBackground(posChoice);

			// 在0,0处放置当前选择位置的字符串，注意结尾有空格留白，可以思考为什么要加这么多空格
			MovePos(0, 0);
			char str[32] = "";
			sprintf_s(str, "当前选择(%u, %u)", posChoice.X, posChoice.Y);
			PutString(str);
			// 执行相应操作
			switch (operation) {
			case 1:
				// 翻开地块
				digBlock();
				break;
			case 2:
				// 标记为地雷
				flagBlock();
				break;
			}

			//显示雷数、步数、时间
			if (gameStart == 1)
			{
				//显示剩余雷数
				MovePos(0, 0);
				sprintf_s(strMine, "剩余雷数%d ", mineSum);
				PutString(strMine);

				//显示已走步数
				MovePos(0, 0);
				sprintf_s(strStep, "步数%d ", stepCount);
				PutString(strStep);

				//显示游戏时间
				timeEnd = GetTickCount64();
				int mintue = (timeEnd - timeStart) / 60000;
				int second = ((timeEnd - timeStart) / 1000) % 60;
				int smallsecond = ((timeEnd - timeStart) / 10) % 100;
				MovePos(0, 0);
				//根据分钟、秒、百分之一秒是否大于10，确定是否要显示零
				if (mintue < 10 && second < 10 && smallsecond < 10)
					sprintf_s(strTime, "时间:0%d:0%d:0%d", mintue, second, smallsecond);
				else if (mintue < 10 && second < 10)
					sprintf_s(strTime, "时间:0%d:0%d:%d", mintue, second, smallsecond);
				else if (mintue < 10 && smallsecond < 10)
					sprintf_s(strTime, "时间:0%d:%d:0%d", mintue, second, smallsecond);
				else if (mintue < 10)
					sprintf_s(strTime, "时间:0%d:%d:%d", mintue, second, smallsecond);
				else if (second < 10 && smallsecond < 10)
					sprintf_s(strTime, "时间:%d:0%d:0%d", mintue, second, smallsecond);
				else if (second < 10)
					sprintf_s(strTime, "时间:%d:0%d:%d", mintue, second, smallsecond);
				else if (smallsecond < 10)
					sprintf_s(strTime, "时间:%d:%d:0%d", mintue, second, smallsecond);
				else
					sprintf_s(strTime, "时间:%d:%d:%d", mintue, second, smallsecond);
				PutString(strTime);
			}

			//游戏是否失败
			if (gameFail == 1)
			{
				MovePos(14, 2); // 移动坐标到 14,2
				PutString("很遗憾，失败了"); // 在这个坐标放置一个string
				MovePos(14, 4); // 移动坐标到 14,4
				PutString("鼠标左击返回主菜单"); // 在这个坐标放置一个string
				Update();// 将地图更新到屏幕
				bool runFlag = true;//判断有没有点击鼠标
				while (runFlag) {
					checkMouse();  // 检查输入
					if (clickMouse == 1)
						runFlag = false;
				}
				return;
			}

			//游戏是否胜利结束
			gameEnd = 0;
			if (operation != 0)
			{
				for (int i = 0; i < 10; i++)
					for (int j = 0; j < 10; j++)
					{
						if (mapCanvas[i * 10 + j] == 0)
							gameEnd = 1;
					}
				if (gameEnd == 0)//游戏结束了
				{
					endGame();
					return;
				}

				else//游戏没结束
				{
					gameEnd = 0;
				}
			}

			// 以下内容不建议修改 处理每帧的事务
			//updateMap(); // 更新地图画板
			Update();    // 更新操作到			
			frame++;  // 渲染帧数自增
			clock_t elapsed = 25 - (clock() - tic); // 检查上一帧渲染时间，并计算与25的差值
			Sleep(elapsed > 0 ? elapsed : 0);	    // 若差值大于零，则休眠该差值的毫秒数，以确保每帧渲染不超过50帧
			tic = clock();						    // 更新上一次记录的时间
		}
	}

	/****************************************
	Function:  DestroyGame()
	Parameter: None(void)
	Return:    None(void)
	Description:
	结束游戏，回收动态申请的变量
	*****************************************/
	void DestroyGame() {
		delete[] mapCanvas;
	}
}