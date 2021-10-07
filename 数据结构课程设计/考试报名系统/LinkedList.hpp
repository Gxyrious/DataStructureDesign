#pragma once
#include<iostream>

using namespace std;

template<class T>
class LinkNode {
public:
	LinkNode() :_data(T()), _next(NULL) {}//初始化为空
	T _data;//结点数据
	LinkNode<T>* _next;//下一结点
};

template <class T>
class LinkedList {
public:
	//构造函数
	LinkedList() :_first(new LinkNode<T>), _length(0) {}

	//析构函数
	~LinkedList() {
		Erase();
		delete _first;
	}
	
	//清空链表
	void Erase() {
		LinkNode<T>* cur;
		while (_first->_next) {
			cur = _first->_next;
			_first->_next = cur->_next;
			delete cur;
		}
		_length = 0;
	}

	//获取链表长度
	int getLength()const {
		return _length;
	}

	//获取附加头结点
	LinkNode<T>* getHead()const {
		return _first;
	}

	//定位
	LinkNode<T>* Locate(int pos) {
		if (pos < 0) {
			return NULL;
		}
		LinkNode<T>* cur = _first;
		while (cur && --pos >= 0) {
			cur = cur->_next;
		}
		return cur;
	}
	
	//在链表末尾添加结点
	bool PushBack(T& t) {
		LinkNode<T>* cur = Locate(_length);
		if (!cur) {
			return false;
		}
		LinkNode<T>* newNode = new LinkNode<T>;
		if (!newNode) {
			return false;
		}
		newNode->_data = t;
		newNode->_next = cur->_next;
		cur->_next = newNode;
		_length++;
		return true;
	}

	//删除结点
	bool Remove(int pos) {
		LinkNode<T>* cur = Locate(pos - 1);
		if (!cur || !(cur->_next)) {
			return false;
		}
		LinkNode<T>* tar = cur->_next;
		cur->_next = tar->_next;
		delete tar;
		_length--;
		return true;
	}
private:
	LinkNode<T>* _first;//链表附加头结点
	int _length;//链表长度
};