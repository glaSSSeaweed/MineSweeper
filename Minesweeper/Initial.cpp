#include "Initial.h"
#include <windows.h>
#include <string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

int Initial::string2num(wchar_t s1[])
{
	wchar_t* pwszUnicode(s1);
	int iSize;
	char* pszMultiByte;
	//返回接受字符串所需缓冲区的大小，已经包含字符结尾符'\0'
	iSize = WideCharToMultiByte(CP_ACP, 0, pwszUnicode, -1, NULL, 0, NULL, NULL); //iSize =wcslen(pwsUnicode)+1=6
	pszMultiByte = (char*)malloc(iSize * sizeof(char)); 
	WideCharToMultiByte(CP_ACP, 0, pwszUnicode, -1, pszMultiByte, iSize, NULL, NULL);
	string str = pszMultiByte;
	return atoi(str.c_str());
}

int Initial::deleteAllMark(string& s, const string& mark)
{
	unsigned int nSize = mark.size();
	while (1)
	{
		unsigned int pos = s.find(mark);
		if (pos == string::npos)
		{
			//TODO
			return -1;
		}

		s.erase(pos, nSize);
	}
	return 1;
}

//vector<vector<int> > map;
//map.resize(R1, vector<int>(C1));
void Initial::Load(vector<vector<int> >& m)
{
	int a;
	m.clear();
	std::ifstream f;
	f.open("data.txt");

	std::string str;
	std::getline(f, str);
	Initial::deleteAllMark(str, " ");
	int SIZE = str.length();
	if (SIZE == 0){
		return;
	}

	//还要判断是不是在EOF，这里暂时不实现 // 如果写入整个棋盘，则不用判断，因为必然有第二行
	f.seekg(0L, std::ios::beg);
	m.resize(SIZE, vector<int>(SIZE));
	for (int i = 0; std::getline(f, str); i++){
		std::istringstream input(str);
		for (int j = 0; input >> a; j++){
			m[i][j] = a;
		}
	}

	//for (int i = 0; i < SIZE; ++i)
	//{
	//	for (int j = 0; j < SIZE; ++j)
	//	{
	//		std::cout << m[i][j] << " ";
	//	}
	//	std::cout << std::endl;
	//}
	f.close();
}
void Initial::write(vector<vector<int> >& arr, int R, int C) {
	std::ofstream outfile("data.txt");
	for (int i = 0; i < R+2; i++) {
		for (int j = 0; j < C+2; j++)
		{
			outfile << arr[i][j] << " ";
		}
		outfile << std::endl;
	}
	outfile.close();
}