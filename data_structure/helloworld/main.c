#include <stdio.h>
#include <stdlib.h>

int main(){
    int *list = NULL;
    int n;
    printf("n is: ");
    scanf("%d", &n);

    list = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++){
        printf("list[%d] = %d\n", i, list[i]);
    }

    free(list);
    return 0;
}