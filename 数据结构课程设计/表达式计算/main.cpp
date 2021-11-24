#include<iostream>
#include<string>
#include"LinkedStack.hpp"
#include"BinaryTree.hpp"

using namespace std;

template<class T>
void print(BinaryTreeNode<T>* p) {
	cout << p->_data;
}
/*ջ�����ȼ�����*/
int isp(char c) {
	if (c == '(')return 1;
	else if (c == '*' || c == '/')return 5;
	else if (c == '+' || c == '-')return 3;
	else if (c == ')')return 6;
	else if (c == '#')return 0;
	else { return -1; }
}
/*ջ�����ȼ�����*/
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
	cout << "��������ʽ��" << endl;
	cin >> infix_exp;
	infix_exp = '#' + infix_exp + '#';
	int length = static_cast<int>(infix_exp.length());
	//	string::const_iterator citer = infix_exp.cbegin();
	int i = 0;
	while (i != length - 1 || !stack_opt.empty()) {
		if ('0' <= infix_exp[i] && '9' >= infix_exp[i]) {
			//����ǲ�������ֱ�Ӵ�������ջ
			//stack_num.Push(infix_exp[i++]);
			stack_numNode.Push(new BinaryTreeNode<char>(infix_exp[i++]));
		}
		else {
			//����ǲ��������ȿ�������ջ��Ԫ�أ����ж����ȼ�
			stack_opt.getTop(cnew);
			if (isp(cnew) < icp(infix_exp[i])) {
				//���ջ��Ԫ�ص����ȼ��ͣ��򽫶�����Ԫ��ֱ����ջ
				stack_opt.Push(infix_exp[i++]);
			}
			else if (isp(cnew) > icp(infix_exp[i])) {
				//���ջ��Ԫ�ص����ȼ��ߣ������ջ
				stack_opt.Pop(opt);
				//��optΪ���㣬stack_num��������Ϊ���Ҷ��ӽ���
				//#��ʾ��һ������Ľ������ȡ��������Ϊ#�Ļ���˵��Ҫ����
				BinaryTreeNode<char>* leftchild = NULL, * rightchild = NULL;
				stack_numNode.Pop(rightchild);
				stack_numNode.Pop(leftchild);
				tree_exp.UpGrow(opt, leftchild, rightchild);
				stack_numNode.Push(tree_exp.getRoot());
			}
			else {
				//����������ȼ���ͬ������ջ�������
				//���ջ��ʱ"("�����ȡ��һ���ַ�
				stack_opt.Pop(opt);
				if (opt == '(') {
					i++;
				}
			}
		}
	}
	//������ֱ��ʽ
	cout << "\nǰ׺���ʽ��";
	tree_exp.preOrder(tree_exp.getRoot(), print);
	cout << "\n��׺���ʽ��";
	tree_exp.inOrder(tree_exp.getRoot(), print);
	cout << "\n��׺���ʽ��";
	tree_exp.postOrder(tree_exp.getRoot(), print);

	return 0;
}