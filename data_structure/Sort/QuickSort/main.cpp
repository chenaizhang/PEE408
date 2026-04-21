#include <iostream>
#include <cstdlib>
#include <ctime>

void Swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// 分区：随机选枢轴 + 挖坑法
int Partition(int A[], int low, int high) {
    int pivotIndex = low + std::rand() % (high - low + 1);
    Swap(A[low], A[pivotIndex]);   // 把随机枢轴放到区间首位

    int pivot = A[low];
    int i = low, j = high;

    while (i < j) {
        while (i < j && A[j] >= pivot) --j;
        if (i < j) A[i++] = A[j];

        while (i < j && A[i] <= pivot) ++i;
        if (i < j) A[j--] = A[i];
    }

    A[i] = pivot;
    return i;
}

void QuickSort(int A[], int low, int high) {
    if (low >= high) return;

    int pivotPos = Partition(A, low, high);
    QuickSort(A, low, pivotPos - 1);
    QuickSort(A, pivotPos + 1, high);
}

void QuickSort(int A[], int n) {
    if (n <= 1) return;
    QuickSort(A, 0, n - 1);
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
        Swap(A[i], A[j]);
    }

    std::cout << "排序前：" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;

    QuickSort(A, n);

    std::cout << "排序后：" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}