#include <iostream>
#include <cstdlib>
#include <ctime>

void InsertSort(int A[], int n) {
    int i, j, temp;
    for (i = 1; i < n; ++i) {
        if (A[i - 1] > A[i]) {
            temp = A[i];
            for (j = i - 1; j >= 0 && A[j] > temp; --j) {
                A[j + 1] = A[j];
            }
            A[j + 1] = temp;
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

    InsertSort(A, n);

    std::cout << "排序后：" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}