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
		this->_first = new CircLinkNode<T>;
		this->_last = new CircLinkNode<T>;
		_first->_next = _last;
		_last->_next = _first;
	}
	//析构函数
	~CircList() {
		Erase();
		delete _first, _last;
	}
	void Erase() {
		CircLinkNode<T>* pos;
		while (_first->_next != _last) {
			pos = _first->_next;
			_first->_next = pos->_next;
			delete pos;
		}
	}
	CircLinkNode<T>* getNode(int s) {
		CircLinkNode<T>* cur = _first;
		while (s--) {
			cur = Next(cur);
		}
		return cur;
	}
	bool Insert(T& t) {
		CircLinkNode<T>* newCircNode = new CircLinkNode<T>;
		if (newCircNode == NULL) {
			cout << "存储分配错误！" << endl;
			return false;
		}
		CircLinkNode<T>* leftNode = _first, * rightNode = _last;
		while (leftNode->_next != _last) {
			leftNode = leftNode->_next;
		}
		newCircNode->_data = t;
		leftNode->_next = newCircNode;
		newCircNode->_next = _last;
		return true;
	}
	bool Remove(CircLinkNode<T>* pre) {
		if (pre == NULL || Next(pre) == NULL) {
			return false;
		}
		CircLinkNode<T>* tar = Next(pre);
		if (pre->_next == _last) {
			_first->_next = tar;
		}
		else {
			pre->_next = tar->_next;
		}
		delete tar;
		return true;
	}
	CircLinkNode<T>* Next(CircLinkNode<T>* cur) {
		if (cur->_next == _last) {
			cur = _first->_next;
		}
		else {
			cur = cur->_next;
		}
		return cur;
	}
	void PrintList() {
		CircLinkNode<T>* cur = _first->_next;
		while (cur != _last) {
			cout << cur->_data << " ";
			cur = cur->_next;
		}
	}
private:
	CircLinkNode<T>* _first, * _last;
};