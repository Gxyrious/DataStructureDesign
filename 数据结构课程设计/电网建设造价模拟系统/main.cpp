#include <iostream>
//#include <stdlib.h>
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
	LinkedGraph<int,char> graph;//�ڽӱ�ͼ
	MinSpanTree<int,char> minspantree;//��С������
	PrintInterface();//��ӡ��ʾ��
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

			for (int i = 0; i < n; i++) {
				cout << "���������붥�����ƣ�\n";
				char name;
				cin >> name;
				if (!graph.insertVertex(name)) {
					cout << i << "����" << name << " ����ʧ�ܣ�\n";
				}
				else { cout << "����ɹ���\n"; }
			}
			cout << "����1ִ����ϣ�\n";

			graph.insertEdge(0, 2, 1);
			graph.insertEdge(0, 1, 6);
			graph.insertEdge(0, 3, 5);
			graph.insertEdge(1, 2, 5);
			graph.insertEdge(2, 3, 5);
			graph.insertEdge(1, 4, 3);
			graph.insertEdge(2, 4, 6);
			graph.insertEdge(5, 4, 6);
			graph.insertEdge(5, 2, 4);
			graph.insertEdge(5, 3, 2);

		}
		else if (operate_num == 2) {
			cout << "�������������㼰�ߵ�Ȩ�أ�����-1 -1 -1�������룺\n";
			int v1, v2, w;
			cin >> v1 >> v2 >> w;
			while (v1 != -1 || v2 != -1 || w != -1) {
				if (graph.insertEdge(v1, v2, w)) { cout << "����ɹ���\n"; }
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
			if (!minspantree.PrintMST(graph)) { cout << "����������С��������\n"; }
		}
		else if (operate_num == 5) {
			//�˳�����
			break;
		}
		else {
			cout << "������������������������\n";
		}
	}
	system("pause");
	return 0;
}