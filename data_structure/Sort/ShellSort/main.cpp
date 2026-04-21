#include <iostream>
#include <cstdlib>
#include <ctime>

void ShellSort1(int A[], int n){
    for (int d = n / 2; d >= 1; d /= 2){
        for (int i = d; i < n; ++i){
            if (A[i] < A[i - d]){
                int temp = A[i], j;
                for (j = i - d; j >=0 && temp < A[j]; j -= d){
                    A[j + d] = A[j];
                }
                A[j + d] = temp;
            }
        }
    }
}

void ShellSort2(int A[], int n){
    for (int d = n / 2; d >= 1; d /= 2){
        for (int i = 0; i < d; ++i){
            for (int j = i + d; j < n; j += d){
                if (A[j] < A[j - d]){
                    int temp = A[j], k;
                    for (k = j - d; k >= 0 && A[k] > temp; k -= d){
                        A[k + d] = A[k];
                    }
                    A[k + d] = temp;
                }
            }
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

    ShellSort2(A, n);

    std::cout << "排序后：" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}