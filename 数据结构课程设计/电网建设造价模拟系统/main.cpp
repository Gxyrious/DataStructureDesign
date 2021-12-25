#include <iostream>
#include "MinSpanTree.hpp"

using namespace std;

void PrintInterface() {
	cout << "**        电网建设造价模拟系统        **\n"
		<< "========================================\n"
		<< "**        1 --- 创建电网顶点          **\n"
		<< "**        2 --- 添加电网的边          **\n"
		<< "**        3 --- 构造最小生成树        **\n"
		<< "**        4 --- 删除边                **\n"
		<< "**        5 --- 删除顶点              **\n"
		<< "**        6 --- 添加边                **\n"
		<< "**        7 --- 添加顶点              **\n"
		<< "**        8 --- 退出程序              **\n";
}
int main() {
	int operate_num;
	LinkedGraph<int, char> graph(-1,'\0');//邻接表图
	MinSpanTree<int, char> minspantree;//最小生成树
	PrintInterface();//打印提示词
	while (true) {
		cout << "请选择要进行的操作：";
		cin >> operate_num;
		if (operate_num == 1) {
			cout << "请输入要插入的顶点的个数：";
			int n;
			cin >> n;
			while (n < 1 || n > graph.getMaxVertices()) {
				cout << "输入有误，请重新输入！\n";
				cin >> n;
			}
			cout << "请依次输入顶点名称：\n";
			bool flag = 1;
			for (int i = 1; i <= n; i++) {
				char name;
				cin >> name;
				if (!graph.insertVertex(name)) {
					cout << i << "号顶点" << name << "插入失败！\n";
					flag = 0;
				}
			}
			if (flag) { cout << "插入成功！"; }
			cout << "操作1执行完毕！\n";
		}
		else if (operate_num == 2) {
			cout << "请输入两个顶点的值及边的权重，输入0 0 0结束插入：\n";
			char v1, v2;
			int weight;
			cin >> v1 >> v2 >> weight;
			while (v1 != '0' || v2 != '0' || weight != 0) {
				if (graph.insertEdge(v1, v2, weight)) { cout << "插入成功！\n"; }
				else { cout << "插入失败，该边已存在！\n"; }
				cin >> v1 >> v2 >> weight;
			}
			cout << "操作2执行完毕！\n";
		}
		else if (operate_num == 3) {
			//构造最小生成树
			minspantree.initSize(graph.getNumVertices());
			if (minspantree.createMinSpanTree(graph)) { cout << "最小生成树构造成功！打印如上\n"; }
			else { cout << "最小生成树构造失败，图不连通！\n"; }
		}
		else if (operate_num == 4) {
			//删除边
			cout << "请输入要删除的边的两个顶点值\n";
			char v1, v2;
			cin >> v1 >> v2;
			if (graph.removeEdge(v1, v2)) { cout << "删除成功！\n"; }
			else { cout << "删除失败，该边不存在！\n"; }
		}
		else if (operate_num == 5) {
			//删除顶点
			cout << "请输入要删除的顶点值\n";
			char v;
			cin >> v;
			if (graph.removeVertex(v)) { cout << "删除成功！\n"; }
			else { cout << "删除失败，该顶点不存在！\n"; }
		}
		else if (operate_num == 6) {
			//添加边
			cout << "请输入要添加的边的两个顶点名称，以及边的权值\n";
			char v1, v2;
			int weight;
			cin >> v1 >> v2 >> weight;
			if (graph.insertEdge(v1, v2, weight)) { cout << "添加成功！\n"; }
			else { cout << "添加失败，顶点不存在！\n"; }
		}
		else if (operate_num == 7) {
			//添加结点
			cout << "请输入要添加的结点的值\n";
			char v;
			cin >> v;
			if (graph.insertVertex(v)) { cout << "添加成功！\n"; }
			else { cout << "插入失败，请检查图是否已满或添加值已经存在！\n"; }
		}
		else if (operate_num == 8) {
			//退出程序
			break;
		}
		else {
			cout << "操作数输入有误，请重新输入\n";
		}
	}
	system("pause");
	return 0;
}