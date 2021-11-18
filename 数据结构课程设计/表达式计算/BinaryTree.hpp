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
	//这直接取就行了
	//BinaryTreeNode<T>* getLeftChild(BinaryTreeNode<T>* tar) {
	//	return (tar == NULL) ? NULL : tar->_leftChild;
	//}
	//BinaryTreeNode<T>* getRightChild(BinaryTreeNode<T>* tar) {
	//	return (tar == NULL) ? NULL : tar->_rightChild;
	//}
	/*对于目标结点tar，添加其左子女或右子女*/
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
	/*传入parent和child，不妨设为左子女，则原树的根结点为右子女，向上生长*/
	bool UpLeftGrow(T& data_parent, T& data_leftchild) {
		BinaryTreeNode<T>* leftchild = new BinaryTreeNode<T>(data_leftchild);
		BinaryTreeNode<T>* parent = new BinaryTreeNode<T>(data_parent);
		if (leftchild == NULL || parent == NULL) { return false; }
		parent->_leftChild = leftchild;//设置父结点的左孩子
		parent->_rightChild = _root;//设置父节点的右孩子为根结点
		this->_root = parent;//设置根结点
		return true;
	}
	bool UpRightGrow(T& data_parent, T& data_rightchild) {
		BinaryTreeNode<T>* rightchild = new BinaryTreeNode<T>(data_rightchild);
		BinaryTreeNode<T>* parent = new BinaryTreeNode<T>(data_parent);
		if (rightchild == NULL || parent == NULL) { return false; }
		parent->_rightChild = rightchild;//设置父结点的右孩子
		parent->_leftChild = _root;//设置父结点的左孩子为根结点
		this->_root = parent;//设置根结点
		return true;
	}
	/*递归删除结点*/
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