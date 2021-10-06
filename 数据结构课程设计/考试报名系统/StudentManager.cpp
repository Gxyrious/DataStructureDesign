#include "StudentManager.h"

void StudentManager::PrintInterFace()
{
	cout << "----------------------" << endl
		<< "|����������������£� |" << endl
		<< "|0�˳�       1���    |" << endl
		<< "|2��ѯ       3�޸�    |" << endl
		<< "|4ɾ��       5��ӡ    |" << endl
		<< "-----------------------" << endl;
}

void StudentManager::insertStudent()
{
	cout << "������Ҫ��ӵĿ�������" << endl;
	int n;
	cin >> n;
	if (n <= 0) {
		cout << "��������" << endl;
	}
	else {
		cout << "����������������Ŀ��š��������Ա�����" << endl;
		for (int i = 1; i <= n; i++) {
			Student stu;
			cin >> stu;
			if (!stuList.push_back(stu)) {
				cout << "��" << i << "����������ʧ�ܣ�" << endl;
				return;
			}
		}
		cout << "����ɹ���" << endl;
	}
}

void StudentManager::pollStudent()
{
	cout << "��������Ҫ��ѯ�Ŀ�����ţ�" << endl;
	int id;
	cin >> id;
	LinkNode<Student>* tar = stuList.Locate(id);
	if (!id || !tar) {
		cout << "����������������" << endl;
	}
	else {
		cout << "��ѯ�ɹ���" << endl << tar->_data << endl;
	}
}

void StudentManager::modifyStudent()
{
	cout << "������Ҫ�޸ĵĿ�����ţ�" << endl;
	int id;
	cin >> id;
	LinkNode<Student>* tar = stuList.Locate(id);
	if (!id || !tar) {
		cout << "����������������" << endl;
	}
	else {
		cout << "�ÿ���Ŀǰ��ϢΪ��" << tar->_data << endl
			<< "�������޸ĺ�Ŀ��š��������Ա����䣺" << endl;
		cin >> tar->_data;
		cout << "�޸ĳɹ���" << endl;
	}
}

void StudentManager::removeStudent()
{
	cout << "������Ҫɾ���Ŀ������ţ�" << endl;
	int id;
	cin >> id;
	LinkNode<Student>* pre = stuList.Locate(id - 1);
	if (!pre || !(pre->_next)) {
		cout << "ɾ��ʧ�ܣ�����������������" << endl;
	}
	else {
		LinkNode<Student>* tar = pre->_next;
		pre->_next = tar->_next;
		delete tar;
		cout << "ɾ���ɹ���" << endl;
	}
}

void StudentManager::printStudent()
{
	stuList.PrintList();
	LinkNode<Student>* cur = stuList.getHead();
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
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	insertStudent();
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