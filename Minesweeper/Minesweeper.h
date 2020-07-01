#pragma once
#include <graphics.h>
#include <vector>
using namespace std;
class Minesweeper
{
public:
	static bool init;
	static int R;
	static int C;
	static void Map_Initial(vector<vector<int> > &map);
	static void showblank(vector<vector<int> > &map, int my, int mx);
	static void drawmap(vector<vector<int> > &map, IMAGE img[]);
	static int moudown(vector<vector<int> > &map);
	static int GameStar(vector<vector<int> > &map,IMAGE img[], HWND hWnd);
	static void FromInputbox2getRC();
	friend bool reset();
	//static bool GetInit() { return init; }
	//static void SetInit(bool ini) { init = ini; }
	//static int GetR() { return R; }
	//static int GetC() { return C; } 

private:
	static int flag;
	static int  Mine_Num;

};
