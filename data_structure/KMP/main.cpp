#include <string.h>
#include <iostream>

int strStr(char* haystack, char* needle) {
    int n_length = strlen(needle);
    int h_length = strlen(haystack);
    int nextval[n_length];
    nextval[0] = -1;
    int i = 0, j = -1;
    while(i < n_length - 1){
        if(j == -1 || needle[i] == needle[j]){
            ++i,++j;
            if (needle[i] != needle[j]){
                nextval[i] = j;
            }
            else{
                nextval[i] = nextval[j];
            }
        }
        else{
            j = nextval[j];
        }
    }

    i = 0, j = 0;
    while (i < h_length && j < n_length){
        if(j == -1 || haystack[i] == needle[j]){
            ++i, ++j;
        }
        else{
            j = nextval[j];
        }
    }

    if (j == n_length){
        return i - j;
    }
    else{
        return -1;
    }
}

int main(){
    char a[100], b[100];
    std::cin >> a >> b;
    std::cout << strStr(a, b) << std::endl;
    return 0;
}