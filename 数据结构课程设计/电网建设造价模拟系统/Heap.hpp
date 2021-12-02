#include <iostream>

using namespace std;

/*
���ڽ��i
i = 0��i�Ǹ����
i�ĸ��ڵ�Ϊ(i - 1) / 2
i������ŮΪ2 * i + 1������ŮΪ2 * i + 2
*/
template<class T>
class MinHeap {
public:
	MinHeap(int maxSize) {
		_maxSize = maxSize;
		_currentSize = 0;
		_heap = new T[_maxSize];
	}
	~MinHeap() { delete[]_heap; }
	bool Insert(const T& data) {
		if (_currentSize == _maxSize) { return false; }
		_heap[_currentSize++] = data;
		siftUp();
		return true;
	}
	bool RemoveMin(T& x) {
		//���ѿգ��򷵻�false����Ȼ���˻���СԪ�ز�����true
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
	//�Ӷ�β���ϵ���
	void siftUp() {
		//j���ӣ�i�Ǹ�
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
	//�ӶѶ����µ���
	void siftDown() {
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