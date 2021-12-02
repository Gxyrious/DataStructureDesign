#pragma once
#include <iostream>

using namespace std;

//const int DefaultSize = 10;

class UFSets {
public:
    UFSets(int sz) {
        size = sz;
        parent = new int[size];
        for (int i = 0; i < size; i++) { parent[i] = -1;}//每个自成单元素集合
    }
    int Find(int x) {
        //搜索并返回包含x的树的根
        while (parent[x] > 0) { x = parent[x]; }
        return x;
    }
    bool Union(int root1,int root2) {
        int r1 = Find(root1), r2 = Find(root2), temp;
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
    int CollapsingFind(int i) {
        int root;
        for (root = i; parent[root] >= 0; root = parent[root]);
        while (i != root) {
            int temp = parent[i];
            parent[i] = root;
            i = temp;
        }
        return root;
    }
private:
    int size;//并查集大小
    int *parent;//集合元素数组
};