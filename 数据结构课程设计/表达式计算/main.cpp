#include<iostream>
#include<string>
#include"LinkedStack.hpp"
#include"BinaryTree.hpp"

using namespace std;

/*遍历时的visit函数，即输出结点值*/
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
void inputWrong() {
	cout << "表达式输入错误！\n";
	system("pause");
	exit(0);
}

bool ifNumberOrLetter(char c) {
	if ('0' <= c && c <= '9' || 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z') { return true; }
	return false;
}

bool ifOperator(char c) {
	if (c == '+' || c == '-' || c == '*' || c == '/') { return true; }
	return false;
}

int main() {
	Stack<char>stack_opt;
	Stack<BinaryTreeNode<char>* >stack_numNode;
	BinaryTree<char>tree_exp;
	//输入的中缀表达式
	string infix_exp;
	char opt, cnew;
	cout << "请输入表达式（只能包含+-*/()和字母）：" << endl;
	while (true) {
		cin >> infix_exp;
		bool b = 1;//表达式是否合法
		int top = 0;
		for (int i = 0; i < infix_exp.length(); i++) {
			if (infix_exp[i] == '(') { top++; }//若为左括号，括号栈指针++
			else if (infix_exp[i] == ')') { top--; }//若为右括号，括号栈指针--
			else if (!ifOperator(infix_exp[i]) && !ifNumberOrLetter(infix_exp[i])) {
				cout << "表达式输入有误，请重新输入\n";
				b = 0;//表达式不合法
				break;
			}
			//括号不匹配
			if (top < 0) { cout << "表达式输入有误，请重新输入\n"; b = 0; break; }
		}
		//判断表达式是否合法
		if (b && (top == 0)) { break; }
	}
	infix_exp = '#' + infix_exp + '#';
	int length = static_cast<int>(infix_exp.length());
	int i = 0;
	while (i != length - 1 || !stack_opt.empty()) {
		if (ifNumberOrLetter(infix_exp[i])) {
			//如果是操作数，直接存入数字栈
			stack_numNode.Push(new BinaryTreeNode<char>(infix_exp[i]));
			if (ifNumberOrLetter(infix_exp[i - 1])) {
				inputWrong();
			}
			i++;
		}
		else {
			//表达式合法性判断
			if (infix_exp[i] == '#') {}
			else if (ifOperator(infix_exp[i])) {
				if (ifOperator(infix_exp[i - 1]) || i == 1) {
					//运算符连续出现或运算符出现在首位
					inputWrong();
				}
			}
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
	cout << "前缀表达式：";
	tree_exp.preOrder(tree_exp.getRoot(), print);
	cout << "\n中缀表达式：";
	tree_exp.inOrder(tree_exp.getRoot(), print);
	cout << "\n后缀表达式：";
	tree_exp.postOrder(tree_exp.getRoot(), print);
	cout << "\n";
	system("pause");
	return 0;
}