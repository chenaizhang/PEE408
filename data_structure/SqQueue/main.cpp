#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MaxSize 10
typedef struct
{
    int data[MaxSize];
    int front,rear;
}SqQueue;

void InitQueue(SqQueue &Q){
    Q.front = 0;
    Q.rear = MaxSize-1;
}

bool QueueEmpty(SqQueue &Q){
    return Q.front == (Q.rear + 1)%MaxSize;
}

bool QueueFull(SqQueue &Q){
    return Q.front == (Q.rear + 2)%MaxSize;
}

bool EnQueue(SqQueue &Q, int x){
    if(QueueFull(Q))return false;
    Q.rear = (Q.rear + 1) % MaxSize;
    Q.data[Q.rear] = x;
    return true;
}

bool DeQueue(SqQueue &Q, int &x){
    if(QueueEmpty(Q))return false;
    x = Q.data[Q.front];
    Q.front = (Q.front+1)%MaxSize;
    return true;
}

bool GetHead(SqQueue &Q, int &x){
    if(QueueEmpty(Q))return false;
    x = Q.data[Q.front];
    return true;
}