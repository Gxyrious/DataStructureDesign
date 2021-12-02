#include <iostream>
#include<stdlib.h>
#include "MinSpanTree.hpp"

using namespace std;

void PrintInterface() {
	cout << "**        电网建设造价模拟系统        **\n"
		<< "========================================\n"
		<< "**        1 --- 创建电网顶点          **\n"
		<< "**        2 --- 添加电网的边          **\n"
		<< "**        3 --- 构造最小生成树        **\n"
		<< "**        4 --- 显示最小生成树        **\n"
		<< "**        5 --- 退出程序              **\n";
}
int main() {
	
	int operate_num;
	LinkedGraph<int> graph;//邻接表图
	MinSpanTree<int> minspantree;//最小生成树
	PrintInterface();
	while (true) {
		cout << "请选择要进行的操作：";
		cin >> operate_num;
		cout << "\n";

		if (operate_num == 1) {
			cout << "请输入要插入的顶点的个数：";
			int n;
			cin >> n;
			while (n <= 1 || n > graph.getMaxVertices()) {
				cout << "输入有误，请重新输入！\n";
				cin >> n;
			}

			bool b = 1;
			for (int i = 0; i < n; i++) {
				if (!graph.insertVertex(i)) { 
					cout << "顶点"<<i<<"插入失败！\n"; 
					b = 0;
				}
			}
			if (b) {
				cout << "顶点0";
				for (int i = 1; i < n; i++) {
					cout << "、" << i;
				}
				cout << "插入成功！\n";
			}
			cout << "操作1执行完毕！\n";

			graph.insertEdge(1, 2, 7);
			graph.insertEdge(0, 3, 11);
			graph.insertEdge(0, 2, 18);
			graph.insertEdge(2, 3, 5);
			graph.insertEdge(0, 1, 8);
			graph.insertEdge(1, 3, 12);

		}
		else if (operate_num == 2) {
			cout << "请输入两个顶点及边的权重，输入-1 -1 -1结束插入：\n";
			int v1, v2, w;
			cin >> v1 >> v2 >> w;
			while (v1 != -1 || v2 != -1 || w != -1) {
				if (graph.insertEdge(v1, v2, w)) {cout << "插入成功！\n";}
				else { cout << "插入失败，该边已存在！\n"; }
				cin >> v1 >> v2 >> w;
			}
			cout << "操作2执行完毕！\n";
		}
		else if (operate_num == 3) {
			//构造最小生成树
			minspantree.initSize(graph.getNumVertices());
			if (minspantree.Kruskal(graph)) { cout << "最小生成树构造成功！\n"; }
			else { cout << "最小生成树构造失败，图不连通！\n"; }
		}
		else if (operate_num == 4) {
			//显示最小生成树
			if (!minspantree.PrintMST()) { cout << "请先生成最小生成树！\n"; }
			
		}
		else if (operate_num == 5) {
			//退出程序
			break;
		}
		else {
			cout << "操作数输入有误，请重新输入\n";
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