#include <iostream>
#include <vector>
#include <list>
using namespace std;

// 链式哈希表
class HashTable {
private:
    vector<list<int>> table;  // 哈希表数组
    int capacity; // 哈希表容量
    int useBucket;  // 当前被占用的桶的个数
    double loadFactor;  // 装载因子

    static const int PRIME_SIZE = 10; // 质数表大小
    static const int PRIMES[PRIME_SIZE]; // 质数表
    int primeIndex; // 质数表索引

    // 哈希函数
    int hash(int key) {
        return key % capacity;
    }

    // 扩容函数
    void expand() {
        primeIndex++; // 质数表索引+1
        if (primeIndex == PRIME_SIZE) {
            throw "HashTable is too large, cannot expand.";
        }
        int newCapacity = PRIMES[primeIndex]; // 计算新的容量
        vector<list<int>> newTable(newCapacity); // 新建哈希表数组
        for (int i = 0; i < capacity; i++) {
            for (auto it = table[i].begin(); it != table[i].end(); ++it) {
                int newIndex = hash(*it) % newCapacity; // 计算新索引
                newTable[newIndex].emplace_front(*it); // 插入新元素
            }
        }
        table = newTable; // 覆盖旧的哈希表数组
        capacity = newCapacity; // 覆盖旧的容量
    }

public:
    HashTable(int capacity = PRIMES[0], double loadFactor = 0.75): useBucket(0), capacity(capacity), loadFactor(loadFactor), primeIndex(0) {
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
        table.resize(capacity);
    }
    // 插入元素
    void insert(int key) {
        // 检查是否需要扩容
        if (useBucket > table.size() * loadFactor) {
            expand();
        }
        // 插入元素
        int index = hash(key);
        if (table[index].empty()) {
            table[index].emplace_front(key);
            useBucket++;
        } else {
            for (auto it = table[index].begin(); it != table[index].end(); ++it) {
                if (*it == key) {
                    return; // 元素已存在
                }
            }
            table[index].emplace_front(key); // 插入新元素
        }
    }
    // 删除元素
    void remove(int key) {
        int index = hash(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (*it == key) {
                table[index].erase(it); // 删除元素
                if (table[index].empty()) {
                    useBucket--; // 如果桶为空，减少被占用的桶数
                }
                return;
            }
        }
    }
    // 查找元素
    bool find(int key) {
        int index = hash(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (*it == key) {
                return true; // 元素存在
            }
        }
        return false; // 元素不存在
    }
};

const int HashTable::PRIMES[PRIME_SIZE] = { 3, 7, 23, 47, 103, 211, 431, 859, 1721, 3461 }; // 质数表

int main() {
    HashTable ht(11, 0.75);
    ht.insert(1);
    ht.insert(2);
    ht.insert(3);
    ht.insert(4);
    ht.insert(5);
    ht.insert(6);
    ht.insert(7);
    ht.insert(8);
    ht.insert(9);
    ht.insert(10);
    ht.insert(11);

    cout << "Find 2: " << (ht.find(2) ? "Found" : "Not Found") << endl;
    cout << "Find 5: " << (ht.find(5) ? "Found" : "Not Found") << endl;
    cout << "Find 11: " << (ht.find(11) ? "Found" : "Not Found") << endl;

    ht.remove(2);
    cout << "After removing 2, Find 2: " << (ht.find(2) ? "Found" : "Not Found") << endl;

    return 0;
}