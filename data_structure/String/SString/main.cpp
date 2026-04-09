/*
 * 串结构与模式匹配示例。
 * 该文件实现定长串的子串、比较、朴素匹配以及 KMP 相关辅助函数。
 */
#include <iostream>
#define MAXLEN 255
typedef struct
{
    char ch[MAXLEN];
    int length;
}SString;

bool SubString(SString &Sub, SString S, int pos, int len){
    if(pos+len-1 > S.length)
        return false;
    for (int i = pos; i < pos + len; i++){
        Sub.ch[i-pos+1]=S.ch[i];        
    }
    Sub.length = len;
    return true;
}

int StrCompare(SString S, SString T){
    for (int i = 1; i <= (S.length>T.length?T.length:S.length); ++i){
        if(S.ch[i]!=T.ch[i]){
            return S.ch[i] - T.ch[i];
        }
    }
    return S.length - T.length;
}

int Index_old(SString S, SString T){
    for(int i = 1; i <= S.length - T.length + 1; ++i){
        SString Sub;
        if(!SubString(Sub, S, i, T.length)){
            std::cerr << "The Sub String not catch" <<std::endl;
            return -1;
        }
        if(!StrCompare(Sub, T)){
            return i;
        }
    }
    return 0;
}

int Index_new(SString S, SString T){
    for(int i = 1; i <= S.length - T.length + 1; ++i){
        for(int j = i; j < i + T.length; ++j){
            if(S.ch[j]!=T.ch[j-i+1]){
                break;
            }
            else if(j-i+1 == T.length){
                return i;
            }
        }
    }
    return 0;
}

int Index_KMP(SString S, SString T, int next[]){
    int i = 1, j = 1;
    while(i <= S.length && j <= T.length){
        if(j ==0 || S.ch[i]==T.ch[j]){
            i++;
            j++;
        }
        else{
            j = next[j];
        }
    }
    if(j>T.length)
        return i-T.length;
    else
        return 0;
}

int *CalNext(SString T){
    int *next = (int*)malloc(sizeof(int)*MAXLEN);
    next[1] = 0;
    int i = 1, j = 0;
    while(i < T.length){
        if(j==0||T.ch[i]==T.ch[j]){
            next[++i] = ++j;
        }
        else{
            j = next[j];
        }
    }
    return next;
}

int *CalNextVal(SString T){
    int *nextVal = (int*)malloc(sizeof(int)*MAXLEN);
    nextVal[1] = 0;
    int i = 2;
    int *next = CalNext(T);
    while (i <= T.length){
        if(T.ch[i] == T.ch[next[i]]){
            nextVal[i] = nextVal[next[i]];
        }
        else{
            nextVal[i] = next[i];
        }
        ++i;
    }
    free(next);
    return nextVal;
}
