#include <iostream>
using namespace std;

// 非递归版本的二分搜索算法
int binarySearch(int arr[], int n, int x) {
    int low = 0, high = n - 1;
    while(low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == x) {
            return mid; 
        } else if (arr[mid] < x) {
            low = mid + 1; 
        } else {
            high = mid - 1; 
        }
    }
    return -1; 
}   

// 递归版本的二分搜索算法
int binarySearchRecursive(int arr[], int low, int high, int x) {
    if (low > high) {
        return -1;
    } 
    int mid = (low + high) / 2;
    if (arr[mid] == x) {
        return mid;
    } else if (arr[mid] < x) {
        return binarySearchRecursive(arr, mid + 1, high, x);
    } else {
        return binarySearchRecursive(arr, low, mid - 1, x);
    }
}

int main() {
    int arr[] = {2, 3, 4, 10, 40};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 10;
    int result = binarySearch(arr, n, x);
    if (result == -1) {
        cout << "Element not present in array";
    } else {
        cout << "Element is present at index " << result;
    }
    cout << endl;
    result = binarySearchRecursive(arr, 0, n - 1, x);
    if (result == -1) {
        cout << "Element not present in array";
    } else {
        cout << "Element is present at index " << result;
    }

    return 0;
}

