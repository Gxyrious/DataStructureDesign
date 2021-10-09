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

void StudentManager::createSystem()
{
	cout << "首先请建立考生信息系统！" << endl
		<< "请输入要添加的考生个数：" << endl;
	int n;
	cin >> n;
	while (n <= 0) {
		cout << "输入有误，请重新输入！" << endl;
		cin >> n;
	}
	cout << "请依次输入各考生的考号、姓名、性别、年龄、报考类别：" << endl;

	//使用匿名函数来定义，用来判断是否考生考号重复
	auto ifRepeat = [&](Student& stu)->bool {
		for (LinkNode<Student>* iter = stuList.getHead()->_next; iter; iter = iter->_next) {
			if (iter->_data.getNumber() == stu.getNumber()) { return false; }
		}
		return true; };

	for (int i = 1; i <= n; i++) {
		Student stu;
		cin >> stu;
		while (!ifRepeat(stu)) {
			//保证考号重复的时候不异常退出，能够紧接着继续添加考生
			cout << "考生考号有重复，请重新输入该考生信息！" << endl;
			cin >> stu;
		}
		if (!stuList.PushBack(stu)) {
			cout << "第" << i << "个考生插入失败！" << endl;
			//在创建系统的时候，即使添加失败，也继续添加
		}
	}
	//更新考生id
	updateStudentId();
	cout << "建立成功！" << endl;
}

void StudentManager::insertStudent()
{
	cout << "请输入要添加的考生个数" << endl;
	int n;
	cin >> n;
	if (n <= 0) {
		cout << "输入有误，异常退出！" << endl;
	}
	else {
		cout << "请依次输入各考生的考号、姓名、性别、年龄、报考类别：" << endl;
		for (int i = 1; i <= n; i++) {
			Student stu;
			cin >> stu;
			//若考生考号重复，直接退出当前操作步骤
			//前面已经输入的考生信息保留
			for (LinkNode<Student>* iter = stuList.getHead()->_next; iter; iter = iter->_next) {
				if (iter->_data.getNumber() == stu.getNumber()) {
					cout << "考生考号有重复，异常退出！" << endl;
					return;
				}
			}
			//输出是否成功
			if (!stuList.PushBack(stu)) {
				cout << "第" << i << "个考生插入失败！" << endl;
			}
			else {
				cout << "第" << i << "个考生插入成功！" << endl;
			}
		}
	}
}

void StudentManager::pollStudent()
{
	cout << "请输入需要查询的考生编号：" << endl;
	int id;
	cin >> id;
	LinkNode<Student>* tar = stuList.Locate(id);
	if (!id || !tar) {
		cout << "不存在这名考生，异常退出！" << endl;
	}
	else {
		cout << "查询成功，该学生的信息：" << endl << tar->_data << endl;
	}
}

void StudentManager::modifyStudent()
{
	cout << "请输入要修改的考生编号：" << endl;
	int id;
	cin >> id;
	//先使用id定位考生
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
	//先使用id定位考生
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
	//若附加头结点指向NULL，则说明考生信息系统为空
	if (!cur) {
		cout << "考生人数为零！" << endl;
	}
	else {
		while (cur) {
			cout << cur->_data << endl;
			cur = cur->_next;
		}
	}
}

void StudentManager::updateStudentId()
{
	//遍历一遍链表，按序修改编号
	LinkNode<Student>* iter = stuList.getHead()->_next;
	int id = 1;
	while (iter != NULL) {
		iter->_data.setId(id++);
		iter = iter->_next;
	}
}

void StudentManager::run()
{
	createSystem();
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
		else if (opeNum == 0) {
			break;
		}
		else {
			cout << "操作码不存在，请重新输入！" << endl;
			continue;
		}
		updateStudentId();
	} while (true);
}