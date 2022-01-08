#include "AVLTree.hpp"

using namespace std;
using namespace myAVLTree;

int main() {
    AVLTree<int> tree;
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(16);
    tree.insert(15);
    tree.insert(14);
    tree.insert(13);
    tree.insert(12);
    tree.insert(11);
    tree.insert(10);
    tree.insert(8);
    tree.insert(9);
    tree.inOrder();
    cout << endl;
    

    AVLTree<int> tree1(tree);
    tree1.remove(8);
    tree1.remove(13);
    tree1.inOrder();
    cout << endl;

    AVLTree<int> tree2;
    tree2 = tree1;
    tree2.insert(8);
    tree2.insert(13);
    
    tree2.inOrder();
    cout << endl;
    cout << tree2.search(11)->_data << endl;
    cout << tree1;

    AVLTree<int> tree3 = tree;
    cout << (tree3 == tree ? "true" : "false") << " " << (tree3 != tree ? "true" : "false") << endl;
    cout << (tree3 == tree1 ? "true" : "false") << " " << (tree3 != tree1 ? "true" : "false") << endl;
    cout << tree.size() << " " << tree3.getRoot()->_left->_height << endl;

    return 0;
}