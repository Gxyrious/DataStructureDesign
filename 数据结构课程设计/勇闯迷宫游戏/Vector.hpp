#pragma once
#include<iostream>

using namespace std;

//��������
template<class T>
class VectorNode {
public:
	VectorNode() :_data(T()), _next(NULL) {}//��ʼ��Ϊ��
	T _data;//�������
	VectorNode<T>* _next;//��һ���
};

//������
template <class T>
class Vector {
public:
	//���캯��
	Vector() :_first(new VectorNode<T>), _length(0) {}

	//��������
	~Vector() {
		Erase();
		delete _first;
	}
	
	//�����������ɾ��
	void Erase() {
		VectorNode<T>* cur;
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
	VectorNode<T>* getHead()const {
		return _first;
	}

	//��λ��pos��Ԫ��
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
	
	//������ĩβ��ӽ��
	bool PushBack(const T& t) {
		VectorNode<T>* cur = Locate(_length);//��λ����ĩβ���
		if (!cur) {
			return false;
		}
		VectorNode<T>* newNode = new VectorNode<T>;//����Ҫ��ӵĽ��
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
	bool PopBack() {
		VectorNode<T>* cur = Locate(_length - 1);//�ȶ�λҪɾ���Ľ��
		if (!cur || !(cur->_next)) {
			return false;
		}
		//����ɾ������
		VectorNode<T>* tar = cur->_next;
		cur->_next = tar->_next;
		delete tar;
		//����ɾ������
		_length--;//����������
		return true;
	}
private:
	VectorNode<T>* _first;//������ͷ���
	int _length;//������
};