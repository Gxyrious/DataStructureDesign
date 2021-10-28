#pragma once
#include<iostream>
#include<time.h>
#define MAX 10000
using namespace std;
class TimeCalculating {
public:
	TimeCalculating(int target[], int (*pfun)(int target[]) = NULL) {
		for (int i = 0; i < MAX; i++) {
			_target[i] = target[i];
		}
		//this->_pfun = pfun;
		clock_t starttime = clock();
		this->_comparison_times = (*pfun)(_target);
		clock_t endtime = clock();
		this->_running_time = (double(endtime) - double(starttime)) / 1000.0;

	}
	TimeCalculating(int target[], int (*pfun)(int target[], int left, int right) = NULL) {
		for (int i = 0; i < MAX; i++) {
			_target[i] = target[i];
		}
		clock_t starttime = clock();
		this->_comparison_times = (*pfun)(_target, 0, MAX - 1);
		clock_t endtime = clock();
		this->_running_time = (double(endtime) - double(starttime)) / 1000.0;
	}
	int getComparisionTimes()const {
		return this->_comparison_times;
	}
	double getRunningTime()const {
		return this->_running_time;
	}
	void print() {
		for (int i = 0; i < MAX; i++) {
			cout << _target[i] << " ";
		}
	}
private:
	//int (*_pfun)(int target[]);
	int _target[MAX], _comparison_times;
	double _running_time;
};