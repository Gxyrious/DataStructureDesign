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
	BSTNode<T>*& getRoot() { return _root; }
	int getNum() { return _number; }
	BST() : _root(NULL), _number(0) {}//构造一棵空树
	BST(const T x) { _root = new BSTNode<T>(x); } //构造根节点
	~BST() { Clear(_root); }
	//二叉搜索树的删除算法
	bool Remove(const T& x) {return Remove(x, _root);}
	//二叉搜索树的插入算法
	bool Insert(const T& x) {	return Insert(x, _root);	}
	//二叉搜索树的搜索算法
	bool Search(const T x) {return Search(x, _root);}
	//二叉搜索树的清空算法
	void Clear() { Clear(_root); _root = NULL; }
	//二叉搜索树的中序遍历算法
	void inOrder(void(*visit)(BSTNode<T>* p)) {
		if (_root == NULL) { cout << "the tree is empty!\n"; }
		inOrder(_root, visit);
	}
private:
	bool Search(const T x, BSTNode<T>* ptr) {
		//先判断当前结点是否为空
		if (ptr == NULL) { return false; }
		//若x小于当前结点，则在左子树中搜索
		else if (x < ptr->_data) { return Search(x, ptr->_left); }
		//若x大于当前结点，则在右子树中搜索
		else if (x > ptr->_data) { return Search(x, ptr->_right); }
		//此时x == ptr->_data，成功找到了该元素
		else { return true; }
	}

	bool Insert(const T& x, BSTNode<T>*& ptr) {
		if (ptr == NULL) {
			//若ptr为空，说明已经之前已经遍历到某个叶子结点
			//ptr为该叶子结点的子女指针的引用
			ptr = new BSTNode<T>(x);
			_number++;
			return true;
		}
		else if (x < ptr->_data) { return Insert(x, ptr->_left); }
		else if (x > ptr->_data) { return Insert(x, ptr->_right); }
		else { return false; }
	}
	
	bool Remove(const T x, BSTNode<T>*& ptr) {
		BSTNode<T>* temp;
		if (ptr != NULL) {
			if (x < ptr->_data) { return Remove(x, ptr->_left); }
			else if (x > ptr->_data) { return Remove(x, ptr->_right); }
			else if (ptr->_left != NULL && ptr->_right != NULL) {
				//若ptr的两个子女都不为空
				//将其中序遍历的后一个，也即右子树中最靠左下的元素与当前结点交换
				//并改为删除右子树中的对应结点
				temp = ptr->_right;
				while (temp->_left != NULL) { temp = temp->_left; }
				ptr->_data = temp->_data;
				Remove(ptr->_data, ptr->_right);
			}
			else {
				//若ptr的子女有一个为空，则将不为空的子女顶替父结点即可
				temp = ptr;
				if (ptr->_left == NULL) { ptr = ptr->_right; }
				else { ptr = ptr->_left; }
				delete temp;
				_number--;
				return true;
			}
		}
		return false;
	}
	//清空整个树
	void Clear(BSTNode<T>* ptr) {
		if (ptr == NULL) { return; }
		Clear(ptr->_left);
		Clear(ptr->_right);
		_number--;
		delete ptr;
	}
	void inOrder(BSTNode<T>* ptr, void(*visit)(BSTNode<T>* p)) {
		if (ptr!=NULL) {
			inOrder(ptr->_left, visit);
			visit(ptr);
			inOrder(ptr->_right, visit);
		}
	}
private:
	BSTNode<T>* _root;
	int _number;
};