#include<iostream>
#include<string>
#include"LinkedStack.hpp"
#include"BinaryTree.hpp"

using namespace std;

template<class T>
void print(BinaryTreeNode<T>* p) {
	cout << p->_data;
}
/*栈内优先级函数*/
int isp(char c) {
	if (c == '(')return 1;
	else if (c == '*' || c == '/')return 5;
	else if (c == '+' || c == '-')return 3;
	else if (c == ')')return 6;
	else if (c == '#')return 0;
	else { return -1; }
}
/*栈外优先级函数*/
int icp(char c) {
	if (c == '(')return 6;
	else if (c == '*' || c == '/')return 4;
	else if (c == '+' || c == '-')return 2;
	else if (c == ')')return 1;
	else if (c == '#')return 0;
	else { return -1; }
}
int main() {
	Stack<char>stack_opt, stack_num;
	BinaryTree<char>tree_exp;
	string infix_exp;
	char opt, cnew;
	cout << "请输入表达式：" << endl;
	cin >> infix_exp;
	infix_exp = '#' + infix_exp + '#';
	int length = static_cast<int>(infix_exp.length());
	//	string::const_iterator citer = infix_exp.cbegin();
	int i = 0;
	while (i != length - 1 || !stack_opt.empty()) {
		if ('0' <= infix_exp[i] && '9' >= infix_exp[i]) {
			//如果是操作数，直接存入数字栈
			stack_num.Push(infix_exp[i++]);
			//cout << *citer;
		}
		else {
			//如果是操作符，先看操作符栈顶元素，并判断优先级
			stack_opt.getTop(cnew);
			if (isp(cnew) < icp(infix_exp[i])) {
				//如果栈顶元素的优先级低，则将读到的元素直接入栈
				stack_opt.Push(infix_exp[i++]);
			}
			else if (isp(cnew) > icp(infix_exp[i])) {
				//如果栈顶元素的优先级高，则将其出栈
				stack_opt.Pop(opt);
				//以opt为顶点，stack_num外侧的两个为左右儿子建树
				//#表示上一次运算的结果，若取出来的数为#的话，说明要长树
				char leftchild, rightchild;
				stack_num.Pop(rightchild);
				stack_num.Pop(leftchild);
				if (leftchild == '$'&&rightchild!='$') {
					//如果左儿子是#，向右上方长树
					tree_exp.UpRightGrow(opt, rightchild);
					stack_num.Push('$');
				}
				else if (rightchild == '$'&&leftchild!='$') {
					//如果右儿子是#，向左上方长树
					tree_exp.UpLeftGrow(opt, leftchild);
					stack_num.Push('$');
				}
				/*else if (leftchild == '$' && rightchild == '$') {
					
				}*/
				else {
					//都是纯数字，构建子树，并用#代表本次运算的结果子树
					tree_exp.setRoot(opt);
					tree_exp.InsertLeftChild(tree_exp.getRoot(), leftchild);
					tree_exp.InsertRightChild(tree_exp.getRoot(), rightchild);
					stack_num.Push('$');
				}
			}
			else {
				//如果两者优先级相同，则退栈但不输出
				//如果栈顶时"("，则读取下一个字符
				stack_opt.Pop(opt);
				if (opt == '(') {
					i++;
				}
			}
		}
		cout << "z";
	}
	//输出各种表达式
	cout << stack_opt.empty() << endl;
	cout << "前缀表达式：";
	tree_exp.preOrder(tree_exp.getRoot(), print);
	cout << endl << "中缀表达式：";
	tree_exp.inOrder(tree_exp.getRoot(), print);
	cout << endl << "后缀表达式：";
	tree_exp.postOrder(tree_exp.getRoot(), print);

	return 0;
}