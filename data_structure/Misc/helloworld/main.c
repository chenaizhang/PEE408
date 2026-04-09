/*
 * 动态内存分配示例。
 * 该文件演示按输入长度申请整型数组并访问数组元素的基本流程。
 */
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
