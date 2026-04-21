#include <iostream>
#include <cstdlib>
#include <ctime>

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void BubbleSort(int A[], int n) {
    for (int i = n - 1; i >= 0; --i){
        bool flag = false;
        for (int j = 0; j < i; ++j){
            if(A[j] > A[j + 1]){
                swap(A[j], A[j + 1]);
                flag = true;
            }
        }
        if (!flag){
            return;
        }
    }
}

int main() {
    const int n = 50;
    int A[n];

    // 初始化为 1~50
    for (int i = 0; i < n; ++i) {
        A[i] = i + 1;
    }

    // 打乱数组（Fisher-Yates 洗牌）
    std::srand((unsigned)std::time(nullptr));
    for (int i = n - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }

    std::cout << "排序前：" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;

    BubbleSort(A, n);

    std::cout << "排序后：" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}