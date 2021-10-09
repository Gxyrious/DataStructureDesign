#pragma once
#include<iostream>
#include"LinkedList.hpp"
#include"StudentModel.h"

class StudentManager
{
public:
	StudentManager() {}
	~StudentManager() {}
	void run();
private:
	LinkedList<Student> stuList;
	void PrintInterFace();//打印控制台提示词
	void createSystem();//建立考生信息系统
	void insertStudent();//添加考生
	void pollStudent();//拉取（查询）考生
	void modifyStudent();//修改考生
	void removeStudent();//移除考生
	void printStudent();//打印考生信息
	void updateStudentId();//更新考生编号id
};