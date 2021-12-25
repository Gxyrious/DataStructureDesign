#include"CircList.hpp"

int main() {
	CircList<int> circlist;
	CircLinkNode<int>* pre;
	int N, S, M, K;
	cout << "请依次输入四个整数，"
		<< "分别为总人数N，"
		<< "第一个报数的人S，"
		<< "每数到第M个人就让其出列，"
		<< "直至剩下K个人为止。\n";
	cin >> N >> S >> M >> K;

	//依次插入N个人
	for (int i = 1; i <= N; i++) {
		circlist.Insert(i);
	}

	//获取第S-1个人，作为前驱结点pre
	pre = circlist.getNode(S - 1);

	//一共N个人，要剩下K个人，所以共需要选出N-K+1个人
	for (int i = 1; i < N - K + 1; i++) {
		//每次让前驱结点向前移动M-1位，因为pre本身也算一个 
		for (int j = 1; j < M; j++) {
			pre = circlist.Next(pre);
		}
		cout << "第" << i << "个：" <<circlist.Next(pre)->_data << endl;
		circlist.Remove(pre);
	}
	//输出剩下的人的编号
	cout << "剩下的人编号：";
	circlist.PrintList();
	cout << "\n";
	system("pause");
	return 0;
}