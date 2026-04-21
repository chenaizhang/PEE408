#include <iostream>
using namespace std;

#define MAX_VERTEX_NUM 100

// ---------------- 图的定义（邻接矩阵） ----------------
typedef char VertexType;

typedef struct {
    VertexType vex[MAX_VERTEX_NUM];               // 顶点表
    int edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM];     // 邻接矩阵，1表示有边，0表示无边
    int vexnum, arcnum;                           // 顶点数、边数
} Graph;

// ---------------- 队列定义（循环队列） ----------------
typedef struct {
    int data[MAX_VERTEX_NUM];
    int front, rear;
} SqQueue;

void InitQueue(SqQueue &Q) {
    Q.front = Q.rear = 0;
}

bool isEmpty(SqQueue Q) {
    return Q.front == Q.rear;
}

bool EnQueue(SqQueue &Q, int x) {
    if ((Q.rear + 1) % MAX_VERTEX_NUM == Q.front) {
        return false; // 队满
    }
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MAX_VERTEX_NUM;
    return true;
}

bool DeQueue(SqQueue &Q, int &x) {
    if (isEmpty(Q)) {
        return false; // 队空
    }
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MAX_VERTEX_NUM;
    return true;
}

// ---------------- 访问标记数组 ----------------
bool visited[MAX_VERTEX_NUM] = {false};

// ---------------- 访问函数 ----------------
void visit(Graph G, int v) {
    cout << G.vex[v] << " ";
}

// ---------------- 找邻接点 ----------------
int FirstNeighbor(Graph G, int v) {
    for (int i = 0; i < G.vexnum; ++i) {
        if (G.edge[v][i] != 0) {
            return i;
        }
    }
    return -1;
}

int NextNeighbor(Graph G, int v, int w) {
    for (int i = w + 1; i < G.vexnum; ++i) {
        if (G.edge[v][i] != 0) {
            return i;
        }
    }
    return -1;
}

// ---------------- BFS ----------------
void BFS(Graph G, int v) {
    SqQueue Q;
    InitQueue(Q);

    visit(G, v);
    visited[v] = true;
    EnQueue(Q, v);

    while (!isEmpty(Q)) {
        int u;
        DeQueue(Q, u);

        for (int w = FirstNeighbor(G, u); w >= 0; w = NextNeighbor(G, u, w)) {
            if (!visited[w]) {
                visit(G, w);
                visited[w] = true;
                EnQueue(Q, w);
            }
        }
    }
}

// ---------------- 遍历非连通图 ----------------
void BFSTraverse(Graph G) {
    for (int i = 0; i < G.vexnum; ++i) {
        visited[i] = false;
    }

    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i]) {
            BFS(G, i);
        }
    }
}

// ---------------- 主函数测试 ----------------
int main() {
    Graph G;

    G.vexnum = 5;
    G.arcnum = 5;

    // 顶点
    G.vex[0] = 'A';
    G.vex[1] = 'B';
    G.vex[2] = 'C';
    G.vex[3] = 'D';
    G.vex[4] = 'E';

    // 初始化邻接矩阵
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = 0; j < G.vexnum; ++j) {
            G.edge[i][j] = 0;
        }
    }

    // 无向图加边
    G.edge[0][1] = G.edge[1][0] = 1; // A-B
    G.edge[0][2] = G.edge[2][0] = 1; // A-C
    G.edge[1][3] = G.edge[3][1] = 1; // B-D
    G.edge[2][4] = G.edge[4][2] = 1; // C-E
    G.edge[3][4] = G.edge[4][3] = 1; // D-E

    cout << "BFS遍历结果：";
    BFSTraverse(G);
    cout << endl;

    return 0;
}