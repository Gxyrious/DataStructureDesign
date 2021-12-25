#include <iostream>
#include <string.h>

using namespace std;

const int maxn = 16;//�������Ϊ15 * 15
int N, location[maxn];
bool column[maxn], main_diagonal[2 * maxn], sub_diagonal[2 * maxn], p = true;
unsigned long long sum = 0;

/***
* maxn��ʾ�������Ϊ(maxn-1)*(maxn-1)��Ϊ�˼򻯴���˴������ö�̬��������ķ�ʽ��
* ʵ����ʹ�û��ݷ��ĸ��ӶȺܸߣ���Ȼ��Խ�˶���ʽ����������ָ�������׳˼����ߣ�������o(n^n)����
* ��N����15ʱ��������ʱ�伫��
* N��ʾ���̵Ĵ�СΪN * N
* sum��ʾ�������
* location[i]�洢��i�еĻʺ����λ��
* column[i]��ʾĿǰ��i���Ƿ��Ѿ����ûʺ�
* main_diagonal[i]��ʾ��i�����Խ����Ƿ��Ѿ����ûʺ�
* sub_diagonal[i]��ʾ��i�����Խ����Ƿ��Ѿ����ûʺ�
***/

//�������
void print() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			//׼�����һ��N * N����
			if (j == location[i]) {
				//���лʺ��λ�ã�(i,location[i])
				//��(i,j)==(i,location[i])��������ʺ󣬲�Ȼ�����0
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
	//���Ѿ��ҵ��˵�N + 1�У������
	if (i == N + 1) {
		if (p) { print(); }
		sum++;
		return;
	}
	for (int j = 1; j <= N; j++) {
		//���ڵ�ǰ�ĵ�i�У�ȥ������
		//������û�б����ù��ʺ��������Խ��߶�û�б����ù��ʺ�
		//���ڸ�λ�÷��ûʺ󣬲�����ظ������鶼���б��
		//��ǹ���ȥѰ�ҵ�i + 1�лʺ���õ�λ��
		//���ݵ�ʱ�򽫱�ǵ�ֵ���Ļ���
		if (column[j] || sub_diagonal[i + j] || main_diagonal[i - j + N]) {
			continue;
		}
		location[i] = j;
		column[j] = true;
		sub_diagonal[i + j] = true;
		main_diagonal[i - j + N] = true;
		search(i + 1);
		//����
		column[j] = false;
		sub_diagonal[i + j] = false;
		main_diagonal[i - j + N] = false;
	}
}
int main() {
	//��ʼ��Ϊ���false
	memset(location, 0, sizeof(location));
	memset(column, false, sizeof(column));
	memset(sub_diagonal, false, sizeof(sub_diagonal));
	memset(main_diagonal, false, sizeof(main_diagonal));
	cout << "���������̴�С��һ��1~15������������\n";
	cin >> N;//�������̴�С
	while (N < 1 || N > 15) {
		cout << "�����N���Ϸ������������룡\n";
		cin >> N;
	}
	cout << "��ѡ���Ƿ�Ҫ��ӡ���̣�1Ϊ��ӡ��0Ϊ����ӡ��\n";
	cin >> p;
	search(1);//�ӵ�һ�п�ʼ��
	cout << "sum=" << sum << endl;
	system("pause");
	return 0;
}