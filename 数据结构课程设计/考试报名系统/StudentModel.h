#pragma once
#include<string>
#include<iostream>
using namespace std;
class Student {
public:
	Student(int id = -1, int num = 0, string name = "", char sex = '\0', short int age = 0);
	int getId()const;
	int getNumber()const;
	string getName()const;
	char getSex()const;
	int getAge()const;
	void setId(int id);
	void setNumber(int num);
	void setName(string name);
	void setSex(char sex);
	void setAge(short int age);
	friend istream& operator>>(istream& input, Student& stu);
	friend ostream& operator<<(ostream& output, const Student& stu);
private:
	int _id;//编号
	int _number;//准考证号
	string _name;//姓名
	char _sex;//性别
	short int _age;//年龄
};