#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>

using namespace std;

class InitFile {
public:
	//构造函数：初始化文件名，并以ios::out形式创建（或打开）文件
	//ios::out形式打开文件：若不存在该文件，则创建文件；若存在，则清空文件之后打开
	InitFile();

	//析构函数：关闭文件
	~InitFile();

	//获取输入的文本（以单独一行的0结尾）
	void InputText();

	//获取文件名
	string getFilename()const;
private:
	//_name是文件名，_input是未经处理的直接从终端输入的内容
	//_fout是文件输出流
	string _name, _input;
	ofstream _fout;
};