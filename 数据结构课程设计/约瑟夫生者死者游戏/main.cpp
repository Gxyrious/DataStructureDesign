#include"CircList.hpp"

int main() {
	CircList<int> circlist;
	CircLinkNode<int>* pre;
	int N, S, M, K;
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
		cout << "第" << i << "个：" << pre->_next->_data << endl;
		circlist.Remove(pre);
	}
	//输出剩下的人的编号
	cout << "剩下的人编号：";
	circlist.PrintList();
	return 0;
}