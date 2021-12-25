#include <iostream>
#include "MinSpanTree.hpp"

using namespace std;

void PrintInterface() {
	cout << "**        �����������ģ��ϵͳ        **\n"
		<< "========================================\n"
		<< "**        1 --- ������������          **\n"
		<< "**        2 --- ��ӵ����ı�          **\n"
		<< "**        3 --- ������С������        **\n"
		<< "**        4 --- ɾ����                **\n"
		<< "**        5 --- ɾ������              **\n"
		<< "**        6 --- ��ӱ�                **\n"
		<< "**        7 --- ��Ӷ���              **\n"
		<< "**        8 --- �˳�����              **\n";
}
int main() {
	int operate_num;
	LinkedGraph<int, char> graph(-1,'\0');//�ڽӱ�ͼ
	MinSpanTree<int, char> minspantree;//��С������
	PrintInterface();//��ӡ��ʾ��
	while (true) {
		cout << "��ѡ��Ҫ���еĲ�����";
		cin >> operate_num;
		if (operate_num == 1) {
			cout << "������Ҫ����Ķ���ĸ�����";
			int n;
			cin >> n;
			while (n < 1 || n > graph.getMaxVertices()) {
				cout << "�����������������룡\n";
				cin >> n;
			}
			cout << "���������붥�����ƣ�\n";
			bool flag = 1;
			for (int i = 1; i <= n; i++) {
				char name;
				cin >> name;
				if (!graph.insertVertex(name)) {
					cout << i << "�Ŷ���" << name << "����ʧ�ܣ�\n";
					flag = 0;
				}
			}
			if (flag) { cout << "����ɹ���"; }
			cout << "����1ִ����ϣ�\n";
		}
		else if (operate_num == 2) {
			cout << "���������������ֵ���ߵ�Ȩ�أ�����0 0 0�������룺\n";
			char v1, v2;
			int weight;
			cin >> v1 >> v2 >> weight;
			while (v1 != '0' || v2 != '0' || weight != 0) {
				if (graph.insertEdge(v1, v2, weight)) { cout << "����ɹ���\n"; }
				else { cout << "����ʧ�ܣ��ñ��Ѵ��ڣ�\n"; }
				cin >> v1 >> v2 >> weight;
			}
			cout << "����2ִ����ϣ�\n";
		}
		else if (operate_num == 3) {
			//������С������
			minspantree.initSize(graph.getNumVertices());
			if (minspantree.createMinSpanTree(graph)) { cout << "��С����������ɹ�����ӡ����\n"; }
			else { cout << "��С����������ʧ�ܣ�ͼ����ͨ��\n"; }
		}
		else if (operate_num == 4) {
			//ɾ����
			cout << "������Ҫɾ���ıߵ���������ֵ\n";
			char v1, v2;
			cin >> v1 >> v2;
			if (graph.removeEdge(v1, v2)) { cout << "ɾ���ɹ���\n"; }
			else { cout << "ɾ��ʧ�ܣ��ñ߲����ڣ�\n"; }
		}
		else if (operate_num == 5) {
			//ɾ������
			cout << "������Ҫɾ���Ķ���ֵ\n";
			char v;
			cin >> v;
			if (graph.removeVertex(v)) { cout << "ɾ���ɹ���\n"; }
			else { cout << "ɾ��ʧ�ܣ��ö��㲻���ڣ�\n"; }
		}
		else if (operate_num == 6) {
			//��ӱ�
			cout << "������Ҫ��ӵıߵ������������ƣ��Լ��ߵ�Ȩֵ\n";
			char v1, v2;
			int weight;
			cin >> v1 >> v2 >> weight;
			if (graph.insertEdge(v1, v2, weight)) { cout << "��ӳɹ���\n"; }
			else { cout << "���ʧ�ܣ����㲻���ڣ�\n"; }
		}
		else if (operate_num == 7) {
			//��ӽ��
			cout << "������Ҫ��ӵĽ���ֵ\n";
			char v;
			cin >> v;
			if (graph.insertVertex(v)) { cout << "��ӳɹ���\n"; }
			else { cout << "����ʧ�ܣ�����ͼ�Ƿ����������ֵ�Ѿ����ڣ�\n"; }
		}
		else if (operate_num == 8) {
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