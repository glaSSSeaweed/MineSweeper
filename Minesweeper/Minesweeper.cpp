#include "Minesweeper.h"
#include "Initial.h"
#include <ctime>        //time
#include <cstdlib>      // rand
#include <graphics.h>
#include <iostream>
#include <conio.h>

int Minesweeper::R = 9;
int Minesweeper::C = 9;
int Minesweeper::Mine_Num = 9;
int Minesweeper::flag = 0;
bool Minesweeper::init = true;

void Minesweeper::Map_Initial(vector<vector<int> >& map)
{

	//initializing MINE
	int rd1 = 0, rd2 = 0;
	srand((unsigned int)time(0));    //random seed
	int n = 0;
	while (n < Mine_Num) {
		rd1 = (rand() % R) + 1;		//a random number between 1-R
		rd2 = (rand() % R) + 1;		//a random number between 1-R
		if (map[rd1][rd2] == 0) {
			map[rd1][rd2] = -1;
			n++;
		}
	}
	//initializing MAP
	int p, q;
	int i = 0, j = 0;
	for (i = 1; i <= R; i++) {
		for (j = 1; j <= R; j++) {
			if (map[i][j] != -1) {
				for (p = i - 1; p <= i + 1; p++) {
					for (q = j - 1; q <= j + 1; q++) {
						if (map[p][q] == -1)
							map[i][j] += 1;
					}
				}
			}
		}
	}
}

void Minesweeper::showblank(vector<vector<int> >& map, int my, int mx)
{
	map[my][mx] = 20;
	int p, q;
	for (p = my - 1; p <= my + 1; p++) {
		for (q = mx - 1; q <= mx + 1; q++) {
			if ((p >= 1) && (p <= R) && (q >= 1) && (q <= C)) {
				if (map[p][q] == -1) {
					//一个雷旁边一定有数字，也可以不用判断。
				}
				else if (map[p][q] <= 8 && map[p][q] > -1) {
					if (map[p][q] == 0)
						showblank(map, p, q);
					else
						map[p][q] += 20;
				}
			}
		}
	}
}

void Minesweeper::drawmap(vector<vector<int> >& map, IMAGE img[]) {
	//int i = 0, j = 0;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= R; j++) {
			//第i行的 第j个元素
			int y = 50 * (i - 1);
			int x = 50 * (j - 1);
			switch (map[i][j]) {
			case -1 + 20:
				putimage(x, y, &img[9]);
				break;
			case 0 + 20:
				putimage(x, y, &img[0]);
				break;
			case 1 + 20:
				putimage(x, y, &img[1]);
				break;
			case 2 + 20:
				putimage(x, y, &img[2]);
				break;
			case 3 + 20:
				putimage(x, y, &img[3]);
				break;
			case 4 + 20:
				putimage(x, y, &img[4]);
				break;
			case 5 + 20:
				putimage(x, y, &img[5]);
				break;
			case 6 + 20:
				putimage(x, y, &img[6]);
				break;
			case 7 + 20:
				putimage(x, y, &img[7]);
				break;
			case 8 + 20:
				putimage(x, y, &img[8]);
				break;
			default:
				if (map[i][j] < -1) {
					if (map[i][j] <= -7 && map[i][j] >= -21)
						putimage(x, y, &img[11]);
					else
						putimage(x, y, &img[12]);
				}
				else
					putimage(x, y, &img[13]);
				break;

			}

		}
	}
}


int Minesweeper::moudown(vector<vector<int> >& map) {
	MOUSEMSG mou;
	while (true)
	{
		mou = GetMouseMsg();
		int mx = mou.x / 50 + 1;
		int my = mou.y / 50 + 1;

		switch (mou.uMsg) {
		case WM_RBUTTONDOWN:
			if (map[my][mx] <= -7 && map[my][mx] >= -21) {
				if (map[my][mx] == -21) {
					--flag;
				}
				map[my][mx] -= 20;
			}
			else if (map[my][mx] <= -27 && map[my][mx] >= -41) {
				map[my][mx] += 40;
			}
			else {
				if (map[my][mx] == -1) {
					++flag;
				}
				map[my][mx] -= 20;
			}
			return map[my][mx];
		case WM_LBUTTONDOWN:
			if (mou.y > 50 * R && mou.x < (C * 25)) {
				//cout << "L" << endl;
				return -100;
			}
			else if (mou.y > 50 * R && mou.x > (C * 25)) {
				//cout << "R" << endl;
				return -101;
			}
			else if (map[my][mx] <= -7 && map[my][mx] >= -21) {
				if (map[my][mx] == -21) {
					flag--;
				}
				map[my][mx] += 20;
			}
			else if ((map[my][mx] <= -27) && (map[my][mx] >= -41)) {
				if (map[my][mx] == -41) {
					flag++;
				}
				map[my][mx] += 20;
			}
			else if (map[my][mx] > 19) {
				continue;
			}
			else if (map[my][mx] == 0) {
				showblank(map, my, mx);
			}
			else if (map[my][mx] == 19 || map[my][mx] == 20) {
				//continue;
			}
			else {
				map[my][mx] += 20;
			}
			return map[my][mx];
		}
	}
}

int Minesweeper::GameStar(vector<vector<int> >& map, IMAGE img[], HWND hWnd)
{

	if (init)
	{
		Map_Initial(map);
	}
	initgraph(50 * R, 50 * (C + 2), SHOWCONSOLE);
	hWnd = GetHWnd();
	//TODO
	//字体按照棋盘大小缩放问题为解决
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 48;						// 设置字体高度为 48
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);
	RECT r = { 0, R * 50, C * 25, (R + 2) * 50 };
	drawtext(_T("LOAD"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r1 = { C * 25, R * 50 , C * 50, (R + 2) * 50 };
	drawtext(_T("SAVE"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	flag = 0;
	while (true)
	{
		//FlushMouseMsgBuffer();
		drawmap(map, img);
		int md = moudown(map);
		if (md == 19) {
			drawmap(map, img);
			MessageBox(hWnd,
				L"GAME OVER",
				L"BOOM",
				MB_OK);
			//MessageBox("这是一个两种属性的消息框！","标题", MB_ICONEXCLAMATION|MB_OKCANCEL ); 
			cout << "长亭送别" << endl;
			cout << "朝朝兮红日，潺潺兮流水。\n醉人兮红尘，侃侃兮君随。" << endl;
			return -1;
		}
		else if (flag == Mine_Num) {
			cout << "win" << endl;
			MessageBox(hWnd,
				L"YOU WIN!",
				L"!CONGRATULATION!",
				MB_OK);
			//return win
			return 221;
		}
		else if (md == -100) {

			return -100;
		}
		else if (md == -101) {
			return -101;
		}

	}
	_getch();              // 按任意键继续
	closegraph();          // 关闭绘图窗口
	return 0;
}

void Minesweeper::FromInputbox2getRC() {
	wchar_t s1[10] = { '\0' };
	InputBox(s1, 10, _T("请输入行数(默认9行列)"));

	int tmp = Initial::string2num(s1);
	if (tmp != 0) {
		R = tmp;
		C = tmp;
		Mine_Num = tmp;
	}
}