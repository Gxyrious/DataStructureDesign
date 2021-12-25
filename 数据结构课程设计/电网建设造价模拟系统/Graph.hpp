#pragma once

using namespace std;
const int DefaultSize = 10;

//边定义
//使用邻接链表存储图
template<class T>
class Edge {
public:
	//默认构造函数
	Edge() { _weight = 0; _nextEdge = 0; _secNode = 0; }
	//含参构造函数
	Edge(int num, T weight) :
		_secNode(num), _weight(weight), _nextEdge(NULL) {}
	int _secNode;//边指向的另一个结点
	T _weight;//边的权值
	Edge<T>* _nextEdge;//该结点接连的下一条边
};

//结点定义
template<class T, class E>
class Vertex {
public:
	//默认构造函数
	Vertex() { _data = 0; _firstEdge = NULL; }
	//含参构造函数
	Vertex(E& data) :_data(data) { _data = 0; _firstEdge = NULL; }
	E _data;//结点数值
	Edge<T>* _firstEdge;//结点接连的第一条边
};

//邻接表的图定义
template<class T, class E>
class LinkedGraph {
public:
	int getMaxVertices()const { return _maxVertices; }//获取结点最大数
	int getNumVertices()const { return _numVertices; }//获取当前结点数
	int getNumEdges()const { return _numEdges; }//获取当前边的数目
	T getDefaultValueOfEdge()const { return _defaultValue_T; }//获取默认边权值
	E getDefaultValueOfVertex()const { return _defaultValue_E; }//获取默认结点数据
	LinkedGraph(T dafaultValue_T = 0, E defaultValue_E = 0, int maxVertices = DefaultSize) {
		//构造函数，要求输入两种数据类型的默认值
		if (maxVertices <= 1) { maxVertices = DefaultSize; }
		_defaultValue_T = dafaultValue_T;
		_defaultValue_E = defaultValue_E;
		_maxVertices = maxVertices;
		_numVertices = 0;
		_numEdges = 0;
		_NodeTable = new Vertex<T, E>[_maxVertices];
		//将每个结点接连的第一条边置为NULL
		for (int i = 0; i < _maxVertices; i++) {
			_NodeTable[i]._firstEdge = NULL;
		}
	}
	~LinkedGraph() {
		//析构函数
		for (int i = 0; i < _numVertices; i++) {
			//对于每个结点，删除其所有的邻接边
			Edge<T>* p = _NodeTable[i]._firstEdge;
			while (p != NULL) {
				//逐条删除
				_NodeTable[i]._firstEdge = p->_nextEdge;
				delete p;
				p = _NodeTable[i]._firstEdge;
			}
		}
		//删除结点数组
		delete[]_NodeTable;
	}
	E getVertexValue(int i)const {
		//获取某个结点的值
		if (i >= 0 && i < _numVertices) { return _NodeTable[i]._data; }
		else { return _defaultValue_E; }
	}
	bool insertVertex(const E& vertex) {
		//插入结点，数据为vertex
		//若结点总数已满，则返回false
		if (_numVertices == _maxVertices) { return false; }
		for (int i = 0; i < _numVertices; i++) {
			//若已经存在相同数据的结点，则返回false
			if (_NodeTable[i]._data == vertex) { return false; }
		}
		_NodeTable[_numVertices++]._data = vertex;
		return true;
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
	bool insertEdge(E& n1, E& n2, const T& weight) {
		//在v1和v2之间插入权值为weight的边，若边已存在则返回false
		int v1 = getVertexPos(n1), v2 = getVertexPos(n2);
		if (v1 >= 0 && v1 < _numVertices && v2 >= 0 && v2 < _numVertices) {
			//结点实际存在，开始插入边操作
			Edge<T>* q, * p = _NodeTable[v1]._firstEdge;
			//先尝试寻找v1的邻接表中的v1-v2边，若找得到则表明此边本就存在，返回false
			while (p != NULL && p->_secNode != v2) { p = p->_nextEdge; }
			if (p != NULL) { return false; }
			//创建两个新的边
			p = new Edge<T>;
			q = new Edge<T>;
			//将p插入在v1的邻接表首位
			p->_secNode = v2;
			p->_weight = weight;
			p->_nextEdge = _NodeTable[v1]._firstEdge;
			_NodeTable[v1]._firstEdge = p;
			//将q插入在v2的邻接表首位
			q->_secNode = v1;
			q->_weight = weight;
			q->_nextEdge = _NodeTable[v2]._firstEdge;
			_NodeTable[v2]._firstEdge = q;
			//边的数量增加
			_numEdges++;
			return true;
		}
		return false;
	}
	bool removeVertex(E& n) {
		//删除值为n的结点
		int v = getVertexPos(n);//首先取得该结点的编号
		if (_numVertices == 1 || v < 0 || v >= _numVertices) { return false; }
		Edge<T>* p, * s, * t;
		int i, k;
		while (_NodeTable[v]._firstEdge != NULL) {
			//删除所有与v相连的边
			p = _NodeTable[v]._firstEdge;
			k = p->_secNode;//先获取此条边的另一结点
			//在边的另一结点的邻接表中删除此条边
			s = _NodeTable[k]._firstEdge;//先获取k结点的第一条边
			t = NULL;
			while (s != NULL && s->_secNode != v) {
				t = s;
				s = s->_nextEdge;
			}
			if (s != NULL) {
				//若t为NULL，说明要删的边是结点的第一条边
				//此时使结点的第一条边指向要删除边的下一条边
				if (t == NULL) { _NodeTable[k]._firstEdge = s->_nextEdge; }
				//使要删除边的前一条边的下一条边指向要删除边的下一条边
				else { t->_nextEdge = s->_nextEdge; }
				delete s;
			}
			//继续下一条边的删除
			_NodeTable[v]._firstEdge = p->_nextEdge;
			delete p;
			_numEdges--;
		}
		_numVertices--;
		//将结点数组中的最后一个结点放置到被删除结点的位置
		//更新邻接表中的所有边
		_NodeTable[v]._data = _NodeTable[_numVertices]._data;
		p = _NodeTable[v]._firstEdge = _NodeTable[_numVertices]._firstEdge;
		while (p != NULL) {
			s = _NodeTable[p->_secNode]._firstEdge;
			while (s != NULL) {
				//若该边的另一结点是_numVertices，则将其改为v
				if (s->_secNode == _numVertices) { s->_secNode = v; break; }
				else { s = s->_nextEdge; }
			}
			p = p->_nextEdge;
		}
		return true;
	}
	bool removeEdge(E& n1, E& n2) {
		//删除n1和n2之间的边，若不存在这条边则返回false
		int v1 = getVertexPos(n1), v2 = getVertexPos(n2);
		if (0 <= v1 && v1 < _numVertices && 0 <= v2 && v2 < _numVertices) {
			//若结点都合理
			Edge<T>* p = _NodeTable[v1]._firstEdge, * q = NULL, * s = p;
			while (p != NULL && p->_secNode != v2) {
				//在v1的邻接表中寻找该边并进行删除
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
				//在v2的邻接表中寻找该边并进行删除
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
	Vertex<T, E>* _NodeTable;//各边链表的头结点
	T _defaultValue_T;
	E _defaultValue_E;
	int _maxVertices, _numEdges, _numVertices;
	inline int getVertexPos(const E& data) {
		//获取数据为vertex的结点序号
		for (int i = 0; i < _numVertices; i++) {
			if (_NodeTable[i]._data == data) { return i; }
		}
		//目标节点不存在，返回-1
		return -1;
	}
};