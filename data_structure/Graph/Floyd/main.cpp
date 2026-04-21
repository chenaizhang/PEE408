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

void Floyd(const Graph &G, int **minLength, int **path){
    for (int i = 0; i < G.vexnum; ++i){
        for (int j = 0; j < G.vexnum; ++j){
            minLength[i][j] = G.edge[i][j];
            path[i][j] = -1;
        }
    }

    for(int k = 0; k < G.vexnum; ++k){
        for (int i = 0; i < G.vexnum; ++i){
            for (int j = 0; j < G.vexnum; ++j){
                if (minLength[i][k] != INF &&
                    minLength[k][j] != INF &&
                    minLength[i][k] + minLength[k][j] < minLength[i][j]){
                    minLength[i][j] = minLength[i][k] + minLength[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
}

// 递归输出 i 到 j 路径中的中间顶点
void PrintPath(const Graph &G, int **path, int i, int j){
    int k = path[i][j];
    if (k == -1) return;
    PrintPath(G, path, i, k);
    std::cout << " -> " << G.vex[k];
    PrintPath(G, path, k, j);
}

int main(){
    Graph G;
    G.vexnum = 4;
    G.arcnum = 5;

    G.vex[0] = 'A';
    G.vex[1] = 'B';
    G.vex[2] = 'C';
    G.vex[3] = 'D';

    // 初始化邻接矩阵
    for (int i = 0; i < G.vexnum; ++i){
        for (int j = 0; j < G.vexnum; ++j){
            if (i == j) G.edge[i][j] = 0;
            else G.edge[i][j] = INF;
        }
    }

    // 构造有向带权图
    G.edge[0][1] = 2;   // A -> B
    G.edge[0][2] = 6;   // A -> C
    G.edge[1][2] = 3;   // B -> C
    G.edge[1][3] = 4;   // B -> D
    G.edge[2][3] = 1;   // C -> D

    // 动态申请二维数组
    int **minLength = new int*[G.vexnum];
    int **path = new int*[G.vexnum];
    for (int i = 0; i < G.vexnum; ++i){
        minLength[i] = new int[G.vexnum];
        path[i] = new int[G.vexnum];
    }

    Floyd(G, minLength, path);

    std::cout << "各顶点之间的最短路径长度矩阵：\n";
    for (int i = 0; i < G.vexnum; ++i){
        for (int j = 0; j < G.vexnum; ++j){
            if (minLength[i][j] == INF) std::cout << "INF\t";
            else std::cout << minLength[i][j] << '\t';
        }
        std::cout << '\n';
    }

    std::cout << "\n具体路径如下：\n";
    for (int i = 0; i < G.vexnum; ++i){
        for (int j = 0; j < G.vexnum; ++j){
            if (i == j) continue;

            std::cout << G.vex[i] << " -> " << G.vex[j] << " : ";
            if (minLength[i][j] == INF){
                std::cout << "不可达\n";
            } else {
                std::cout << "长度 = " << minLength[i][j] << "，路径 = ";
                std::cout << G.vex[i];
                PrintPath(G, path, i, j);
                std::cout << " -> " << G.vex[j] << '\n';
            }
        }
    }

    // 释放空间
    for (int i = 0; i < G.vexnum; ++i){
        delete[] minLength[i];
        delete[] path[i];
    }
    delete[] minLength;
    delete[] path;

    return 0;
}