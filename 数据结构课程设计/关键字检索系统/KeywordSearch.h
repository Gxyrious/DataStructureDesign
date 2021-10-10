#pragma once
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class KeywordSearch {
public:
	//构造函数传入要寻找的关键字，将要搜索的文件打开
	KeywordSearch(const string& keyword, const string& filename);
	
	//析构函数，关闭文件
	~KeywordSearch();

	//获取关键字出现的次数
	int getCount();
private:
	string _filename,_keyword;
	ifstream _fin;
	int _count;
};