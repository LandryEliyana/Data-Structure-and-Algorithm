#include <iostream>
#include <queue>
#include <stack>
using namespace std;


class BSTree {
private:
    struct Node {
        int data; // 节点数据
        Node* left; // 左子节点
        Node* right; // 右子节点
        Node(int value) : data(value), left(nullptr), right(nullptr) {} // 节点构造函数
    };

    Node* root; // 根节点指针

    // 前序遍历内部函数
    void preorder(Node *p) {
        if (p != nullptr) {
            cout << p->data << " "; // 访问当前节点
            preorder(p->left); // 前序遍历左子树
            preorder(p->right); // 前序遍历右子树
        }
    }

    // 中序遍历内部函数
    void inorder(Node *p) {
        if (p != nullptr) {
            inorder(p->left); // 中序遍历左子树
            cout << p->data << " "; // 访问当前节点
            inorder(p->right); // 中序遍历右子树
        }
    }

    // 后序遍历内部函数
    void postorder(Node *p) {
        if (p != nullptr) {
            postorder(p->left); // 后序遍历左子树
            postorder(p->right); // 后序遍历右子树
            cout << p->data << " "; // 访问当前节点
        }
    }

    // 层序遍历内部函数
    void levelorder(Node *p) {
        if (p != nullptr) {
            queue<Node*> q; // 队列
            q.push(p); // 将根节点入队
            while (!q.empty()) {
                Node* node = q.front(); // 取队首元素
                q.pop(); // 出队
                cout << node->data << " "; // 访问当前节点
                if (node->left != nullptr) {
                    q.push(node->left); // 左子节点入队
                }
                if (node->right != nullptr) {
                    q.push(node->right); // 右子节点入队
                }
            }
        }
    }
    // 递归删除节点
    Node* remove(Node *node, int value) {
        if (node == nullptr) {
            return nullptr; // 要删除的节点不存在，则直接返回
        }
        if (value < node->data) {
            node->left = remove(node->left, value); // 向左子树删除
        } else if (value > node->data) {
            node->right = remove(node->right, value); // 向右子树删除
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right; // 右子树为最小节点
                delete node; // 删除当前节点
                return temp; // 返回右子树
            } else if (node->right == nullptr) {
                Node* temp = node->left; // 左子树为最小节点
                delete node; // 删除当前节点
                return temp; // 返回左子树
            } else {
                Node* successor = node->right; // 右子树的最小节点
                while (successor->left != nullptr) {
                    successor = successor->left; // 向左子树移动
                }
                node->data = successor->data; // 用后继节点的值替换当前节点的值
                node->right = remove(node->right, successor->data); // 删除后继节点
            }
        }
        return node; // 返回当前节点
    }

public:
    // 构造函数
    BSTree(): root(nullptr) {}
    // 析构函数
    ~BSTree() {
        if (root != nullptr) {
            queue<Node*> q; // 队列用于层序遍历删除节点
            q.push(root); // 将根节点入队
            while (!q.empty()) {
                Node* node = q.front(); // 取队首元素
                q.pop(); // 出队
                if (node->left != nullptr) {
                    q.push(node->left); // 左子节点入队
                }
                if (node->right != nullptr) {
                    q.push(node->right); // 右子节点入队
                }
                delete node; // 删除当前节点
            }
        }
    }
    // 插入节点
    void insert(int value) {
        if (root == nullptr) {
            root = new Node(value); // 根节点为空，则插入新节点为根节点
            return;
        }
        else {
            Node* p = root; // 初始指针指向根节点
            while(p != nullptr) {
                if (value < p->data) {
                    if (p->left == nullptr) {
                        p->left = new Node(value); // 左子树为空，则插入新节点为左子节点
                        return;
                    } else {
                        p = p->left; // 向左子树移动
                    }
                } else if (value > p->data) {
                    if (p->right == nullptr) {
                        p->right =new Node(value); // 右子树为空，则插入新节点为右子节点
                        return;
                    } else {
                        p = p->right; // 向右子树移动
                    }
                } else {
                    return; // 如果值已存在，则直接返回
                }
            }
        }
    }
    // 递归插入节点
    Node* insert(Node *node, int value) {
        if (node == nullptr) {
            return new Node(value); // 如果当前节点为空，则创建新节点
        }
        if (value < node->data) {
            node->left = insert(node->left, value); // 向左子树插入
        } else if (value > node->data) {
            node->right = insert(node->right, value); // 向右子树插入
        } else {
            // 如果值已存在，则不插入
            return node;
        }
        return node; // 返回当前节点
    }

    // 删除节点
    void remove(int value) {
        Node* p = root; // 初始指针指向根节点
        Node* parent = nullptr; // 记录父节点指针
        // 寻找要删除的节点及其父节点
        while (p != nullptr && p->data != value) {
            parent = p; // 更新父节点
            if (value < p->data) {
                p = p->left; // 向左子树移动
            } else {
                p = p->right; // 向右子树移动
            }
        }
        if (p == nullptr) {
            return; // 要删除的节点不存在，则直接返回
        }
        // 根据子节点情况处理
        if (p->left == nullptr && p->right == nullptr) {
            // 叶子节点，直接删除
            if (p == root) {
                root = nullptr; // 根节点为空，则删除节点后树为空
            } else if (p == parent->left) {
                parent->left = nullptr; // 左子节点为空，则删除节点后父节点的左子节点为空
            } else {
                parent->right = nullptr; // 右子节点为空，则删除节点后父节点的右子节点为空
            }
            delete p; // 删除节点
        } else if (p->left == nullptr || p->right == nullptr) {
            // 有一个子节点，直接用子节点替换父节点
            Node* child = p->left == nullptr ? p->right : p->left;
            if (p == root) {
                root = child; // 根节点为空，则用子节点替换
            } else if (p == parent->left) {
                parent->left = child; // 左子节点为空，则用子节点替换
            } else {
                parent->right = child; // 右子节点为空，则用子节点替换
            }
            delete p; // 删除节点
        } else {
            // 有两个子节点, 找到前驱节点
            Node* predecessor = p->left; // 前驱节点初始为左子节点
            Node* predParent = p; // 前驱节点的父节点初始为当前
            while (predecessor->right != nullptr) {
                predParent = predecessor; // 更新前驱节点的父节点
                predecessor = predecessor->right; // 向右子树移动
            }
            // 替换当前节点数据
            p->data = predecessor->data;
            // 删除前驱节点(一定没有右子树)
            if (predecessor == predParent->right) {
                predParent->right = predecessor->left; // 前驱节点是右子节点，则更新父节点的右子节点
            } else {
                predParent->left = predecessor->left; // 前驱节点是左子节点，则更新父节点的左子节点
            }
            delete predecessor; // 删除前驱节点
        }
    }
    // 对外公开的递归删除接口
    void removeRecursively(int value) {
        root = remove(root, value);
    }
    // 查找节点
    bool query(int value) {
        Node* p = root; // 初始指针指向根节点
        while (p != nullptr) {
            if (value < p->data) {
                p = p->left; // 向左子树移动
            } else if (value > p->data) {
                p = p->right; // 向右子树移动
            } else {
                return true; // 找到节点
            }
        }
        return false; // 未找到节点
    }
    // 递归查找节点
    Node* query(Node *node, int value) {
        if (node == nullptr) {
            return nullptr; // 未找到节点
        }
        if (value < node->data) {
            return query(node->left, value); // 向左子树查找
        } else if (value > node->data) {
            return query(node->right, value); // 向右子树查找
        } else {
            return node; // 找到节点
        }
    }
    // 前序遍历
    void preOrder() {
        cout << "前序遍历: ";
        preorder(root);
        cout << endl;
    }
    // 中序遍历
    void inOrder() {
        cout << "中序遍历: ";
        inorder(root);
        cout << endl;
    }
    // 后序遍历
    void postOrder() {
        cout << "后序遍历: ";
        postorder(root);
        cout << endl;
    }
    // 层序遍历
    void levelOrder() {
        cout << "层序遍历: ";
        levelorder(root);
        cout << endl;
    }
    // 非递归前序遍历
    void preOrderIterative() {
        cout << "非递归前序遍历: ";
        if (root == nullptr) {
            return;
        }
        stack<Node*> s; // 栈
        s.push(root); // 将根节点入栈
        while (!s.empty()) {
            Node* node = s.top(); // 取栈顶元素
            s.pop(); // 出栈
            cout << node->data << " "; // 访问当前节点
            if (node->right != nullptr) {
                s.push(node->right); // 右子节点入栈
            }
            if (node->left != nullptr) {
                s.push(node->left); // 左子节点入栈
            }
        }
        cout << endl;
    }
    // 非递归中序遍历
    void inOrderIterative() {
        cout << "非递归中序遍历: ";
        if (root == nullptr) {
            return;
        }
        stack<Node*> s; // 栈
        Node* node = root; // 当前节点
        while (node != nullptr || !s.empty()) {
            while (node != nullptr) {
                s.push(node); // 左子节点入栈
                node = node->left; // 向左子树移动
            }
            node = s.top(); // 取栈顶元素
            s.pop(); // 出栈
            cout << node->data << " "; // 访问当前节点
            node = node->right; // 向右子树移动
        }
        cout << endl;
    }
    // 非递归后序遍历
    void postOrderIterative() {
        cout << "非递归后序遍历: ";
        if (root == nullptr) {
            return;
        }
        stack<Node*> s; // 栈
        s.push(root); // 将根节点入栈
        stack<Node*> output; // 输出栈
        while (!s.empty()) {
            Node* node = s.top(); // 取栈顶元素
            s.pop(); // 出栈
            output.push(node); // 输出栈入栈
            if (node->left != nullptr) {
                s.push(node->left); // 左子节点入栈
            }
            if (node->right != nullptr) {
                s.push(node->right); // 右子节点入栈
            }
        }
        while (!output.empty()) {
            Node* node = output.top(); // 取输出栈顶元素
            output.pop(); // 出栈
            cout << node->data << " "; // 访问当前节点
        }
        cout << endl;
    }
    // 非递归层序遍历
    void levelOrderIterative() {
        cout << "非递归层序遍历: ";
        if (root == nullptr) {
            return;
        }
        queue<Node*> q; // 队列
        q.push(root); // 将根节点入队
        while (!q.empty()) {
            Node* node = q.front(); // 取队首元素
            q.pop(); // 出队
            cout << node->data << " "; // 访问当前节点
            if (node->left != nullptr) {
                q.push(node->left); // 左子节点入队
            }
            if (node->right != nullptr) {
                q.push(node->right); // 右子节点入队
            }
        }
        cout << endl;
    }
};

int main() {
    int arr[] = {5, 3, 7, 2, 4, 6, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    BSTree tree;
    for (int i = 0; i < n; i++) {
        tree.insert(arr[i]);
    }
    tree.preOrder(); // 前序遍历输出
    return 0;
}