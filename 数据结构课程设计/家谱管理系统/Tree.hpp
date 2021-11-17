#pragma once
#include<iostream>
using namespace std;

template<class T>
class TreeNode {
public:
	TreeNode() { _data = T(); _brother = NULL; _parent = NULL; _firstson = NULL; }
	TreeNode(T& data) :_brother(NULL), _parent(NULL), _firstson(NULL) { _data = data; }
	T _data;
	TreeNode<T>* _brother;//�ֵܽ�㣬��������
	TreeNode<T>* _parent;
	TreeNode<T>* _firstson;//��һ�����ӽ��
};


template<class T>
class Tree {
public:
	Tree() { _root = NULL; }
	Tree(T& rootdata) { _root = new TreeNode<T>(rootdata); }
	~Tree() { Remove(_root); }
	bool setRoot(T& data) {
		//����㣬brother parent firstson����NULL��Ŀǰֻ������
		if (_root != NULL) {
			//������Ѵ��ڣ�ֻ�޸�����
			_root->_data = data;
			return true;
		}
		else {
			//�����δ����
			_root = new TreeNode<T>(data);
			return _root != NULL ? true : false;
		}
	}
	bool IfEmpty() { return _root == NULL; }
	TreeNode<T>* getRoot()const { return _root; }
	TreeNode<T>* getParent(TreeNode<T>* tar) { return tar != NULL ? tar->_parent : NULL; }
	TreeNode<T>* getSons(TreeNode<T>* tar) { return tar != NULL ? tar->_firstson : NULL; }//������е��������ɻ�����ж���
	bool Insert(TreeNode<T>* tar, TreeNode<T>* firstson) {
		if (tar == NULL || firstson == NULL) {
			return false;
		}
		//��������Ů����parentָ��ȫ���óɸ����
		for (TreeNode<T>* iter = firstson; iter != NULL; iter = iter->_brother) {
			iter->_parent = tar;
		}
		//��cur�²����ӽ��
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
		//�õ�һ����㣬ֱ��ɾ������Ů
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
		//��Ѱ������Ů
		if (tar->_firstson != NULL) {
			TreeNode<T>* search_son = search(tar->_firstson, data);
			if (search_son != NULL)return search_son;
		}
		//��Ѱ�����ֵ�
		if (tar->_brother != NULL) {
			TreeNode<T>* search_brother = search(tar->_brother, data);
			if (search_brother != NULL)return search_brother;
		}
		return NULL;//�Ҳ���
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