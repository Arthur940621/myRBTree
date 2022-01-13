#include <vector>
#include <algorithm>
#include <ctime>
#include "AVLTree.hpp"

using namespace std;
using namespace myAVLTree;

int main() {
    vector <int> vec;
    for (int i = 0; i != 1000; ++i) {
        vec.push_back(i);
    }
    random_shuffle(vec.begin(), vec.end());

    AVLTree<int> tree;
    for (vector<int>::size_type i = 0; i != vec.size(); ++i) {
        tree.insert(vec[i]);
        if (!tree.isBalance()) {
            throw AVLTException("this tree is not a alvtree");
        }
    }
    tree.inOrder();
    cout << endl;

    random_shuffle(vec.begin(), vec.end());
    clock_t startTime, endTime;
    startTime = clock();
    for (vector<int>::size_type i = 0; i != vec.size(); ++i) {
        tree.search(vec[i]);
    }
    endTime = clock();
    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    
    random_shuffle(vec.begin(), vec.end());
    for (vector<int>::size_type i = 0; i != vec.size(); ++i) {
        tree.remove(vec[i]);
        if (!tree.isBalance()) {
            throw AVLTException("this tree is not a alvtree");
        }
    }
    cout << (tree.empty() ? "tree is empty" : "tree is not empty") << endl;

    return 0;
}
