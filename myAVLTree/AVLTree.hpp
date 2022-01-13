#include <iostream>
#include <queue>
#include <stack>
#include "AVLTNode.h"
#include "AVLTException.h"

namespace myAVLTree {

template<class T>
class AVLTree;

template<class T>
std::ostream& operator<<(std::ostream&, AVLTree<T>&);

template<class T>
class AVLTree {

    friend std::ostream& operator<<<T>(std::ostream&, AVLTree<T>&);

public:
    AVLTree() : _root(nullptr) { } // 默认构造函数

    ~AVLTree() { // 析构函数
        destroy(_root);
    }

    AVLTree(AVLTree<T>& rhs) { // 拷贝构造函数
        _root = copy(rhs.getRoot());
    }

    AVLTree<T>& operator=(AVLTree<T>& rhs) { // 拷贝赋值函数
        if (rhs.getRoot() == _root) {
            return *this;
        } else {
            destroy(_root);
            _root = copy(rhs.getRoot());
            return *this;
        }
    }

    bool operator==(AVLTree<T>& rhs) { // 判断是否相等
        return (equal(this->getRoot(), rhs.getRoot()));
    }

    bool operator!=(AVLTree<T>& rhs) { // 判断是否不相等
        return !(*this == rhs);
    }

    
    void preOrder() { // 递归先序遍历
        preOrder(_root);
    }

    void inOrder() { // 递归中序遍历
        inOrder(_root);
    }

    void postOrder() { // 递归后序遍历
        postOrder(_root);
    }

    void levelOrder() { // 层次遍历
        std::queue<AVLTNode<T>*> que;
        que.push(_root);
        AVLTNode<T>* p = nullptr;
        while (!que.empty()) {
            p = que.front();
            que.pop();
            std::cout << p->_data << " ";
            if (p->_left != nullptr) {
                que.push(p->_left);
            }
            if (p->_right != nullptr) {
                que.push(p->_right);
            }
        }
    }

    AVLTNode<T>* getRoot() { // 获取二叉树的根节点
        return _root;
    }

    void insert(const T& x) { // 插入新节点
        insert(_root, x);
    }

    void remove(const T& x) { // 删除节点
        AVLTNode<T>* z = search(_root, x);
        remove(_root, z);
        // if (z != nullptr) {
        //     _root = remove(_root, z);
        // }
    }

    AVLTNode<T>* search(const T& x) { // 搜索节点
        return search(_root, x);
    }

    void destroy() {// 销毁二叉树
        destroy(_root);
    }
     
    std::size_t size() { // 计算二叉树节点个数
        return size(_root);
    }

    int height() { // 计算二叉树的高度
        return height(_root);
    }

    bool empty() { // 判断二叉树是否为空
        return (_root == nullptr) ? true : false;
    }

    void printAVL() { // 打印二叉树
        printAVL(_root, 0);
    }

    bool isBalance() {
        return isBalance(_root);
    }

protected:

    AVLTNode<T>* search(AVLTNode<T>*& subTree, const T& x) { // 搜索节点
        if (subTree == nullptr) {
            throw AVLTException("this node could not be found.");
        } else if (subTree->_data == x) {
            return subTree;
        } else if (x < subTree->_data) {
            return search(subTree->_left, x);
        } else {
            return search(subTree->_right, x);
        }
    }

    void preOrder(AVLTNode<T>*& subTree) { // 前序遍历
        if (subTree != nullptr) {
            std::cout << subTree->_data << " ";
            preOrder(subTree->_left);
            preOrder(subTree->_right);
        }
    }

    void inOrder(AVLTNode<T>*& subTree) { // 中序遍历
        if (subTree != nullptr) {
            inOrder(subTree->_left);
            std::cout << subTree->_data << " ";
            inOrder(subTree->_right);
        }
    }

    void postOrder(AVLTNode<T>*& subTree) { // 后续遍历
        if (subTree != nullptr) {
            postOrder(subTree->_left);
            postOrder(subTree->_right);
            std::cout << subTree->_data << " ";
        }
    }

    void destroy(AVLTNode<T>*& subTree) { // 销毁二叉树
        if (subTree != nullptr) {
            destroy(subTree->_left);
            destroy(subTree->_right);
            delete subTree;
            subTree = nullptr;
        }
    }

    AVLTNode<T>* copy(AVLTNode<T>* orginNode) { // 拷贝二叉树
        if (orginNode == nullptr) {
            return nullptr;
        }
        AVLTNode<T>* temp = new AVLTNode<T>;
        temp->_data = orginNode->_data;
        temp->_height = orginNode->_height;
        temp->_left = copy(orginNode->_left);
        temp->_right = copy(orginNode->_right);
        return temp;
    }

    bool equal(AVLTNode<T>* lhs, AVLTNode<T>* rhs) { // 判断是否相等
        if (lhs == nullptr && rhs == nullptr) {
            return true;
        }
        if (lhs != nullptr && rhs != nullptr && lhs->_data == rhs->_data && lhs->_height == rhs->_height && equal(lhs->_left, rhs->_left) && equal(lhs->_right, rhs->_right)) {
            return true;
        }
        return false;
    }

    /* LL: 左子树的左边失去平衡(左单旋转)
     *       k2              k1     
     *      /  \            /  \
     *     k1   z   ===>   x    k2
     *    /  \                 /  \
     *   x    y               y    z
     */
    AVLTNode<T>* leftLeftRotation(AVLTNode<T>*& k2) { // LL旋转
        AVLTNode<T>* k1 = k2->_left;
        k2->_left = k1->_right;
        k1->_right = k2;
        k2->_height = std::max(height(k2->_left), height(k2->_right)) + 1;
        k1->_height = std::max(height(k1->_left), k2->_height) + 1;
        return k1;
    }

    /* RR: 右子树的右边失去平衡(右单旋转)
     *       k1              k2     
     *      /  \            /  \
     *     x   k2   ===>   k1   z
     *        /  \        /  \   
     *       y    z      x    y  
     */
    AVLTNode<T>* rightRightRotation(AVLTNode<T>*& k1) { // RR旋转
        AVLTNode<T>* k2 = k1->_right;
        k1->_right = k2->_left;
        k2->_left = k1;
        k1->_height = std::max(height(k1->_left), height(k1->_right)) + 1;
        k2->_height = std::max(height(k2->_right), k1->_height) + 1;
        return k2;
    }

    /* LR: 左子树的右边失去平衡(左双旋转)
     *       k3               k3               k2
     *      /  \     RR      /  \     LL      /  \
     *     k1   D   ===>   k2    D   ===>   k1    k3
     *    /  \            /  \             /  \  /  \
     *   A    K2         k1   C           A    B C   D
     *       /  \       /  \
     *      B    C     A    B
     */
    AVLTNode<T>* leftRightRotation(AVLTNode<T>*& k3) { // LR旋转
        k3->_left = rightRightRotation(k3->_left);
        return leftLeftRotation(k3);
    }

    /* RL: 右子树的左边失去平衡(右双旋转)
     *     k1               k1                K2
     *    /  \      LL     /  \      RR      /  \
     *   A    k3   ===>   A    k2   ===>   k1    K3
     *       /  \             /  \        /  \  /  \
     *      k2   D           B    k3     A    B C   D
     *     /  \                  /  \
     *    B    D                C     D
     */
    AVLTNode<T>* rightLeftRotation(AVLTNode<T>*& k1) { // RR旋转
        k1->_right = leftLeftRotation(k1->_right);
        return rightRightRotation(k1);
    }

    AVLTNode<T>* maximum(AVLTNode<T>* subTree) { // 找出最大节点（最右节点）
        if (subTree == nullptr) {
            return nullptr;
        }
        while (subTree->_right != nullptr) {
            subTree = subTree->_right;
        }
        return subTree;
    }

    AVLTNode<T>* minimum(AVLTNode<T>* subTree) { // 找出最小节点（最左节点）
        if (subTree == nullptr) {
            return nullptr;
        }
        while (subTree->_left != nullptr) {
            subTree = subTree->_left;
        }
        return subTree;
    }

    void insert(AVLTNode<T>*& subTree, const T& x) { // 插入
        if (subTree == nullptr) {
            subTree = new AVLTNode<T>(x);
            if (subTree == nullptr) {
                throw AVLTException("space allocation error.");
            }
        } else if (x < subTree->_data) {
            insert(subTree->_left, x);
            subTree->_height = std::max(height(subTree->_left), height(subTree->_right)) + 1;
            if (height(subTree->_left) - height(subTree->_right) == 2) {
                if (x < subTree->_left->_data) {
                    subTree = leftLeftRotation(subTree);
                } else {
                    subTree = leftRightRotation(subTree);
                }
            } 
        } else if (x >= subTree->_data) {
            insert(subTree->_right, x);
            subTree->_height = std::max(height(subTree->_left), height(subTree->_right)) + 1;
            if (height(subTree->_right) - height(subTree->_left) == 2) {
                if (x > subTree->_right->_data) {
                    subTree = rightRightRotation(subTree);
                } else {
                    subTree = rightLeftRotation(subTree);
                }
            }
        } else {
            throw AVLTException("node already exists, insertion failed.");
        }
    }

    void remove(AVLTNode<T>*& subTree, AVLTNode<T>*& z) { // 删除
        if (subTree == nullptr || z == nullptr) {
            return;
        }
        if (z->_data < subTree->_data) { // 待删除的节点在subTree的左子树中
            remove(subTree->_left, z);
            if (height(subTree->_right) - height(subTree->_left) == 2) { // 删除节点后，若AVL树失去平衡，则进行相应的调节
                AVLTNode<T>* r = subTree->_right;
                if (height(r->_left) > height(r->_right)) {
                    subTree = rightLeftRotation(subTree);
                } else {
                    subTree = rightRightRotation(subTree);
                }
            }
        } else if (z->_data > subTree->_data) { // 待删除的节点在subTree的右子树中
            remove(subTree->_right, z);
            if (height(subTree->_left) - height(subTree->_right) == 2) { // 删除节点后，若AVL树失去平衡，则进行相应的调节
                AVLTNode<T>* l = subTree->_left;
                if (height(l->_left) < height(l->_right)) {
                    subTree = leftRightRotation(subTree);
                } else {
                    subTree = leftLeftRotation(subTree);
                }
            }
        } else { // subTree就是要删除的节点
            if (subTree->_left != nullptr && subTree->_right != nullptr) { // subTree左右孩子都非空
                if (height(subTree->_left) > height(subTree->_right)) {
                    // 如果subTree的左子树比右子树高；
                    // 则(01)找出subTree的左子树中的最大节点
                    //   (02)将该最大节点的值赋值给subTree
                    //   (03)删除该最大节点
                    // 这类似于用"subTree的左子树中最大节点"做"subTree"的替身；
                    // 采用这种方式的好处是: 删除"subTree的左子树中最大节点"之后，AVL树仍然是平衡的
                    AVLTNode<T>* max = maximum(subTree->_left);
                    subTree->_data = max->_data;
                    remove(subTree->_left, max);
                } else {
                    // 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
                    // 则(01)找出tree的右子树中的最小节点
                    //   (02)将该最小节点的值赋值给tree
                    //   (03)删除该最小节点
                    // 这类似于用"tree的右子树中最小节点"做"tree"的替身；
                    // 采用这种方式的好处是: 删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的
                    AVLTNode<T>* min = minimum(subTree->_right);
                    subTree->_data = min->_data;
                    remove(subTree->_right, min);
                }
            } else { // subTree有一个子树，指向该节点的指针指向子树，释放该节点的内存，如果是叶子节点，直接删除
                AVLTNode<T>* temp = subTree;
                subTree = (subTree->_left == nullptr) ? subTree->_right : subTree->_left;
                delete temp;
            }
        }
        if (subTree != nullptr) {
            subTree->_height = std::max(height(subTree->_left), height(subTree->_right)) + 1;
        }
    }

    void printAVL(AVLTNode<T>* subTree, std::size_t nLayer) {
        if (subTree == nullptr) {
            return;
        }
        printAVL(subTree->_right, nLayer + 1);
        for (std::size_t i = 0; i != nLayer; ++i) {
            std::cout << "     ";
        }
        std::cout << subTree->_data << "-" << subTree->_height << "\n";
        printAVL(subTree->_left, nLayer + 1);
    }

    std::size_t size(AVLTNode<T>* subTree) { // 节点个数
        if (subTree != nullptr) {
            return 1 + size(subTree->_left) + size(subTree->_right);
        } else {
            return 0;
        }
    }

    int height(AVLTNode<T>* subTree) { // 树的高度
        return subTree == nullptr ? 0 : subTree->_height;
    }

    bool isBalance(AVLTNode<T>* subTree) { // 是否平衡
        if (subTree == nullptr) {
            return true;;
        }
        return (std::abs(height(subTree->_left) - height(subTree->_right)) <= 1 && isBalance(subTree->_left) && isBalance(subTree->_right));
    }

private:

    AVLTNode<T>* _root;
};

template<class T>
std::ostream& operator<<(std::ostream& os, AVLTree<T>& rhs) {
    rhs.printAVL();
    return os;
}

}
