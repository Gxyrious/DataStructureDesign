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
	Stack<char>stack_opt;
	Stack<BinaryTreeNode<char>* >stack_numNode;
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
			//stack_num.Push(infix_exp[i++]);
			stack_numNode.Push(new BinaryTreeNode<char>(infix_exp[i++]));
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
				BinaryTreeNode<char>* leftchild = NULL, * rightchild = NULL;
				stack_numNode.Pop(rightchild);
				stack_numNode.Pop(leftchild);
				tree_exp.UpGrow(opt, leftchild, rightchild);
				stack_numNode.Push(tree_exp.getRoot());
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
	}
	//输出各种表达式
	cout << "\n前缀表达式：";
	tree_exp.preOrder(tree_exp.getRoot(), print);
	cout << "\n中缀表达式：";
	tree_exp.inOrder(tree_exp.getRoot(), print);
	cout << "\n后缀表达式：";
	tree_exp.postOrder(tree_exp.getRoot(), print);

	return 0;
}