#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
using namespace std;

// 冒泡排序
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool flag = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                flag = true;
            }
        }
        if (!flag) {
            break;   // 已经排序好了，不需要再继续
        }
    }
}

// 选择排序
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdex]) {
                minIdex = j;
            }
        }
        if (minIdex != i) {
            swap(arr[i], arr[minIdex]);
        }
    }
}

// 插入排序
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int j = i - 1;
        int key = arr[i];
        for (; j >= 0; j--) {
            if (arr[j] <= key) {
                break;
            } else {
                arr[j + 1] = arr[j];
            }
        }
        arr[j + 1] = key;
    }
}

// 希尔排序
void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i+=gap) {
            int j = i - gap;
            int key = arr[i];
            for (; j >= 0; j -= gap) {
                if (arr[j] <= key) {
                    break;
                } else {
                    arr[j + gap] = arr[j];
                }
            }
            arr[j + gap] = key;
        }
    }
}

// 快速排序
int partaion(int arr[], int left, int right) {
    int pivot = arr[left];
    while (left < right) {
        while (left < right && arr[right] > pivot) {
            right--;
        }
        if (left < right) {
            arr[left] = arr[right]; // 将小于基准的元素移动到左边
            left++;
        }
        while (left < right && arr[left] < pivot) {
            left++;
        }
        if (left < right) {
            arr[right] = arr[left]; // 将大于基准的元素移动到右边
            right--;
        }
    }
    arr[left] = pivot; // 基准元素归位
    return left; // 返回基准元素的位置
}
void quickSort(int arr[], int left, int right) {
    if (left >= right) {
        return; // 如果左边索引大于或等于右边索引，则不需要排序
    }
    int pos = partaion(arr, left, right);
    quickSort(arr, left, pos - 1); // 对左半部分进行快速排序
    quickSort(arr, pos + 1, right); // 对右半部分进行快速
}

// 归并排序
void merge(int arr[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = 0;
    int *temp = new int[right - left + 1];
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    
    for (i = left, k = 0; i <= right; i++, k++) {
        arr[i] = temp[k];
    }
    
    delete[] temp;
}
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// 基数排序
void radixSort(int arr[], int n) {
    int maxNum = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxNum) {
            maxNum = arr[i];
        }
    }
    int len = to_string(maxNum).length();
    
    vector<vector<int>> buckets;
    int mod = 10;
    int dev = 1;
    for (int i = 0; i < len; i++) {
        buckets.resize(10); // 初始化10个桶
        for (int j = 0; j < n; j++) {
            int digit = arr[j] % mod / dev; // 计算当前位数上的数字
            buckets[digit].push_back(arr[j]); // 将元素放入对应的桶中
        }
        int k = 0;
        for (auto bucket : buckets) {
            for (int value : bucket) {
                arr[k++] = value; // 将桶中的元素按顺序放回原数组
            }
        }
        mod *= 10;
        dev *= 10;
        // 清空桶
        buckets.clear();
    }
}

// 堆排序
void adjustHeap(int arr[], int i, int size) {
    int val = arr[i];
    while (i < size / 2) {
        int child = 2 * i + 1; // 左子节点
        if (child + 1 < size && arr[child] < arr[child + 1]) {
            child++; // 选择较大的子节点
        }
        if (val < arr[child]) {
            arr[i] = arr[child]; // 将较大的子节点上移
            i = child; // 更新当前节点为子节点
        } else {
            break; // 如果当前节点大于等于子节点，则调整结束
        }
    }
    arr[i] = val; // 将原节点值放到正确的位置
}
void heapSort(int arr[], int size) {
    int n = size - 1;
    // 从第一个非叶子节点开始调整堆
    for (int i = (n - 1) / 2; i >= 0; i--) {
        adjustHeap(arr, i, size);
    }
    // 堆排序
    for (int i = n; i > 0; i--) {
        swap(arr[0], arr[i]); // 将堆顶元素与最后一个元素交换
        adjustHeap(arr, 0, i); // 调整堆
    }
}

int main() {
    int arr[10];
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 100;
    }
    cout << "Before sorting: ";
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    // bubbleSort(arr, 10);
    // selectionSort(arr, 10);
    // insertionSort(arr, 10);
    // shellSort(arr, 10);
    // quickSort(arr, 0, 9);
    // mergeSort(arr, 0, 9);
    // radixSort(arr, 10);
    heapSort(arr, 10);
    cout << "After sorting: ";
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}