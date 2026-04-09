/*
 * 顺序表示例。
 * 该文件实现顺序表的初始化、插入、删除、查找、区间删除和逆置操作。
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define InitSize 100

typedef struct{
    int *data;
    int MaxLength;
    int length;
}SeqList;

void InitList(SeqList *L, int initLen);
bool Insert(SeqList *L, int i, int e);
bool DeleteItem(SeqList *L, int i, int *e);
void DeleteItemAll(SeqList *L, int e);
bool DeleteItemAllIn(SeqList *L, int min, int max);
void PrintAll(const SeqList *L);
int LocateItem(SeqList *L, int e);
void Reverse(SeqList *L);

int main(){
    SeqList L;
    InitList(&L, InitSize);

    Insert(&L, 1, 5);
    Insert(&L, 1, 4);
    Insert(&L, 1, 3);
    Insert(&L, 1, 9);
    Insert(&L, 2, 1);
    Insert(&L, 1, 3);
    Insert(&L, 1, 3);
    Insert(&L, 1, 3);
    Insert(&L, 1, 3);

    PrintAll(&L);
    int temp;
    DeleteItem(&L, 4, &temp);
    PrintAll(&L);
    printf("%d\n", LocateItem(&L, 3));

    DeleteItemAll(&L, 3);
    PrintAll(&L);
    
    Insert(&L, 1, 5);
    Insert(&L, 1, 4);
    Insert(&L, 1, 3);
    Insert(&L, 2, 1);
    Insert(&L, 5, 7);
    Insert(&L, 1, 3);
    Insert(&L, 1, 3);
    PrintAll(&L);

    DeleteItemAllIn(&L, 4, 5);
    PrintAll(&L);

    Reverse(&L);
    PrintAll(&L);

}

void Reverse(SeqList *L){
    for(int i = 0; i < L->length / 2; i++){
        int temp = L->data[i];
        L->data[i] = L->data[L->length - 1 - i];
        L->data[L->length - 1 - i] = temp;
    }
}

bool DeleteItemAllIn(SeqList *L, int min, int max){
    if(min > max){
        return false;
    }

    int k = 0;
    for(int i = 0; i < L->length; i++){
        if(L->data[i] > max || L->data[i] < min){
            L->data[k] = L->data[i];
            k++;
        }
    }

    L->length = k;
    return true;
}

void DeleteItemAll(SeqList *L, int e){
    int k = 0;
    for(int i = 0; i < L->length; i++){
        if(L->data[i] != e){
            L->data[k] = L->data[i];
            k++;
        }
    }
    L->length = k;
}

int LocateItem(SeqList *L, int e){
    for(int i = 1; i <= L->length;i++){
        if(L->data[i-1]==e){
            return i;
        }
    }
    return 0;
}

void InitList(SeqList *L, int initLen){
    (*L).data = (int*)malloc(initLen * sizeof(int));
    L->MaxLength = initLen;
    L->length = 0;
}

bool Insert(SeqList *L, int i, int e){
    if(i < 1 || i > L->length + 1){
        return false;
    }
    if(L->length >= L->MaxLength){
        return false;
    }

    // 将第i个元素与之后的元素后移
    for (int j = L->length; j >= i; j--){
        L->data[j] = L->data[j - 1];
    }
    L->data[i - 1] = e;
    L->length++;
    return true;
}

bool DeleteItem(SeqList *L, int i, int *e){
    if(i < 1 || i > L->length){
        return false;
    }

    *e = L->data[i-1];

    for(int j = i; j < L->length;j++){
        L->data[j - 1] = L->data[j];
    }
    
    L->length--;
    return true;
}

void PrintAll(const SeqList *L){
    for (int i = 0; i < L->length;i++){
        printf("%d ",L->data[i]);
    }
    printf("\n");
}
