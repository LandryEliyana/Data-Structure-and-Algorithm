#include <iostream>
using namespace std;

// 顺序栈
class Stack {
private:
    int* data; // 数据数组
    int top; // 栈顶指针
    int capacity; // 栈容量
    // 扩容函数
    void _expand() {
        int new_capacity = capacity * 2; // 新容量为原容量的两倍
        int* new_data = new int[new_capacity]; // 动态分配新数组
        for (int i = 0; i < top; i++) {
            new_data[i] = data[i]; // 复制原数组元素到新数组
        }
        delete[] data; // 释放原数组
        data = new_data; // 指向新数组
        capacity = new_capacity; // 更新容量
    } 
public:
    Stack(int size = 10): capacity(size), top(0) {
        data = new int[capacity]; // 动态分配内存
    }
    ~Stack() {
        delete[] data; // 释放内存
        data = nullptr;
    }
    // 入栈操作
    void push(int value) {
        if (top == capacity) {
            _expand(); // 栈满时扩容
        }
        data[top++] = value; // 栈顶指针后移，插入新值
    }
    // 出栈操作
    void pop() {
        if (top == 0) {
            throw "Stack is empty"; // 栈空时抛出异常
        }
        top--; // 栈顶指针前移
    }
    // 获取栈顶元素
    int peek() {
        if (top == 0) {
            throw "Stack is empty"; // 栈空时抛出异常
        }
        return data[top - 1]; // 返回栈顶元素
    }
    // 判断栈是否为空
    bool empty() const {
        return top == 0; // 如果栈顶指针为0，则栈为空
    }
};

int main() {
    Stack stack; // 创建栈对象
    for (int i = 0; i < 10; i++) {
        stack.push(i); // 入栈操作
    }
    while (!stack.empty()) {
        cout << stack.peek() << " "; // 出栈操作
        stack.pop();
    }
    cout << endl;
    return 0;
}