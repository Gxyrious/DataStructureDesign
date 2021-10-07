#include"CircList.hpp"

int main() {
	CircList<int> circlist;
	CircLinkNode<int>* pre, * p;
	int N, S, M, K;
	cin >> N >> S >> M >> K;
	for (int i = 1; i <= N; i++) {
		circlist.Insert(i);
	}
	pre = circlist.getNode(S - 1);
	for (int i = 1; i < N - K + 1; i++) {
		for (int j = 1; j < M; j++) {
			pre = circlist.Next(pre);
		}
		p = pre->_next;
		cout << "µÚ" << i << "¸ö£º" << p->_data << endl;
		circlist.Remove(pre);
	}
	circlist.PrintList();
	return 0;
}