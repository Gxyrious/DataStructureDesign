#pragma once
using namespace std;

/****
* 对于结点i：
* i = 0则i是根结点
* i的父节点为(i - 1) / 2
* i的左子女为2 * i + 1，右子女为2 * i + 2
****/

template<class T>
class MinHeap {
public:
	MinHeap(int maxSize) {
		_maxSize = maxSize;
		_currentSize = 0;
		_heap = new T[_maxSize];
	}
	~MinHeap() { 
		//delete[] _heap; 
	}
	bool Insert(const T& data) {
		//插入元素data。插入成功返回true，失败返回false
		if (_currentSize == _maxSize) { return false; }
		_heap[_currentSize++] = data;
		siftUp();
		return true;
	}
	bool RemoveMin(T& x) {
		//若堆空，则返回false；不然则退回最小元素并返回true
		if (_currentSize == 0) { return false; }
		x = _heap[0];
		_heap[0] = _heap[_currentSize - 1];
		_currentSize--;
		siftDown();
		return true;
	}
private:
	T* _heap;
	int _currentSize;
	int _maxSize;
	void siftUp() {
		//从堆尾向上调整
		int j = _currentSize - 1, i = (j - 1) / 2;
		T temp = _heap[j];
		while (j > 0) {
			if (temp < _heap[i]) {
				_heap[j] = _heap[i];
				j = i;
				i = (i - 1) / 2;
			}
			else { break; }
		}
		_heap[j] = temp;
	}
	void siftDown() {
		//从堆顶向下调整
		int i = 0, j = i * 2 + 1;
		T temp = _heap[i];
		while (j < _currentSize) {
			if (j + 1 < _currentSize && _heap[j] > _heap[j + 1]) { j++; }
			if (temp > _heap[j]) {
				_heap[i] = _heap[j];
				i = j;
				j = j * 2 + 1;
			}
			else { break; }
		}
		_heap[i] = temp;
	}
};