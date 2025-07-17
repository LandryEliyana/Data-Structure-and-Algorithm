#include <iostream>
using namespace std;

// 环形队列
class CircularQueue {
private:
    int* data; // 数据数组
    int front; // 队头指针
    int rear; // 队尾指针
    int capacity; // 队列容量

    // 扩容操作
    void _expand() {
        int* new_data = new int[2 * capacity]; // 申请新的内存
        for (int i = front; i!= rear; i = (i + 1) % capacity) {
            new_data[i - front] = data[i]; // 复制数据
        }
        delete[] data; // 释放旧内存
        data = new_data; // 指向新内存
        front = 0; // 队头指针指向新内存的开始位置
        rear = capacity; // 队尾指针指向新内存的结束位置
        capacity *= 2; // 容量翻倍
    }
public:
    // 构造函数
    CircularQueue(int size = 10): capacity(size), front(0), rear(0) {
        data = new int[capacity]; // 动态分配内存
    }
    // 析构函数
    ~CircularQueue() {
        delete[] data; // 释放内存
        data = nullptr;
    }
    // 入队操作
    void enqueue(int value) {
        if ((rear + 1) % capacity == front) {
            _expand(); // 队列已满，扩容
        }
        data[rear] = value; // 插入新元素
        rear = (rear + 1) % capacity; // 更新队尾指针
    }
    // 出队操作
    void dequeue() {
        if (front == rear) {
            throw "Queue is empty"; // 队列为空时抛出异常
        }
        front = (front + 1) % capacity; // 更新队头指针
    }
    // 取队头元素
    int getFront() {
        if (front == rear) {
            throw "Queue is empty"; // 队列为空时抛出异常
        }
        return data[front]; // 返回队头元素
    }
    // 取队尾元素
    int getRear() {
        if (front == rear) {
            throw "Queue is empty"; // 队列为空时抛出异常
        }
        return data[(rear - 1 + capacity) % capacity]; // 返回队尾元素
    }
    // 判断队列是否为空
    bool isEmpty() const {
        return front == rear;
    }
    // 判断队列是否已满
    bool isFull() const {
        return (rear + 1) % capacity == front;
    }
};

int main() {
    CircularQueue queue; // 创建环形队列
    for (int i = 0; i < 15; ++i) {
        queue.enqueue(i); // 入队操作
    }
    
    cout << "Front: " << queue.getFront() << endl; // 输出队头元素
    cout << "Rear: " << queue.getRear() << endl; // 输出队尾元素
    
    while (!queue.isEmpty()) {
        cout << "Dequeue: " << queue.getFront() << endl; // 输出出队元素
        queue.dequeue(); // 出队操作
    }
    
    return 0;
}