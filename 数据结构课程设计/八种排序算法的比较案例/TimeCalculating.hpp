#pragma once
#include<iostream>
#include<time.h>
#define MAX 10000
using namespace std;
class TimeCalculating {
public:
	//����ݹ�������㷨
	TimeCalculating(int target[], int (*pfun)(int target[]) = NULL) {
		for (int i = 0; i < MAX; i++) {
			_target[i] = target[i];
		}
		clock_t starttime = clock();//��ʼ��ʱ
		this->_comparison_times = (*pfun)(_target);//��������
		clock_t endtime = clock();//������ʱ
		this->_running_time = (double(endtime) - double(starttime)) / 1000.0;
	}
	//��Ҫ�ݹ�������㷨
	TimeCalculating(int target[], int (*pfun)(int target[], int left, int right) = NULL) {
		for (int i = 0; i < MAX; i++) { _target[i] = target[i]; }
		clock_t starttime = clock();//��ʼ��ʱ
		this->_comparison_times = (*pfun)(_target, 0, MAX - 1);//��������
		clock_t endtime = clock();//������ʱ
		this->_running_time = (double(endtime) - double(starttime)) / 1000.0;
	}
	//��ȡ�Ƚϴ���
	int getComparisionTimes()const {
		return this->_comparison_times;
	}
	//��ȡ����ʱ��
	double getRunningTime()const {
		return this->_running_time;
	}
	//��ӡ������������
	void print() {
		for (int i = 0; i < MAX; i++) {
			cout << _target[i] << " ";
		}
	}
private:
	int _target[MAX], _comparison_times;
	double _running_time;
};