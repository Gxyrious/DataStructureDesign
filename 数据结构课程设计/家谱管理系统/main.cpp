#include<iostream>
#include<string>
#include"Tree.hpp"

using namespace std;

Tree<string> family_tree;

void PrintInterface() {
	cout << "��ѡ��Ҫִ�еĲ�����\n"
		<< "A���齨�µļ�ͥ��������µĸ���ĸ�Լ����ǵ�������Ů��\n"
		<< "B�������Ů������������Ů�ĸ���ĸ��\n"
		<< "C����ɢ��ͥ��ɾ���������������\n"
		<< "D�����������������ԭ����������"
		<< "P��ǰ�������ӡ�����Ա\n"
		<< "E���˳�����\n";
}

int main() {
	char c = char();
	cout << "���Ƚ���һ�����ף�" << endl;
	cout << "���������ȵ�������";
	string ancestor;
	cin >> ancestor;
	family_tree.setRoot(ancestor);
	cout << "�˼��׵������ǣ�" << family_tree.getRoot()->_data << endl;
	PrintInterface();
	while (true) {
		cin >> c;
		if (c == 'A') {
			cout << "������Ҫ������ͥ���˵�������";
			string parent;
			cin >> parent;
			TreeNode<string>* tar = family_tree.search(family_tree.getRoot(), parent);
			if (tar == NULL) {
				cout << "���޴��ˣ�" << endl;
				continue;
			}
			if (tar->_firstson != NULL) {
				cout << "����������Ů����ѡ��B�������������Ů��ӣ����ǽ�����ͥ��" << endl;
				continue;
			}
			cout << "������" << parent << "�Ķ�Ů������";
			int n;
			cin >> n;
			if (n <= 0) {
				cout << "�����Ƿ���" << endl;
				continue;
			}
			cout << "����������" << parent << "��" << n << "����Ů������" << endl;
			TreeNode<string>* insert_data = new TreeNode<string>;
			for (int i = 0; i < n - 1; i++) {
				TreeNode<string>* temp = new TreeNode<string>;
				temp->_brother = insert_data;
				insert_data = temp;
			}
			//������n���ڴ�
			for (TreeNode<string>* iter = insert_data; iter != NULL; iter = iter->_brother) {
				cin >> iter->_data;
			}
			if (family_tree.Insert(tar, insert_data)) {
				cout << "�����ɹ���" << endl;
			}
			else {
				cout << "δ֪ԭ�򣬽���ʧ�ܣ�" << endl;
			}
		}
		else if (c == 'B') {//����ĳ�˵�n����Ů
			cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
			string parent;
			cin >> parent;
			TreeNode<string>* tar = family_tree.search(family_tree.getRoot(), parent);
			if (tar == NULL) {
				cout << "���޴��ˣ�" << endl;
				continue;
			}
			cout << "������Ҫ��ӵ�" << parent << "�Ķ�Ů������";
			int n;
			cin >> n;
			if (n <= 0) {
				cout << "�����Ƿ���" << endl;
				continue;
			}
			cout << "����������" << parent << "��" << n << "����Ů������" << endl;
			TreeNode<string>* insert_data = new TreeNode<string>;
			for (int i = 0; i < n - 1; i++) {
				TreeNode<string>* temp = new TreeNode<string>;
				temp->_brother = insert_data;
				insert_data = temp;
			}
			//������n���ڴ�
			for (TreeNode<string>* iter = insert_data; iter != NULL; iter = iter->_brother) {
				cin >> iter->_data;
			}
			if (family_tree.Insert(tar, insert_data)) {
				cout << "��ӳɹ�" << endl;
			}
			else {
				cout << "δ֪ԭ�����ʧ�ܣ�" << endl;
			}
		}
		else if (c == 'C') {
			cout << "������Ҫ��ɢ��ͥ���˵�������";
			string parent;
			cin >> parent;
			TreeNode<string>* tar = family_tree.search(family_tree.getRoot(), parent);
			if (tar == family_tree.getRoot()) {
				cout << "�޷�ɾ�����ȣ�" << endl;
				continue;
			}
			else if (tar == NULL) {
				cout << "Ҫɾ���Ľ�㲻���ڣ�" << endl;
				continue;
			}
			else {
				TreeNode<string>* par = tar->_parent;
				if (par->_firstson == tar) {
					//Ҫɾ���Ľ����firstson����Ҫ���⴦������
					par->_firstson = tar->_brother;
				}
				else {
					par = par->_firstson;
					while (par->_brother != tar)par = par->_brother;
					par->_brother = tar->_brother;
				}
			}
			if (family_tree.Remove(tar)) {
				cout << "��ɢ�ɹ���" << endl;
			}
			else {
				cout << "δ֪ԭ�򣬽�ɢʧ�ܣ�" << endl;
			}
		}
		else if (c == 'D') {
			cout << "������Ҫ���ĵ��˵�������" << endl;
			string name;
			cin >> name;
			TreeNode<string>* tar = family_tree.search(family_tree.getRoot(), name);
			if (tar == NULL) {
				cout << "���˲��ڼ����У�" << endl;
				continue;
			}
			else {
				cout << "��������ĺ��������" << endl;
				cin >> tar->_data;
				cout << "�޸ĳɹ���" << endl;
			}
		}
		else if (c == 'P') {
			family_tree.PreOrder(family_tree.getRoot());
			cout << endl;
		}
		else if (c == 'E') {
			cout << "�˳���" << endl;
			break;
		}
		else {
			cout << "��������ȷ�Ĳ�������" << endl;
		}
	}
	return 0;
}