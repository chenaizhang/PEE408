#include <iostream>
#include <stack>

#define MaxVertexNum 100

using VertexType = char;

typedef struct ArcNode {
    int adjvex;              // 该边指向的顶点下标
    struct ArcNode *nextarc; // 指向下一条边
} ArcNode;

typedef struct VNode {
    VertexType data;         // 顶点信息
    ArcNode *firstarc;       // 第一条边
} VNode, AdjList[MaxVertexNum];

typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
} ALGraph, Graph;

// 初始化图
void InitGraph(Graph &G, int vexnum) {
    G.vexnum = vexnum;
    G.arcnum = 0;
    for (int i = 0; i < vexnum; ++i) {
        G.vertices[i].firstarc = nullptr;
        G.vertices[i].data = 'A' + i; // 默认顶点名 A, B, C...
    }
}

// 加一条有向边 v -> w
void AddEdge(Graph &G, int v, int w) {
    ArcNode *p = new ArcNode;
    p->adjvex = w;
    p->nextarc = G.vertices[v].firstarc;
    G.vertices[v].firstarc = p;
    G.arcnum++;
}

// 拓扑排序
bool TopologicalSort(const Graph &G) {
    int indegree[MaxVertexNum] = {0};
    int topoOrder[MaxVertexNum];

    // 统计各顶点入度
    for (int i = 0; i < G.vexnum; ++i) {
        for (ArcNode *p = G.vertices[i].firstarc; p != nullptr; p = p->nextarc) {
            indegree[p->adjvex]++;
        }
    }

    std::stack<int> S;

    // 入度为 0 的点入栈
    for (int i = 0; i < G.vexnum; ++i) {
        if (indegree[i] == 0) {
            S.push(i);
        }
    }

    int count = 0;

    while (!S.empty()) {
        int i = S.top();
        S.pop();

        topoOrder[count++] = i;

        for (ArcNode *p = G.vertices[i].firstarc; p != nullptr; p = p->nextarc) {
            int v = p->adjvex;
            if (--indegree[v] == 0) {
                S.push(v);
            }
        }
    }

    if (count < G.vexnum) {
        return false; // 有回路
    } else {
        std::cout << "拓扑排序结果：";
        for (int i = 0; i < count; ++i) {
            std::cout << G.vertices[topoOrder[i]].data << " ";
        }
        std::cout << std::endl;
        return true;
    }
}

// 释放邻接表空间
void DestroyGraph(Graph &G) {
    for (int i = 0; i < G.vexnum; ++i) {
        ArcNode *p = G.vertices[i].firstarc;
        while (p != nullptr) {
            ArcNode *temp = p;
            p = p->nextarc;
            delete temp;
        }
        G.vertices[i].firstarc = nullptr;
    }
}

int main() {
    Graph G;
    InitGraph(G, 6);

    // 构造一个 DAG
    // A -> C
    // A -> D
    // B -> C
    // B -> E
    // C -> F
    // D -> F
    // E -> F
    AddEdge(G, 0, 2); // A -> C
    AddEdge(G, 0, 3); // A -> D
    AddEdge(G, 1, 2); // B -> C
    AddEdge(G, 1, 4); // B -> E
    AddEdge(G, 2, 5); // C -> F
    AddEdge(G, 3, 5); // D -> F
    AddEdge(G, 4, 5); // E -> F

    if (!TopologicalSort(G)) {
        std::cout << "该有向图存在回路，无法进行拓扑排序。" << std::endl;
    }

    DestroyGraph(G);
    return 0;
}