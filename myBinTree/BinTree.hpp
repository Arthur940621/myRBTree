#pragma once

#include <iostream>
#include <stack>
#include <queue>
#include "BinTreeNode.h"
#include "BinTreeException.h"

namespace myBinTree {

template<class T>
class BinTree;

template<class T>
std::ostream& operator<<(std::ostream&, BinTree<T>&);

template<class T>
std::istream& operator>>(std::istream&, BinTree<T>&);

template <typename T>
class BinTree {

    friend std::ostream& operator<<<T>(std::ostream&, BinTree<T>&);
    friend std::istream& operator>><T>(std::istream&, BinTree<T>&);

public:

    BinTree() : _root(nullptr) { } // 默认构造函数

    BinTree(const T& value) : RefValue(value), _root(nullptr) { } // 指定结束标志的构造函数

    ~BinTree() { destroy(_root); } // 析构函数

    BinTree(BinTree<T>& rhs) { // 拷贝构造函数
        _root = copy(rhs.getRoot());
    }

    BinTree<T>& operator=(BinTree<T>& rhs) { // 拷贝赋值函数
        if (rhs.getRoot() == _root) {
            return *this;
        } else {
            destroy(_root);
            _root = copy(rhs.getRoot());
            return *this;
        }
    }

    bool operator==(BinTree<T>& rhs) { return (equal(this->getRoot(), rhs.getRoot())); }

    bool operator!=(BinTree<T>& rhs) { return !(*this == rhs); }

    void createBinTree() { createBinTree(_root); } // 前序遍历创建二叉树

    void preOrder() { preOrder(_root); } // 递归先序遍历

    void inOrder() { inOrder(_root); } // 递归中序遍历

    void postOrder() { postOrder(_root); } // 递归后序遍历

    void preOrderNoRecurve() { // 非递归先序遍历
        std::stack<BinTreeNode<T>*> stk;
        BinTreeNode<T>* p = _root;
        while (p != nullptr || !stk.empty()) {
            if (p != nullptr) {
                std::cout << p->_data << " ";
                stk.push(p);
                p = p->_left;
            } else {
                p = stk.top();
                stk.pop();
                p = p->_right;
            }
        }
    }

    void inOrderNoRecurve() { // 非递归中序遍历
        std::stack<BinTreeNode<T>*> stk;
        BinTreeNode<T>* p = _root;
        while (p != nullptr || !stk.empty()) {
            if (p != nullptr) {
                stk.push(p);
                p = p->_left;
            } else {
                p = stk.top();
                stk.pop();
                std::cout << p->_data << " ";
                p = p->_right;
            }
        }
    }

    void postOrderNoRecurve() { // 非递归后序遍历
        std::stack<BinTreeNode<T>*> stk;
        BinTreeNode<T>* p= _root;
        BinTreeNode<T>* q = nullptr;
        while (p != nullptr || !stk.empty()) {
            if (p != nullptr) {
                stk.push(p);
                p = p->_left;
            } else {
                p = stk.top();
                if (p->_right == nullptr || p->_right == q) {
                    std::cout << p->_data << " ";
                    q = p;
                    stk.pop();
                    p = nullptr;
                } else {
                    p = p->_right;
                }
            }
        }
    }

    void levelOrder() { // 层次遍历
        std::queue<BinTreeNode<T>*> que;
        que.push(_root);
        BinTreeNode<T>* p = nullptr;
        while (!que.empty()) {
            p = que.front();
            que.pop();
            std::cout << p->_data << " ";
            if (p->_left != nullptr) {
                que.push(p->_left);
            }
            if (p->_right != nullptr) {
                que.push(p->_right);
            }
        }
        
    }

    BinTreeNode<T>* getRoot() { return _root; } // 获取二叉树的根节点

    BinTreeNode<T>* parent(BinTreeNode<T>* current) { // 如果没有根节点或current结点就是root结点，就没有父节点
        if (current == _root || _root == nullptr) {
            return nullptr;
        } else {
            return parent(_root, current);
        }
    }

    BinTreeNode<T>* leftChild(BinTreeNode<T>* current) { // 获取current结点的左结点
        if (current == nullptr) {
            throw BinTreeException("current node is null.");
        } else {
            return current->_left;
        }
    }

    BinTreeNode<T>* rightChild(BinTreeNode<T>* current) { // 获取current结点的右结点
        if (current == nullptr) {
            throw BinTreeException("current node is null.");
        } else {
            return current->_right;
        }
    }

    void destroy() { destroy(_root); } // 销毁二叉树

    std::size_t size() { return size(_root); } // 计算二叉树节点个数

    std::size_t height() { return height(_root); } // 计算二叉树的高度

    bool empty() { return (_root == nullptr) ? true : false; } // 判断二叉树是否为空

    void printBinTree() { printBinTree(_root, 0); } // 打印二叉树

    void invertTree() { invertTree(_root); } // 反转二叉树

protected:

    void createBinTree(BinTreeNode<T>*& subTree) { // 传进来节点指针的引用，目的是让传递进来的指针发生改变
        T item;
        if (std::cin >> item) {
            if (item != RefValue) {
                subTree = new BinTreeNode<T>(item);
                if (subTree == nullptr) {
                    throw BinTreeException("space allocation error.");
                }
                createBinTree(subTree->_left);
                createBinTree(subTree->_right);
            } else {
                subTree = nullptr;
            }
        } else {
            throw BinTreeException("cin error.");
        }
    }

    void preOrder(BinTreeNode<T>*& subTree) {
        if (subTree != nullptr) {
            std::cout << subTree->_data << " ";
            preOrder(subTree->_left);
            preOrder(subTree->_right);
        }
    }

    void inOrder(BinTreeNode<T>*& subTree) {
        if (subTree != nullptr) {
            inOrder(subTree->_left);
            std::cout << subTree->_data << " ";
            inOrder(subTree->_right);
        }
    }

    void postOrder(BinTreeNode<T>*& subTree) {
        if (subTree != nullptr) {
            postOrder(subTree->_left);
            postOrder(subTree->_right);
            std::cout << subTree->_data << " ";
        }
    }

    BinTreeNode<T>* parent(BinTreeNode<T>* subTree, BinTreeNode<T>* current) {
        if (subTree == nullptr) {
            return nullptr;
        }
        if (subTree->_left == current || subTree->_right == current) {
            return subTree;
        }
        BinTreeNode<T>* p = nullptr;
        if ((p = parent(subTree->_left, current)) != nullptr) {
            return p;
        } else {
            return parent(subTree->_right, current);
        }
    }

    void destroy(BinTreeNode<T>*& subTree) {
        if (subTree != nullptr) {
            destroy(subTree->_left);
            destroy(subTree->_right);
            delete subTree;
            subTree = nullptr;
        }
    }
    
    BinTreeNode<T>* copy(BinTreeNode<T>* orginNode) {
        if (orginNode == nullptr) {
            return nullptr;
        }
        BinTreeNode<T>* temp = new BinTreeNode<T>;
        temp->_data = orginNode->_data;
        temp->_left = copy(orginNode->_left);
        temp->_right = copy(orginNode->_right);
        return temp;
    }

    bool equal(BinTreeNode<T>* lhs, BinTreeNode<T>* rhs) {
        if (lhs == nullptr && rhs == nullptr) {
            return true;
        }
        if (lhs != nullptr && rhs != nullptr && lhs->_data == rhs->_data && equal(lhs->_left, rhs->_left) && equal(lhs->_right, rhs->_right)) {
            return true;
        }
        return false;
    }

    std::size_t size(BinTreeNode<T>* subTree) {
        if (subTree != nullptr) {
            return 1 + size(subTree->_left) + size(subTree->_right);
        } else {
            return 0;
        }
    }

    std::size_t height(BinTreeNode<T>* subTree) {
        if (subTree != nullptr) {
            std::size_t hl = height(subTree->_left);
            std::size_t hr = height(subTree->_right);
            std::size_t max = hl > hr ? hl : hr;
            return max + 1;
        } else {
            return 0;
        }
    }

    void printBinTree(BinTreeNode<T>* subTree, std::size_t nLayer) {
        if (subTree == nullptr) {
            return;
        }
        printBinTree(subTree->_right, nLayer + 1);
        for (std::size_t i = 0; i != nLayer; ++i) {
            std::cout << "   ";
        }
        std::cout << subTree->_data << " \n";
        printBinTree(subTree->_left, nLayer + 1);
    }

    void invertTree(BinTreeNode<T>* originNode) {
        if (originNode == nullptr) {
            return;
        }
        BinTreeNode<T>* temp = originNode->_left;
        originNode->_left = originNode->_right;
        originNode->_right = temp;
        invertTree(originNode->_left);
        invertTree(originNode->_right);
    }
    
private:
    T RefValue; // 数据输入停止的标志，需要一个构造函数
    BinTreeNode<T>* _root; // 根节点
};

template<class T>
std::ostream& operator<<(std::ostream& os, BinTree<T>& rhs) {
    rhs.printBinTree();
    return os;
}

template<class T>
std::istream& operator>>(std::istream& is, BinTree<T>& rhs) {
    rhs.createBinTree();
    return is;
}

}