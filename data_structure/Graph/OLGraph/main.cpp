/*
 * 十字链表图示例。
 * 该文件定义了有向图的十字链表存储结构，便于同时访问入边和出边。
 */
#include <iostream>

constexpr int MaxVertexNum = 100;
using VertexType = char;

struct ArcNode
{
    int tailvex, headvex;
    ArcNode *hlink, *tlink;

    ArcNode(int tv = -1, int hv = -1)
        : tailvex(tv), headvex(hv), hlink(nullptr), tlink(nullptr) {}
};

struct VerNode
{
    VertexType data;
    ArcNode *firstin;
    ArcNode *firstout;

    VerNode() : data(0), firstin(nullptr), firstout(nullptr) {}
};

using OLList = VerNode[MaxVertexNum];

struct OLGraph
{
    OLList vertices;
    int vexnum;
    int arcnum;

    OLGraph() : vexnum(0), arcnum(0) {}
};
