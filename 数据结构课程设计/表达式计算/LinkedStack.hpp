#pragma once
#include<iostream>

template<class T>
class LinkNode {
public:
	LinkNode() {
		_data = T();
		_next = NULL;
	}
	T _data;
	LinkNode<T>* _next;
};

template<class T>
class Stack {
public:
	Stack() { _top = NULL; _size = 0; }
	~Stack() {
		erase();
	}
	int getSize() { return _size; }
	void Push(const T& data) {
		LinkNode<T>* tmp = new LinkNode<T>;
		tmp->_data = data;
		tmp->_next = _top;
		_top = tmp;
		_size++;
	}
	bool Pop(T& data) {
		if (empty())return false;
		LinkNode<T>* tmp = _top;
		_top = _top->_next;
		data = tmp->_data;
		delete tmp;
		_size--;
		return true;
	}
	bool getTop(T& data)const {
		if (empty())return false;
		data = _top->_data;
		return true;
	}
	bool empty()const {
		return (_top == NULL) ? true : false;
		//return top == NULL;
		//return (top == NULL) ? true : false;
	}
	void erase() {
		LinkNode<T>* tmp;
		while (_top != NULL) {
			tmp = _top;
			_top = _top->_next;
			delete tmp;
		}
	}

private:
	LinkNode<T>* _top;
	int _size;
};