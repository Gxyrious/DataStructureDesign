#include "StudentManager.h"

void StudentManager::PrintInterFace()
{
	cout << "----------------------" << endl
		<< "|请输入操作数，如下： |" << endl
		<< "|0退出       1添加    |" << endl
		<< "|2查询       3修改    |" << endl
		<< "|4删除       5打印    |" << endl
		<< "-----------------------" << endl;
}

void StudentManager::insertStudent()
{
	cout << "请输入要添加的考生个数" << endl;
	int n;
	cin >> n;
	if (n <= 0) {
		cout << "输入有误！" << endl;
	}
	else {
		cout << "请依次输入各考生的考号、姓名、性别、年龄、报考类别：" << endl;
		for (int i = 1; i <= n; i++) {
			Student stu;
			cin >> stu;
			for (LinkNode<Student>* iter = stuList.getHead()->_next; iter; iter = iter->_next) {
				if (iter->_data.getNumber() == stu.getNumber()) {
					cout << "考生考号有重复，异常退出！" << endl;
					return;
				}
			}
			if (!stuList.push_back(stu)) {
				cout << "第" << i << "个考生插入失败！" << endl;
				return;
			}
		}
		cout << "插入成功！" << endl;
	}
}

void StudentManager::pollStudent()
{
	cout << "请输入需要查询的考生编号：" << endl;
	int id;
	cin >> id;
	LinkNode<Student>* tar = stuList.Locate(id);
	if (!id || !tar) {
		cout << "不存在这名考生！" << endl;
	}
	else {
		cout << "查询成功！" << endl << tar->_data << endl;
	}
}

void StudentManager::modifyStudent()
{
	cout << "请输入要修改的考生编号：" << endl;
	int id;
	cin >> id;
	LinkNode<Student>* tar = stuList.Locate(id);
	if (!id || !tar) {
		cout << "不存在这名考生！" << endl;
	}
	else {
		cout << "该考生目前信息为：" << tar->_data << endl
			<< "请输入修改后的考号、姓名、性别、年龄：" << endl;
		cin >> tar->_data;
		cout << "修改成功！" << endl;
	}
}

void StudentManager::removeStudent()
{
	cout << "请输入要删除的考生编号：" << endl;
	int id;
	cin >> id;
	LinkNode<Student>* pre = stuList.Locate(id - 1);
	if (!stuList.Remove(id)) {
		cout << "删除失败！" << endl;
	}
	else {
		cout << "删除成功！" << endl;
	}
}

void StudentManager::printStudent()
{
	LinkNode<Student>* cur = stuList.getHead()->_next;
	while (cur) {
		cout << cur->_data << endl;
		cur = cur->_next;
	}
}

void StudentManager::updateStudentId()
{
	LinkNode<Student>* iter = stuList.getHead()->_next;
	int id = 1;
	while (iter != NULL) {
		iter->_data.setId(id++);
		iter = iter->_next;
	}
}

void StudentManager::run()
{
	cout << "首先请建立考生信息系统！" << endl;
	insertStudent();
	updateStudentId();
	int opeNum;
	do {
		PrintInterFace();
		cin >> opeNum;
		if (opeNum == 1) {
			insertStudent();
		}
		else if (opeNum == 2) {
			pollStudent();
		}
		else if (opeNum == 3) {
			modifyStudent();
		}
		else if (opeNum == 4) {
			removeStudent();
		}
		else if (opeNum == 5) {
			printStudent();
		}
		updateStudentId();
	} while (opeNum != 0);
}