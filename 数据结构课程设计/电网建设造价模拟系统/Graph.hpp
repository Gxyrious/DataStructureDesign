#pragma once

using namespace std;
const int DefaultSize = 10;

//�߶���
//ʹ���ڽ�����洢ͼ
template<class T>
class Edge {
public:
	//Ĭ�Ϲ��캯��
	Edge() { _weight = 0; _nextEdge = 0; _secNode = 0; }
	//���ι��캯��
	Edge(int num, T weight) :
		_secNode(num), _weight(weight), _nextEdge(NULL) {}
	int _secNode;//��ָ�����һ�����
	T _weight;//�ߵ�Ȩֵ
	Edge<T>* _nextEdge;//�ý���������һ����
};

//��㶨��
template<class T, class E>
class Vertex {
public:
	//Ĭ�Ϲ��캯��
	Vertex() { _data = 0; _firstEdge = NULL; }
	//���ι��캯��
	Vertex(E& data) :_data(data) { _data = 0; _firstEdge = NULL; }
	E _data;//�����ֵ
	Edge<T>* _firstEdge;//�������ĵ�һ����
};

//�ڽӱ��ͼ����
template<class T, class E>
class LinkedGraph {
public:
	int getMaxVertices()const { return _maxVertices; }//��ȡ��������
	int getNumVertices()const { return _numVertices; }//��ȡ��ǰ�����
	int getNumEdges()const { return _numEdges; }//��ȡ��ǰ�ߵ���Ŀ
	T getDefaultValueOfEdge()const { return _defaultValue_T; }//��ȡĬ�ϱ�Ȩֵ
	E getDefaultValueOfVertex()const { return _defaultValue_E; }//��ȡĬ�Ͻ������
	LinkedGraph(T dafaultValue_T = 0, E defaultValue_E = 0, int maxVertices = DefaultSize) {
		//���캯����Ҫ�����������������͵�Ĭ��ֵ
		if (maxVertices <= 1) { maxVertices = DefaultSize; }
		_defaultValue_T = dafaultValue_T;
		_defaultValue_E = defaultValue_E;
		_maxVertices = maxVertices;
		_numVertices = 0;
		_numEdges = 0;
		_NodeTable = new Vertex<T, E>[_maxVertices];
		//��ÿ���������ĵ�һ������ΪNULL
		for (int i = 0; i < _maxVertices; i++) {
			_NodeTable[i]._firstEdge = NULL;
		}
	}
	~LinkedGraph() {
		//��������
		for (int i = 0; i < _numVertices; i++) {
			//����ÿ����㣬ɾ�������е��ڽӱ�
			Edge<T>* p = _NodeTable[i]._firstEdge;
			while (p != NULL) {
				//����ɾ��
				_NodeTable[i]._firstEdge = p->_nextEdge;
				delete p;
				p = _NodeTable[i]._firstEdge;
			}
		}
		//ɾ���������
		delete[]_NodeTable;
	}
	E getVertexValue(int i)const {
		//��ȡĳ������ֵ
		if (i >= 0 && i < _numVertices) { return _NodeTable[i]._data; }
		else { return _defaultValue_E; }
	}
	bool insertVertex(const E& vertex) {
		//�����㣬����Ϊvertex
		//����������������򷵻�false
		if (_numVertices == _maxVertices) { return false; }
		for (int i = 0; i < _numVertices; i++) {
			//���Ѿ�������ͬ���ݵĽ�㣬�򷵻�false
			if (_NodeTable[i]._data == vertex) { return false; }
		}
		_NodeTable[_numVertices++]._data = vertex;
		return true;
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
	bool insertEdge(E& n1, E& n2, const T& weight) {
		//��v1��v2֮�����ȨֵΪweight�ıߣ������Ѵ����򷵻�false
		int v1 = getVertexPos(n1), v2 = getVertexPos(n2);
		if (v1 >= 0 && v1 < _numVertices && v2 >= 0 && v2 < _numVertices) {
			//���ʵ�ʴ��ڣ���ʼ����߲���
			Edge<T>* q, * p = _NodeTable[v1]._firstEdge;
			//�ȳ���Ѱ��v1���ڽӱ��е�v1-v2�ߣ����ҵõ�������˱߱��ʹ��ڣ�����false
			while (p != NULL && p->_secNode != v2) { p = p->_nextEdge; }
			if (p != NULL) { return false; }
			//���������µı�
			p = new Edge<T>;
			q = new Edge<T>;
			//��p������v1���ڽӱ���λ
			p->_secNode = v2;
			p->_weight = weight;
			p->_nextEdge = _NodeTable[v1]._firstEdge;
			_NodeTable[v1]._firstEdge = p;
			//��q������v2���ڽӱ���λ
			q->_secNode = v1;
			q->_weight = weight;
			q->_nextEdge = _NodeTable[v2]._firstEdge;
			_NodeTable[v2]._firstEdge = q;
			//�ߵ���������
			_numEdges++;
			return true;
		}
		return false;
	}
	bool removeVertex(E& n) {
		//ɾ��ֵΪn�Ľ��
		int v = getVertexPos(n);//����ȡ�øý��ı��
		if (_numVertices == 1 || v < 0 || v >= _numVertices) { return false; }
		Edge<T>* p, * s, * t;
		int i, k;
		while (_NodeTable[v]._firstEdge != NULL) {
			//ɾ��������v�����ı�
			p = _NodeTable[v]._firstEdge;
			k = p->_secNode;//�Ȼ�ȡ�����ߵ���һ���
			//�ڱߵ���һ�����ڽӱ���ɾ��������
			s = _NodeTable[k]._firstEdge;//�Ȼ�ȡk���ĵ�һ����
			t = NULL;
			while (s != NULL && s->_secNode != v) {
				t = s;
				s = s->_nextEdge;
			}
			if (s != NULL) {
				//��tΪNULL��˵��Ҫɾ�ı��ǽ��ĵ�һ����
				//��ʱʹ���ĵ�һ����ָ��Ҫɾ���ߵ���һ����
				if (t == NULL) { _NodeTable[k]._firstEdge = s->_nextEdge; }
				//ʹҪɾ���ߵ�ǰһ���ߵ���һ����ָ��Ҫɾ���ߵ���һ����
				else { t->_nextEdge = s->_nextEdge; }
				delete s;
			}
			//������һ���ߵ�ɾ��
			_NodeTable[v]._firstEdge = p->_nextEdge;
			delete p;
			_numEdges--;
		}
		_numVertices--;
		//����������е����һ�������õ���ɾ������λ��
		//�����ڽӱ��е����б�
		_NodeTable[v]._data = _NodeTable[_numVertices]._data;
		p = _NodeTable[v]._firstEdge = _NodeTable[_numVertices]._firstEdge;
		while (p != NULL) {
			s = _NodeTable[p->_secNode]._firstEdge;
			while (s != NULL) {
				//���ñߵ���һ�����_numVertices�������Ϊv
				if (s->_secNode == _numVertices) { s->_secNode = v; break; }
				else { s = s->_nextEdge; }
			}
			p = p->_nextEdge;
		}
		return true;
	}
	bool removeEdge(E& n1, E& n2) {
		//ɾ��n1��n2֮��ıߣ����������������򷵻�false
		int v1 = getVertexPos(n1), v2 = getVertexPos(n2);
		if (0 <= v1 && v1 < _numVertices && 0 <= v2 && v2 < _numVertices) {
			//����㶼����
			Edge<T>* p = _NodeTable[v1]._firstEdge, * q = NULL, * s = p;
			while (p != NULL && p->_secNode != v2) {
				//��v1���ڽӱ���Ѱ�Ҹñ߲�����ɾ��
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
				//��v2���ڽӱ���Ѱ�Ҹñ߲�����ɾ��
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
private:
	Vertex<T, E>* _NodeTable;//���������ͷ���
	T _defaultValue_T;
	E _defaultValue_E;
	int _maxVertices, _numEdges, _numVertices;
	inline int getVertexPos(const E& data) {
		//��ȡ����Ϊvertex�Ľ�����
		for (int i = 0; i < _numVertices; i++) {
			if (_NodeTable[i]._data == data) { return i; }
		}
		//Ŀ��ڵ㲻���ڣ�����-1
		return -1;
	}
};