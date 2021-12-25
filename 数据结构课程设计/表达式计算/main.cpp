#include<iostream>
#include<string>
#include"LinkedStack.hpp"
#include"BinaryTree.hpp"

using namespace std;

/*����ʱ��visit��������������ֵ*/
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
void inputWrong() {
	cout << "���ʽ�������\n";
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
	//�������׺���ʽ
	string infix_exp;
	char opt, cnew;
	cout << "��������ʽ��ֻ�ܰ���+-*/()����ĸ����" << endl;
	while (true) {
		cin >> infix_exp;
		bool b = 1;//���ʽ�Ƿ�Ϸ�
		int top = 0;
		for (int i = 0; i < infix_exp.length(); i++) {
			if (infix_exp[i] == '(') { top++; }//��Ϊ�����ţ�����ջָ��++
			else if (infix_exp[i] == ')') { top--; }//��Ϊ�����ţ�����ջָ��--
			else if (!ifOperator(infix_exp[i]) && !ifNumberOrLetter(infix_exp[i])) {
				cout << "���ʽ������������������\n";
				b = 0;//���ʽ���Ϸ�
				break;
			}
			//���Ų�ƥ��
			if (top < 0) { cout << "���ʽ������������������\n"; b = 0; break; }
		}
		//�жϱ��ʽ�Ƿ�Ϸ�
		if (b && (top == 0)) { break; }
	}
	infix_exp = '#' + infix_exp + '#';
	int length = static_cast<int>(infix_exp.length());
	int i = 0;
	while (i != length - 1 || !stack_opt.empty()) {
		if (ifNumberOrLetter(infix_exp[i])) {
			//����ǲ�������ֱ�Ӵ�������ջ
			stack_numNode.Push(new BinaryTreeNode<char>(infix_exp[i]));
			if (ifNumberOrLetter(infix_exp[i - 1])) {
				inputWrong();
			}
			i++;
		}
		else {
			//���ʽ�Ϸ����ж�
			if (infix_exp[i] == '#') {}
			else if (ifOperator(infix_exp[i])) {
				if (ifOperator(infix_exp[i - 1]) || i == 1) {
					//������������ֻ��������������λ
					inputWrong();
				}
			}
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
	cout << "ǰ׺���ʽ��";
	tree_exp.preOrder(tree_exp.getRoot(), print);
	cout << "\n��׺���ʽ��";
	tree_exp.inOrder(tree_exp.getRoot(), print);
	cout << "\n��׺���ʽ��";
	tree_exp.postOrder(tree_exp.getRoot(), print);
	cout << "\n";
	system("pause");
	return 0;
}