#include <iostream>
#include<stdlib.h>
#include "MinSpanTree.hpp"

using namespace std;

void PrintInterface() {
	cout << "**        �����������ģ��ϵͳ        **\n"
		<< "========================================\n"
		<< "**        1 --- ������������          **\n"
		<< "**        2 --- ��ӵ����ı�          **\n"
		<< "**        3 --- ������С������        **\n"
		<< "**        4 --- ��ʾ��С������        **\n"
		<< "**        5 --- �˳�����              **\n";
}
int main() {
	
	int operate_num;
	LinkedGraph<int> graph;//�ڽӱ�ͼ
	MinSpanTree<int> minspantree;//��С������
	PrintInterface();
	while (true) {
		cout << "��ѡ��Ҫ���еĲ�����";
		cin >> operate_num;
		cout << "\n";

		if (operate_num == 1) {
			cout << "������Ҫ����Ķ���ĸ�����";
			int n;
			cin >> n;
			while (n <= 1 || n > graph.getMaxVertices()) {
				cout << "�����������������룡\n";
				cin >> n;
			}

			bool b = 1;
			for (int i = 0; i < n; i++) {
				if (!graph.insertVertex(i)) { 
					cout << "����"<<i<<"����ʧ�ܣ�\n"; 
					b = 0;
				}
			}
			if (b) {
				cout << "����0";
				for (int i = 1; i < n; i++) {
					cout << "��" << i;
				}
				cout << "����ɹ���\n";
			}
			cout << "����1ִ����ϣ�\n";

			graph.insertEdge(1, 2, 7);
			graph.insertEdge(0, 3, 11);
			graph.insertEdge(0, 2, 18);
			graph.insertEdge(2, 3, 5);
			graph.insertEdge(0, 1, 8);
			graph.insertEdge(1, 3, 12);

		}
		else if (operate_num == 2) {
			cout << "�������������㼰�ߵ�Ȩ�أ�����-1 -1 -1�������룺\n";
			int v1, v2, w;
			cin >> v1 >> v2 >> w;
			while (v1 != -1 || v2 != -1 || w != -1) {
				if (graph.insertEdge(v1, v2, w)) {cout << "����ɹ���\n";}
				else { cout << "����ʧ�ܣ��ñ��Ѵ��ڣ�\n"; }
				cin >> v1 >> v2 >> w;
			}
			cout << "����2ִ����ϣ�\n";
		}
		else if (operate_num == 3) {
			//������С������
			minspantree.initSize(graph.getNumVertices());
			if (minspantree.Kruskal(graph)) { cout << "��С����������ɹ���\n"; }
			else { cout << "��С����������ʧ�ܣ�ͼ����ͨ��\n"; }
		}
		else if (operate_num == 4) {
			//��ʾ��С������
			if (!minspantree.PrintMST()) { cout << "����������С��������\n"; }
			
		}
		else if (operate_num == 5) {
			//�˳�����
			break;
		}
		else {
			cout << "������������������������\n";
		}
	}

	/*for (int i = 0; i < 5; i++) {
		graph.insertVertex(i);
	}
	cout << graph.insertEdge(0, 1, 1) << " ";
	cout << graph.insertEdge(0, 3, 1) << " ";
	cout << graph.insertEdge(1, 2, 1) << " ";
	cout << graph.insertEdge(2, 3, 1) << " ";
	cout << graph.insertEdge(3, 4, 1) << " ";
	cout << graph.insertEdge(4, 0, 1) << " ";
	cout << graph.insertEdge(4, 0, 1) << " ";
	cout << graph.removeEdge(0, 4) << " ";
	cout << graph.removeEdge(0, 4) << "\n";
	cout << graph.insertEdge(4, 0, 1) << " ";
	cout << graph.insertEdge(4, 0, 1) << " ";*/

	//srand((unsigned)time(NULL));
	//MinHeap<int> heap(100);
	//for (int i = 0; i < 100; i++) {
	//	heap.Insert(rand());
	//}
	//for (int i = 0; i < 110; i++) {
	//	int x;
	//	heap.RemoveMin(x);
	//	cout << x << " ";
	//}

	system("pause");
	return 0;
}