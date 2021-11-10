#pragma once
#include <iostream>
using namespace std;

template <class T>
class BSTNode {
public:
	T _data;
	BSTNode<T>* _left, * _right;
	BSTNode() { _left = NULL; _right = NULL; }
	BSTNode(const T data, BSTNode<T>* left = NULL, BSTNode<T>* right = NULL) : _data(data), _left(left), _right(right) {}
	~BSTNode() {}
};

template <class T>
class BST {
public:
	BSTNode<T>* _root;
	BSTNode<T>* getRoot()const { return _root; }
	BST() : _root(NULL) {}                        //构造一棵空树
	BST(const T x) { _root = new BSTNode<T>(x); } //构造根节点
	//二叉搜索树的搜索算法
	bool Search(const T x, BSTNode<T>* ptr) {
		if (ptr == NULL) { return false; }
		else if (x < ptr->_data) { return Search(x, ptr->_left); }
		else if (x > ptr->_data) { return Search(x, ptr->_right); }
		else { return true; }
	}
	// BSTNode<T> *Search(const T x, BSTNode<T> *ptr) {
	// 	if (ptr == NULL) { return NULL; }
	// 	else if (x < ptr->_data) { return Search(x, ptr->_left); }
	// 	else if (x > ptr->_data) { return Search(x, ptr->_right); }
	// 	else { return ptr; }
	// }

	//二叉搜索树的插入算法
	bool Insert(const T& x, BSTNode<T>*& ptr) {
		if (ptr == NULL) {
			ptr = new BSTNode<T>(x);
			return true;
		}
		else if (x < ptr->_data) { return Insert(x, ptr->_left); }
		else if (x > ptr->_data) { return Insert(x, ptr->_right); }
		else { return false; }
	}
	//二叉搜索树的删除算法
	bool Remove(const T x, BSTNode<T>*& ptr) {
		BSTNode<T>* temp;
		if (ptr != NULL) {
			if (x < ptr->_data) { return Remove(x, ptr->_left); }
			else if (x > ptr->_data) { return Remove(x, ptr->_right); }
			else if (x < ptr->_data) { return Remove(x, ptr->_right); }
			else if (ptr->_left != NULL && ptr->_right != NULL) {
				temp = ptr->_right;
				while (temp->_left != NULL) { temp = temp->_left; }
				ptr->_data = temp->_data;
				Remove(ptr->_data, ptr->_right);
			}
			else {
				//ptr即为需要删除的结点
				temp = ptr;
				if (ptr->_left == NULL) { ptr = ptr->_right; }
				else { ptr = ptr->_left; }
				delete temp;
				return true;
			}
		}
		return false;
	}
	void inOrder(BSTNode<T>* ptr, void(*visit)(BSTNode<T>* p)) {
		if (ptr) {
			inOrder(ptr->_left, visit);
			visit(ptr);
			inOrder(ptr->_right, visit);
		}
	}
	void preOrder(BSTNode<T>* ptr, void(*visit)(BSTNode<T>* p)) {
		if (ptr) {
			preOrder(ptr->_left, visit);
			preOrder(ptr->_right, visit);
			visit(ptr);
		}
	}
	~BST() {}
};