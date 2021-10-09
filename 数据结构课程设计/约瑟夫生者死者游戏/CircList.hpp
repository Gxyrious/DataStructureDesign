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
	//���캯��
	CircList() {
		//��������ͷβ���
		this->_first = new CircLinkNode<T>;
		this->_last = new CircLinkNode<T>;
		//�ø���ͷβ��㻥��ָ��Է�
		_first->_next = _last;
		_last->_next = _first;
	}
	//��������
	~CircList() {
		//��delete���������㣬��delete����ͷβ���
		Erase();
		delete _first, _last;
	}
	//�������
	void Erase() {
		CircLinkNode<T>* pos;
		while (_first->_next != _last) {
			pos = _first->_next;
			_first->_next = pos->_next;
			delete pos;
		}
	}
	//��ȡ�����pos��Ԫ��
	CircLinkNode<T>* getNode(int pos) {
		CircLinkNode<T>* cur = _first;
		while (pos--) {
			cur = Next(cur);
		}
		return cur;
	}
	//������ĩβ����Ԫ��
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
	//�Ƴ�Ԫ��
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
	//��װָ����һ����������ֹ���һ�������ת����һ����㷢������
	CircLinkNode<T>* Next(CircLinkNode<T>* cur) {
		if (cur->_next == _last) {
			cur = _first->_next;
		}
		else {
			cur = cur->_next;
		}
		return cur;
	}
	//��ӡ����
	void PrintList() {
		CircLinkNode<T>* cur = _first->_next;
		while (cur != _last) {
			cout << cur->_data << " ";
			cur = cur->_next;
		}
	}
private:
	//����ͷβ���
	CircLinkNode<T>* _first, * _last;
};