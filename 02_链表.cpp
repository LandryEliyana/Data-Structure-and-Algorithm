#include <iostream>
using namespace std;

// 定义链表节点类型
struct Node {
    Node(int value = 0): data(value), next(nullptr) {}
    int data;
    Node* next;
};

// 定义链表类
class LinkedList {
private: 
    Node* head; // 头指针
    friend void reverse(LinkedList& list); // 声明链表逆序函数
    friend Node* findKthToTail(LinkedList& list, int k); // 声明求倒数第k个节点函数

public:
    // 构造函数
    LinkedList() {
        head = new Node(); 
    }
    // 析构函数
    ~LinkedList() {
        Node* temp = head;
        while (temp != nullptr) {
            head = head->next; // 移动头指针
            delete temp;
            temp = head;
        }
        head = nullptr; // 最后将头指针置为nullptr
    }

    // 头插法插入元素
    void insertHead(int value) {
        Node* node = new Node(value);
        node->next = head->next;
        head->next = node;
    }

    // 尾插法插入元素
    void insertTail(int value) {
        Node* node = new Node(value);
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next; // 找到链表的最后一个节点
        }
        temp->next = node; // 插入节点
    }

    // 按值删除节点
    void remove(int value) {
        Node* temp = head;
        while (temp->next != nullptr) {
            if (temp->next->data == value) {
                Node* toDelete = temp->next; // 找到要删除的节点
                temp->next = toDelete->next; // 跳过要删除的节点
                delete toDelete; // 释放内存
                return;
            }
            temp = temp->next; // 移动到下一个节点
        }
        cout << "Value not found in the list." << endl; // 如果未找到值
    }

    // 删除所有值为value的节点
    void removeAll(int value) {
        Node* temp = head;
        while (temp->next != nullptr) {
            if (temp->next->data == value) {
                Node* toDelete = temp->next; // 找到要删除的节点
                temp->next = toDelete->next; // 跳过要删除的节点
                delete toDelete; // 释放内存
                // return;
            } else {
                temp = temp->next; // 移动到下一个节点
            }
        }
    }

    // 打印链表
    void print() {
        Node* temp = head->next;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next; // 移动到下一个节点
        }
        cout << endl;
    }
};

// 链表逆序
void reverse(LinkedList& list) {
    Node* p = list.head->next; // 当前节点
    if (p == nullptr || p->next == nullptr) {
        return; // 如果链表为空或只有一个节点，直接返回
    }
    
    list.head->next = nullptr; // 头指针指向nullptr

    while (p != nullptr) {
        Node* q = p->next; // 保存下一个节点
        p->next = list.head->next; // 当前节点指向头指针的下一个节点
        list.head->next = p; // 头指针指向当前节点
        p = q; // 移动到下一个节点
    }
}

// 求倒数第k个节点
Node* findKthToTail(LinkedList& list, int k) {
    Node* p1 = list.head->next; // 快指针
    Node* p2 = list.head->next; // 慢指针
    if (k <= 0 || p1 == nullptr) {
        return nullptr; // 如果k小于等于0或链表为空，返回nullptr
    }
    for (int i = 0; i < k; i++) {
        if (p1 == nullptr) {
            return nullptr; // 如果k大于链表长度，返回nullptr
        }
        p1 = p1->next; // 快指针前进k步
    }
    while (p1 != nullptr) {
        p1 = p1->next; // 快指针和慢指针同时前进
        p2 = p2->next;
    }
    return p2; // 返回慢指针，即倒数第k个节点
}

int main() {
    LinkedList list; // 创建链表
    srand(time(0)); // 初始化随机数种子
    for (int i = 0; i < 10; i++) {
        int value = rand() % 100; // 生成1-100之间的随机数
        list.insertHead(value); // 头插法插入10个随机数
        cout << value << " "; // 打印插入的值
    }
    cout << endl;

    list.print(); // 打印链表
    list.insertTail(200); // 尾插法插入一个元素
    list.print(); // 打印链表
    list.remove(200); // 删除值为200的节点
    list.print(); // 打印链表
    list.insertTail(200); // 尾插法插入一个元素
    list.insertTail(100); // 尾插法插入一个元素
    list.insertTail(200); // 尾插法插入一个元素
    list.print(); // 打印链表
    list.removeAll(200); // 删除所有值为200的节点
    list.print(); // 打印链表
    reverse(list); // 逆序链表
    list.print(); // 打印逆序后的链表

    int k = 0; // 查找倒数第k个节点
    Node* kthNode = findKthToTail(list, k);
    if (kthNode != nullptr) {
        cout << "The " << k << "th to tail node is " << kthNode->data << endl;
    } else {
        cout << "The " << k << "th to tail node is not found." << endl;
    }
    return 0;
}