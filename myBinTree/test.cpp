#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include "BinTree.hpp"
using namespace std;
using namespace myBinTree;

int main() {
    BinTree<char> bt1('#');
    cin >> bt1;
    if (!bt1.empty()) {
        bt1.preOrder();
        cout << endl;
        bt1.inOrder();
        cout << endl;
        bt1.postOrder();
        cout << endl;
        cout << bt1.size() << endl;
        cout << bt1.height() << endl;
    }

    BinTree<char> bt2(bt1);
    if (bt2 == bt1) {
        bt2.invertTree();
        bt2.preOrderNoRecurve();
        cout << endl;
        bt2.inOrderNoRecurve();
        cout << endl;
        bt2.postOrderNoRecurve();
        cout << endl;
        cout << bt1 << bt2 << endl;
    }

    BinTree<char> bt3('$');
    bt3 = bt2;
    cout << "bt2 != bt3 ? " << (bt2 != bt3 ? "true" : "false") << endl;
    bt3.levelOrder();
    auto bt3Node = bt3.rightChild(bt3.leftChild(bt3.getRoot()));
    cout << endl;
    cout << bt3.parent(bt3Node)->_data << endl;
    
    return 0;
}