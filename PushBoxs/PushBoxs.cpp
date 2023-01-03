#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include <iostream>
#include <string>
#include <fstream>
#define RELEASE
using namespace std;
const int plate[5][100] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,4,0,1,1,1,1,1,1,0,3,2,0,1,1,1,1,1,1,4,1,3,0,1,1,1,1,1,1,0,3,0,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,4,0,1,1,1,1,1,1,0,3,2,0,1,1,1,1,1,1,4,1,3,0,1,1,1,1,1,1,0,3,0,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,4,0,1,1,1,1,1,1,0,3,2,0,1,1,1,1,1,1,4,1,3,0,1,1,1,1,1,1,0,3,0,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,4,0,1,1,1,1,1,1,0,3,2,0,1,1,1,1,1,1,4,1,3,0,1,1,1,1,1,1,0,3,0,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,4,0,1,1,1,1,1,1,0,3,2,0,1,1,1,1,1,1,4,1,3,0,1,1,1,1,1,1,0,3,0,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
// 0为空场地(白)，1为墙（黑），2为人物（圆形红色），3为箱子（橙），4为箱子目的地（圆形绿色），7为到达目的地的箱子（橙底圆形绿色0）
int* load(int round);
void save(int round);
void drawOriginPlate(int* plate);
void drawPlate(int* plate);
int pushBoxs(int* plate);
void push(int*,char operate);
int judgeWin(int*);
int judgeOutOfBound(int*, char operate);
int main() {
	cout << "Push Box" << endl;
	cout << endl;
	cout << "This red circle is you! Type in the 'w' 'a' 's' 'd' to control the red circle, " << endl << "push the orange box on their destination --the green circle."<<endl;
	cout << "If you want to save the level, press the 'p'. " << endl;
	cout << "And if you make a wrong choice, just press the 'r' to restart this level." << endl;
	cout << endl;
	int round = 1;
	ifstream box;
	box.open("C:\\CandCPP\\pushbox.txt", ios::out);
	if (box.is_open()) {
#ifdef DEBUG
		cout << "Open successfully" << endl;
		cout << endl;
#endif // 
		box >> round;
		cout << "Now you are in Level " << round << endl;
		cout << endl;
		cout << "If you want to change the level, please open 'pushbox.txt' and modify the level number." << endl;
		cout << endl;
		cout << endl;
	}
	else
	{
		cout << "Open failed!" << endl;
		cout << "Attention! The path of file 'pushbox.txt' can't involve Chinese!" << endl;
		box.close();
		return 1;
	}
	box.close();
	int state = -1;
	while (1) {
		int* plate = load(round);//load函数读取
		if (*plate == 100) {
			cout << "If you want to add some levels, please modify the array -- plate in the code." << endl;
			cout << endl;
			return 2;
		}
		state = pushBoxs(plate);
		if (state == 0) 
		{
			round++;
		}
		else if (state == 2) 
		{
			state = -1;
		}
		else if (state == 1) {
			break;
		}
	}
	save(round - 1);
	return 0;
}
int pushBoxs(int* plate) {
	int state;
	drawOriginPlate(plate);
	int judge = 0;
	while (judge == 0) 
	{
		char operate;
		cin >> operate;
		switch (operate)
			{
				case 'w':
				case 'a':
				case 's':
				case 'd':
				{
					push(plate, operate);
					drawPlate(plate);
					break;
				}
				case 'r':
					return 2;
				case 'p':
					return 1;
				default:
					cout << "ERROR! You are trying to type in an illegal char!" << endl;
					cout << endl;
					break;
			}
		judge = judgeWin(plate);
	}
	return 0;
}
int* load(const int round) 
{
	if (round >= 5) {
		cout << "ERROR! We don't have write so many levels!" << endl;
		int* p = (int*)malloc(sizeof(int));
		*p = 100;
		return p;
	}
	else {
		int* p = (int*)malloc(sizeof(int) * 100);
		for (int i = 0; i < 100; i++) {
			p[i] = plate[round][i];
		}
#ifdef DEBUG
		for (int i = 0; i < 100; i++) {
			cout << p[i] << " ";
			if ((i + 1) % 10 == 0) {
				cout << endl;
			}
		}
#endif//DEBUG
		return p;
	}
}
void save(int round) 
{
	fstream box;
	box.open("C:\\Users\\陈旭\\source\\repos\\PushBoxs\\PushBoxspushBox.txt", ios::in|ios::out);
	box << round;
	box.close();
}
void drawOriginPlate(int* plate) 
{
	initgraph(600, 600, EX_SHOWCONSOLE);
	COLORREF origincolor[6] = { RGB(0,0,38),WHITE,BLACK,RGB(255,128,0),GREEN,RED};
	setbkcolor(origincolor[0]);
	cleardevice();
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			int temp = *(plate + 10 * i + j);
			switch (temp)
			{
			case 0: {
				setfillcolor(origincolor[1]);
				fillrectangle((50 * (j + 1)), (50 * (i + 1)), (50 * (j + 2)), (50 * (i + 2)));
				break;
			}
			case 1: {
				setfillcolor(origincolor[2]);
				fillrectangle((50 * (j + 1)), (50 * (i + 1)), (50 * (j + 2)), (50 * (i + 2)));
				break;
			}
			case 2: {
				setfillcolor(origincolor[1]);
				fillrectangle((50 * (j + 1)), (50 * (i + 1)), (50 * (j + 2)), (50 * (i + 2)));
				setfillcolor(origincolor[5]);
				fillcircle((50 * (j + 1) + 20), (50 * (i + 1) + 20), 10);
				break;
			}
			case 3: {
				setfillcolor(origincolor[3]);
				fillrectangle((50 * (j + 1)), (50 * (i + 1)), (50 * (j + 2)), (50 * (i + 2)));
				break;
			}
			case 4:{
				setfillcolor(origincolor[1]);
				fillrectangle((50 * (j + 1)), (50 * (i + 1)), (50 * (j + 2)), (50 * (i + 2)));
				setfillcolor(origincolor[4]);
				fillcircle((50 * (j + 1) + 20), (50 * (i + 1) + 20), 5);
				
				break;
			}
			case 7: {
				setfillcolor(origincolor[3]);
				fillrectangle((50 * (j + 1)), (50 * (i + 1)), (50 * (j + 2)), (50 * (i + 2)));
				setfillcolor(origincolor[4]);
				fillcircle((50 * (j + 1) + 20), (50 * (i + 1) + 20), 5);
				break;
			}
			default:
#ifdef DEBUG
printf("Block information ERROR!");
#endif // DEBUG
				break;
			}
		}
	}
}
void drawPlate(int* plate) 
{
	initgraph(600, 600, EX_SHOWCONSOLE);
	COLORREF origincolor[6] = { RGB(0,0,38),WHITE,BLACK,RGB(255,128,0),GREEN,RED };
	setbkcolor(origincolor[0]);
	cleardevice();
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			int temp = *(plate + 10 * i + j);
			switch (temp)
			{
			case 0: {
				setfillcolor(origincolor[1]);
				fillrectangle((50 * (j + 1)), (50 * (i + 1)), (50 * (j + 2)), (50 * (i + 2)));
				break;
			}
			case 1: {
				setfillcolor(origincolor[2]);
				fillrectangle((50 * (j + 1)), (50 * (i + 1)), (50 * (j + 2)), (50 * (i + 2)));
				break;
			}
			case 2: {
				setfillcolor(origincolor[1]);
				fillrectangle((50 * (j + 1)), (50 * (i + 1)), (50 * (j + 2)), (50 * (i + 2)));
				setfillcolor(origincolor[5]);
				fillcircle((50 * (j + 1) + 20), (50 * (i + 1) + 20), 10);
				break;
			}
			case 3: {
				setfillcolor(origincolor[3]);
				fillrectangle((50 * (j + 1)), (50 * (i + 1)), (50 * (j + 2)), (50 * (i + 2)));
				break;
			}
			case 4: {
				setfillcolor(origincolor[1]);
				fillrectangle((50 * (j + 1)), (50 * (i + 1)), (50 * (j + 2)), (50 * (i + 2)));
				setfillcolor(origincolor[4]);
				fillcircle((50 * (j + 1) + 20), (50 * (i + 1) + 20), 5);

				break;
			}
			case 7: {
				setfillcolor(origincolor[3]);
				fillrectangle((50 * (j + 1)), (50 * (i + 1)), (50 * (j + 2)), (50 * (i + 2)));
				setfillcolor(origincolor[4]);
				fillcircle((50 * (j + 1) + 20), (50 * (i + 1) + 20), 5);
				break;
			}
			default:
#ifdef DEBUG
				printf("Block information ERROR!");
#endif // DEBUG
				break;
			}
		}
	}
}
void push(int* plate, char operate) 
{
	int judge = judgeOutOfBound(plate,operate);
	if (judge == 0)
	{
		//实现功能的代码
	}
	else 
	{
		return;//超出则终止函数
	}
}
int judgeWin(int* plate) 
{
	int judge = 0;
	for (int i = 0; i < 100; i++) {
		if (plate[i] == 7) {
			judge++;
		}
	}
	if (judge == 3) {
		return 1;
	}
	else
	{
		return 0;
	}
}
int judgeOutOfBound(int* plate, char operate)
{
	return 0;
}