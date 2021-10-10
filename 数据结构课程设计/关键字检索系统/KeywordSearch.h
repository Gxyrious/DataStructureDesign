#pragma once
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class KeywordSearch {
public:
	KeywordSearch(const string& keyword, const string& filename);
	~KeywordSearch();
	int getCount();
private:
	string _filename,_keyword;
	ifstream _fin;
	int _count;
};