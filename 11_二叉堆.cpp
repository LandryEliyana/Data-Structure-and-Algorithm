#include <iostream>
#include <time.h>
using namespace std;

// 优先级队列实现
class PriorityQueue {
private:
    int *data;  // 数组
    int size;   // 堆的大小
    int capacity;  // 堆的容量

    // 上浮操作
    void siftUp(int i, int value) {
        while (i > 0) {
            int parent = (i - 1) / 2;  // 父节点索引
            if (data[parent] < value) {
                data[i] = data[parent];  // 将父节点下沉
                i = parent;  // 更新当前索引为父节点索引
            } else {
                break;  // 如果父节点大于等于当前值，停止上浮
            }
        }
        data[i] = value;  // 将当前值放到正确的位置
    }

    // 下沉操作
    void siftDown(int i, int value) {
        while (i < size / 2) {
            int child = 2 * i + 1;
            if (child + 1 < size && data[child + 1] > data[child]) {
                child += 1;  // 如果右子节点存在且大于左子节点，选择右子节点;
            }
            
            if (data[child] > value) {
                data[i] = data[child];
                i = child;
            } else {
                break;
            }
        }
        data[i] = value;  // 将堆顶元素放到最后一个位置
    }
public:
    PriorityQueue(int capacity): size(0), capacity(capacity) {
        data = new int[capacity];
    }
    ~PriorityQueue() {
        delete[] data;
        data = nullptr;
    }
    // 入堆操作
    void push(int value) {
        if (size == capacity) {
            int *newData = new int[capacity * 2];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity *= 2;
        } else if (size == 0) {
            data[size] = value;  // 如果堆为空，直接插入
        } else {
            siftUp(size, value);
        }
        size++;
    }
    // 删除堆顶元素
    void pop() {
        if (size == 0) {
            throw "Priority Queue is empty";
        }
        size--;
        if (size > 0) {
            siftDown(0, data[size]);  // 将最后一个元素上浮到堆顶
        }
    }
    // 获取堆顶元素
    int top() {
        if (size == 0) {
            throw "Priority Queue is empty";
        }
        return data[0];
    }
    // 判断堆是否为空
    bool empty() {
        return size == 0;
    }
    // 获取指定索引的元素
    int getData(int index) {
        if (index < 0 || index >= size) {
            throw "Index out of bounds";
        }
        return data[index];
    }
};

int main() {
    PriorityQueue pq(10);  // 创建优先级队列
    srand(time(NULL));
    cout << "Insert" << endl;
    for (int i = 0; i < 10; i++) {
        int value = rand() % 100;  // 随机生成1-100之间的整数
        cout << value << " ";
        pq.push(value);  // 随机插入10个元素
    }
    cout << endl;
    cout << "output elements of an arry" << endl;
    for (int i = 0; i < 10; i++) {
        cout << pq.getData(i) << " ";
    }
    cout << endl;
    cout << "Priority Queue elements in descending order:" << endl;
    while (!pq.empty()) {
        cout << pq.top() << " ";  // 输出堆顶元素
        pq.pop();  // 删除堆顶元素
    }
    cout << endl;
    return 0;
}