#include "BSTree.hpp"

using namespace std;
using namespace myBSTree;

int main() {
    BSTree<char> bt1('#');
    bt1.insert('f');
    bt1.insert('e');
    bt1.insert('g');
    bt1.preOrder();
    cout << endl;
    bt1.inOrder();
    cout << endl;
    bt1.postOrder();
    cout << endl;
    cout << bt1.size() << " " << bt1.height() << endl;
    cout << bt1.search('c')->_data << endl;
    cout << bt1.getRoot()->_data << endl;

    BSTree<char> bt2(bt1);
    if (bt2 == bt1) {
        bt2.insert('d');
        cout << bt2 << endl;
        bt2.levelOrder();
        cout << endl;
    }

    BSTree<char> bt3;
    bt3 = bt2;
    if (!bt3.empty()) {
        cout << "bt1 == bt3 ? " << (bt1 == bt3 ? "true" : "false") << endl;
        bt3.remove('a');
        bt3.insert('h');
        bt3.remove('f');
        cout << bt3;
    }
    return 0;
}
