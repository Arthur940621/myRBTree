#pragma once

#include <iostream>
#include <queue>
#include "BSTNode.h"
#include "BSTException.h"

namespace myBSTree {

template<class T>
class BSTree;

template<class T>
std::ostream& operator<<(std::ostream&, BSTree<T>&);

template<class T>
class BSTree {
    
    friend std::ostream& operator<<<T>(std::ostream&, BSTree<T>&);

public:

    BSTree() : _root(nullptr) { } // 默认构造函数

    BSTree(const T& value) : RefValue(value), _root(nullptr) { // 指定结束标志的构造函数
        T x;
        std::cin >> x;
        while (x != RefValue) {
            insert(_root, x);
            std::cin >> x;
        }
    }

    ~BSTree() { // 析构函数
        destroy(_root);
    }

    BSTree(BSTree<T>& rhs) { // 拷贝构造函数
        _root = copy(rhs.getRoot());
    }

    BSTree<T>& operator=(BSTree<T>& rhs) { // 拷贝赋值函数
        if (rhs.getRoot() == _root) {
            return *this;
        } else {
            destroy(_root);
            _root = copy(rhs.getRoot());
            return *this;
        }
    }

    bool operator==(BSTree<T>& rhs) {
        return (equal(this->getRoot(), rhs.getRoot()));
    }

    bool operator!=(BSTree<T>& rhs) {
        return !(*this == rhs);
    }

    
    void preOrder() { // 递归先序遍历
        preOrder(_root);
    }

    void inOrder() { // 递归中序遍历
        inOrder(_root);
    }

    void postOrder() { // 递归后序遍历
        postOrder(_root);
    }

    void levelOrder() { // 层次遍历
        std::queue<BSTNode<T>*> que;
        que.push(_root);
        BSTNode<T>* p = nullptr;
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

    BSTNode<T>* getRoot() { // 获取二叉树的根节点
        return _root;
    }

    void insert(const T& x) { // 插入新节点
        insert(_root, x);
    }

    void remove(const T& x) { // 删除节点
        remove(_root, x);
    }

    BSTNode<T>* search(const T& x) { // 搜索节点
        return search(_root, x);
    }

    BSTNode<T>* searchNoRecurve(const T& x) { // 搜索节点非递归版
        return searchNoRecurve(_root, x);
    }

    void destroy() {// 销毁二叉树
        destroy(_root);
    }
     
    std::size_t size() { // 计算二叉树节点个数
        return size(_root);
    }

    std::size_t height() { // 计算二叉树的高度
        return height(_root);
    }

    bool empty() { // 判断二叉树是否为空
        return (_root == nullptr) ? true : false;
    }

    void printBST() { // 打印二叉树
        printBST(_root, 0);
    }

protected:

    void insert(BSTNode<T>*& subTree, const T& x) {
        if (subTree == nullptr) {
            subTree = new BSTNode<T>(x);
            if (subTree == nullptr) {
                throw BSTException("space allocation error.");
            }
        } else if (x < subTree->_data) {
            insert(subTree->_left, x);
        } else if (x > subTree->_data) {
            insert(subTree->_right, x);
        } else {
            throw BSTException("node already exists, insertion failed.");
        }
    }

    void remove(BSTNode<T>*& subTree, const T& x) {
        BSTNode<T>* p = subTree;
        BSTNode<T>* f = nullptr;
        BSTNode<T>* s = nullptr;
        BSTNode<T>* q = nullptr;
        while (p != nullptr) { // 查找关键字x的待删除节点p
            if (p->_data == x) {
                break; // 找到则跳出循环
            }
            f = p; // f指向p节点的双亲节点
            if (x < p->_data) {
                p = p->_left;
            } else {
                p = p->_right;
            }
        }
        if (p == nullptr) {
            throw BSTException("node does not exist, deletion failed."); // 若找不到，抛出异常
        }
        if (p->_left == nullptr) { // 如果p无左子树
            if (f == nullptr) { // p是原二叉排序树的根
                subTree = p->_right;
            } else if (f->_left == p) { // p是f的左孩子
                f->_left = p->_right; // 将p的右子树链到f的左链上
            } else { // p是f的右孩子
                f->_right = p->_right; // 将p的右子树链到f的右链上
            }
            delete p; // 释放被删除的节点p
        } else { // p有左子树
            q = p;
            s = p->_left;
            while (s->_right) { // 在p的左子树中查找最右下节点
                q = s;
                s = s->_right;
            }
            if (q == p) {
                q->_left = s->_left; // 将s的左子树链到q上
            } else {
                q->_right = s->_left;
            }
            p->_data = s->_data;
            delete s;
        }
    }

    BSTNode<T>* search(BSTNode<T>*& subTree, const T& x) {
        if (subTree == nullptr) {
            throw BSTException("this node could not be found.");
        } else if (subTree->_data == x) {
            return subTree;
        } else if (x < subTree->_data) {
            return search(subTree->_left, x);
        } else {
            return search(subTree->_right, x);
        }
    }

    BSTNode<T>* searchNoRecurve(BSTNode<T>*& subTree, const T& x) {
        BSTNode<T>* q = subTree;
        while (q != nullptr) {
            if (q->_data == x) {
                return q;
            }
            if (x < q->_data) {
                q = q->_left;
            } else {
                q = q->_right;
            }
        }
        return nullptr;
    }

    void preOrder(BSTNode<T>*& subTree) { // 前序遍历
        if (subTree != nullptr) {
            std::cout << subTree->_data << " ";
            preOrder(subTree->_left);
            preOrder(subTree->_right);
        }
    }

    void inOrder(BSTNode<T>*& subTree) { // 中序遍历
        if (subTree != nullptr) {
            inOrder(subTree->_left);
            std::cout << subTree->_data << " ";
            inOrder(subTree->_right);
        }
    }

    void postOrder(BSTNode<T>*& subTree) { // 后续遍历
        if (subTree != nullptr) {
            postOrder(subTree->_left);
            postOrder(subTree->_right);
            std::cout << subTree->_data << " ";
        }
    }

    void destroy(BSTNode<T>*& subTree) {
        if (subTree != nullptr) {
            destroy(subTree->_left);
            destroy(subTree->_right);
            delete subTree;
            subTree = nullptr;
        }
    }

    BSTNode<T>* copy(BSTNode<T>* orginNode) {
        if (orginNode == nullptr) {
            return nullptr;
        }
        BSTNode<T>* temp = new BSTNode<T>;
        temp->_data = orginNode->_data;
        temp->_left = copy(orginNode->_left);
        temp->_right = copy(orginNode->_right);
        return temp;
    }

    bool equal(BSTNode<T>* lhs, BSTNode<T>* rhs) {
        if (lhs == nullptr && rhs == nullptr) {
            return true;
        }
        if (lhs != nullptr && rhs != nullptr && lhs->_data == rhs->_data && equal(lhs->_left, rhs->_left) && equal(lhs->_right, rhs->_right)) {
            return true;
        }
        return false;
    }

    void printBST(BSTNode<T>* subTree, std::size_t nLayer) {
        if (subTree == nullptr) {
            return;
        }
        printBST(subTree->_right, nLayer + 1);
        for (std::size_t i = 0; i != nLayer; ++i) {
            std::cout << "   ";
        }
        std::cout << subTree->_data << " \n";
        printBST(subTree->_left, nLayer + 1);
    }

    std::size_t size(BSTNode<T>* subTree) {
        if (subTree != nullptr) {
            return 1 + size(subTree->_left) + size(subTree->_right);
        } else {
            return 0;
        }
    }

    std::size_t height(BSTNode<T>* subTree) {
        if (subTree != nullptr) {
            std::size_t hl = height(subTree->_left);
            std::size_t hr = height(subTree->_right);
            std::size_t max = hl > hr ? hl : hr;
            return max + 1;
        } else {
            return 0;
        }
    }

private:
    T RefValue; // 数据输入停止的标志
    BSTNode<T>* _root; // 根节点
};

template<class T>
std::ostream& operator<<(std::ostream& os, BSTree<T>& rhs) {
    rhs.printBST();
    return os;
}

}
