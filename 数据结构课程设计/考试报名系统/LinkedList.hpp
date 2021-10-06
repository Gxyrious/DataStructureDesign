#pragma once
#include<iostream>
using namespace std;

//template<class T>
//class List;

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

template <class T>
class List {
public:
	//���캯��
	List() {
		_first = new LinkNode<T>;
		_length = 0;
	}
	//��������
	~List() {
		Erase();
		delete _first;
	}
	void Erase() {
		LinkNode<T>* cur;
		while (_first->_next) {
			cur = _first->_next;
			_first->_next = cur->_next;
			delete cur;
		}
		_length = 0;
	}
	int getLength()const {
		return _length;
	}
	LinkNode<T>* getHead()const {
		return _first;
	}
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
	bool push_back(T& t) {
		LinkNode<T>* cur = Locate(_length);
		if (!cur) {
			return false;
		}
		LinkNode<T>* newNode = new LinkNode<T>;
		if (!newNode) {
			cout << "�洢�������" << endl;
			return false;
		}
		newNode->_data = t;
		newNode->_next = cur->_next;
		cur->_next = newNode;
		_length++;
		return true;
	}
	bool Remove(int pos) {
		LinkNode<T>* cur = Locate(pos - 1);
		if (!cur || !(cur->_next)) {
			cout << "ɾ��ʧ�ܣ�" << endl;
			return false;
		}
		LinkNode<T>* tar = cur->_next;
		cur->_next = tar->_next;
		delete tar;
		cout << "ɾ���ɹ���" << endl;
		_length--;
		return true;
	}
	void PrintList() {
		LinkNode<T>* cur = _first->_next;
		while (cur != NULL) {
			cout << cur->_data << endl;
			cur = cur->_next;
		}
	}

private:
	LinkNode<T>* _first;
	int _length;
};