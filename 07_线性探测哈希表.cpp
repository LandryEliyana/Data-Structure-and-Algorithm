#include <iostream>
using namespace std;

// 桶的状态
enum BucketStatus {
    EMPTY, // 空桶
    OCCUPIED, // 已占用桶
    DELETED // 已删除桶
};  

// 桶的类型
struct Bucket {
    Bucket(int key = 0, BucketStatus status = EMPTY) : key(key), status(status) {} // 构造函数

    int key; // 存储的数据
    BucketStatus status; // 桶状态
};

// 线性探测哈希表
class LinearProbingHashTable {
private:
    Bucket* table; // 哈希表数组
    int capacity; // 哈希表容量
    int size; // 当前元素数量
    double loadFactor; // 装载因子

    static const int PRIME_SIZE = 10; // 质数表大小
    static const int PRIMES[PRIME_SIZE]; // 质数表
    int primeIndex; // 质数表索引

    // 扩容函数
    void expand() {
        primeIndex++; // 质数表索引+1
        if (primeIndex == PRIME_SIZE) {
            throw "HashTable is too large, cannot expand.";
        }
        Bucket* newTable = new Bucket[PRIMES[primeIndex]]; // 新建哈希表数组
        for (int i = 0; i < capacity; i++) {
            if (table[i].status == OCCUPIED) {
                int index = hash(table[i].key); // 计算哈希值
                int j = index; // 探测起始位置
                do {
                    if (newTable[j].status == EMPTY) {
                        newTable[j] = table[i]; // 移动元素
                        break;
                    }
                    j = (j + 1) % PRIMES[primeIndex]; // 探测下一个位置
                } while (j != index);
            }
        }
        delete[] table; // 释放旧哈希表数组
        table = newTable; // 指向新哈希表数组
        capacity = PRIMES[primeIndex]; // 容量更新 
    }

public:
    LinearProbingHashTable(int capacity = PRIMES[0], double loadFactor = 0.75) 
        : capacity(capacity), size(0), loadFactor(loadFactor), primeIndex(0) {
        
        // 把用户传入的size调整到合适的容量
        if (capacity != PRIMES[0]) {
            for(; primeIndex < PRIME_SIZE; primeIndex++) {
                if (capacity <= PRIMES[primeIndex]) {
                    capacity = PRIMES[primeIndex];
                    break;
                }
            }
            if (primeIndex == PRIME_SIZE) {
                primeIndex--;
                capacity = PRIMES[primeIndex];
            }
        }

        table = new Bucket[capacity]; // 初始化哈希表数组

    }
    ~LinearProbingHashTable() {
        delete[] table; // 释放哈希表数组
        table = nullptr;
    }

    // 哈希函数
    int hash(int key) {
        return key % capacity;
    }

    // 插入元素
    void insert(int key) {
        // 检查是否需要扩容
        if (size >= capacity * loadFactor) {
            expand();
        } 
        int index = hash(key); // 计算哈希值
        int i = index; // 探测起始位置

        do {
            if (table[i].status != OCCUPIED) {
                table[i].key = key;
                table[i].status = OCCUPIED;
                size++; // 元素数量+1
            } 
            i = (i + 1) % capacity; // 探测下一个位置
        } while (i != index);
    }

    // 删除元素
    void remove(int key) {
        int index = hash(key); // 计算哈希值
        int i = index; // 探测起始位置

        do {
            if (table[i].status == OCCUPIED && table[i].key == key) {
                table[i].status = DELETED; // 标记为已删除
                size--; // 元素数量-1
            }
            i = (i + 1) % capacity; // 探测下一个位置
        } while (i != index && table[i].status != EMPTY);
    }

    // 查找元素
    bool find(int key) {
        int index = hash(key); // 计算哈希值
        int i = index; // 探测起始位置

        do {
            if (table[i].status == OCCUPIED && table[i].key == key) {
                return true;
            }
            i = (i + 1) % capacity; // 探测下一个位置
        } while (i != index && table[i].status != EMPTY);

        return false; // 未找到元素
    }
};

const int LinearProbingHashTable::PRIMES[PRIME_SIZE] = { 3, 7, 23, 47, 103, 211, 431, 859, 1721, 3461 }; // 质数表

int main() {
    LinearProbingHashTable hashTable; // 创建哈希表实例

    // 插入元素
    hashTable.insert(10);
    hashTable.insert(20);
    hashTable.insert(30);
    hashTable.insert(40);
    // 查找元素
    cout << "Find 20: " << (hashTable.find(20) ? "Found" : "Not Found") << endl;
    cout << "Find 40: " << (hashTable.find(40) ? "Found" : "Not Found") << endl;

    // 删除元素
    hashTable.remove(20);
    cout << "After removing 20, find 20: " << (hashTable.find(20) ? "Found" : "Not Found") << endl;

    return 0;
}