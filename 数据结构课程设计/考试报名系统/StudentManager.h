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
	void PrintInterFace();
	void createSystem();
	void insertStudent();
	void pollStudent();
	void modifyStudent();
	void removeStudent();
	void printStudent();
	void updateStudentId();
};