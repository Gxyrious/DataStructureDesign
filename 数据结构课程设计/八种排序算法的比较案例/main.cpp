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
				//若后者小于前者，交换两者
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
			//选取最小的数，打擂法
			times++;
			if (target[j] < target[min]) {
				min = j;
			}
		}
		//交换两者
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
				//说明已经插入在正确位置上
				break;
			}
			else {
				//与前者进行交换
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
		//gap序列为MAX/2,MAX/4,...,0
		for (int i = gap; i < MAX; i++) {
			//对于某个间距gap，将间隔gap的子序列取出，进行直接插入排序
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
	int m = left;//选取基准数
	while (true) {
		//将小于target[m]的数全部移到基准数左边
		//将大于target[m]的数全部移到基准数右边
		while (target[++i] < target[m]) {
			//寻找第一个比基准数大的数
			times++;
			if (i == right) {
				break;
			}
		}
		while (target[--j] > target[m]) {
			//寻找第一个比基准数小的数
			times++;
			if (j == left) {
				break;
			}
		}
		if (i >= j) {
			break;
		}
		//交换两者
		int temp = target[i];
		target[i] = target[j];
		target[j] = temp;
	}
	//将基准数放在中间
	int temp = target[m];
	target[m] = target[j];
	target[j] = temp;
	//分别对左子序列和有子序列进行快速排序
	times += QuickSort(target, left, j - 1);
	times += QuickSort(target, j + 1, right);
	return times;
}
int HeapSort(int target[]) {
	int times = 0;
	//构造最小堆，定义匿名函数变量
	auto siftDown = [&target, &times](int start, int end) ->void {
		int father = start, son = father * 2 + 1;
		while (son <= end) {
			times++;
			if (son + 1 <= end && target[son] < target[son + 1]) {
				//选取较大的子结点
				son++;
			}
			times++;
			if (target[father] > target[son]) {
				//若子结点大于父结点则代表调整完毕
				return;
			}
			else {
				//子结点和父结点进行交换
				int temp = target[father];
				target[father] = target[son];
				target[son] = temp;
				//继续下一趟比较
				father = son;
				son = father * 2 + 1;
			}
		}
	};

	for (int i = MAX / 2 - 1; i >= 0; i--) {
		//逐步调整为最小堆
		siftDown(i, MAX - 1);
	}
	for (int i = MAX - 1; i > 0; i--) {
		//将最后一个元素和第一个交换，并再次调整堆
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
		//无需再进行归并
		return times;
	}
	//将序列分成左右两部分，分别进行归并
	int mid = (left + right) / 2;
	times += MergeSort(target, left, mid);
	times += MergeSort(target, mid + 1, right);
	//左右序列已经有序，将两者进行归并
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
		//左序列有剩余
		r[k++] = target[i++];
	}
	while (j <= right) {
		//右序列有剩余
		r[k++] = target[j++];
	}
	for (i = left; i <= right; i++) {
		//将归并完的序列复制到原序列中
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
	int d = 1;//d为最大的数的位数
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
		//进行d次排序
		for (int j = 0; j < 10; j++) { count[j] = 0; }
		for (int j = 0; j < MAX; j++) {
			int k = (target[j] / radix) % 10;
			count[k]++;
		}
		for (int j = 1; j < 10; j++) {
			//将temp中的位置依次分配给每个桶
			count[j] += count[j - 1];
		}
		for (int j = MAX - 1; j >= 0; j--) {
			//倒序拿出桶中的元素
			int k = (target[j] / radix) % 10;
			temp[--count[k]] = target[j];
		}
		for (int j = 0; j < MAX; j++) {
			//将暂存数组的内容复制到原数组中
			target[j] = temp[j];
		}
		//进行下一关键码的比较
		radix *= 10;
	}
	return times;
}
int main() {
	srand((unsigned)time(NULL));
	for (int i = 0; i < MAX; i++) { target[i] = rand(); }
	/*使用计时器类，对不同的排序算法进行计时*/
	//冒泡排序
	TimeCalculating* bubble_sort = new TimeCalculating(target, BubbleSort);
	cout << "BubbleSort:\n比较次数：" << bubble_sort->getComparisionTimes() << "\n运行时间：" << bubble_sort->getRunningTime() << endl;
	delete bubble_sort;

	//选择排序
	TimeCalculating* select_sort = new TimeCalculating(target, SelectSort);
	cout << "\nSelectSort:\n比较次数：" << select_sort->getComparisionTimes() << "\n运行时间：" << select_sort->getRunningTime() << endl;
	delete select_sort;

	//插入排序
	TimeCalculating* insert_sort = new TimeCalculating(target, InsertSort);
	cout << "\nInsertSort:\n比较次数：" << insert_sort->getComparisionTimes() << "\n运行时间：" << insert_sort->getRunningTime() << endl;
	delete insert_sort;

	//希尔排序
	TimeCalculating* shell_sort = new TimeCalculating(target, ShellSort);
	cout << "\nShellSort:\n比较次数：" << shell_sort->getComparisionTimes() << "\n运行时间：" << shell_sort->getRunningTime() << endl;
	delete shell_sort;

	//快速排序
	TimeCalculating* quick_sort = new TimeCalculating(target, QuickSort);
	cout << "\nQuickSort:\n比较次数：" << quick_sort->getComparisionTimes() << "\n运行时间：" << quick_sort->getRunningTime() << endl;
	delete quick_sort;

	//堆排序
	TimeCalculating* heap_sort = new TimeCalculating(target, HeapSort);
	cout << "\nHeapSort:\n比较次数：" << heap_sort->getComparisionTimes() << "\n运行时间：" << heap_sort->getRunningTime() << endl;
	delete heap_sort;

	//归并排序
	TimeCalculating* merge_sort = new TimeCalculating(target, MergeSort);
	cout << "\nMergeSort:\n比较次数：" << merge_sort->getComparisionTimes() << "\n运行时间:" << merge_sort->getRunningTime() << endl;
	delete merge_sort;

	//基数排序
	TimeCalculating* radix_sort = new TimeCalculating(target, RadixSort);
	cout << "\nRadixSort:\n比较次数：" << radix_sort->getComparisionTimes() << "\n运行时间：" << radix_sort->getRunningTime() << endl;
	system("pause");
	return 0;
}