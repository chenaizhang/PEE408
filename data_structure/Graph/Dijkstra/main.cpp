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

void Dijkstra(const Graph &G, int startVex, int *dist, int *path) {
    bool final[MAX_VERTEX_NUM];

    for (int i = 0; i < G.vexnum; ++i) {
        final[i] = false;
        dist[i] = G.edge[startVex][i];
        if (i == startVex) path[i] = -1;
        else path[i] = (dist[i] == INF ? -1 : startVex);
    }

    final[startVex] = true;
    dist[startVex] = 0;

    for (int i = 0; i < G.vexnum - 1; ++i) {
        int minLength = INF;
        int minIndex = -1;

        // 找到当前未确定的最短路径顶点
        for (int j = 0; j < G.vexnum; ++j) {
            if (!final[j] && dist[j] < minLength) {
                minLength = dist[j];
                minIndex = j;
            }
        }

        // 剩余顶点都不可达
        if (minIndex == -1) break;

        final[minIndex] = true;

        // 松弛
        for (int j = 0; j < G.vexnum; ++j) {
            if (!final[j] &&
                G.edge[minIndex][j] != INF &&
                dist[minIndex] != INF &&
                dist[j] > dist[minIndex] + G.edge[minIndex][j]) {
                dist[j] = dist[minIndex] + G.edge[minIndex][j];
                path[j] = minIndex;
            }
        }
    }
}

// 递归输出从源点到当前点的路径
void PrintPath(const Graph &G, int *path, int v) {
    if (path[v] == -1) {
        std::cout << G.vex[v];
        return;
    }
    PrintPath(G, path, path[v]);
    std::cout << " -> " << G.vex[v];
}

int main() {
    Graph G;
    G.vexnum = 6;
    G.arcnum = 9;

    // 顶点
    G.vex[0] = 'A';
    G.vex[1] = 'B';
    G.vex[2] = 'C';
    G.vex[3] = 'D';
    G.vex[4] = 'E';
    G.vex[5] = 'F';

    // 初始化邻接矩阵
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = 0; j < G.vexnum; ++j) {
            if (i == j) G.edge[i][j] = 0;
            else G.edge[i][j] = INF;
        }
    }

    // 构造无向带权图
    G.edge[0][1] = G.edge[1][0] = 6;   // A-B
    G.edge[0][2] = G.edge[2][0] = 3;   // A-C
    G.edge[1][2] = G.edge[2][1] = 2;   // B-C
    G.edge[1][3] = G.edge[3][1] = 5;   // B-D
    G.edge[2][3] = G.edge[3][2] = 3;   // C-D
    G.edge[2][4] = G.edge[4][2] = 4;   // C-E
    G.edge[3][4] = G.edge[4][3] = 2;   // D-E
    G.edge[3][5] = G.edge[5][3] = 3;   // D-F
    G.edge[4][5] = G.edge[5][4] = 5;   // E-F

    int dist[MAX_VERTEX_NUM];
    int path[MAX_VERTEX_NUM];

    int startVex = 0; // 从 A 出发
    Dijkstra(G, startVex, dist, path);

    std::cout << "从顶点 " << G.vex[startVex] << " 到各顶点的最短路径如下：\n";

    for (int i = 0; i < G.vexnum; ++i) {
        std::cout << G.vex[startVex] << " -> " << G.vex[i] << " : ";

        if (dist[i] == INF) {
            std::cout << "不可达\n";
        } else {
            std::cout << "最短长度 = " << dist[i] << "，路径 = ";
            PrintPath(G, path, i);
            std::cout << '\n';
        }
    }

    return 0;
}