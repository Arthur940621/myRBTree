#include <vector>
#include "RBTNode.h"
#include "RBTException.h"

namespace myRBTree {

template<class K, class V>
class RBTree;

template<class K, class V>
std::ostream& operator<<(std::ostream&, RBTree<K, V>&);

template<class K, class V>
class RBTree {

    friend std::ostream& operator<<<K, V>(std::ostream&, RBTree<K, V>&);

public:

    RBTree();
    RBTree(RBTree<K, V>& rhs);
    RBTree<K, V>& operator=(RBTree<K, V>& rhs);
    ~RBTree();

    void preOrder();
    void inOrder();
    void postOrder();
    RBTNode<K, V>*& getRoot();
    void printRBT();
    bool isRBTree();
    bool operator==(RBTree<K, V>& rhs);
    bool operator!=(RBTree<K, V>& rhs);

    V search(const K& key);
    void insert(const K& key, const V& value);
    void remove(const K& key);

protected:

    void destroy(RBTNode<K, V>*& root);
    RBTNode<K, V>* copy(RBTNode<K, V>*& root);

    void preOrder(RBTNode<K, V>* root);
    void inOrder(RBTNode<K, V>* root);
    void postOrder(RBTNode<K, V>* root);
    void printRBT(RBTNode<K, V>* root, std::size_t nLayer);
    bool isRBTree(RBTNode<K, V>* root, int BlackNum, int CurBlackNum);
    Color colorOf(RBTNode<K, V>* node);
    bool equal(RBTNode<K, V>* lhs, RBTNode<K, V>* rhs);

    void leftRotate(RBTNode<K, V>*& root, RBTNode<K, V>* x);
    void rightRotate(RBTNode<K, V>*& root, RBTNode<K, V>* x);

    RBTNode<K, V>* search(RBTNode<K, V>* root, const K& key);
    void insert(RBTNode<K, V>*& root, const K& key, const V& value);
    void insertFixUp(RBTNode<K, V>*& root, RBTNode<K, V>* node);
    void remove(RBTNode<K, V>*& root, RBTNode<K, V>* node);
    void removeFixUp(RBTNode<K, V>*& root, RBTNode<K, V>* node);

private:

    RBTNode<K, V>* _root;
};

template<class K, class V>
RBTree<K, V>::RBTree() : _root(nullptr) { }

template<class K, class V>
RBTree<K, V>::~RBTree() {
    destroy(_root);
}

template<class K, class V>
RBTree<K, V>::RBTree(RBTree<K, V>& rhs) {
    _root = copy(rhs.getRoot());
}

template<class K, class V>
RBTree<K, V>& RBTree<K, V>::operator=(RBTree<K, V>& rhs) {
    if (rhs.getRoot() == _root) {
        return *this;
    } else {
        destroy(_root);
        _root = copy(rhs.getRoot());
        return *this;
    }
}

template<class K, class V>
void RBTree<K, V>::destroy(RBTNode<K, V>*& root) {
    if (root != nullptr) {
        destroy(root->_left);
        destroy(root->_right);
        delete root;
        root = nullptr;
    }
}

template<class K, class V>
RBTNode<K, V>* RBTree<K, V>::copy(RBTNode<K, V>*& root) {
    if (root == nullptr) {
        return nullptr;
    }
    RBTNode<K, V>* temp = new RBTNode<K, V>(root->_key, root->_value);
    temp->_color = root->_color;
    temp->_left = copy(root->_left);
    temp->_right = copy(root->_right);
    if (temp->_left != nullptr) {
        temp->_left->_parent = temp;
    }
    if (temp->_right != nullptr) {
        temp->_right->_parent = temp;
    }
    return temp;
}

template<class K, class V>
RBTNode<K, V>* RBTree<K, V>::search(RBTNode<K, V>* root, const K& key) {
    if (root->_key == key) {
        return root;
    } else if (key < root->_key) {
        return search(root->_left, key);
    } else {
        return search(root->_right, key);
    }
}

template<class K, class V>
V RBTree<K, V>::search(const K& key) {
    RBTNode<K, V>* res = search(_root, key);
    if (res == nullptr) {
        throw RBTException("this keyword cannot be found.");
    } else {
        return res->_value;
    }
}

/* 左旋示意图(对节点x进行左旋)：
 *     px                              px
 *     /                               /
 *    x                               y
 *   / \      --(左旋)-->            / \
 *  lx  y                          x  ry
 *     / \                        / \
 *    ly  ry                     lx  ly
 *
 *       px                              px
 *        \                               \
 *         x                               y
 *        / \      --(左旋)-->            / \
 *       lx  y                           x  ry
 *          / \                         / \
 *         ly  ry                      lx  ly
 */
template <class K, class V>
void RBTree<K, V>::leftRotate(RBTNode<K, V>*& root, RBTNode<K, V>* x) {
    if (x != nullptr) {
        RBTNode<K, V>* y = x->_right; // 设置y是当前节点的右孩子
        x->_right = y->_left; // 将y的左孩子设为x的右孩子
        if (y->_left != nullptr) { // 如果y的左孩子非空，将x设为y的左孩子的父亲
            y->_left->_parent = x;
        }
        y->_parent = x->_parent; // y的父亲变为x的父亲
        if (x->_parent == nullptr) { // 如果x的父亲为空（x是根节点），更新根节点为y
            root = y;
        } else { // 将y节点设为x的父节点的孩子（依据x是左孩子还是右孩子）
            if (x->_parent->_left == x) {
                x->_parent->_left = y;
            } else {
                x->_parent->_right = y;
            }
        }
        y->_left = x; // x设为y的左孩子
        x->_parent = y; // y设为x的父亲
    }
}

/* 右旋示意图(对节点y进行右旋)：
 *            py                              py
 *           /                               /
 *          y                               x
 *         / \      --(右旋)-->            / \
 *        x  ry                           lx  y
 *       / \                                 / \
 *      lx  rx                              rx  ry
 * 
 *           py                              py
 *            \                               \
 *             y                               x
 *            / \      --(右旋)-->             / \
 *           x  ry                           lx  y
 *          / \                                 / \
 *         lx  rx                              rx  ry
 */
template <class K, class V>
void RBTree<K, V>::rightRotate(RBTNode<K, V>*& root, RBTNode<K, V>* y) {
    if (y != nullptr) {
        RBTNode<K, V>* x = y->_left; // 设置x是当前节点的左孩子
        y->_left = x->_right; // 将x的右孩子设为y的左孩子
        if (x->_right != nullptr) { // 如果x的右孩子非空，将y设为x的右孩子的父亲
            x->_right->_parent = y;
        }
        x->_parent = y->_parent; // x的父亲变为y的父亲
        if (y->_parent == nullptr) { // 如果x的父亲为空（x是根节点），更新根节点为y
            root = x;
        } else { // 将x节点设为y的父节点的孩子（依据y是左孩子还是右孩子）
            if (y->_parent->_left == y) {
                y->_parent->_left = x;
            } else {
                y->_parent->_right = x;
            }
        }
        x->_right = y; // y设为x的右孩子
        y->_parent = x; // x设为y的父亲
    }
}

template<class K, class V>
void RBTree<K, V>::insert(RBTNode<K, V>*& root, const K& key, const V& value) {
    RBTNode<K, V>* node = new RBTNode<K, V>(key, value);
    if (node == nullptr) {
        throw RBTException("space allocation error.");
    }
    RBTNode<K, V>* y = nullptr;
    RBTNode<K, V>* x = root;
    while (x != nullptr) { // 将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中
        y = x;
        if (node->_key < x->_key) {
            x = x->_left;
        } else if (node->_key > x->_key) {
            x = x->_right;
        } else {
            x->_value = node->_value;
            return;
        }
    }
    node->_parent = y; // 将y设置为插入节点的父亲
    if (y != nullptr) {
        if (node->_key < y->_key) {
            y->_left = node;
        } else {
            y->_right = node;
        }
    } else {
        root = node;
    }
    node->_color = Color::RED; // 设置节点为红色
    insertFixUp(root, node); //修正
}

template<class K, class V>
void RBTree<K, V>::insertFixUp(RBTNode<K, V>*& root, RBTNode<K, V>* node) {
    RBTNode<K, V>* partent, *gparent;
    while ((partent = node->_parent) && (colorOf(partent) == Color::RED)) { // 若父节点存在且父节点颜色是红色
        gparent = partent->_parent; // 因为父节点是红色，所以必有祖先节点
        if (partent == gparent->_left) { // 父节点是祖先节点的左孩子
            // case1: 叔叔节点是红色
            {
                RBTNode<K, V>* uncle = gparent->_right;
                if (uncle && (colorOf(uncle) == Color::RED)) {
                    uncle->_color = Color::BLACK;
                    partent->_color = Color::BLACK;
                    gparent->_color = Color::RED;
                    node = gparent;
                    continue;
                }
            }
            // 如果执行到这里，说明上面的语句块未执行，否则会触发continue
            // 即叔叔节点为黑色或者不存在（不存在节点也为黑色）
            // case2: 叔叔节点是黑色，且当前节点是右孩子
            if (partent->_right == node) {
                RBTNode<K, V>* tmp;
                leftRotate(root, partent);
                tmp = partent;
                partent = node;
                node = tmp;
            }
            // 无论是否执行了上面的if语句，此时叔叔节点一定是黑色，且当前节点是左孩子
            // case3: 叔叔节点是黑色，且当前节点是左孩子
            partent->_color = Color::BLACK;
            gparent->_color = Color::RED;
            rightRotate(root, gparent);
        } else { // 父节点是祖先节点的右孩子
            // case1: 叔叔节点是红色
            {
                RBTNode<K, V>* uncle = gparent->_left;
                if (uncle && (colorOf(uncle) == Color::RED)) {
                    uncle->_color = Color::BLACK;
                    partent->_color = Color::BLACK;
                    gparent->_color = Color::RED;
                    node = gparent;
                    continue;
                }
            }
            // case2: 叔叔节点是黑色，且当前节点是左孩子
            if (partent->_left == node) {
                RBTNode<K, V>* tmp;
                rightRotate(root, partent);
                tmp = partent;
                partent = node;
                node = tmp;
            }
            // case3: 叔叔节点是黑色，且当前节点是右孩子
            partent->_color = Color::BLACK;
            gparent->_color = Color::RED;
            leftRotate(root, gparent);
        }
    }
    root->_color = Color::BLACK;
}

template<class K, class V>
void RBTree<K, V>::insert(const K& key, const V& value) {
    insert(_root, key, value);
}

template<class K, class V>
void RBTree<K, V>::remove(RBTNode<K, V>*& root, RBTNode<K, V>* node) {
    if ((node->_left != nullptr) && (node->_right != nullptr)) { // 被删除节点左右孩子都不为空
        // 找到被删除节点的后继节点，用它来取代被删除节点的位置，再将被删除节点remove
        RBTNode<K, V>* successor = node;
        successor = successor->_right; // node节点必有右孩子
        while (successor->_left != nullptr) {
            successor = successor->_left;
        }
        node->_key = successor->_key;
        node->_value = successor->_value;
        node = successor; // 将success更新为待处理节点
    }
    // 执行到这里，node节点要么有左孩子，要么有右孩子，要么左右孩子都没有
    // 不可能左右孩子都有
    // 如果仅有右孩子，replacement指向右孩子
    // 如果仅有左孩子，replacement指向左孩子
    // 如果左右孩子都没有，replacement指向空
    RBTNode<K, V>* replacement = (node->_left != nullptr ? node->_left : node->_right);
    if (replacement != nullptr) { // 替代指针不为空，替代者的父亲指针指向原来node的父亲
        replacement->_parent = node->_parent;
        if (node->_parent == nullptr) { // 待删除节点为根节点
            root = replacement;
        } else if (node == node->_parent->_left) { // 待删除节点是左孩子，所以替代者依然是左孩子
            node->_parent->_left = replacement;
        } else {
            node->_parent->_right = replacement; // 待删除节点是右孩子，所以替代者依然是右孩子
        }
        node->_left = node->_right = node->_parent = nullptr;
        if (colorOf(node) == Color::BLACK) { // 需要调整,这种情况替代节点一定是红色，此时只要变色
            removeFixUp(root, replacement);
        }
    } else if (node->_parent == nullptr) { // 待删除节点为根节点，且没有左右孩子
        root = nullptr; // 直接将根节点设为空
    } else { // 待删除叶子节点node为非根节点且为叶子节点，replacement为空
        if (colorOf(node) == Color::BLACK) {
            removeFixUp(root, node);
        }
        if (node->_parent != nullptr) {
            if (node == node->_parent->_left) {
                node->_parent->_left = nullptr;
            } else {
                node->_parent->_right = nullptr;
            }
            node->_parent = nullptr;
        }
    }
    delete node;
    node = nullptr;
}

template<class K, class V>
void RBTree<K, V>::removeFixUp(RBTNode<K, V>*& root, RBTNode<K, V>* node) {
    while (node != root && colorOf(node) == Color::BLACK) { // 删除的是黑色节点，黑高不平衡
        if (node == node->_parent->_left) { // 删除节点为父节点的左孩子情况
            RBTNode<K, V>* rnode = node->_parent->_right;
            if (colorOf(rnode) == Color::RED) { // case1：兄弟节点为红色
                rnode->_color = Color::BLACK;
                node->_parent->_color = Color::RED;
                leftRotate(root, node->_parent);
                rnode = node->_parent->_right;
            }
            if (colorOf(rnode->_left) == Color::BLACK && colorOf(rnode->_right) == Color::BLACK) { // case2：兄弟节点为黑色，左右侄子节点为黑色
                rnode->_color = Color::RED;
                node = node->_parent;
            } else {
                if (colorOf(rnode->_right) == Color::BLACK) { // case3：兄弟节点为黑色，左侄子节点为红色，右侄子节点为黑色
                    rnode->_left->_color = Color::BLACK;
                    rnode->_color = Color::RED;
                    rightRotate(root, rnode);
                    rnode = node->_parent->_right;
                }
                // case4：兄弟节点为黑色，右侄子节点为红色。
                rnode->_color = rnode->_parent->_color;
                node->_parent->_color = Color::BLACK;
                rnode->_right->_color = Color::BLACK;
                leftRotate(root, node->_parent);
                node = root;
            }
        } else { // 删除节点为父节点的右孩子情况
            RBTNode<K, V>* rnode = node->_parent->_left;
            if (colorOf(rnode) == Color::RED) {
                rnode->_color = Color::BLACK;
                node->_parent->_color = Color::RED;
                rightRotate(root, node->_parent);
                rnode = node->_parent->_left;
            }
            if (colorOf(rnode->_right) == Color::BLACK && colorOf(rnode->_left) == Color::BLACK) {
                rnode->_color = Color::RED;
                node = node->_parent;
            } else {
                if (colorOf(rnode->_left) == Color::BLACK) {
                    rnode->_right->_color = Color::BLACK;
                    rnode->_color = Color::RED;
                    leftRotate(root, rnode);
                    rnode = node->_parent->_left;
                }
                rnode->_color = node->_parent->_color;
                node->_parent->_color = Color::BLACK;
                rnode->_left->_color = Color::BLACK;
                rightRotate(root, node->_parent);
                node = root;
            }
        }
    }
    node->_color = Color::BLACK; // 如果当前节点是根节点或者是红色节点，直接置黑
}

template<class K, class V>
void RBTree<K, V>::remove(const K& key) {
    RBTNode<K, V>* res = search(_root, key);
    if (res == nullptr) {
        throw RBTException("this keyword cannot be found.");
    } else {
        remove(_root, res);
    }
}

template<class K, class V>
Color RBTree<K, V>::colorOf(RBTNode<K, V>* node) {
    return node == nullptr ? Color::BLACK : node->_color;
}

template<class K, class V>
void RBTree<K, V>::printRBT() {
    printRBT(_root, 0);
}

template<class K, class V>
void RBTree<K, V>::printRBT(RBTNode<K, V>* root, std::size_t nLayer) {
    if (root == nullptr) {
        return;
    }
    printRBT(root->_right, nLayer + 1);
    for (std::size_t i = 0; i != nLayer; ++i) {
        std::cout << "        ";
    }
    std::cout << root->_value << "-" << (colorOf(root) == Color::RED ? "red" : "black") << "\n";
    printRBT(root->_left, nLayer + 1);
}

template<class K, class V>
bool RBTree<K, V>::isRBTree() {
    if (_root != NULL && colorOf(_root) == Color::RED) // 根为红则不是红黑树
        return false;

    int CurBlackNum = 0; // 用来记录每路的黑节点个数

    int BlackNum = 0; // 先统计出一条路径的黑色节点的个数
    RBTNode<K, V>* cur = _root;
    while (cur)
    {
        if (colorOf(cur) == Color::BLACK)
            BlackNum++;
        cur = cur->_left;
    }
    return isRBTree(_root, BlackNum, CurBlackNum);
}

template<class K, class V>
bool RBTree<K, V>::isRBTree(RBTNode<K, V>* root, int BlackNum, int CurBlackNum)
{
    if (root == NULL)
        return true;

    if (colorOf(root) == Color::RED && colorOf(root->_parent) == Color::RED) // 两个连续的红节点则不为红黑树
        return false;

    if (colorOf(root) == Color::BLACK) // 黑节点就将CurBlackNum++
        CurBlackNum++;

    if (root->_left == NULL && root->_right == NULL)
    {
        if (CurBlackNum == BlackNum)
            return true;
        else // 黑色节点不相等返回false
            return false;
    }

    return isRBTree(root->_left, BlackNum, CurBlackNum) && isRBTree(root->_right, BlackNum, CurBlackNum); // 判断左子树和右子树
}

template<class K, class V>
void RBTree<K, V>::preOrder(RBTNode<K, V>* root) {
    if (root != nullptr) {
        std::cout << root->_value << " ";
        preOrder(root->_left);
        preOrder(root->_right);
    }
}

template<class K, class V>
void RBTree<K, V>::preOrder() {
    preOrder(_root);
}

template<class K, class V>
void RBTree<K, V>::inOrder(RBTNode<K, V>* root) {
    if (root != nullptr) {
        inOrder(root->_left);
        std::cout << root->_value << " ";
        inOrder(root->_right);
    }
}

template<class K, class V>
void RBTree<K, V>::inOrder() {
    inOrder(_root);
}

template<class K, class V>
void RBTree<K, V>::postOrder(RBTNode<K, V>* root) {
    if (root != nullptr) {
        postOrder(root->_left);
        postOrder(root->_right);
        std::cout << root->_value << " ";
    }
}

template<class K, class V>
void RBTree<K, V>::postOrder() {
    postOrder(_root);
}

template<class K, class V>
RBTNode<K, V>*& RBTree<K, V>::getRoot() {
    return _root;
}

template<class K, class V>
bool RBTree<K, V>::equal(RBTNode<K, V>* lhs, RBTNode<K, V>* rhs) {
    if (lhs == nullptr && rhs == nullptr) {
        return true;
    }
    if (lhs != nullptr && rhs != nullptr && lhs->_key == rhs->_key && lhs->_value == rhs->_value && lhs->_color == rhs->_color && equal(lhs->_left, rhs->_left) && equal(lhs->_right, rhs->_right)) {
        return true;
    }
    return false;
}

template<class K, class V>
bool RBTree<K, V>::operator==(RBTree<K, V>& rhs) {
        return (equal(this->getRoot(), rhs.getRoot()));
}

template<class K, class V>
bool RBTree<K, V>::operator!=(RBTree<K, V>& rhs) {
    return !(*this == rhs);
}

template<class K, class V>
std::ostream& operator<<(std::ostream& os, RBTree<K, V>& rhs) {
    rhs.printRBT();
    return os;
}

}
