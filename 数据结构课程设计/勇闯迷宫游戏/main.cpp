#include<iostream>

using namespace std;
bool defaule_map[20][20] = {
	{0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1},
	{1,0,0,1,0,0,1,0,0,0,0,1,0,1,1,1,1,0,0,1},
	{0,0,0,0,0,0,0,1,0,1,0,1,0,0,1,1,1,1,0,1},
	{0,1,0,1,0,0,1,0,0,1,0,1,1,0,0,0,0,0,1,1},
	{1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,1,1,0,1},
	{0,0,1,0,1,1,1,0,0,1,0,1,1,1,1,1,0,1,0,1},
	{1,0,0,0,0,1,0,0,0,0,1,1,1,1,0,1,0,1,1,0},
	{1,0,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,1,1,1},
	{0,0,1,0,0,1,1,1,0,0,1,0,1,1,1,1,0,0,1,1},
	{1,0,0,1,0,0,0,1,0,1,0,1,1,0,1,0,0,0,0,0},
	{0,0,1,0,1,1,0,0,0,0,0,0,0,0,1,1,0,1,0,1},
	{0,1,1,0,0,0,0,1,1,0,0,1,0,1,0,1,0,0,1,0},
	{0,0,0,1,0,0,0,0,0,1,1,0,1,1,0,1,1,0,1,0},
	{0,0,0,1,0,1,1,0,1,0,1,0,1,0,0,0,0,1,0,1},
	{1,1,0,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1},
	{0,1,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,1,0,1},
	{1,1,1,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0},
	{0,0,1,1,0,1,0,1,0,1,1,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,1,0,0,1,1,0,1,1,0,1,1,1,1,0,0,1},
	{1,1,1,1,0,1,1,0,0,1,1,1,0,1,1,1,0,0,0,0}
};
const int maxn = 20, maxm = 20;
int n, m, curLength = 0, minLength = maxn * maxm, step[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
bool map[maxn + 1][maxm + 1], b[maxn + 1][maxm + 1];

//定义点类
class Point {
public:
	int _x, _y;
	Point(int x = 0, int y = 0) :_x(x), _y(y) {}
}startPoint, endPoint;

//定义路线和最短路线
Point route[maxn * maxm], shortest_route[maxn * maxm];

//输入函数
void input() {
	//起点(1,1);终点(n,m)
	cin >> n >> m;
	startPoint = Point(1, 1);
	endPoint = Point(n, m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> map[i][j];
		}
	}
}

//生成默认地图
void generate() {
	n = maxn; m = maxm;
	startPoint = Point(1, 1);
	endPoint = Point(maxn, maxm);
	cout << "默认地图为：\n";
	for (int i = 1; i <= maxn; i++) {
		for (int j = 1; j <= maxm; j++) {
			cout << defaule_map[i - 1][j - 1] << " ";
			map[i][j] = defaule_map[i - 1][j - 1];
		}
		cout << "\n";
	}
	cout << "\n";
}

//输出函数
void output() {
	cout << "路径为：\n";
	if (minLength != maxn * maxm) {
		cout << "(" << shortest_route[0]._x << "," << shortest_route[0]._y << ")";
		for (int i = 1; i <= minLength; i++) {
			cout << "--->(" << shortest_route[i]._x << "," << shortest_route[i]._y << ")";
		}
	}
	else {
		cout << "没有通向终点的路径！" << endl;
	}
}
void search_shortest_route(int x, int y) {
	//判断当前路径长度是否大于等于最短路径
	if (curLength >= minLength) {
		//若是，则直接返回
		return;
	}
	else if (x == endPoint._x && y == endPoint._y) {
		//若小于，且当前已是终点，则复制路径，并更新最短路径，注意这个地方最短路径应该要减1
		for (int i = 0; i < curLength; i++) {
			shortest_route[i]._x = route[i]._x;
			shortest_route[i]._y = route[i]._y;
		}
		minLength = curLength - 1;
		return;
	}
	int tx, ty;
	//对于当前的位置，试着向上下左右四个方向移动
	//移动之前判断目标位置是否合理，即是否越界、已经走过、有障碍物
	for (int i = 0; i < 4; i++) {
		tx = x + step[i][0];
		ty = y + step[i][1];
		if (tx >= 1 && ty >= 1 && tx <= n && ty <= m && !map[tx][ty] && !b[tx][ty]) {
			//走之前将其标记为走过，并当前路径长度加一，加入到当前路径之中
			b[tx][ty] = 1;
			route[curLength] = Point(tx, ty);
			curLength++;
			search_shortest_route(tx, ty);
			//走之后路径长度减一，并将其标记为未走过
			curLength--;
			b[tx][ty] = 0;
		}
	}
}
int main() {
	cout << "请输入是否要使用程序自带的迷宫地图，若是则输入yes，若否则输入no\n";
	string str;
	cin >> str;
	if (str == "yes") {
		generate();
	}
	else {
		cout << "请输入迷宫的行数和列数，然后换行再输入01迷宫，1表示有障碍\n";
		input();
	}
	route[curLength++] = startPoint;
	search_shortest_route(1, 1);
	output();
	cout << "\n";
	system("pause");
	return 0;
}