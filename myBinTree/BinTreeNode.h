#pragma once

namespace myBinTree {

template<class T>
struct BinTreeNode
{
    T _data; // 节点存储的数据
    BinTreeNode<T> *_left; // 左子树
    BinTreeNode<T> *_right; // 右子树
    BinTreeNode() : _left(nullptr), _right(nullptr) { } // 默认构造函数
    BinTreeNode(T data, BinTreeNode<T> *left = nullptr, BinTreeNode<T> *right = nullptr) :
                _data(data), _left(left), _right(right) { } // 构造函数
};

}

