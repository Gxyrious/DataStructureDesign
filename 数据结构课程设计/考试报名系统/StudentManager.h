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
	void PrintInterFace();//��ӡ����̨��ʾ��
	void createSystem();//����������Ϣϵͳ
	void insertStudent();//��ӿ���
	void pollStudent();//��ȡ����ѯ������
	void modifyStudent();//�޸Ŀ���
	void removeStudent();//�Ƴ�����
	void printStudent();//��ӡ������Ϣ
	void updateStudentId();//���¿������id
};