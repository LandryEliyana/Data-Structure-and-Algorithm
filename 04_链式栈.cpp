#include <iostream>
using namespace std;

struct Node {
    Node(int val = 0): data(val), next(nullptr) {}
    int data;
    Node* next;
};

class LinkStack {
private:
    Node* top; // 栈顶指针
public:
    // 构造函数
    LinkStack() {
        top = new Node(); // 栈底指针
    }
    // 析构函数
    ~LinkStack() {
        Node* p = top;
        while (p != nullptr) {
            top = top->next; // 移动栈顶指针
            delete p; // 释放当前节点内存
            p = top; // 指向下一个节点
        }
    }
    // 入栈操作
    void push(int val) {
        Node* newNode = new Node(val);
        newNode->next = top->next; // 新节点指向原栈顶
        top->next = newNode; // 栈顶指针指向新节点
    }
    // 出栈操作
    void pop() {
        if (top->next == nullptr) {
            throw "Stack is empty";
        }
        Node* p = top->next; // 指向栈顶节点
        top->next = p->next; // 栈顶指针指向下一个节点
        delete p; // 释放栈顶节点内存
    }
    // 栈顶元素
    int peek() {
        if (top->next == nullptr) {
            throw "Stack is empty";
        }
        return top->next->data; // 返回栈顶节点的数据
    }
    // 栈是否为空
    bool isEmpty() {
        return top->next == nullptr;
    }
};

int main() {
    LinkStack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    cout << "peek: " << stack.peek() << endl; // peek: 3
    stack.pop();
    cout << "peek: " << stack.peek() << endl; // peek: 2
    stack.pop();
    cout << "peek: " << stack.peek() << endl; // peek: 1
    stack.pop();
    cout << "isEmpty: " << stack.isEmpty() << endl; // isEmpty: 1
    return 0;
}