#include <iostream>
#include <stack>
#include <functional>
using namespace std;

/*Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
 то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.
 2_2. Выведите элементы в порядке in-order (слева направо). Вначале
обрабатывается левое поддерево, затем сам узел и правое
поддерево..
*/


class BinaryTree {
    struct Node {
        int data;
        Node *left;
        Node *right;
        Node *parent;

        explicit Node(int p_data = 0, Node *p_left = nullptr, Node *p_right = nullptr, Node *p_parent = nullptr) {
            data = p_data;
            left = p_left;
            right = p_right;
            parent = p_parent;
        }
    };

public:


    void Insert(int value) {
        if (root == NULL) {
            root = new Node(value);
            return;
        }

        Node *newNode = new Node(value);
        Node *parent = nullptr;
        Node **node = &root;
        while (*node) {
            parent = *node;
            if ((*node)->data > value) {
                node = &(*node)->left;
            } else {
                node = &(*node)->right;
            }
        }
        *node = newNode;
        newNode->parent = parent;
    };


    BinaryTree(Node *root = nullptr) : root(root) {}

    ~BinaryTree() {
        deleteTree();
    }

    void printInOrder(Node *root) {
        if (root == nullptr)
            return;
        printInOrder(root->left);
        cout << root->data << " ";
        printInOrder(root->right);
    }


    template<typename Operation>
    void inOrder(Operation op) {
        stack<Node *> stack;
        Node *node = root;
        while (node != nullptr || !stack.empty()) {
            if (node != nullptr) {
                stack.push(node);
                node = node->left;
            } else {
                node = stack.top();
                stack.pop();
                op(node->data);
                node = node->right;
            }

        }
    }


    void printPostOrder() {
        stack<Node *> stack;
        Node *node = root;
        Node *lastNodeVisited = nullptr;
        while (!stack.empty() || node != nullptr) {
            if (node != nullptr) {
                stack.push(node);
                node = node->left;
            } else {
                Node *peekNode = stack.top();
                // если правый потомок существует и обход пришёл из левого потомка, двигаемся вправо
                if (peekNode->right != nullptr && lastNodeVisited != peekNode->right) {
                    node = peekNode->right;
                } else {
                    cout << peekNode->data << " ";
                    lastNodeVisited = stack.top();
                    stack.pop();
                }
            }
        }
    }

    Node *root;
private:
    void deleteTree() {
        stack<Node *> stack;
        Node *node = root;
        Node *lastNodeVisited = nullptr;
        while (!stack.empty() || node != nullptr) {
            if (node != nullptr) {
                stack.push(node);
                node = node->left;
            } else {
                Node *peekNode = stack.top();
                // если правый потомок существует и обход пришёл из левого потомка, двигаемся вправо
                if (peekNode->right != nullptr && lastNodeVisited != peekNode->right) {
                    node = peekNode->right;
                } else {
                    delete peekNode;
                    lastNodeVisited = stack.top();
                    stack.pop();
                }
            }
        }
    }
};


int main() {
    BinaryTree tree;
    int n, val;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> val;
        tree.Insert(val);
    }

    tree.inOrder([](int value){cout<<value<<" ";});
    return 0;
}