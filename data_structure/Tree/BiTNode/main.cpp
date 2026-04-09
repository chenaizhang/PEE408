/*
 * 二叉链表结点示例。
 * 该文件演示二叉树结点的定义以及根结点的动态创建方式。
 */
#include <stdlib.h>


typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

int main(){
    BiTree root = nullptr;

    root = (BiTNode*)malloc(sizeof(BiTNode));
    root->data = {1};
    root->lchild = nullptr;
    root->rchild = nullptr;

}
