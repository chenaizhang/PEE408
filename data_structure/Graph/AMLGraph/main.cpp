/*
 * 邻接多重表图示例。
 * 该文件仅定义无向图的邻接多重表存储结构。
 */

constexpr int MaxVertexNum = 100;

using VertexType = char;

typedef struct EBox
{
    bool mark;
    int ivex, jvex;
    struct EBox *ilink, *jlink;
} EBox;

typedef struct VexBox
{
    VertexType data;
    EBox *firstedge;
} VexBox, AdjMulist[MaxVertexNum];

typedef struct
{
    AdjMulist vertices;
    int vexnum, edgenum;
} AMLGraph;
