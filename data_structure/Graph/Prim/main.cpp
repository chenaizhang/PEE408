#include <iostream>
#include <climits>

#define MAX_VERTEX_NUM 100
#define INF INT_MAX

using VertexType = char;

typedef struct Graph {
    VertexType vex[MAX_VERTEX_NUM];
    int edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;
} Graph;

// 构造最小生成树 T
void Prim(const Graph &G, Graph &T, int startVex) {
    if (startVex < 0 || startVex >= G.vexnum) {
        std::cerr << "startVex 越界" << std::endl;
        return;
    }

    // 初始化最小生成树 T
    T.vexnum = G.vexnum;
    T.arcnum = 0;
    for (int i = 0; i < G.vexnum; ++i) {
        T.vex[i] = G.vex[i];
        for (int j = 0; j < G.vexnum; ++j) {
            if (i == j) T.edge[i][j] = 0;
            else T.edge[i][j] = INF;
        }
    }

    bool isJoin[MAX_VERTEX_NUM] = {false};
    int lowCost[MAX_VERTEX_NUM];
    int adjVex[MAX_VERTEX_NUM];

    // 初始化辅助数组
    for (int i = 0; i < G.vexnum; ++i) {
        lowCost[i] = G.edge[startVex][i];
        adjVex[i] = startVex;
    }

    isJoin[startVex] = true;
    lowCost[startVex] = 0;   // 已加入生成树的点，lowCost 可置 0

    // 还要加入 G.vexnum - 1 个顶点
    for (int i = 0; i < G.vexnum - 1; ++i) {
        int minCost = INF;
        int k = -1;

        // 1. 选出当前未加入、且 lowCost 最小的顶点 k
        for (int j = 0; j < G.vexnum; ++j) {
            if (!isJoin[j] && lowCost[j] < minCost) {
                minCost = lowCost[j];
                k = j;
            }
        }

        // 图不连通
        if (k == -1) {
            std::cerr << "该图不是连通图，无法构造最小生成树" << std::endl;
            return;
        }

        // 2. 将边 (adjVex[k], k) 加入最小生成树
        T.edge[adjVex[k]][k] = G.edge[adjVex[k]][k];
        T.edge[k][adjVex[k]] = G.edge[k][adjVex[k]];
        T.arcnum++;

        isJoin[k] = true;
        lowCost[k] = 0;

        // 3. 用新加入的顶点 k 更新其余顶点的 lowCost 和 adjVex
        for (int j = 0; j < G.vexnum; ++j) {
            if (!isJoin[j] && G.edge[k][j] < lowCost[j]) {
                lowCost[j] = G.edge[k][j];
                adjVex[j] = k;
            }
        }
    }
}

// 输出邻接矩阵
void PrintGraph(const Graph &G) {
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = 0; j < G.vexnum; ++j) {
            if (G.edge[i][j] == INF) std::cout << "INF ";
            else std::cout << G.edge[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    Graph G, T;
    G.vexnum = 5;
    G.arcnum = 7;

    G.vex[0] = 'A';
    G.vex[1] = 'B';
    G.vex[2] = 'C';
    G.vex[3] = 'D';
    G.vex[4] = 'E';

    // 初始化邻接矩阵
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = 0; j < G.vexnum; ++j) {
            if (i == j) G.edge[i][j] = 0;
            else G.edge[i][j] = INF;
        }
    }

    // 无向图加边
    G.edge[0][1] = G.edge[1][0] = 2; // A-B
    G.edge[0][3] = G.edge[3][0] = 6; // A-D
    G.edge[1][2] = G.edge[2][1] = 3; // B-C
    G.edge[1][3] = G.edge[3][1] = 8; // B-D
    G.edge[1][4] = G.edge[4][1] = 5; // B-E
    G.edge[2][4] = G.edge[4][2] = 7; // C-E
    G.edge[3][4] = G.edge[4][3] = 9; // D-E

    Prim(G, T, 0);

    std::cout << "最小生成树的邻接矩阵：" << std::endl;
    PrintGraph(T);

    return 0;
}