#include"InitFile.h"

InitFile::InitFile()
{
	_input = "";
	cout << "�������ļ�����Ĭ�������ΪDefault.txt����";
	getline(cin, _input);
	//������뻻�У���_input��Ϊ""
	_name = (_input == "" ? "Default.txt" : _input);
	_fout.open(_name, ios::out /*| ios::app*/);
}

InitFile::~InitFile()
{
	_fout.close();
}

void InitFile::InputText()
{
	cout << "������Ӣ�Ķ��䣨�Ե���һ�е�0��Ϊ������־����" << endl;
	while (getline(cin, _input))
	{
		if (_input == "0") {
			break;
		}
		transform(_input.begin(), _input.end(), _input.begin(),std::tolower);//ȫ��תΪСд
		_fout << _input << endl;
	}
}

string InitFile::getFilename() const
{
	return _name;
}
