/*
 * 邻接矩阵图示例。
 * 该文件使用数组和二维矩阵描述图的顶点集合与边关系。
 */
#include <iostream>

#define MaxVertexNum 100

using VertexType = char;
using EdgeType = int;

typedef struct
{
    VertexType Vex[MaxVertexNum];
    EdgeType Edge[MaxVertexNum][MaxVertexNum];
    int vexnum, arcnum;
}MGragh;

