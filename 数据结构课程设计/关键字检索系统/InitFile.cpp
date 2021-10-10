#include"InitFile.h"

InitFile::InitFile()
{
	_input = "";
	cout << "请输入文件名（默认情况下为Default.txt）：";
	getline(cin, _input);
	//如果输入换行，则_input仍为""
	_name = (_input == "" ? "Default.txt" : _input);
	_fout.open(_name, ios::out /*| ios::app*/);
}

InitFile::~InitFile()
{
	_fout.close();
}

void InitFile::InputText()
{
	cout << "请输入英文段落（以单独一行的0作为结束标志）：" << endl;
	while (getline(cin, _input))
	{
		if (_input == "0") {
			break;
		}
		transform(_input.begin(), _input.end(), _input.begin(),std::tolower);//全部转为小写
		_fout << _input << endl;
	}
}

string InitFile::getFilename() const
{
	return _name;
}
