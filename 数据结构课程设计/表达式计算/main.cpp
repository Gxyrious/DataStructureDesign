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
	Stack<char>stack_opt, stack_num;
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
			stack_num.Push(infix_exp[i++]);
			//cout << *citer;
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
				char leftchild, rightchild;
				stack_num.Pop(rightchild);
				stack_num.Pop(leftchild);
				if (leftchild == '$'&&rightchild!='$') {
					//����������#�������Ϸ�����
					tree_exp.UpRightGrow(opt, rightchild);
					stack_num.Push('$');
				}
				else if (rightchild == '$'&&leftchild!='$') {
					//����Ҷ�����#�������Ϸ�����
					tree_exp.UpLeftGrow(opt, leftchild);
					stack_num.Push('$');
				}
				/*else if (leftchild == '$' && rightchild == '$') {
					
				}*/
				else {
					//���Ǵ����֣���������������#����������Ľ������
					tree_exp.setRoot(opt);
					tree_exp.InsertLeftChild(tree_exp.getRoot(), leftchild);
					tree_exp.InsertRightChild(tree_exp.getRoot(), rightchild);
					stack_num.Push('$');
				}
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
		cout << "z";
	}
	//������ֱ��ʽ
	cout << stack_opt.empty() << endl;
	cout << "ǰ׺���ʽ��";
	tree_exp.preOrder(tree_exp.getRoot(), print);
	cout << endl << "��׺���ʽ��";
	tree_exp.inOrder(tree_exp.getRoot(), print);
	cout << endl << "��׺���ʽ��";
	tree_exp.postOrder(tree_exp.getRoot(), print);

	return 0;
}