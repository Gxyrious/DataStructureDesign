#include<iostream>
#include<fstream>
#include"InitFile.h"
#include"KeywordSearch.h"

using namespace std;

int main() {
	InitFile init_file;
	init_file.InputText();

	string keyword;
	cout << "请输入要检索的关键字：" << endl;
	cin >> keyword;
	transform(keyword.begin(), keyword.end(), keyword.begin(), std::tolower);//全部转为小写

	KeywordSearch kwSearch(keyword, init_file.getFilename());
	cout << "出现次数为：" << kwSearch.getCount() << "\n";
	system("pause");
	return 0;
}