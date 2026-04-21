#include <iostream>
#include <climits>
#include <algorithm>

#define MAX_VERTEX_NUM 100
#define INF INT_MAX

using VertexType = char;

typedef struct Graph {
    VertexType vex[MAX_VERTEX_NUM];
    int edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;
} Graph;

typedef struct {
    int u, v;
    int w;
} Edge;

// 并查集查找
int Find(int parent[], int x) {
    while (parent[x] >= 0) {
        x = parent[x];
    }
    return x;
}

// 并查集合并（按集合大小合并）
void Union(int parent[], int x, int y) {
    int rx = Find(parent, x);
    int ry = Find(parent, y);

    if (rx == ry) return;

    // parent[root] 存负数，绝对值表示集合大小
    if (parent[rx] <= parent[ry]) {   // rx 集合更大
        parent[rx] += parent[ry];
        parent[ry] = rx;
    } else {
        parent[ry] += parent[rx];
        parent[rx] = ry;
    }
}

void Kruskal(const Graph &G, Graph &T) {

    // 1. 初始化 T
    T.vexnum = G.vexnum;
    T.arcnum = 0;
    for (int i = 0; i < G.vexnum; ++i) {
        T.vex[i] = G.vex[i];
        for (int j = 0; j < G.vexnum; ++j) {
            if (i == j) T.edge[i][j] = 0;
            else T.edge[i][j] = INF;
        }
    }

    // 2. 提取所有边
    Edge edges[MAX_VERTEX_NUM * MAX_VERTEX_NUM];
    int edgeCount = 0;

    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = i + 1; j < G.vexnum; ++j) {   // 无向图只取一半
            if (G.edge[i][j] != INF && G.edge[i][j] != 0) {
                edges[edgeCount].u = i;
                edges[edgeCount].v = j;
                edges[edgeCount].w = G.edge[i][j];
                ++edgeCount;
            }
        }
    }

    // 3. 按边权从小到大排序
    std::sort(edges, edges + edgeCount, [](const Edge &a, const Edge &b) {
        return a.w < b.w;
    });

    // 4. 初始化并查集
    int parent[MAX_VERTEX_NUM];
    for (int i = 0; i < G.vexnum; ++i) {
        parent[i] = -1;
    }

    // 5. 依次考察最小边
    int chosen = 0;
    for (int i = 0; i < edgeCount && chosen < G.vexnum - 1; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;

        if (Find(parent, u) != Find(parent, v)) {
            Union(parent, u, v);

            T.edge[u][v] = edges[i].w;
            T.edge[v][u] = edges[i].w;
            T.arcnum++;
            chosen++;
        }
    }

    // 6. 判断是否生成成功
    if (chosen < G.vexnum - 1) {
        std::cerr << "该图不是连通图，无法构造最小生成树" << std::endl;
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

    Kruskal(G, T);

    std::cout << "最小生成树的邻接矩阵：" << std::endl;
    PrintGraph(T);

    return 0;
}