#pragma once
#include <iostream>
#include <vector>
using namespace std;
class Initial
{
public:
	static int string2num(wchar_t s1[]);
	static int deleteAllMark(std::string& s, const std::string& mark);
	static void Load(vector<vector<int> > &m);
	static void write(vector<vector<int> >& map, int R, int C);
};

