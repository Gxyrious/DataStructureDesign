#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>

using namespace std;

class InitFile {
public:
	InitFile();
	~InitFile();
	void InputText();
	string getFilename()const;
private:
	string _name, _input;
	ofstream _fout;
};