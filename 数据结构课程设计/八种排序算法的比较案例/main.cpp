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
				//������С��ǰ�ߣ���������
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
			//ѡȡ��С���������޷�
			times++;
			if (target[j] < target[min]) {
				min = j;
			}
		}
		//��������
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
				//˵���Ѿ���������ȷλ����
				break;
			}
			else {
				//��ǰ�߽��н���
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
		//gap����ΪMAX/2,MAX/4,...,0
		for (int i = gap; i < MAX; i++) {
			//����ĳ�����gap�������gap��������ȡ��������ֱ�Ӳ�������
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
	int m = left;//ѡȡ��׼��
	while (true) {
		//��С��target[m]����ȫ���Ƶ���׼�����
		//������target[m]����ȫ���Ƶ���׼���ұ�
		while (target[++i] < target[m]) {
			//Ѱ�ҵ�һ���Ȼ�׼�������
			times++;
			if (i == right) {
				break;
			}
		}
		while (target[--j] > target[m]) {
			//Ѱ�ҵ�һ���Ȼ�׼��С����
			times++;
			if (j == left) {
				break;
			}
		}
		if (i >= j) {
			break;
		}
		//��������
		int temp = target[i];
		target[i] = target[j];
		target[j] = temp;
	}
	//����׼�������м�
	int temp = target[m];
	target[m] = target[j];
	target[j] = temp;
	//�ֱ���������к��������н��п�������
	times += QuickSort(target, left, j - 1);
	times += QuickSort(target, j + 1, right);
	return times;
}
int HeapSort(int target[]) {
	int times = 0;
	//������С�ѣ�����������������
	auto siftDown = [&target, &times](int start, int end) ->void {
		int father = start, son = father * 2 + 1;
		while (son <= end) {
			times++;
			if (son + 1 <= end && target[son] < target[son + 1]) {
				//ѡȡ�ϴ���ӽ��
				son++;
			}
			times++;
			if (target[father] > target[son]) {
				//���ӽ����ڸ���������������
				return;
			}
			else {
				//�ӽ��͸������н���
				int temp = target[father];
				target[father] = target[son];
				target[son] = temp;
				//������һ�˱Ƚ�
				father = son;
				son = father * 2 + 1;
			}
		}
	};

	for (int i = MAX / 2 - 1; i >= 0; i--) {
		//�𲽵���Ϊ��С��
		siftDown(i, MAX - 1);
	}
	for (int i = MAX - 1; i > 0; i--) {
		//�����һ��Ԫ�غ͵�һ�����������ٴε�����
		int temp = target[0];
		target[0] = target[i];
		target[i] = temp;
		times++;
		siftDown(0, i - 1);
	}
	return times;
}
int MergeSort(int target[], int left, int right) {
	int r[MAX], times = 0;
	memset(r, 0, sizeof(r));
	if (left == right) {
		//�����ٽ��й鲢
		return times;
	}
	//�����зֳ����������֣��ֱ���й鲢
	int mid = (left + right) / 2;
	times += MergeSort(target, left, mid);
	times += MergeSort(target, mid + 1, right);
	//���������Ѿ����򣬽����߽��й鲢
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
		//��������ʣ��
		r[k++] = target[i++];
	}
	while (j <= right) {
		//��������ʣ��
		r[k++] = target[j++];
	}
	for (i = left; i <= right; i++) {
		//���鲢������и��Ƶ�ԭ������
		target[i] = r[i];
	}
	return times;
}
int RadixSort(int target[]) {
	int times = 0;
	int maxNum = target[0];
	for (int i = 0; i < MAX; i++) {
		if (maxNum < target[i]) {
			maxNum = target[i];
		}
	}
	int d = 1;//dΪ��������λ��
	while (maxNum >= 10) {
		maxNum /= 10;
		d++;
	}
	int rear[10], front[10];
	for (int i = d - 1; i >= 0; i--) {
		for (int j = 0; j < 10; j++) { front[j] = 0; }

	}

	int temp[MAX], count[10], radix = 1;
	for (int i = 0; i < d; i++) {
		//����d������
		for (int j = 0; j < 10; j++) { count[j] = 0; }
		for (int j = 0; j < MAX; j++) {
			int k = (target[j] / radix) % 10;
			count[k]++;
		}
		for (int j = 1; j < 10; j++) {
			//��temp�е�λ�����η����ÿ��Ͱ
			count[j] += count[j - 1];
		}
		for (int j = MAX - 1; j >= 0; j--) {
			//�����ó�Ͱ�е�Ԫ��
			int k = (target[j] / radix) % 10;
			temp[--count[k]] = target[j];
		}
		for (int j = 0; j < MAX; j++) {
			//���ݴ���������ݸ��Ƶ�ԭ������
			target[j] = temp[j];
		}
		//������һ�ؼ���ıȽ�
		radix *= 10;
	}
	return times;
}
int main() {
	srand((unsigned)time(NULL));
	for (int i = 0; i < MAX; i++) { target[i] = rand(); }
	/*ʹ�ü�ʱ���࣬�Բ�ͬ�������㷨���м�ʱ*/
	//ð������
	TimeCalculating* bubble_sort = new TimeCalculating(target, BubbleSort);
	cout << "BubbleSort:\n�Ƚϴ�����" << bubble_sort->getComparisionTimes() << "\n����ʱ�䣺" << bubble_sort->getRunningTime() << endl;
	delete bubble_sort;

	//ѡ������
	TimeCalculating* select_sort = new TimeCalculating(target, SelectSort);
	cout << "\nSelectSort:\n�Ƚϴ�����" << select_sort->getComparisionTimes() << "\n����ʱ�䣺" << select_sort->getRunningTime() << endl;
	delete select_sort;

	//��������
	TimeCalculating* insert_sort = new TimeCalculating(target, InsertSort);
	cout << "\nInsertSort:\n�Ƚϴ�����" << insert_sort->getComparisionTimes() << "\n����ʱ�䣺" << insert_sort->getRunningTime() << endl;
	delete insert_sort;

	//ϣ������
	TimeCalculating* shell_sort = new TimeCalculating(target, ShellSort);
	cout << "\nShellSort:\n�Ƚϴ�����" << shell_sort->getComparisionTimes() << "\n����ʱ�䣺" << shell_sort->getRunningTime() << endl;
	delete shell_sort;

	//��������
	TimeCalculating* quick_sort = new TimeCalculating(target, QuickSort);
	cout << "\nQuickSort:\n�Ƚϴ�����" << quick_sort->getComparisionTimes() << "\n����ʱ�䣺" << quick_sort->getRunningTime() << endl;
	delete quick_sort;

	//������
	TimeCalculating* heap_sort = new TimeCalculating(target, HeapSort);
	cout << "\nHeapSort:\n�Ƚϴ�����" << heap_sort->getComparisionTimes() << "\n����ʱ�䣺" << heap_sort->getRunningTime() << endl;
	delete heap_sort;

	//�鲢����
	TimeCalculating* merge_sort = new TimeCalculating(target, MergeSort);
	cout << "\nMergeSort:\n�Ƚϴ�����" << merge_sort->getComparisionTimes() << "\n����ʱ��:" << merge_sort->getRunningTime() << endl;
	delete merge_sort;

	//��������
	TimeCalculating* radix_sort = new TimeCalculating(target, RadixSort);
	cout << "\nRadixSort:\n�Ƚϴ�����" << radix_sort->getComparisionTimes() << "\n����ʱ�䣺" << radix_sort->getRunningTime() << endl;
	system("pause");
	return 0;
}