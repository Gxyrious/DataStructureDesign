#pragma once
#include<string>
#include<iostream>

using namespace std;

class Student {
public:
	//��������
	Student(int id = -1, int num = 0, string name = "", char sex = '\0', short int age = 0,string category = "");
	
	//��ȡ����������Ϣ
	int getId()const;
	int getNumber()const;
	string getName()const;
	char getSex()const;
	int getAge()const;
	string getCategory()const;

	//�޸Ŀ���������Ϣ
	void setId(int id);
	void setNumber(int num);
	void setName(string name);
	void setSex(char sex);
	void setAge(short int age);
	void setCategory(string category);

	//������Ϣ�����������
	friend istream& operator>>(istream& input, Student& stu);
	friend ostream& operator<<(ostream& output, const Student& stu);
private:
	int _id;//���
	int _number;//׼��֤��
	string _name;//����
	char _sex;//�Ա�
	short int _age;//����
	string _category;//�������
};