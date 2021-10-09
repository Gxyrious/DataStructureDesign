#include"CircList.hpp"

int main() {
	CircList<int> circlist;
	CircLinkNode<int>* pre;
	int N, S, M, K;
	cin >> N >> S >> M >> K;

	//���β���N����
	for (int i = 1; i <= N; i++) {
		circlist.Insert(i);
	}

	//��ȡ��S-1���ˣ���Ϊǰ�����pre
	pre = circlist.getNode(S - 1);

	//һ��N���ˣ�Ҫʣ��K���ˣ����Թ���Ҫѡ��N-K+1����
	for (int i = 1; i < N - K + 1; i++) {
		//ÿ����ǰ�������ǰ�ƶ�M-1λ����Ϊpre����Ҳ��һ�� 
		for (int j = 1; j < M; j++) {
			pre = circlist.Next(pre);
		}
		cout << "��" << i << "����" << pre->_next->_data << endl;
		circlist.Remove(pre);
	}
	//���ʣ�µ��˵ı��
	cout << "ʣ�µ��˱�ţ�";
	circlist.PrintList();
	return 0;
}