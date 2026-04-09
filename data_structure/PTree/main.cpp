#include <iostream>

#define MAX_TREE_SIZE 100

using ElemType = int;

typedef struct {
    ElemType data;
    int parent;   // 根结点存负的集合大小；非根结点存双亲下标
} PTNode;

typedef struct {
    PTNode nodes[MAX_TREE_SIZE];
    int n;
} PTtree;

void Initial(PTtree &S, int n) {
    S.n = n;
    for (int i = 0; i < n; i++) {
        S.nodes[i].parent = -1;
    }
}

int Find(PTtree &S, int x) {
    if (x < 0 || x >= S.n) {
        std::cerr << "wrong index!" << std::endl;
        return -1;
    }

    if (S.nodes[x].parent < 0) return x;

    // 路径压缩
    return S.nodes[x].parent = Find(S, S.nodes[x].parent);
}

void Union(PTtree &S, int n1, int n2) {
    int R1 = Find(S, n1);
    int R2 = Find(S, n2);

    if (R1 == -1 || R2 == -1) return;
    if (R1 == R2) return;

    // 按集合大小合并：小树挂到大树上
    if (S.nodes[R1].parent > S.nodes[R2].parent) {
        S.nodes[R2].parent += S.nodes[R1].parent;
        S.nodes[R1].parent = R2;
    } else {
        S.nodes[R1].parent += S.nodes[R2].parent;
        S.nodes[R2].parent = R1;
    }
}

int main() {
    PTtree S;
    Initial(S, 5);

    Union(S, 0, 1);
    Union(S, 2, 3);
    Union(S, 1, 2);

    for (int i = 0; i < S.n; i++) {
        std::cout << "nodes[" << i << "].parent = " << S.nodes[i].parent << std::endl;
    }

    return 0;
}