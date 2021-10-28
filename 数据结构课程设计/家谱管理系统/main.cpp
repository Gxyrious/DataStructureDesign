#include<iostream>
#include<string>
#include"Tree.hpp"
using namespace std;
Tree<string> family_tree;
int main() {
	char c = char();
	cout << "首先建立一个家谱！" << endl;
	cout << "请输入祖先的姓名：";
	string ancestor;
	cin >> ancestor;
	family_tree.setRoot(ancestor);
	cout << "此家谱的祖先是：" << family_tree.getRoot()->_data << endl;
	while (true)
	{
		cout << "请选择要执行的操作：\n"
			<< "A：组建新的家庭（需包含新的父或母以及它们的若干子女）\n"
			<< "B：添加子女（需给定添加子女的父或母）\n"
			<< "C：解散家庭（删除它及其所有子孙）\n"
			<< "D：更改姓名（需给定原来的姓名）"
			<< "P1：前序遍历打印家族成员\n"
			<< "P2：中序遍历打印家族成员\n"
			<< "P3：后序遍历打印家族成员\n"
			<< "E:退出程序\n";

		cin >> c;
		if (c == 'A') {
			cout << "请输入要建立家庭的人的姓名：";
			string parent;
			cin >> parent;
			TreeNode<string>* tar = family_tree.search(family_tree.getRoot(), parent);
			if (tar == NULL) {
				cout << "查无此人！" << endl;
				continue;
			}
			if (tar->_firstson != NULL) {
				cout << "此人已有子女，请选择B操作代码进行子女添加，而非建立家庭！" << endl;
				continue;
			}
			cout << "请输入" << parent << "的儿女人数：";
			int n;
			cin >> n;
			if (n <= 0) {
				cout << "个数非法！" << endl;
				continue;
			}
			cout << "请依次输入" << parent << "的" << n << "个儿女姓名：" << endl;
			TreeNode<string>* insert_data = new TreeNode<string>;
			for (int i = 0; i < n - 1; i++) {
				TreeNode<string>* temp = new TreeNode<string>;
				temp->_brother = insert_data;
				insert_data = temp;
			}
			//申请了n块内存
			for (TreeNode<string>* iter = insert_data; iter != NULL; iter = iter->_brother) {
				cin >> iter->_data;
			}
			if (family_tree.Insert(tar, insert_data)) {
				cout << "建立成功！" << endl;
			}
			else {
				cout << "未知原因，建立失败！" << endl;
			}
			//测试
			//for (TreeNode<string>* iter = insert_data; iter != NULL; iter = iter->_brother) {
			//	cout << iter->_data << endl;
			//}

		}
		else if (c == 'B') {//插入某人的n个子女
			cout << "请输入要添加儿子（或女儿）的人的姓名：";
			string parent;
			cin >> parent;
			TreeNode<string>* tar = family_tree.search(family_tree.getRoot(), parent);
			if (tar == NULL) {
				cout << "查无此人！" << endl;
				continue;
			}
			cout << "请输入要添加的" << parent << "的儿女人数：";
			int n;
			cin >> n;
			if (n <= 0) {
				cout << "个数非法！" << endl;
				continue;
			}
			cout << "请依次输入" << parent << "的" << n << "个儿女姓名：" << endl;
			TreeNode<string>* insert_data = new TreeNode<string>;
			for (int i = 0; i < n - 1; i++) {
				TreeNode<string>* temp = new TreeNode<string>;
				temp->_brother = insert_data;
				insert_data = temp;
			}
			//申请了n块内存
			for (TreeNode<string>* iter = insert_data; iter != NULL; iter = iter->_brother) {
				cin >> iter->_data;
			}
			if (family_tree.Insert(tar, insert_data)) {
				cout << "添加成功" << endl;
			}
			else {
				cout << "未知原因，添加失败！" << endl;
			}
		}
		else if (c == 'C') {
			cout << "请输入要解散家庭的人的姓名：";
			string parent;
			cin >> parent;
			TreeNode<string>* tar = family_tree.search(family_tree.getRoot(), parent);
			if (tar == family_tree.getRoot()) {
				cout << "无法删除祖先！" << endl;
				continue;
			}
			if (tar != family_tree.getRoot()) {
				TreeNode<string>* par = tar->_parent;
				if (par->_firstson == tar) {
					par->_firstson = tar->_brother;
				}
				else {
					par = par->_firstson;
					while (par->_brother != tar)par = par->_brother;
					par->_brother = tar->_brother;
				}
			}
			if (family_tree.Remove(tar)) {
				cout << "解散成功！" << endl;
			}
			else {
				cout << "未知原因，解散失败！" << endl;
			}
		}
		else if (c == 'P') {
			family_tree.PreOrder(family_tree.getRoot());
			cout << endl;
		}
		else if (c == 'E') {
			cout << "退出！" << endl;
			break;
		}
		else {
			cout << "请输入正确的操作代码" << endl;
		}
	}

	//测试插入树
	family_tree.PreOrder(family_tree.getRoot());
	return 0;
}