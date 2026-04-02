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