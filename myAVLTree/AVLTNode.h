#pragma once

namespace myAVLTree {

template <class T>
struct AVLTNode {
    T _data; // 节点存储的数据
    int _height; // 左子树
    AVLTNode* _left; // 右子树
    AVLTNode* _right;
    AVLTNode() : _height(0), _left(nullptr), _right(nullptr) { } // 默认构造函数
    AVLTNode(T data, std::size_t height = 0, AVLTNode<T> *left = nullptr, AVLTNode<T> *right = nullptr) :
                _data(data), _height(height), _left(left), _right(right) { } // 构造函数
};


}
