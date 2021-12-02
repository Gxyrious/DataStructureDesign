#include <iostream>
#include "Graph.hpp"
#include "Heap.hpp"
#include "UFSets.hpp"
using namespace std;

template<class T>
class MSTEdge {
public:
	int _head, _tail;
	T _weight;
	MSTEdge() :_head(-1), _tail(-1) {}
	MSTEdge(int u, int v, int w) :_tail(u), _head(v), _weight(w) {}
	bool operator<(const MSTEdge<T>& edge) {
		return this->_weight < edge._weight;
	}
	bool operator>(const MSTEdge<T>& edge) {
		return this->_weight > edge._weight;
	}
	bool operator<=(const MSTEdge<T>& edge) {
		return this->_weight <= edge._weight;
	}
	bool operator>=(const MSTEdge<T>& edge) {
		return this->_weight >= edge._weight;
	}
	bool operator==(const MSTEdge<T>& edge) {
		return this->_weight == edge._weight;
	}
	bool operator!=(const MSTEdge<T>& edge) {
		return this->_weight != edge._weight;
	}
};

template<class T>
class MinSpanTree {
public:
	MinSpanTree() {
		maxSize = -1;
		currentSize = -1;
	}
	void initSize(int numVertices) {
		currentSize = 0;
		maxSize = numVertices - 1;//最多边数等于顶点数减一
		_edges = new MSTEdge<T>[maxSize - 1];//开辟空间存储边
	}
	bool Kruskal(LinkedGraph<T>& graph) {
		if (maxSize == -1) { return false; }
		int u, v, n = graph.getNumVertices(), m = graph.getNumEdges();
		//MSTEdge<T> e;
		MinHeap<MSTEdge<T>>heap(m);
		UFSets ufsets(n);
		for (u = 0; u < n; u++) {
			for (v = u + 1; v < n; v++) {
				if (graph.getWeight(u, v) != graph.getDefaultValue()) {
					MSTEdge<T> e(u, v, graph.getWeight(u, v));
					//e._tail = u; e._head = v;
					//e._weight = graph.getWeight(u, v);
					heap.Insert(e);
				}
			}
		}
		while (currentSize < maxSize) {
			MSTEdge<T> e;
			heap.RemoveMin(e);
			u = ufsets.Find(e._tail);
			v = ufsets.Find(e._head);
			if (u != v) {
				ufsets.Union(u, v);
				this->_edges[currentSize++] = e;
			}
		}
		return true;
	}
	bool PrintMST() {
		if (maxSize == -1) { return false; }
		for (int i = 0; i < currentSize; i++) {
			cout << _edges[i]._head << " " << _edges[i]._tail << " " << _edges[i]._weight << "\n";
		}
		return true;
	}
private:
	MSTEdge<T>* _edges;
	int maxSize, currentSize;

};