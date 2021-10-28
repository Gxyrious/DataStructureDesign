#include<iostream>
#include<stdlib.h>
#include"TimeCalculating.hpp"
using namespace std;
#define MAX 10000
int target[MAX];
int BubbleSort(int target[]) {
	int temp, times = 0;
	for (int i = 0; i < MAX - 1; i++) {
		for (int j = 0; j < MAX - 1 - i; j++) {
			times++;
			if (target[j] > target[j + 1]) {
				temp = target[j];
				target[j] = target[j + 1];
				target[j + 1] = temp;
			}
		}
	}
	return times;
}
int SelectSort(int target[]) {
	int temp, min, times = 0;
	for (int i = 0; i < MAX - 1; i++) {
		min = i;
		for (int j = i + 1; j < MAX; j++) {
			times++;
			if (target[j] < target[min]) {
				min = j;
			}
		}
		temp = target[i];
		target[i] = target[min];
		target[min] = temp;
	}
	return times;
}
int InsertSort(int target[]) {
	int temp, times = 0;
	for (int i = 1; i < MAX; i++) {
		for (int j = i; j > 0; j--) {
			times++;
			if (target[j - 1] <= target[j]) {
				break;
			}
			else {
				temp = target[j - 1];
				target[j - 1] = target[j];
				target[j] = temp;
			}
		}
	}
	return times;
}
int ShellSort(int target[]) {
	int temp, times = 0, j;
	for (int gap = MAX / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < MAX; i++) {
			temp = target[i];
			for (j = i; j >= gap && temp < target[j - gap]; j -= gap) {
				times++;
				target[j] = target[j - gap];
			}
			target[j] = temp;
		}
	}
	return times;
}
int QuickSort(int target[], int left, int right) {
	int times = 0;
	if (left >= right) {
		return times;
	}
	int i = left, j = right + 1;
	int m = left;
	while (true) {
		while (target[++i] < target[m]) {
			times++;
			if (i == right) {
				break;
			}
		}
		while (target[--j] > target[m]) {
			times++;
			if (j == left) {
				break;
			}
		}
		if (i >= j) {
			break;
		}
		int temp = target[i];
		target[i] = target[j];
		target[j] = temp;
	}
	//cout << (i >= j) << endl;
	int temp = target[m];
	target[m] = target[j];
	target[j] = temp;
	//target[left] = target[j];
	//target[j] = m;
	times += QuickSort(target, left, j - 1);
	times += QuickSort(target, j + 1, right);
	return times;
}
int HeapSort(int target[]) {
	int times = 0;
	auto max_heapify = [&target,&times](int start, int end) ->void {
		int father = start, son = father * 2 + 1;
		while (son <= end) {
			if (son + 1 <=end && target[son] < target[son + 1]) {
				son++;
			}
			if (target[father] > target[son]) {
				return;
			}
			else {
				int temp = target[father];
				target[father] = target[son];
				target[son] = temp;
				times++;
				father = son;
				son = father * 2 + 1;
			}
		}
	};
	
	for (int i = MAX / 2 - 1; i >= 0; i--) {
		max_heapify(i, MAX - 1);
	}
	for (int i = MAX - 1; i > 0; i--) {
		int temp = target[0];
		target[0] = target[i];
		target[i] = temp;
		times++;
		max_heapify(0, i - 1);
	}
	return times;
}
int MergeSort(int target[], int left, int right) {
	int r[MAX], times = 0;
	memset(r, 0, sizeof(r));
	if (left == right) {
		return times;
	}
	int mid = (left + right) / 2;
	times += MergeSort(target, left, mid);
	times += MergeSort(target, mid + 1, right);
	int i = left, j = mid + 1, k = left;
	while (i <= mid && j <= right) {
		times++;
		if (target[i] <= target[j]) {
			r[k++] = target[i++];
		}
		else {
			r[k++] = target[j++];
		}
	}
	while (i <= mid) {
		//times++;
		r[k++] = target[i++];
	}
	while (j <= right) {
		//times++;
		r[k++] = target[j++];
	}
	for (i = left; i <= right; i++) {
		//times++;
		target[i] = r[i];
	}
	return times;
}
int RadixSort(int target[]) {
	int radix[32768], times = 0;
	memset(radix, 0, sizeof(radix));
	for (int i = 0; i < MAX; i++) {
			radix[target[i]]++;
	}
	return times;
}
int main() {
	srand((unsigned)time(NULL));
	for (int i = 0; i < MAX; i++) {
		target[i] = rand();
	}
	//Ã°ÅÝÅÅÐò
	TimeCalculating* bubble_sort = new TimeCalculating(target, BubbleSort);
	cout << "BubbleSort:" << bubble_sort->getComparisionTimes() << " " << bubble_sort->getRunningTime() << endl;
	delete bubble_sort;

	//Ñ¡ÔñÅÅÐò
	TimeCalculating* select_sort = new TimeCalculating(target, SelectSort);
	cout << "SelectSort:" << select_sort->getComparisionTimes() << " " << select_sort->getRunningTime() << endl;
	delete select_sort;

	//²åÈëÅÅÐò
	TimeCalculating* insert_sort = new TimeCalculating(target, InsertSort);
	cout << "InsertSort:" << insert_sort->getComparisionTimes() << " " << insert_sort->getRunningTime() << endl;
	delete insert_sort;

	//Ï£¶ûÅÅÐò£¬´ýÉîÈëÌ½¾¿
	TimeCalculating* shell_sort = new TimeCalculating(target, ShellSort);
	cout << "ShellSort:" << shell_sort->getComparisionTimes() << " " << shell_sort->getRunningTime() << endl;
	delete shell_sort;

	//¿ìËÙÅÅÐò£¬´ýÉîÈëÑÐ¾¿
	TimeCalculating* quick_sort = new TimeCalculating(target, QuickSort);
	cout << "QuickSort:" << quick_sort->getComparisionTimes() << " " << quick_sort->getRunningTime() << endl;
	delete quick_sort;

	//¶ÑÅÅÐò
	TimeCalculating* heap_sort = new TimeCalculating(target, HeapSort);
	cout << "HeapSort:" << heap_sort->getComparisionTimes() << " " << heap_sort->getRunningTime() << endl;

	TimeCalculating* merge_sort = new TimeCalculating(target, MergeSort);
	cout << "MergeSort:" << merge_sort->getComparisionTimes() << " " << merge_sort->getRunningTime() << endl;
	delete merge_sort;

	//»ùÊýÅÅÐò
	TimeCalculating* radix_sort = new TimeCalculating(target, RadixSort);
	cout << "RadixSort:" << radix_sort->getComparisionTimes() << " " << radix_sort->getRunningTime() << endl;

	return 0;
}