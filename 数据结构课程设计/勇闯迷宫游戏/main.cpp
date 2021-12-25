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

//�������
class Point {
public:
	int _x, _y;
	Point(int x = 0, int y = 0) :_x(x), _y(y) {}
}startPoint, endPoint;

//����·�ߺ����·��
Point route[maxn * maxm], shortest_route[maxn * maxm];

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

//����Ĭ�ϵ�ͼ
void generate() {
	n = maxn; m = maxm;
	startPoint = Point(1, 1);
	endPoint = Point(maxn, maxm);
	cout << "Ĭ�ϵ�ͼΪ��\n";
	for (int i = 1; i <= maxn; i++) {
		for (int j = 1; j <= maxm; j++) {
			cout << defaule_map[i - 1][j - 1] << " ";
			map[i][j] = defaule_map[i - 1][j - 1];
		}
		cout << "\n";
	}
	cout << "\n";
}

//�������
void output() {
	cout << "·��Ϊ��\n";
	if (minLength != maxn * maxm) {
		cout << "(" << shortest_route[0]._x << "," << shortest_route[0]._y << ")";
		for (int i = 1; i <= minLength; i++) {
			cout << "--->(" << shortest_route[i]._x << "," << shortest_route[i]._y << ")";
		}
	}
	else {
		cout << "û��ͨ���յ��·����" << endl;
	}
}
void search_shortest_route(int x, int y) {
	//�жϵ�ǰ·�������Ƿ���ڵ������·��
	if (curLength >= minLength) {
		//���ǣ���ֱ�ӷ���
		return;
	}
	else if (x == endPoint._x && y == endPoint._y) {
		//��С�ڣ��ҵ�ǰ�����յ㣬����·�������������·����ע������ط����·��Ӧ��Ҫ��1
		for (int i = 0; i < curLength; i++) {
			shortest_route[i]._x = route[i]._x;
			shortest_route[i]._y = route[i]._y;
		}
		minLength = curLength - 1;
		return;
	}
	int tx, ty;
	//���ڵ�ǰ��λ�ã����������������ĸ������ƶ�
	//�ƶ�֮ǰ�ж�Ŀ��λ���Ƿ�������Ƿ�Խ�硢�Ѿ��߹������ϰ���
	for (int i = 0; i < 4; i++) {
		tx = x + step[i][0];
		ty = y + step[i][1];
		if (tx >= 1 && ty >= 1 && tx <= n && ty <= m && !map[tx][ty] && !b[tx][ty]) {
			//��֮ǰ������Ϊ�߹�������ǰ·�����ȼ�һ�����뵽��ǰ·��֮��
			b[tx][ty] = 1;
			route[curLength] = Point(tx, ty);
			curLength++;
			search_shortest_route(tx, ty);
			//��֮��·�����ȼ�һ����������Ϊδ�߹�
			curLength--;
			b[tx][ty] = 0;
		}
	}
}
int main() {
	cout << "�������Ƿ�Ҫʹ�ó����Դ����Թ���ͼ������������yes������������no\n";
	string str;
	cin >> str;
	if (str == "yes") {
		generate();
	}
	else {
		cout << "�������Թ���������������Ȼ����������01�Թ���1��ʾ���ϰ�\n";
		input();
	}
	route[curLength++] = startPoint;
	search_shortest_route(1, 1);
	output();
	cout << "\n";
	system("pause");
	return 0;
}