#pragma once
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class KeywordSearch {
public:
	//���캯������ҪѰ�ҵĹؼ��֣���Ҫ�������ļ���
	KeywordSearch(const string& keyword, const string& filename);
	
	//�����������ر��ļ�
	~KeywordSearch();

	//��ȡ�ؼ��ֳ��ֵĴ���
	int getCount();
private:
	string _filename,_keyword;
	ifstream _fin;
	int _count;
};