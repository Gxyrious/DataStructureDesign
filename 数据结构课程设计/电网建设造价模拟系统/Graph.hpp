#pragma once

using namespace std;
const int DefaultSize = 10;

//边定义
template<class T>
class Edge {
public:
	Edge() { _weight = 0; _nextEdge = 0; _secNode = 0; }
	Edge(int num, T weight) :
		_secNode(num), _weight(weight), _nextEdge(NULL) {}
	int _secNode;
	T _weight;
	Edge<T>* _nextEdge;
	/*bool operator!=(Edge<T>& R)const {
		return _secNode != R._secNode;
	}*/
};

//结点定义
template<class T,class E>
class Vertex {
public:
	Vertex() { _data = 0; _firstEdge = NULL; }
	Vertex(E& data) :_data(data) { _data = 0; _firstEdge = NULL; }
	E _data;
	Edge<T>* _firstEdge;
};

//邻接表的图定义
template<class T,class E>
class LinkedGraph {
public:
	int getMaxVertices()const { return _maxVertices; }//获取结点最大数
	int getNumVertices()const { return _numVertices; }//获取当前结点数
	int getNumEdges()const { return _numEdges; }//获取当前边的数目
	T getDefaultValueOfEdge()const { return _defaultValue_T; }//获取默认边权值
	E getDefaultValueOfVertex()const { return _defaultValue_E; }//获取默认结点数据
	LinkedGraph(T dafaultValue_T = 0,E defaultValue_E=0, int maxVertices = DefaultSize) {
		//构造函数，要求输入两种数据类型的默认值
		if (maxVertices <= 1) { maxVertices = DefaultSize; }
		_defaultValue_T = dafaultValue_T;
		_defaultValue_E = defaultValue_E;
		_maxVertices = maxVertices;
		_numVertices = 0;
		_numEdges = 0;
		_NodeTable = new Vertex<T,E>[_maxVertices];
		for (int i = 0; i < _maxVertices; i++) {
			_NodeTable[i]._firstEdge = NULL;
		}
	}
	~LinkedGraph() {
		//析构函数
		/*
		for (int i = 0; i < _numVertices; i++) {
			Edge<T>* p = _NodeTable[i]._firstEdge;
			while (p != NULL) {
				_NodeTable[i]._firstEdge = p;
				delete p;
				p = _NodeTable[i]._firstEdge;
			}
		}
		delete[]_NodeTable;
		*/
	}
	E getVertexValue(int i)const {
		//获取某个结点的值
		if (i >= 0 && i < _numVertices) { return _NodeTable[i]._data; }
		else { return _defaultValue_E; }
	}
	T getEdgeWeight(int v1, int v2)const {
		//获取某条边的权值
		if (v1 != -1 && v2 != -1) {
			Edge<T>* p = _NodeTable[v1]._firstEdge;
			while (p != NULL && p->_secNode != v2) { p = p->_nextEdge; }
			if (p != NULL) { return p->_weight; }
		}
		return _defaultValue_T;
	}
	bool insertVertex(const E& vertex) {
		//插入结点，数据为vertex
		if (_numVertices == _maxVertices) { return false; }
		for (int i = 0; i < _numVertices; i++) {
			if (_NodeTable[i]._data == vertex) { return false; }
		}
		_NodeTable[_numVertices++]._data = vertex;
		return true;
	}
	bool removeVertex(const E& vertex) {
		//删除值为vertex的结点
		return	removeVertex(getVertexPos(vertex));
	}
	bool removeVertex(int v) {
		//删除第v个结点
		if (_numVertices == 1 || v < 0 || v >= _numVertices) { return false; }
		Edge<T>* p, * s, * t;
		int i, k;
		while (_NodeTable[v]._frstEdge != NULL) {
			p = _NodeTable[v]._firstEdge;
			k = p->_secNode;
			s = _NodeTable[k]._firstEdge;
			t = NULL;
			while (s != NULL && s->_secNode != v) {
				t = s;
				s = s->_nextEdge;
			}
			if (s != NULL) {
				if (t == NULL) { _NodeTable[k]._firstEdge = s->_nextEdge; }
				else { t->_nextEdge = s->_nextEdge; }
				delete s;
			}
			_NodeTable[v]._firstNode = p->_nextEdge;
			delete p;
			_numEdges--;
		}
		_numVertices--;
		_NodeTable[v]._data = _NodeTable[_numVertices]._data;
		p = _NodeTable[v]._firstEdge = _NodeTable[_numVertices]._firstEdge;
		//start from v,search circles
		while (p != NULL) {
			s = _NodeTable[p->_secNode]._firstEdge;
			while (s != NULL) {
				if (s->_secNode == _numVertices) { s->_secNode = v; break; }
				else { s = s->_nextEdge; }
			}
			p = p->_nextEdge;//???
		}
		return true;
	}
	bool insertEdge(int v1, int v2, const T& weight) {
		//在v1和v2之间插入权值为weight的边，若边已存在则返回false
		if (v1 >= 0 && v1 < _numVertices && v2 >= 0 && v2 < _numVertices) {
			Edge<T>* q, * p = _NodeTable[v1]._firstEdge;
			while (p != NULL && p->_secNode != v2) { p = p->_nextEdge; }
			if (p != NULL) { return false; }//此边本就存在
			p = new Edge<T>;
			q = new Edge<T>;
			p->_secNode = v2;
			p->_weight = weight;
			p->_nextEdge = _NodeTable[v1]._firstEdge;
			_NodeTable[v1]._firstEdge = p;
			q->_secNode = v1;
			q->_weight = weight;
			q->_nextEdge = _NodeTable[v2]._firstEdge;
			_NodeTable[v2]._firstEdge = q;
			_numEdges++;
			return true;
		}
		return false;
	}
	bool removeEdge(int v1, int v2) {
		//删除v1和v2之间的边，若不存在这条边则返回false
		if (v1 != -1 && v2 != -1) {
			Edge<T>* p = _NodeTable[v1]._firstEdge, * q = NULL, * s = p;
			while (p != NULL && p->_secNode != v2) {
				q = p;
				p = p->_nextEdge;
			}
			if (p != NULL) {
				if (p == s) { _NodeTable[v1]._firstEdge = p->_nextEdge; }
				else { q->_nextEdge = p->_nextEdge; }
				delete p;
			}
			else { return false; }
			p = _NodeTable[v2]._firstEdge;
			q = NULL;
			s = p;
			while (p->_secNode != v1) {
				q = p;
				p = p->_nextEdge;
			}
			if (p == s) { _NodeTable[v2]._firstEdge = p->_nextEdge; }
			else { q->_nextEdge = p->_nextEdge; }
			delete p;
			return true;
		}
		return false;
	}
	int getFirstNeighbour(int v) {
		//获取结点v引出的第一条边
		if (v != -1) {//target vertex exists
			Edge<T>* p = _NodeTable[v]._firstEdge;
			if (p != NULL) { return p->_secNode; }
		}
		return -1;
	}
	int getNextNeighbour(int v, int w) {
		//获取结点v引出的边链表中，w的下一条边
		if (v != -1) {
			Edge<T>* p = _NodeTable[v]._firstEdge;
			while (p != NULL && p->_secNode != w) { p = p->_nextEdge; }
			if (p != NULL && p->_nextEdge != NULL) { return p->_nextEdge->_secNode; }
		}
		//target vertex not exists
		return -1;
	}
private:
	Vertex<T,E>* _NodeTable;//各边链表的头结点
	int getVertexPos(const E& vertex) {
		//获取数据为vertex的结点序号
		for (int i = 0; i < _numVertices; i++) {
			if (_NodeTable[i]._data == vertex) { return i; }
		}
		//target vertex not exists
		return -1;
	}

	T _defaultValue_T;
	E _defaultValue_E;
	int _maxVertices;
	int _numEdges;
	int _numVertices;
};