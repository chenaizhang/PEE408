/*
 * 邻接表图示例。
 * 该文件定义了顶点结点、边结点以及邻接表图的基本存储结构。
 */
#include <iostream>

#define MaxVertexNum 100

using VertexType = char;

typedef struct ArcNode
{
    int  adjvex;
    struct ArcNode *nextarc;
    // InfoType info;
}ArcNode;

typedef struct VNode
{
    VertexType data;
    ArcNode *firstarc;
}VNode, AdjList[MaxVertexNum];

typedef struct
{
    AdjList vertices;
    int vexnum, arcnum;
}ALGraph;
