#pragma once

namespace myRBTree {

enum class Color { RED, BLACK };

template <class K, class V>
struct RBTNode {

    K _key;
    V _value;
    Color _color;
    RBTNode<K, V>* _left;
    RBTNode<K, V>* _right;
    RBTNode<K, V>* _parent;

    RBTNode(K key, V value, Color color = Color::RED,
            RBTNode<K, V>* left = nullptr,
            RBTNode<K, V>* right = nullptr,
            RBTNode<K, V>* parent = nullptr) : _key(key), _value(value), _color(color), _left(left), _right(right), _parent(parent) { }

};

}
