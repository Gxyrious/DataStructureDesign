#pragma once
#include<iostream>
using namespace std;

template<class T>
class TreeNode {
public:
	TreeNode() { _data = T(); _brother = NULL; _parent = NULL; _firstson = NULL; }
	TreeNode(T& data) :_brother(NULL), _parent(NULL), _firstson(NULL) { _data = data; }
	T _data;
	TreeNode<T>* _brother;//兄弟结点，构成链表
	TreeNode<T>* _parent;
	TreeNode<T>* _firstson;//第一个儿子结点
};


template<class T>
class Tree {
public:
	Tree() { _root = NULL; }
	Tree(T& rootdata) { _root = new TreeNode<T>(rootdata); }
	~Tree() { Remove(_root); }
	bool setRoot(T& data) {
		//根结点，brother parent firstson都是NULL，目前只有数据
		if (_root != NULL) {
			//根结点已存在，只修改数据
			_root->_data = data;
			return true;
		}
		else {
			//根结点未建立
			_root = new TreeNode<T>(data);
			return _root != NULL ? true : false;
		}
	}
	bool IfEmpty() { return _root == NULL; }
	TreeNode<T>* getRoot()const { return _root; }
	TreeNode<T>* getParent(TreeNode<T>* tar) { return tar != NULL ? tar->_parent : NULL; }
	TreeNode<T>* getSons(TreeNode<T>* tar) { return tar != NULL ? tar->_firstson : NULL; }//将其进行迭代，即可获得所有儿子
	bool Insert(TreeNode<T>* tar, TreeNode<T>* firstson) {
		if (tar == NULL || firstson == NULL) {
			return false;
		}
		//将所有子女结点的parent指针全部置成父结点
		for (TreeNode<T>* iter = firstson; iter != NULL; iter = iter->_brother) {
			iter->_parent = tar;
		}
		//在cur下插入子结点
		if (tar->_firstson == NULL) {
			tar->_firstson = firstson;
		}
		else {
			tar = tar->_firstson;
			while (tar->_brother != NULL) { tar = tar->_brother; }
			tar->_brother = firstson;
		}
		return true;
	}
	bool Remove(TreeNode<T>* tar) {
		//拿到一个结点，直接删它的子女
		TreeNode<T>* son = tar->_firstson;
		while (son != NULL) {
			TreeNode<T>* tmp = son->_brother;
			Remove(son);
			son = tmp;
		}
		delete tar;
		return true;
	}
	TreeNode<T>* search(TreeNode<T>* tar, const T& data) {
		if (tar->_data == data)return tar;
		if (tar == NULL)return NULL;
		//先寻找其子女
		if (tar->_firstson != NULL) {
			TreeNode<T>* search_son = search(tar->_firstson, data);
			if (search_son != NULL)return search_son;
		}
		//再寻找其兄弟
		if (tar->_brother != NULL) {
			TreeNode<T>* search_brother = search(tar->_brother, data);
			if (search_brother != NULL)return search_brother;
		}
		return NULL;//找不到
	}
	void PreOrder(TreeNode<T>* cur) {
		if (cur == NULL)return;
		else cout << cur->_data << " ";
		PreOrder(cur->_firstson);
		PreOrder(cur->_brother);
		return;
	}
private:
	TreeNode<T>* _root;
};