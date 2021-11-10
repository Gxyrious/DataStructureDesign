#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "BinarySearchTree.hpp"

using namespace std;

BST<int> binary_search_tree;

void PrintInterface() {
	cout << "********           Binary Search Tree           ********\n"
		<< "========================================================\n"
		<< "**              1 --- insert elements                 **\n"
		<< "**              2 --- insert random numbers           **\n"
		<< "**              3 --- delete elements                 **\n"
		<< "**              4 --- search elements                 **\n"
		<< "**              5 --- print tree sequently            **\n"
		<< "**              6 --- exit program                    **\n"
		<< "please input operating number......\n";
}

int main() {
	srand((unsigned)time(NULL));
	BSTNode<int>* nonconst_root = binary_search_tree.getRoot();
	int operate_number;
	while (true) {
		PrintInterface();
		cin >> operate_number;
		if (operate_number == 1) {
			cout << "please input the number of elements to insert......\n";
			//输入插入元素个数
			int n;
			while (true) {
				cin >> n;
				if (n <= 0) { cout << "input number is illegal, please reinput again!\n"; }
				else { break; }
			}
			//插入元素
			bool ifSuccess = true;
			for (int i = 0; i < n; i++) {
				int insert_number;
				cin >> insert_number;
				if (!binary_search_tree.Insert(insert_number, nonconst_root)) {
					cout << "number" << insert_number << "failed to insert!\n";
					ifSuccess = false;
					break;
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
				if (!binary_search_tree.Insert(rand(), nonconst_root)) {
					cout << "failed to insert!\n";
					ifSuccess = false;
					break;
				}
			}
			if (ifSuccess) {
				cout << "insert successfully!\n";
			}
		}
		else if (operate_number == 3) {
			cout << "please input the target element to delete......\n";
			int target;
			cin >> target;
			if (binary_search_tree.Remove(target, nonconst_root)) { cout << "remove successfully!\n"; }
			else { cout << "failed to remove!\n"; }
		}
		else if (operate_number == 4) {
			cout << "please input the target element to search......\n";
			int target;
			cin >> target;
			if (binary_search_tree.Search(target, nonconst_root)) { cout << "target exists!\n"; }
			else { cout << "target not exists!\n"; }
		}
		else if (operate_number == 5) {
			binary_search_tree.inOrder(nonconst_root, [](BSTNode<int>* p) -> void {
				cout << p->_data << " ";
				});
			cout << "\n";
		}
		else if (operate_number == 6) {
			cout << "pragram successfully exit\n!";
			break;
		}
		else { cout << "operating number is illegal, please reinput again!\n"; }
	}
	system("pause");
	return 0;
}