/*
 * 链式队列示例。
 * 该文件实现链式队列的初始化、判空、入队和出队操作。
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct LinkNode
{
    int data;
    struct LinkNode *next;
}LinkNode;

typedef struct
{
    LinkNode *rear;
    LinkNode *front;
}LinkQueue;

void Initialize(LinkQueue &Q){
    Q.rear = Q.front = (LinkNode*)malloc(sizeof(LinkNode));
    Q.rear->next = NULL;
}

bool QueueEmpty(LinkQueue &Q){
    return Q.rear == Q.front;
}

bool EnQueue(LinkQueue &Q, int x){
    LinkNode *newnode = (LinkNode*)malloc(sizeof(LinkNode));
    newnode->data = x;
    newnode->next = NULL;

    Q.rear->next = newnode;
    Q.rear = newnode;
    return true;
}

bool DeQueue(LinkQueue &Q, int &x){
    if(QueueEmpty(Q))return false;

    LinkNode *q = Q.front->next;
    x = q->data;

    if(Q.rear == q) Q.rear = Q.front; 
    Q.front->next = q->next;
    free(q);
    
    return true;
}

int main(){
    LinkQueue Q;
    Initialize(Q);
}
