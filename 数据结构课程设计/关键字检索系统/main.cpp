#include<iostream>
#include<fstream>
#include"InitFile.h"
#include"KeywordSearch.h"

using namespace std;

int main() {
	InitFile init_file;
	init_file.InputText();

	string keyword;
	cout << "������Ҫ�����Ĺؼ��ʣ�" << endl;
	cin >> keyword;
	transform(keyword.begin(), keyword.end(), keyword.begin(), std::tolower);//ȫ��תΪСд

	KeywordSearch kwSearch(keyword, init_file.getFilename());
	cout << kwSearch.getCount();
	return 0;
}