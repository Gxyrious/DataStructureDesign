#pragma once
#include<string>
#include<iostream>

using namespace std;

class Student {
public:
	//构建函数
	Student(int id = -1, int num = 0, string name = "", char sex = '\0', short int age = 0,string category = "");
	
	//获取考生各种信息
	int getId()const;
	int getNumber()const;
	string getName()const;
	char getSex()const;
	int getAge()const;
	string getCategory()const;

	//修改考生各种信息
	void setId(int id);
	void setNumber(int num);
	void setName(string name);
	void setSex(char sex);
	void setAge(short int age);
	void setCategory(string category);

	//考生信息输入输出重载
	friend istream& operator>>(istream& input, Student& stu);
	friend ostream& operator<<(ostream& output, const Student& stu);
private:
	int _id;//编号
	int _number;//准考证号
	string _name;//姓名
	char _sex;//性别
	short int _age;//年龄
	string _category;//报考类别
};