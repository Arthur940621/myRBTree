#pragma once

namespace myBSTree
{

template<class T>
struct BSTNode {
    T _data;
    BSTNode<T>* _left; // 左子树
    BSTNode<T>* _right; // 右子树
    BSTNode() : _left(nullptr), _right(nullptr) { } // 默认构造函数
    BSTNode(T data, BSTNode<T> *left = nullptr, BSTNode<T> *right = nullptr) :
                _data(data), _left(left), _right(right) { } // 构造函数
};
    
}
