#pragma once
#include<iostream>

using namespace std;

//链表结点类
template<class T>
class VectorNode {
public:
	VectorNode() :_data(T()), _next(NULL) {}//初始化为空
	T _data;//结点数据
	VectorNode<T>* _next;//下一结点
};

//链表类
template <class T>
class Vector {
public:
	//构造函数
	Vector() :_first(new VectorNode<T>), _length(0) {}

	//析构函数
	~Vector() {
		Erase();
		delete _first;
	}
	
	//清空链表，依次删除
	void Erase() {
		VectorNode<T>* cur;
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
	VectorNode<T>* getHead()const {
		return _first;
	}

	//定位第pos个元素
	VectorNode<T>* Locate(int pos) {
		if (pos < 0) {
			return NULL;
		}
		VectorNode<T>* cur = _first;
		while (cur && --pos >= 0) {
			cur = cur->_next;
		}
		return cur;
	}
	
	//在链表末尾添加结点
	bool PushBack(const T& t) {
		VectorNode<T>* cur = Locate(_length);//定位链表末尾结点
		if (!cur) {
			return false;
		}
		VectorNode<T>* newNode = new VectorNode<T>;//创建要添加的结点
		if (!newNode) {
			return false;
		}
		//添加结点核心代码
		newNode->_data = t;
		newNode->_next = cur->_next;
		cur->_next = newNode;
		//添加结点核心代码
		_length++;//更新链表长度
		return true;
	}

	//删除结点
	bool PopBack() {
		VectorNode<T>* cur = Locate(_length - 1);//先定位要删除的结点
		if (!cur || !(cur->_next)) {
			return false;
		}
		//核心删除代码
		VectorNode<T>* tar = cur->_next;
		cur->_next = tar->_next;
		delete tar;
		//核心删除代码
		_length--;//更新链表长度
		return true;
	}
private:
	VectorNode<T>* _first;//链表附加头结点
	int _length;//链表长度
};