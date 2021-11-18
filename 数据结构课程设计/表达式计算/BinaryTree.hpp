#pragma once
#include<iostream>
using namespace std;

template<class T>
class BinaryTreeNode {
public:
	BinaryTreeNode() {
		_data = T();
		_leftChild = NULL;
		_rightChild = NULL;
	}
	BinaryTreeNode(T& data) {
		BinaryTreeNode();
		_data = data;
	}
	T _data;
	BinaryTreeNode<T>* _leftChild, * _rightChild;
};

template<class T>
class BinaryTree {
public:
	BinaryTree() { _root = NULL; }
	BinaryTree(T& rootdata) { _root = new BinaryTreeNode<T>(rootdata); }
	~BinaryTree() {Remove(_root);}
	bool setRoot(T& data) {
		if (_root != NULL) {
			_root->_data = data;
			return true;
		}
		else {
			_root = new BinaryTreeNode<T>(data);
			return (_root != NULL);
		}
	}
	bool IfEmpty() { return _root == NULL; }
	BinaryTreeNode<T>* getRoot()const { return _root; }
	//��ֱ��ȡ������
	//BinaryTreeNode<T>* getLeftChild(BinaryTreeNode<T>* tar) {
	//	return (tar == NULL) ? NULL : tar->_leftChild;
	//}
	//BinaryTreeNode<T>* getRightChild(BinaryTreeNode<T>* tar) {
	//	return (tar == NULL) ? NULL : tar->_rightChild;
	//}
	/*����Ŀ����tar�����������Ů������Ů*/
	bool InsertLeftChild(BinaryTreeNode<T>* tar, T& data) {
		if (tar == NULL)return false;
		BinaryTreeNode<T>* leftchild = new BinaryTreeNode<T>(data);
		tar->_leftChild = leftchild;
		return true;
	}
	bool InsertRightChild(BinaryTreeNode<T>* tar, T& data) {
		if (tar == NULL)return false;
		BinaryTreeNode<T>* rightchild = new BinaryTreeNode<T>(data);
		tar->_rightChild = rightchild;
		return true;
	}
	/*����parent��child��������Ϊ����Ů����ԭ���ĸ����Ϊ����Ů����������*/
	bool UpLeftGrow(T& data_parent, T& data_leftchild) {
		BinaryTreeNode<T>* leftchild = new BinaryTreeNode<T>(data_leftchild);
		BinaryTreeNode<T>* parent = new BinaryTreeNode<T>(data_parent);
		if (leftchild == NULL || parent == NULL) { return false; }
		parent->_leftChild = leftchild;//���ø���������
		parent->_rightChild = _root;//���ø��ڵ���Һ���Ϊ�����
		this->_root = parent;//���ø����
		return true;
	}
	bool UpRightGrow(T& data_parent, T& data_rightchild) {
		BinaryTreeNode<T>* rightchild = new BinaryTreeNode<T>(data_rightchild);
		BinaryTreeNode<T>* parent = new BinaryTreeNode<T>(data_parent);
		if (rightchild == NULL || parent == NULL) { return false; }
		parent->_rightChild = rightchild;//���ø������Һ���
		parent->_leftChild = _root;//���ø���������Ϊ�����
		this->_root = parent;//���ø����
		return true;
	}
	/*�ݹ�ɾ�����*/
	void Remove(BinaryTreeNode<T>* tar) {
		if (!tar) {
			Remove(tar->_leftChild);//nihao
			Remove(tar->_rightChild);
			delete tar;
		}
	}
	void preOrder(BinaryTreeNode<T>* tar, void(*visit)(BinaryTreeNode<T>* p)) {
		if (tar) {
			visit(tar);
			preOrder(tar->_leftChild, visit);
			preOrder(tar->_rightChild, visit);
		}
	}
	void inOrder(BinaryTreeNode<T>* tar, void(*visit)(BinaryTreeNode<T>* p)) {
		if (tar) {
			inOrder(tar->_leftChild, visit);
			visit(tar);
			inOrder(tar->_rightChild, visit);
		}
	}
	void postOrder(BinaryTreeNode<T>* tar, void(*visit)(BinaryTreeNode<T>* p)) {
		if (tar) {
			postOrder(tar->_leftChild, visit);
			postOrder(tar->_rightChild, visit);
			visit(tar);
		}
	}
private:
	BinaryTreeNode<T>* _root;
};