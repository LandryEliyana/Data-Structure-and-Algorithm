#include <iostream>
using namespace std;

// 数组实现
class Array {
private:
    int* arr; // 数组指针，指向动态分配的数组
    int capcity;  // 数组容量
    int cur;  // 数组当前元素个数
    
    // 扩容函数
    void _expand() {
        int new_capcity = capcity * 2; // 新容量为原容量的两倍
        int* new_arr = new int[new_capcity]; // 动态分配新数组
        for (int i = 0; i < cur; i++) {
            new_arr[i] = arr[i]; // 复制原数组元素到新数组
        }
        delete[] arr; // 释放原数组
        arr = new_arr; // 指向新数组
        capcity = new_capcity; // 更新容量
    } 

public:
    // 构造函数，默认数组大小为10
    Array(int size = 10): capcity(size), cur(0) {
        arr = new int[size]; // 动态分配内存
    } 
    // 析构函数，释放动态分配的内存
    ~Array() { 
        delete[] arr;
        arr = nullptr;
    }
    // 添加元素到数组末尾
    void push_back(int value) {
        if (cur == capcity) { // 数组已满
            _expand(); // 扩容
            arr[cur++] = value; // 将新元素添加到数组末尾
        } else {
            arr[cur++] = value; // 将新元素添加到数组末尾
        }
    } 
    // 删除数组末尾元素并返回值
    void pop_back() {
        if (cur == 0) {
            throw out_of_range("Array is empty"); // 如果数组为空，抛出异常
        }
        cur--; // 减少当前元素个数
    }
    // 在指定位置插入元素
    void insert(int index, int value) {
        if (index < 0 || index > cur) {
            throw out_of_range("Index out of range"); // 如果索引越界，抛出异常
        }
        if (cur == capcity) { // 数组已满
            _expand(); // 扩容
        }
        for (int i = cur - 1; i >= index; i--) {
            arr[i + 1] = arr[i]; // 后移元素
        }
        arr[index] = value; // 插入新元素
        cur++; // 增加当前元素个数
    }
    // 删除指定位置元素
    void remove(int index) {
        if (index < 0 || index >= cur) {
            throw out_of_range("Index out of range"); // 如果索引越界，抛出异常
        }
        for (int i = index; i < cur - 1; i++) {
            arr[i] = arr[i + 1]; // 前移元素
        }
        cur--; // 减少当前元素个数
    }
    // 获取数组指定位置元素的值
    int get(int index) {
        if (index < 0 || index >= cur) {
            throw out_of_range("Index out of range"); // 如果索引越界，抛出异常
        }
        return arr[index]; // 返回指定位置的元素值
    }
    // 查找元素，返回其索引
    int find(int val) {
        for (int i = 0; i < cur; i++) {
            if (arr[i] == val) {
                return i; // 返回元素索引
            }
        }
        return -1; // 没有找到元素，返回-1
    }
    // 打印数组内容
    void print() {
        for (int i = 0; i < cur; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Array arr;
    srand(time(nullptr)); // 初始化随机数种子
    for (int i = 0; i < 10; i++) {
        arr.push_back(rand() % 100); // 随机添加10个0-99之间的整数
    }
    arr.print();
    arr.pop_back();
    arr.print(); 
    arr.insert(2, 100);
    arr.print();
    arr.remove(2);
    arr.print();
    
    int pos = arr.find(50);
    if (pos != -1) {
        cout << "Element 50 found at index " << pos << endl;
    } else {
        cout << "Element 50 not found" << endl;
    }
    return 0;
}