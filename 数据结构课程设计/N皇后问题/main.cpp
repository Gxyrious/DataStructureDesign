#include <iostream>
#include <string.h>

using namespace std;

const int maxn = 16;//最大棋盘为15 * 15
int N, location[maxn];
bool column[maxn], main_diagonal[2 * maxn], sub_diagonal[2 * maxn], p = true;
unsigned long long sum = 0;

/***
* maxn表示最大棋盘为(maxn-1)*(maxn-1)（为了简化处理此处不采用动态申请数组的方式）
* 实际上使用回溯法的复杂度很高，必然超越了多项式级别，甚至比指数级、阶乘级还高，到达了o(n^n)级别
* 当N大于15时程序运行时间极长
* N表示棋盘的大小为N * N
* sum表示情况总数
* location[i]存储第i行的皇后放置位置
* column[i]表示目前第i列是否已经放置皇后
* main_diagonal[i]表示第i条主对角线是否已经放置皇后
* sub_diagonal[i]表示第i条副对角线是否已经放置皇后
***/

//输出函数
void print() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			//准备输出一个N * N矩阵
			if (j == location[i]) {
				//所有皇后的位置：(i,location[i])
				//若(i,j)==(i,location[i])，则输出皇后，不然则输出0
				cout << "X ";
			}
			else {
				cout << "0 ";
			}
		}
		cout << endl;
	}
	cout << endl;
}
void search(int i) {
	//若已经找到了第N + 1行，则输出
	if (i == N + 1) {
		if (p) { print(); }
		sum++;
		return;
	}
	for (int j = 1; j <= N; j++) {
		//对于当前的第i行，去遍历列
		//若该列没有被放置过皇后、且主副对角线都没有被放置过皇后
		//则在该位置放置皇后，并将相关辅助数组都进行标记
		//标记过后去寻找第i + 1行皇后放置的位置
		//回溯的时候将标记的值更改回来
		if (column[j] || sub_diagonal[i + j] || main_diagonal[i - j + N]) {
			continue;
		}
		location[i] = j;
		column[j] = true;
		sub_diagonal[i + j] = true;
		main_diagonal[i - j + N] = true;
		search(i + 1);
		//回溯
		column[j] = false;
		sub_diagonal[i + j] = false;
		main_diagonal[i - j + N] = false;
	}
}
int main() {
	//初始化为零和false
	memset(location, 0, sizeof(location));
	memset(column, false, sizeof(column));
	memset(sub_diagonal, false, sizeof(sub_diagonal));
	memset(main_diagonal, false, sizeof(main_diagonal));
	cout << "请输入棋盘大小（一个1~15的正整数）：\n";
	cin >> N;//输入棋盘大小
	while (N < 1 || N > 15) {
		cout << "输入的N不合法，请重新输入！\n";
		cin >> N;
	}
	cout << "请选择是否要打印棋盘，1为打印，0为不打印：\n";
	cin >> p;
	search(1);//从第一行开始找
	cout << "sum=" << sum << endl;
	system("pause");
	return 0;
}