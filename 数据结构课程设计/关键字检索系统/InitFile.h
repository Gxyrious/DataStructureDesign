#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>

using namespace std;

class InitFile {
public:
	//���캯������ʼ���ļ���������ios::out��ʽ��������򿪣��ļ�
	//ios::out��ʽ���ļ����������ڸ��ļ����򴴽��ļ��������ڣ�������ļ�֮���
	InitFile();

	//�����������ر��ļ�
	~InitFile();

	//��ȡ������ı����Ե���һ�е�0��β��
	void InputText();

	//��ȡ�ļ���
	string getFilename()const;
private:
	//_name���ļ�����_input��δ�������ֱ�Ӵ��ն����������
	//_fout���ļ������
	string _name, _input;
	ofstream _fout;
};