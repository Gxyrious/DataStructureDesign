#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "BinarySearchTree.hpp"

using namespace std;

BST<int> binary_search_tree;

//打印菜单
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
	//随机数种子
	srand((unsigned)time(NULL));
	int operate_number;//操作数
	PrintInterface();
	while (true) {
		cin >> operate_number;
		if (operate_number == 1) {
			cout << "please input the number of elements to insert......\n";
			//输入插入元素个数
			int n;
			//输入判断
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
				if (!binary_search_tree.Insert(insert_number)) {
					//元素已经存在，则不进行插入
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
				//存在元素没有被插入
				cout << "insert successfully!\n";
			}
		}
		else if (operate_number == 3) {
			cout << "please input the target element to delete......\n";
			int target;
			cin >> target;
			//被删元素不存在
			if (binary_search_tree.Remove(target)) { cout << "remove successfully!\n"; }
			else { cout << "failed to remove!\n"; }
		}
		else if (operate_number == 4) {
			cout << "please input the target element to search......\n";
			int target;
			cin >> target;
			//寻找是否存在该元素
			if (binary_search_tree.Search(target)) { cout << "target exists!\n"; }
			else { cout << "target not exists!\n"; }
		}
		else if (operate_number == 5) {
			//中序遍历打印二叉搜索树
			binary_search_tree.inOrder([](BSTNode<int>* p) -> void {
				cout << p->_data << " ";
				});
			cout << "\n";
		}
		else if (operate_number == 6) {
			//清空二叉树
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