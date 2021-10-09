#pragma once
#include<iostream>

using namespace std;

template<class T>
class CircLinkNode {
public:
	CircLinkNode() :_data(T()), _next(NULL) { }
	T _data;
	CircLinkNode<T>* _next;
};

template <class T>
class CircList {
public:
	//构造函数
	CircList() {
		//创建附加头尾结点
		this->_first = new CircLinkNode<T>;
		this->_last = new CircLinkNode<T>;
		//让附加头尾结点互相指向对方
		_first->_next = _last;
		_last->_next = _first;
	}
	//析构函数
	~CircList() {
		//先delete所有链表结点，再delete附加头尾结点
		Erase();
		delete _first, _last;
	}
	//清空链表
	void Erase() {
		CircLinkNode<T>* pos;
		while (_first->_next != _last) {
			pos = _first->_next;
			_first->_next = pos->_next;
			delete pos;
		}
	}
	//获取链表第pos个元素
	CircLinkNode<T>* getNode(int pos) {
		CircLinkNode<T>* cur = _first;
		while (pos--) {
			cur = Next(cur);
		}
		return cur;
	}
	//在链表末尾插入元素
	bool Insert(T& t) {
		CircLinkNode<T>* newCircNode = new CircLinkNode<T>;
		if (newCircNode == NULL) {
			return false;
		}
		CircLinkNode<T>* leftNode = _first;
		while (leftNode->_next != _last) {
			leftNode = leftNode->_next;
		}
		newCircNode->_data = t;
		leftNode->_next = newCircNode;
		newCircNode->_next = _last;
		return true;
	}
	//移除元素
	bool Remove(CircLinkNode<T>* pre) {
		if (pre == NULL || Next(pre) == NULL) {
			return false;
		}
		CircLinkNode<T>* tar = Next(pre);
		if (pre->_next == _last) {
			_first->_next = tar->_next;
		}
		else {
			pre->_next = tar->_next;
		}
		delete tar;
		return true;
	}
	//封装指向下一结点操作，防止最后一个结点跳转到第一个结点发生错误
	CircLinkNode<T>* Next(CircLinkNode<T>* cur) {
		if (cur->_next == _last) {
			cur = _first->_next;
		}
		else {
			cur = cur->_next;
		}
		return cur;
	}
	//打印链表
	void PrintList() {
		CircLinkNode<T>* cur = _first->_next;
		while (cur != _last) {
			cout << cur->_data << " ";
			cur = cur->_next;
		}
	}
private:
	//附加头尾结点
	CircLinkNode<T>* _first, * _last;
};