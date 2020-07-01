#include <iostream>
#include <graphics.h>
#include <string>
#include<fstream>
#include<sstream>
#include <vector>
#include "Minesweeper.h"
#include "Initial.h"

using namespace std;
IMAGE img[14];
HWND hWnd;
int R1, C1;
bool reset();// friend Minesweeper
void LoadImg();


int main() {
	Minesweeper::FromInputbox2getRC();
	vector<vector<int> > map;
	map.resize(Minesweeper::R + 2, vector<int>(Minesweeper::C + 2));
	LoadImg();

	int state;
	while (true) {
		state = Minesweeper::GameStar(map, img, hWnd);
		if (state == -100) {
			Minesweeper::init = false;
			if (!reset()) {
				MessageBox(hWnd, L"NO SAVE", L"NO SAVE", MB_OK);
				continue;
			}
			//cout << "LOAD GAME" << endl;
			map.clear();
			Initial::Load(map);
			continue;
		}
		else if (state == -101) {
			Initial::write(map, Minesweeper::R, Minesweeper::C);
			MessageBox(hWnd, L"SAVE", L"SAVE", MB_OK);
			//cout << "SAVE" << endl;
			return 0;
		}
		else if (state == 221) {
			return 0;
		}
		else if (state == -1) {
			return 0;
		}
	}
	return 0;

}
void LoadImg() {
	loadimage(&img[0], _T("blank.png"), 50, 50);
	loadimage(&img[1], _T("1.png"), 50, 50);
	loadimage(&img[2], _T("2.png"), 50, 50);
	loadimage(&img[3], _T("3.png"), 50, 50);
	loadimage(&img[4], _T("4.png"), 50, 50);
	loadimage(&img[5], _T("5.png"), 50, 50);
	loadimage(&img[6], _T("6.png"), 50, 50);
	loadimage(&img[7], _T("7.png"), 50, 50);
	loadimage(&img[8], _T("8.png"), 50, 50);
	loadimage(&img[9], _T("mine.png"), 50, 50);
	//loadimage(&img[10], _T("explode.png"), 50, 50);
	loadimage(&img[11], _T("flag.png"), 50, 50);
	loadimage(&img[12], _T("question.png"), 50, 50);
	loadimage(&img[13], _T("initial.png"), 50, 50);
}

bool reset() {
	ifstream f;
	f.open("data.txt");

	string str1;
	getline(f, str1);
	if (str1 == "") {
		return false;
	}
	Initial::deleteAllMark(str1, " ");
	int SIZE = str1.length();
	f.close();
	Minesweeper::R = SIZE - 2;
	Minesweeper::C = SIZE - 2;
	Minesweeper::Mine_Num = SIZE - 2;
	return true;
}


