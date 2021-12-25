#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "BinarySearchTree.hpp"

using namespace std;

BST<int> binary_search_tree;

//��ӡ�˵�
void PrintInterface() {
	cout << "********           Binary Search Tree           ********\n"
		<< "========================================================\n"
		<< "**              1 --- insert elements                 **\n"
		<< "**              2 --- insert random numbers           **\n"
		<< "**              3 --- delete elements                 **\n"
		<< "**              4 --- search elements                 **\n"
		<< "**              5 --- print tree sequently            **\n"
		<< "**              6 --- clear the tree                  **\n"
		<< "**              7 --- exit program                    **\n"
		<< "please input operating number......\n";
}

int main() {
	//���������
	srand((unsigned)time(NULL));
	int operate_number;//������
	PrintInterface();
	while (true) {
		cin >> operate_number;
		if (operate_number == 1) {
			cout << "please input the number of elements to insert......\n";
			//�������Ԫ�ظ���
			int n;
			//�����ж�
			while (true) {
				cin >> n;
				if (n <= 0) { cout << "input number is illegal, please reinput again!\n"; }
				else { break; }
			}
			//����Ԫ��
			bool ifSuccess = true;
			for (int i = 0; i < n; i++) {
				int insert_number;
				cin >> insert_number;
				if (!binary_search_tree.Insert(insert_number)) {
					//Ԫ���Ѿ����ڣ��򲻽��в���
					cout << "number" << insert_number << "failed to insert!\n";
					ifSuccess = false;
				}
			}
			if (ifSuccess) { cout << "insert successfully!\n"; }
		}
		else if (operate_number == 2) {
			cout << "please input the number of random elements to insert......\n";
			int n;
			while (true) {
				cin >> n;
				if (n <= 0) { cout << "input number is illegal, please reinput again!\n"; }
				else { break; }
			}
			bool ifSuccess = true;
			for (int i = 0; i < n; i++) {
				if (!binary_search_tree.Insert(rand())) {
					cout << "Number "<<i<<" failed to insert!\n";
					ifSuccess = false;
				}
			}
			if (ifSuccess) {
				//����Ԫ��û�б�����
				cout << "insert successfully!\n";
			}
		}
		else if (operate_number == 3) {
			cout << "please input the target element to delete......\n";
			int target;
			cin >> target;
			//��ɾԪ�ز�����
			if (binary_search_tree.Remove(target)) { cout << "remove successfully!\n"; }
			else { cout << "failed to remove!\n"; }
		}
		else if (operate_number == 4) {
			cout << "please input the target element to search......\n";
			int target;
			cin >> target;
			//Ѱ���Ƿ���ڸ�Ԫ��
			if (binary_search_tree.Search(target)) { cout << "target exists!\n"; }
			else { cout << "target not exists!\n"; }
		}
		else if (operate_number == 5) {
			//���������ӡ����������
			binary_search_tree.inOrder([](BSTNode<int>* p) -> void {
				cout << p->_data << " ";
				});
			cout << "\n";
		}
		else if (operate_number == 6) {
			//��ն�����
			binary_search_tree.Clear();
			cout << "clear successfully!\n";
		}
		else if (operate_number == 7) {
			cout << "program successfully exit!\n";
			break;
		}
		else { cout << "operating number is illegal, please reinput again!\n"; }
	}
	system("pause");
	return 0;
}