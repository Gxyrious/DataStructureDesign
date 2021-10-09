#pragma once
#include<iostream>

using namespace std;

//��������
template<class T>
class LinkNode {
public:
	LinkNode() :_data(T()), _next(NULL) {}//��ʼ��Ϊ��
	T _data;//�������
	LinkNode<T>* _next;//��һ���
};

//������
template <class T>
class LinkedList {
public:
	//���캯��
	LinkedList() :_first(new LinkNode<T>), _length(0) {}

	//��������
	~LinkedList() {
		Erase();
		delete _first;
	}
	
	//�����������ɾ��
	void Erase() {
		LinkNode<T>* cur;
		while (_first->_next) {
			cur = _first->_next;
			_first->_next = cur->_next;
			delete cur;
		}
		_length = 0;
	}

	//��ȡ������
	int getLength()const {
		return _length;
	}

	//��ȡ����ͷ���
	LinkNode<T>* getHead()const {
		return _first;
	}

	//��λ��pos��Ԫ��
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
	
	//������ĩβ��ӽ��
	bool PushBack(T& t) {
		LinkNode<T>* cur = Locate(_length);//��λ����ĩβ���
		if (!cur) {
			return false;
		}
		LinkNode<T>* newNode = new LinkNode<T>;//����Ҫ��ӵĽ��
		if (!newNode) {
			return false;
		}
		//��ӽ����Ĵ���
		newNode->_data = t;
		newNode->_next = cur->_next;
		cur->_next = newNode;
		//��ӽ����Ĵ���
		_length++;//����������
		return true;
	}

	//ɾ�����
	bool Remove(int pos) {
		LinkNode<T>* cur = Locate(pos - 1);//�ȶ�λҪɾ���Ľ��
		if (!cur || !(cur->_next)) {
			return false;
		}
		//����ɾ������
		LinkNode<T>* tar = cur->_next;
		cur->_next = tar->_next;
		delete tar;
		//����ɾ������
		_length--;//����������
		return true;
	}
private:
	LinkNode<T>* _first;//������ͷ���
	int _length;//������
};