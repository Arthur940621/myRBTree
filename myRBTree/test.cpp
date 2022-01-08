#include <iostream>
#include "RBTree.hpp"

using namespace std;
using namespace myRBTree;

int main() {
    RBTree<char, int> tree;
    char c1 = 'a';
    for (int i = 0; i != 26; ++i) {
        if (!tree.isRBTree()) {
            throw RBTException("this tree is not a rbtree.");
        } else {
            tree.insert(c1, i);
            ++c1;
        }
    }
    tree.inOrder();
    cout << endl;

    char c2 = 'a';
    for (int i = 0; i != 26; ++i) {
        cout << tree.search(c2) << endl;
        ++c2;
    }

    RBTree<char, int> tree2(tree);
    std::cout << (tree2 == tree) << endl;
    char c3 = 'h';
    for (int i = 0; i != 12; ++i) {
        if (!tree.isRBTree()) {
            throw RBTException("this tree is not a rbtree.");
        } else {
            tree2.remove(c3);
            ++c3;
        }
    }
    
    RBTree<char, int> tree3;
    tree3 = tree;
    std::cout << (tree3 != tree2) << endl;
    cout << tree3;
    return 0;
}