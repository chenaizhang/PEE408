#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct LNode{
    int data;
    struct LNode *next;
}LNode, *LinkList;

bool InitList(LinkList &L);
bool ListInsert(LinkList &L, int i, int e);
bool ListInsertNext(LNode *p, int e);
int Length(LinkList &L);
LNode *GetElem(LinkList &L, int i);
LNode *LocateElem(LinkList &L, int e);
bool ListDelete(LinkList &L, int i, int &e);


int main(){
    LinkList L;
    InitList(L);

}

bool ListDelete(LinkList &L, int i, int &e){
    LNode *p = GetElem(L, i - 1);
    
    if(p == NULL || p->next == NULL)return false;

    LNode *temp = p->next;
    e = temp->data;
    p->next = temp->next;
    free(temp);
    return true;

    

}

bool ListInsertNext(LNode *p, int e){
    if(p == NULL)return false;

    LNode *temp = (LNode*)malloc(sizeof(LNode));
    temp->data = e;
    temp->next = p->next;
    p->next = temp;
    return true;
}

LNode *LocateElem(LinkList &L, int e){
    LNode *p = L->next;
    while(p != NULL && p->data != e){
        p = p->next;
    }
    return p;
}

LNode *GetElem(LinkList &L, int i){
    LNode *p = L;
    int j = 0;
    while(p != NULL && j < i){
        p = p->next;
        j++;
    }

    return p;
}

int Length(LinkList &L){
    LNode *p = L;
    int length = 0;
    while(p->next != NULL){
        length++;
        p = p->next;
    }

    return length;
}

bool InitList(LinkList &L){
    L = (LNode*)malloc(sizeof(LNode));
    L->next = NULL;
    return true;
}

bool ListInsert(LinkList &L, int i, int e){
    if(i<1)
        return false;
    LNode *p;
    p = L;
    for(int j = 0; p != NULL && j < i - 1; j++){
        p = p->next;
    }

    if(p == NULL)return false;

    LNode *s = (LNode*)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}