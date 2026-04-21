#include <iostream>
using namespace std;

#define MAX_VERTEX_NUM 100

bool visited[MAX_VERTEX_NUM] = {false};

// ---------- 图的定义（这里用邻接矩阵示例） ----------
typedef char VertexType;

typedef struct {
    VertexType vex[MAX_VERTEX_NUM];
    int edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;
} Graph;

// ---------- 访问函数 ----------
void visit(Graph G, int v) {
    cout << G.vex[v] << " ";
}

// ---------- 找第一个邻接点 ----------
int FirstNeighbor(Graph G, int v) {
    for (int i = 0; i < G.vexnum; ++i) {
        if (G.edge[v][i] != 0) return i;
    }
    return -1;
}

// ---------- 找下一个邻接点 ----------
int NextNeighbor(Graph G, int v, int w) {
    for (int i = w + 1; i < G.vexnum; ++i) {
        if (G.edge[v][i] != 0) return i;
    }
    return -1;
}

// ---------- DFS ----------
void DFS(Graph G, int v) {
    visit(G, v);
    visited[v] = true;

    for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)) {
        if (!visited[w]) {
            DFS(G, w);
        }
    }
}

// ---------- 遍历整个图（处理非连通图） ----------
void DFSTraverse(Graph G) {
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = false;
    }

    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i]) {
            DFS(G, i);
        }
    }
}

int main() {
    Graph G;
    G.vexnum = 5;
    G.arcnum = 4;

    G.vex[0] = 'A';
    G.vex[1] = 'B';
    G.vex[2] = 'C';
    G.vex[3] = 'D';
    G.vex[4] = 'E';

    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = 0; j < G.vexnum; ++j) {
            G.edge[i][j] = 0;
        }
    }

    // 无向图
    G.edge[0][1] = G.edge[1][0] = 1; // A-B
    G.edge[0][2] = G.edge[2][0] = 1; // A-C
    G.edge[1][3] = G.edge[3][1] = 1; // B-D
    G.edge[2][4] = G.edge[4][2] = 1; // C-E

    cout << "DFS遍历结果: ";
    DFSTraverse(G);
    cout << endl;

    return 0;
}