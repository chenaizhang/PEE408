#include <iostream>

using ElemType = int;

typedef struct ThreadNode
{
    ElemType data;
    struct ThreadNode *lchild = nullptr, *rchild = nullptr;
    bool ltag = false, rtag = false;
} ThreadNode, *ThreadTree;

void InThread(ThreadTree p, ThreadNode *&pre) {
    if (p != nullptr) {
        InThread(p->lchild, pre);

        if (p->lchild == nullptr) {
            p->lchild = pre;
            p->ltag = true;
        }
        if (pre != nullptr && pre->rchild == nullptr) {
            pre->rchild = p;
            pre->rtag = true;
        }
        pre = p;

        InThread(p->rchild, pre);
    }
}

void CreateInThread(ThreadTree T) {
    ThreadNode *pre = nullptr;
    if (T != nullptr) {
        InThread(T, pre);
        if (pre->rchild == nullptr) {
            pre->rtag = true;
        }
    }
}

ThreadNode *FirstNode(ThreadNode *p){
    if (p == nullptr) return nullptr;
    while (p->ltag == false){
        p = p->lchild;
    }
    return p;
}

ThreadNode *LastNode(ThreadNode *p){
    if (p == nullptr) return nullptr;
    while (p->rtag == false){
        p = p->rchild;
    }
    return p;
}

ThreadNode *NextNode(ThreadNode *p){
    if (p == nullptr) return nullptr;
    if (p->rtag == false){
        return FirstNode(p->rchild);
    } else {
        return p->rchild;
    }
}

ThreadNode *PreNode(ThreadNode *p){
    if (p == nullptr) return nullptr;
    if (p->ltag == false){
        return LastNode(p->lchild);
    } else {
        return p->lchild;
    }
}

void Inorder(ThreadTree T){
    for (ThreadNode *p = FirstNode(T); p != nullptr; p = NextNode(p)){
        // visit(p);
    }
}

void RevInorder(ThreadTree T){
    for (ThreadNode *p = LastNode(T); p != nullptr; p = PreNode(p)){
        // visit(p);
    }
}