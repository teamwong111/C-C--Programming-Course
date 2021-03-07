#pragma once
//头
#include <time.h>
#include <conio.h>
#include <vector>
#include <graphics.h>
#include<iostream>
#include<fstream>
using namespace std;
//按钮
#define MY_OK 0//只有“确定”按钮							
#define MY_YESNO 1//有“是”按钮和“否”按钮						
//枚举蛇的方向
enum position { up, down, Left, Right };		