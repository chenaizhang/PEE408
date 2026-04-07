#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>



typedef struct Node{
    int data;
    struct Node *next;
}Node,*LinkStack;



void InitStack(LinkStack &S){
    Node *HeadNode = (Node*)malloc(sizeof(Node));
    HeadNode->next = NULL;
    HeadNode->data = 0;
    S = HeadNode;
}

bool StackEmpty(LinkStack &S){
    return S->data == 0;
}

bool Push(LinkStack &S, int x){
    Node *NewNode = (Node*)malloc(sizeof(Node));
    NewNode->data = x;
    NewNode->next = S->next;
    S->data++;
    S->next = NewNode;
    return true;
}

bool Pop(LinkStack &S, int &x){
    if(StackEmpty(S))
        return false;

    Node *p = S->next;
    x = p->data;
    S->next = p->next;
    free(p);
    S->data--;
    return true;
}

bool GetTop(LinkStack &S, int &x){
        if(StackEmpty(S))
        return false;

    x = S->next->data;
    return true;
}

int main(){
    LinkStack S;
    InitStack(S);
}