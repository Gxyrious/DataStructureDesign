#pragma once

using namespace std;

class UFSets {
public:
    UFSets(int sz) {
        size = sz;
        parent = new int[size];
        for (int i = 0; i < size; i++) { parent[i] = -1;}//每个自成单元素集合
    }
    int Find(int x) {
        //搜索并返回包含x的树的根
        while (parent[x] >= 0) { x = parent[x]; }
        return x;
    }
    int CollapsingFind(int x) {
        //搜索并返回包含x的树的根，并压缩路径
        int root;
        for (root = x; parent[root] >= 0; root = parent[root]);
        while (x != root) {
            int temp = parent[x];
            parent[x] = root;
            x = temp;
        }
        return root;
    }
    bool Union(int x1,int x2) {
        //合并结点x1与x2所在集合
        int r1 = Find(x1), r2 = Find(x2), temp;
        if (r1 != r2) { temp = parent[r1] + parent[r2]; }
        else { return false; }
        if (parent[r2] < parent[r1]) {
            parent[r1] = r2;
            parent[r2] = temp;//r2数目少，因此r2作为父指针
        }
        else {
            parent[r2] = r1;
            parent[r1] = temp;//r1数目少，因此r1作为父指针
        }
        return true;
    }
private:
    int size;//并查集大小
    int *parent;//集合元素数组
};