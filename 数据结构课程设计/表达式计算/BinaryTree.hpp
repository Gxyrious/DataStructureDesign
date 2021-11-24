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
	/*向上生长*/
	bool UpGrow(T& data_parent,BinaryTreeNode<T>*& leftchild,BinaryTreeNode<T>*& rightchild) {
		BinaryTreeNode<T>* parent = new BinaryTreeNode<T>(data_parent);
		if (parent == NULL) { return false; }
		parent->_leftChild = leftchild;
		parent->_rightChild = rightchild;
		this->_root = parent;
		return true;
	}
	/*递归删除结点*/
	void Remove(BinaryTreeNode<T>* tar) {
		if (tar != NULL) {
			Remove(tar->_leftChild);//nihao
			Remove(tar->_rightChild);
			delete tar;
		}
	}
	/*前序遍历*/
	void preOrder(BinaryTreeNode<T>* tar, void(*visit)(BinaryTreeNode<T>* p)) {
		if (tar != NULL) {
			visit(tar);
			preOrder(tar->_leftChild, visit);
			preOrder(tar->_rightChild, visit);
		}
	}
	/*中序遍历*/
	void inOrder(BinaryTreeNode<T>* tar, void(*visit)(BinaryTreeNode<T>* p)) {
		if (tar != NULL) {
			inOrder(tar->_leftChild, visit);
			visit(tar);
			inOrder(tar->_rightChild, visit);
		}
	}
	/*后序遍历*/
	void postOrder(BinaryTreeNode<T>* tar, void(*visit)(BinaryTreeNode<T>* p)) {
		if (tar != NULL) {
			postOrder(tar->_leftChild, visit);
			postOrder(tar->_rightChild, visit);
			visit(tar);
		}
	}
private:
	BinaryTreeNode<T>* _root;
};