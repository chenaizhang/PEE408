/*
 * 双链表示例。
 * 该文件实现双链表的初始化、前插和后插等基础操作。
 */
#include<stdio.h>
#include<stdlib.h>



typedef struct DNode{
    int data;
    struct DNode *prior, *next;
}DNode, *DLinkList;


void DListFrontInsert(DNode *p, int e);
void DListBehindInsert(DNode *p, int e);
void Initialize(DLinkList &L);
int main(){
    DLinkList L;
}

void Initialize(DLinkList &L){
    DNode *newNode = (DNode*)malloc(sizeof(DNode));

    L = newNode;
    newNode->next = NULL;
    newNode->prior = NULL;
}

void DListFrontInsert(DNode *p, int e){
    DNode *newNode = (DNode*)malloc(sizeof(DNode));

    newNode->data = e;
    newNode->next = p;
    newNode->prior = p->prior;
    p->prior = newNode;
    newNode->prior->next = newNode;
}

void DListBehindInsert(DNode *p, int e){
    DNode *newNode = (DNode*)malloc(sizeof(DNode));

    newNode->data = e;
    newNode->next = p->next;
    newNode->prior = p;
    p->next = newNode;

    if(newNode->next != NULL){
        newNode->next->prior = newNode;
    }
}
