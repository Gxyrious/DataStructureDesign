#pragma once
#include<iostream>
#include<time.h>
#define MAX 10000
using namespace std;
class TimeCalculating {
public:
	//不需递归的排序算法
	TimeCalculating(int target[], int (*pfun)(int target[]) = NULL) {
		for (int i = 0; i < MAX; i++) {
			_target[i] = target[i];
		}
		clock_t starttime = clock();//开始计时
		this->_comparison_times = (*pfun)(_target);//进行排序
		clock_t endtime = clock();//结束计时
		this->_running_time = (double(endtime) - double(starttime)) / 1000.0;
	}
	//需要递归的排序算法
	TimeCalculating(int target[], int (*pfun)(int target[], int left, int right) = NULL) {
		for (int i = 0; i < MAX; i++) { _target[i] = target[i]; }
		clock_t starttime = clock();//开始计时
		this->_comparison_times = (*pfun)(_target, 0, MAX - 1);//进行排序
		clock_t endtime = clock();//结束计时
		this->_running_time = (double(endtime) - double(starttime)) / 1000.0;
	}
	//获取比较次数
	int getComparisionTimes()const {
		return this->_comparison_times;
	}
	//获取运行时间
	double getRunningTime()const {
		return this->_running_time;
	}
	//打印排完序后的数组
	void print() {
		for (int i = 0; i < MAX; i++) {
			cout << _target[i] << " ";
		}
	}
private:
	int _target[MAX], _comparison_times;
	double _running_time;
};