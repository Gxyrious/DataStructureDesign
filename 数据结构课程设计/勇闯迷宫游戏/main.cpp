#include<iostream>
#include<vector>
#include"Vector.hpp"

using namespace std;

const int maxn = 100, maxm = 100;
int n, m, minLength = maxn * maxm, step[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
bool map[maxn + 1][maxm + 1], b[maxn + 1][maxm + 1];

//�������
class Point {
public:
	int _x, _y;
	Point(int x = 0, int y = 0) :_x(x), _y(y) {}
}startPoint, endPoint;

//����·�ߺ����·��
Vector<Point>route, shortest_route;
vector<Point>p;

//���뺯��
void input() {
	//���(1,1);�յ�(n,m)
	cin >> n >> m;
	startPoint = Point(1, 1);
	endPoint = Point(n, m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> map[i][j];
		}
	}
}

//�������
void output() {
	VectorNode<Point>* vectorNode = shortest_route.getHead()->_next;
	cout << "(" << vectorNode->_data._x << "," << vectorNode->_data._y << ")";
	vectorNode = vectorNode->_next;
	for (; vectorNode;vectorNode = vectorNode->_next) {
		cout << "--->(" << vectorNode->_data._x << "," << vectorNode->_data._y << ")";
	}
}
void search_shortest_route(int x, int y) {
	if (route.getLength() >= minLength) {
		return;
	}
	else if (x == endPoint._x && y == endPoint._y) {
		shortest_route = route;
		minLength = route.getLength();
		return;
	}
	int tx, ty;
	for (int i = 0; i < 4; i++) {
		tx = x + step[i][0];
		ty = y + step[i][1];
		if (tx >= 1 && ty >= 1 && tx <= n && ty <= m && !map[tx][ty] && !b[tx][ty]) {
			b[tx][ty] = 1;
			route.PushBack(Point(tx, ty));
			search_shortest_route(tx, ty);
			route.PopBack();
			b[tx][ty] = 0;
		}

	}
}
int main() {
	cout << "�������Թ���������������Ȼ����������01�Թ���1��ʾ���ϰ�" << endl
		<< "������ʦ����Ȥ����ҵĴ�����ȷ�ԣ���û����Ȥ�Լ�����һ���Թ���" << endl
		<< "���ڴ���������˼�����Ϊ���ӵ����룬����ֱ�Ӹ���ճ����" << endl;
	input();
	route.PushBack(startPoint);
	search_shortest_route(1, 1);
	route.PopBack();
	output();
	return 0;
}
/*
* ����1
8 9
0 1 1 1 1 0 0 0 0
0 0 0 0 0 0 1 1 0
1 0 1 1 1 0 0 0 0
0 0 0 0 1 1 0 1 0
0 1 1 0 0 0 0 1 0
0 1 0 0 1 0 1 0 0
1 0 1 0 1 0 1 0 0
0 0 0 0 0 0 1 0 0
 * ����2

*/