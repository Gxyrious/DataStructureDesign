#pragma once

using namespace std;
const int DefaultSize = 10;

//�߶���
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

//��㶨��
template<class T,class E>
class Vertex {
public:
	Vertex() { _data = 0; _firstEdge = NULL; }
	Vertex(E& data) :_data(data) { _data = 0; _firstEdge = NULL; }
	E _data;
	Edge<T>* _firstEdge;
};

//�ڽӱ��ͼ����
template<class T,class E>
class LinkedGraph {
public:
	int getMaxVertices()const { return _maxVertices; }//��ȡ��������
	int getNumVertices()const { return _numVertices; }//��ȡ��ǰ�����
	int getNumEdges()const { return _numEdges; }//��ȡ��ǰ�ߵ���Ŀ
	T getDefaultValueOfEdge()const { return _defaultValue_T; }//��ȡĬ�ϱ�Ȩֵ
	E getDefaultValueOfVertex()const { return _defaultValue_E; }//��ȡĬ�Ͻ������
	LinkedGraph(T dafaultValue_T = 0,E defaultValue_E=0, int maxVertices = DefaultSize) {
		//���캯����Ҫ�����������������͵�Ĭ��ֵ
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
		//��������
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
		//��ȡĳ������ֵ
		if (i >= 0 && i < _numVertices) { return _NodeTable[i]._data; }
		else { return _defaultValue_E; }
	}
	T getEdgeWeight(int v1, int v2)const {
		//��ȡĳ���ߵ�Ȩֵ
		if (v1 != -1 && v2 != -1) {
			Edge<T>* p = _NodeTable[v1]._firstEdge;
			while (p != NULL && p->_secNode != v2) { p = p->_nextEdge; }
			if (p != NULL) { return p->_weight; }
		}
		return _defaultValue_T;
	}
	bool insertVertex(const E& vertex) {
		//�����㣬����Ϊvertex
		if (_numVertices == _maxVertices) { return false; }
		for (int i = 0; i < _numVertices; i++) {
			if (_NodeTable[i]._data == vertex) { return false; }
		}
		_NodeTable[_numVertices++]._data = vertex;
		return true;
	}
	bool removeVertex(const E& vertex) {
		//ɾ��ֵΪvertex�Ľ��
		return	removeVertex(getVertexPos(vertex));
	}
	bool removeVertex(int v) {
		//ɾ����v�����
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
		//��v1��v2֮�����ȨֵΪweight�ıߣ������Ѵ����򷵻�false
		if (v1 >= 0 && v1 < _numVertices && v2 >= 0 && v2 < _numVertices) {
			Edge<T>* q, * p = _NodeTable[v1]._firstEdge;
			while (p != NULL && p->_secNode != v2) { p = p->_nextEdge; }
			if (p != NULL) { return false; }//�˱߱��ʹ���
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
		//ɾ��v1��v2֮��ıߣ����������������򷵻�false
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
		//��ȡ���v�����ĵ�һ����
		if (v != -1) {//target vertex exists
			Edge<T>* p = _NodeTable[v]._firstEdge;
			if (p != NULL) { return p->_secNode; }
		}
		return -1;
	}
	int getNextNeighbour(int v, int w) {
		//��ȡ���v�����ı������У�w����һ����
		if (v != -1) {
			Edge<T>* p = _NodeTable[v]._firstEdge;
			while (p != NULL && p->_secNode != w) { p = p->_nextEdge; }
			if (p != NULL && p->_nextEdge != NULL) { return p->_nextEdge->_secNode; }
		}
		//target vertex not exists
		return -1;
	}
private:
	Vertex<T,E>* _NodeTable;//���������ͷ���
	int getVertexPos(const E& vertex) {
		//��ȡ����Ϊvertex�Ľ�����
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