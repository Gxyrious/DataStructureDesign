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
	MSTEdge() :_head(-1), _tail(-1),_weight(0) {}
	MSTEdge(int u, int v, int w) :_tail(u), _head(v), _weight(w) {}
	//重载运算符
	bool operator<(const MSTEdge<T>& edge) { return this->_weight < edge._weight; }
	bool operator>(const MSTEdge<T>& edge) { return this->_weight > edge._weight; }
	bool operator<=(const MSTEdge<T>& edge) { return this->_weight <= edge._weight; }
	bool operator>=(const MSTEdge<T>& edge) { return this->_weight >= edge._weight; }
	bool operator==(const MSTEdge<T>& edge) { return this->_weight == edge._weight; }
	bool operator!=(const MSTEdge<T>& edge) { return this->_weight != edge._weight; }
};

template<class T, class E>
class MinSpanTree {
public:
	MinSpanTree() {
		maxSize = -1;
		currentSize = -1;
		_edges = NULL;
	}
	~MinSpanTree() {
		//delete[] _edges;
	}
	void initSize(int numVertices) {
		if (_edges != NULL){ delete[] _edges; }
		//先清空
		currentSize = 0;
		maxSize = numVertices - 1;//最多边数等于顶点数减一
		_edges = new MSTEdge<T>[maxSize];//开辟空间存储边
	}
	bool createMinSpanTree(const LinkedGraph<T, E>& graph) {
		if (!Kruskal(graph)) { return false; }
		else { PrintMST(graph); }
	}
private:
	MSTEdge<T>* _edges;
	int maxSize, currentSize;
	bool Kruskal(const LinkedGraph<T, E>& graph) {
		int u, v, n = graph.getNumVertices(), m = graph.getNumEdges();
		MinHeap<MSTEdge<T> >heap(m);
		UFSets ufsets(n);
		for (u = 0; u < n; u++) {
			for (v = u + 1; v < n; v++) {
				if (graph.getEdgeWeight(u, v) != graph.getDefaultValueOfEdge()) {
					MSTEdge<T> edge(u, v, graph.getEdgeWeight(u, v));
					heap.Insert(edge);
				}
			}
		}
		while (currentSize < maxSize) {
			MSTEdge<T> addEdge;
			if (!heap.RemoveMin(addEdge)) { break; }
			u = ufsets.Find(addEdge._tail);
			v = ufsets.Find(addEdge._head);
			if (u != v) {
				ufsets.Union(u, v);
				this->_edges[currentSize++] = addEdge;
			}
		}
		int b = ufsets.Find(0);
		for (int i = 1; i < n; i++) {
			if (b != ufsets.Find(i)) { return false; }
		}
		return true;
	}
	void PrintMST(const LinkedGraph<T, E>& graph) {
		for (int i = 0; i < currentSize; i++) {
			cout << graph.getVertexValue(_edges[i]._head) << " " << graph.getVertexValue(_edges[i]._tail) << " " << _edges[i]._weight << "\n";
		}
	}
};