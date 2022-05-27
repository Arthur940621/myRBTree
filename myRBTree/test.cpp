#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "RBTree.hpp"

using namespace std;
using namespace myRBTree;

int main() {

    vector <pair<int, int>> vec;
    for (int i = 0; i != 1000; ++i) {
        vec.push_back({i, i});
    }
    random_shuffle(vec.begin(), vec.end());

    RBTree<int, int> tree;
    for (vector<int>::size_type i = 0; i != vec.size(); ++i) {
        tree.insert(vec[i].first, vec[i].second);
        if (!tree.isRBTree()) {
            throw RBTException("this tree is not a rbtree");
        }
    }
    tree.inOrder();
    cout << endl;

    random_shuffle(vec.begin(), vec.end());
    clock_t startTime,endTime;
    startTime = clock();
    for (vector<int>::size_type i = 0; i != vec.size(); ++i) {
        tree.search(vec[i].first);
    }
    endTime = clock();
    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

    random_shuffle(vec.begin(), vec.end());
    for (vector<int>::size_type i = 0; i != vec.size(); ++i) {
        tree.remove(vec[i].first);
        if (!tree.isRBTree()) {
            throw RBTException("this tree is not a rbtree");
        }
    }
    
    cout << (tree.getRoot() == nullptr) << endl;

    return 0;
}
