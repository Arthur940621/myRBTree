# 二叉树

## 定义

满足以下两个条件的树结构称为二叉树：

* 每个节点的度都不大于 `2`。
* 每个节点的孩子节点次序不能任意颠倒。

它有五种基本形态：

![](https://raw.githubusercontent.com/Arthur940621/image/main/Project/RBTree/001.png)

## 性质

二叉树有以下几个性质：

* 性质 `1`：二叉树第 `i` 层上的结点数目最多为 `2^(i-1)`，其中 `(i≥1)`。
* 性质 `2`：深度为 `k` 的二叉树至多有 `2^k - 1` 个结点，其中 `(k≥1)`，`2^0 + 2^1 + … + 2^(k-1) = 2^k - 1`。
* 性质 `3`：在任意一棵二叉树中，若叶子结点的个数为 `n0`，度为 `2` 的结点数为 `n2`，则 `n0 = n2 + 1`。

# 满二叉树

## 定义

深度为 `k` 且有 `2^k - 1` 个节点的二叉树。在满二叉树中，每层节点都是满的，即每层节点都有最大节点数。

满二叉树的示意图如下：

![](https://raw.githubusercontent.com/Arthur940621/image/main/Project/RBTree/002.png)

# 完全二叉树

## 定义

深度为 `k`，节点数为 `n` 的二叉树，如果其节点 `1 ~ n` 的位置序号分别与等高的满二叉树的节点 `1 ~ n` 的位置序号一一对应，则为完全二叉树。

完全二叉树的示意图如下：

![](https://raw.githubusercontent.com/Arthur940621/image/main/Project/RBTree/003.png)

## 性质

* 具有 n 个节点的完全二叉树的深度为 `⌊log2n⌋ + 1`。
* 对于具有 n 个节点的完全二叉树，如果按照从上到下、从左到右的顺序对二叉树中的所有节点从 1 开始顺序编号，则对于任意的序号为 i 的节点有：
    * 如果 `i = 1`，则序号为 `i` 的节点是根节点，无双亲节点；如果 `i > 1`，则序号为 `i` 的节点的双亲节点序号是 `⌊i/2⌋`。
    * 如果 `2i > n`，则序号为 `i` 的节点无左孩子；如果 `2i ≤ n`，则序号为 `i` 的节点的左孩子节点的序号为 `2i`。
    * 如果 `2i + 1 > n`，则序号为 `i` 的节点无右孩子；如果 `2i + 1 ≤ n`，则序号为 `i` 的节点的右孩子节点的序号为 `2i + 1`。

# 二叉排序树

## 定义

或者是一棵空树，或者是具有如下性质的二叉树：

* 若它的左子树非空，则左子树上所有结点的值均小于它的根结点的值；
* 若它的右子树非空，则右子树上所有结点的值均大于（或大于等于）它的根结点的值；
* 左、右子树分别为二叉排序树。

## 查找：

从根节点开始查找；

若查找值比当前值大，则搜索右子树；

若查找值等于当前值，停止查找，返回当前节点；

若查找值比当前值小，则搜索左子树。

## 插入：

插入类似于查找过程，从根节点开始比较，小于根节点的话就和左子树比较，反之与右子树比较，直到左子树为空或者右子树为空，则插入到相应为空的位置。

## 删除：

本质上是找前驱或者后继节点来替代；

叶子节点直接删除（没有前驱或后继节点）；

只有一个子节点的用子节点替代（本质上就是找的前驱节点或者是后继节点，左节点就是前驱节点，右节点就是后继节点）；

有两个子节点的，需要找到替代节点（替代节点就是前驱节点或者后继节点）。

![](https://raw.githubusercontent.com/Arthur940621/image/main/Project/RBTree/004.png)

# 平衡二叉排序树

## 定义

一颗平衡二叉排序树或者是空树，或者是具有下列性质的二叉排序树：

* 左子树与右子树的高度之差的绝对值小于等于 `1`。
* 左子树和右子树页数平衡二叉排序树。

二叉排序树存在的问题是，树在插入的时候会导致倾斜，不同的插入顺序会导致数的高度不一样，而树的高度直接影响了树的查找效率。最坏的情况所有的节点都在一条斜线上。

平衡二叉排序树的查找、插入和删除在平均和最坏情况下时间复杂度均为 `O(log2n)`。

如果在平衡二叉排序树中插入或删除节点后，使得高度之差大于 `1`。此时，平衡二叉排序树的平衡状态就被破坏，不再平衡，为了维持一个平衡状态，需要对其进行旋转处理。

平衡二叉排序树加入了平衡因子概念，定义为：

某个结点的左子树的高度减去右子树的高度得到的差值。所有结点的平衡因子的绝对值都不超过 `1`。

## 失衡

平衡二叉排序树进行插入或删除节点后，可能导致失去平衡。这种失衡可以概括为 `4` 种姿态：

`LL`（左左），`LR`（左右），`RR`（右右）和 `RL`（右左）：

![](https://raw.githubusercontent.com/Arthur940621/image/main/Project/RBTree/005.png)

除了上面的情况之外，还有其它的失去平衡的衡二叉排序树，如下图：

![](https://raw.githubusercontent.com/Arthur940621/image/main/Project/RBTree/006.png)

失去平衡时的情况一定是 `LL`、`LR`、`RL`、`RR` 这 `4` 种之一，它们都由各自的定义：

* `LL`：插入或删除一个节点后，根节点的左子树的左子树还有非空子节点，导致根的左子树的高度比根的右子树的高度大 `2`，导致失去了平衡。
  * 例如，在上面 `LL` 情况中，由于根节点 `(8)` 的左子树 `(4)` 的左子树 `(2)` 还有非空子节点，而根节点 `(8)` 的右子树 `(12)` 没有子节点；导致根节点 `(8)` 的左子树 `(4)` 高度比根节点 `(8)` 的右子树 `(12)`高 `2`。

* `LR`：插入或删除一个节点后，根节点的左子树的右子树还有非空子节点，导致根的左子树的高度比根的右子树的高度大 `2`，导致失去了平衡。
  * 例如，在上面 `LR` 情况中，由于根节点 `(8)` 的左子树 `(4)` 的左子树 `(6)` 还有非空子节点，而根节点 `(8)` 的右子树 `(12)` 没有子节点；导致根节点 `(8)` 的左子树 `(4)` 高度比根节点 `(8)` 的右子树 `(12)`高 `2`。

* `RL`：插入或删除一个节点后，根节点的右子树的左子树还有非空子节点，导致根的右子树的高度比根的左子树的高度大 `2`，导致失去了平衡。
  * 例如，在上面 `RL` 情况中，由于根节点 `(8)` 的右子树 `(12)` 的左子树 `(10)` 还有非空子节点，而根节点 `(8)` 的左子树 `(4)` 没有子节点；导致根节点 `(8)` 的右子树 `(12)` 高度比根节点 `(8)` 的左子树 `(4)`高 `2`。

* `RR`：插入或删除一个节点后，根节点的右子树的右子树还有非空子节点，导致根的右子树的高度比根的左子树的高度大 `2`，导致失去了平衡。
  * 例如，在上面 `RR` 情况中，由于根节点 `(8)` 的右子树 `(12)` 的右子树 `(14)` 还有非空子节点，而根节点 `(8)` 的左子树 `(4)` 没有子节点；导致根节点 `(8)` 的右子树 `(12)` 高度比根节点 `(8)` 的左子树 `(4)`高  `2`。

在平衡二叉排序树中进行插入或删除节点后，可能导致平衡二叉排序树失去平衡。失去平衡之后，可以通过旋转使其恢复平衡，下面分别介绍 `LL`，`LR`，`RR` 和 `RL` 这 `4` 种情况对应的旋转方法。

## 旋转

通过左旋或者右旋，使得平衡二叉排序树实现平衡。

`LL` 失去平衡的情况，可以通过一次旋转恢复平衡。如下图：

![](https://raw.githubusercontent.com/Arthur940621/image/main/Project/RBTree/007.png)

实现代码：

```cpp
/* LL：左子树的左边失去平衡(左单旋转)
 *       k2              k1     
 *      /  \            /  \
 *     k1   z   ===>   x    k2
 *    /  \                 /  \
 *   x    y               y    z
 */
AVLTNode<T>* leftLeftRotation(AVLTNode<T>*& k2) {
    AVLTNode<T>* k1 = k2->_left; // k1指向k2的左孩子(左边比右边高，一定存在左孩子)
    k2->_left = k1->_right; // 断开k1与k2的链接，k2的左孩子指向k1的右孩子
    k1->_right = k2; // 将k1变为k2的父亲节点
    k2->_height = std::max(height(k2->_left), height(k2->_right)) + 1; // 先更新k2的高度
    k1->_height = std::max(height(k1->_left), k2->_height) + 1; // k1的高度取决于k2，x、y、z的高度没有变化
    return k1; // 返回旋转后的根节点k1
}
```

`RR` 的旋转与 `LL` 对称：

![](https://raw.githubusercontent.com/Arthur940621/image/main/Project/RBTree/008.png)

实现代码：

```cpp
/* RR：右子树的右边失去平衡(右单旋转)
 *       k1              k2     
 *      /  \            /  \
 *     x   k2   ===>   k1   z
 *        /  \        /  \   
 *       y    z      x    y  
 */
AVLTNode<T>* rightRightRotation(AVLTNode<T>*& k1) {
    AVLTNode<T>* k2 = k1->_right;
    k1->_right = k2->_left;
    k2->_left = k1;
    k1->_height = std::max(height(k1->_left), height(k1->_right)) + 1;
    k2->_height = std::max(height(k2->_right), k1->_height) + 1;
    return k2;
}
```

`LR` 失去平衡的情况，需要经过两次旋转才能恢复平衡。如下图：

![](https://raw.githubusercontent.com/Arthur940621/image/main/Project/RBTree/009.png)

第一次旋转是围绕 `k1` 进行的 `RR` 旋转，第二次是围绕 `k3` 进行的 `LL` 旋转。

实现代码：

```cpp
/* LR：左子树的右边失去平衡(左双旋转)
*       k3               k3               k2
*      /  \     RR      /  \     LL      /  \
*     k1   D   ===>   k2    D   ===>   k1    k3
*    /  \            /  \             /  \  /  \
*   A    K2         k1   C           A    B C   D
*       /  \       /  \
*      B    C     A    B
*/
AVLTNode<T>* leftRightRotation(AVLTNode<T>*& k3) {
  k3->_left = rightRightRotation(k3->_left);
  return leftLeftRotation(k3);
}
```

`RL` 与 `LR` 对称：

![](https://raw.githubusercontent.com/Arthur940621/image/main/Project/RBTree/010.png)

实现代码：

```cpp
/* RL：右子树的左边失去平衡(右双旋转)
*     k1               k1                K2
*    /  \      LL     /  \      RR      /  \
*   A    k3   ===>   A    k2   ===>   k1    K3
*       /  \             /  \        /  \  /  \
*      k2   D           B    k3     A    B C   D
*     /  \                  /  \
*    B    D                C     D
*/
AVLTNode<T>* rightLeftRotation(AVLTNode<T>*& k1) {
  k1->_right = leftLeftRotation(k1->_right);
  return rightRightRotation(k1);
}
```

## 插入

插入类似于二叉排序树，递归插入，比根节点值小插入左子树，比根节点值大插入右子树，遇到 `nullptr` 后新建节点。返回到上一层递归（父节点）。

进入 `else if` 后更新高度，判断左右子树高度之差。

如果左右子树绝对值之差不等于 `2`（二叉排序树的左右子树之差只可能是 `0` 或 `1`，插入一个节点后有可能变成 `2`），说明没有失衡，跳出本层递归。

否则，如果插入的是左子树的左子树，`LL` 旋转，如果插入的是左子树的右子树，`LR` 旋转，如果插入的是右子树的右子树，`RR` 旋转，如果插入的是右子树的左子树，`RL` 旋转。

```cpp
void insert(AVLTNode<T>*& subTree, const T& x) {
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
```

## 删除

删除类似于二叉排序树，待删除的节点在左子树中，递归进入左子树，待删除的节点在右子树中，递归进入右子树。

找到待删除节点后，判断其节点是否左右孩子都存在，如果仅有一棵子树或者是叶子节点，直接用其子树节点替代即可（叶子节点的子树是 `nullptr`）。

如果左右孩子都存在，根据左右孩子的高度选择前驱或后继节点替代，问题转变为删除左（右）子树上的最右（左）节点，该节点一定仅有一棵子树或者是叶子节点。

节点删除后，沿着删除节点递归返回，判断是否失衡。

如果失衡：
* 如果右子树比左子树高，即删除的节点在 `subTree` 的左子树中：
  * 令 `r` 指向该节点的右子树。
  * 如果 `r` 的左子树的高度大于 `r` 的右子树的高度，`RL` 旋转。
  * 如果 `r` 的左子树的高度小于等于 `r` 的右子树的高度，`RR` 旋转。
* 如果左子树比右子树高，即删除的节点在 `subTree` 的右子树中：
  * 令 `l` 指向该节点的左子树。
  * 如果 `l` 的左子树的高度小于 `l` 的右子树的高度，`LR` 旋转。
  * 如果 `l` 的左子树的高度大于等于 `l` 的右子树的高度，`LL` 旋转。

最后沿着递归方向调整高度。

```cpp
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
                // 这类似于用subTree的左子树中最大节点做subTree的替身；
                // 采用这种方式的好处是：删除subTree的左子树中最大节点之后，AVL树仍然是平衡的
                AVLTNode<T>* max = maximum(subTree->_left);
                subTree->_data = max->_data;
                remove(subTree->_left, max);
            } else {
                // 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
                // 则(01)找出tree的右子树中的最小节点
                //   (02)将该最小节点的值赋值给tree
                //   (03)删除该最小节点
                // 这类似于用tree的右子树中最小节点做tree的替身；
                // 采用这种方式的好处是：删除tree的右子树中最小节点之后，AVL树仍然是平衡的
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
```

# `2-3-4` 树

## 定义 
`2-3-4` 树是四阶的 `B` 树，他属于一种多路查找树，它的结构有以下限制：

* 所有叶子节点都拥有相同的深度。
* 节点只能是 `2节点`、`3节点`、`4节点` 之一。
    * `2节点`：包含 `1` 个元素的节点，有 `2` 个子节点或者没有子节点。
    * `3节点`：包含 `2` 个元素的节点，有 `3` 个子节点或者没有子节点。
    * `4节点`：包含 `3` 个元素的节点，有 `4` 个子节点或者没有子节点。

* 元素始终保持排序顺序，整体上保持二叉查找树的性质，即父结点大于左子结点，小于右子结点；而且结点有多个元素时，每个元素必须大于它左边的和它的左子树中元素。

下图是一个 `2-3-4` 树：

![](https://raw.githubusercontent.com/Arthur940621/image/main/Project/RBTree/011.png)

## 插入

* 如果 `2-3-4` 树中已存在当前插入的值，则插入失败，否则最终一定是在叶子节点中进行插入操作。
* 如果待插入的节点不是 `4节点`，那么直接在该节点插入。
* 如果待插入的节点是 `4节点`，那么应该先分裂该节点然后再插入。一个 `4节点` 可以分裂成一个根节点和两个子节点（这三个节点各含一个值）然后在子节点中插入，把分裂形成的根节点中的值看成向上层插入的值，然后重复第 `2` 步和第 `3` 步。

如果是在 `4节点` 中进行插入，每次插入会多出一个分支，如果插入操作导致根节点分裂，则 `2-3-4` 树会生长一层。

`2-3-4` 树都是自下向上生长的：

![](https://raw.githubusercontent.com/Arthur940621/image/main/Project/RBTree/012.png)

## 删除：

* 如果 `2-3-4` 树中不存在当前需要删除的值，则删除失败。
* 如果当前需要删除的值不位于叶子节点上，则用后继值覆盖，然后在它后继值所在的子支中删除该后继值。
* 如果当前需要删除的值位于叶子节点上：
    * 该节点不是 `2节点`，删除值，结束。
    * 该节点是 `2节点`，删除该节点：
        * 如果兄弟节点不是 `2节点`，则父节点中的值下移到该节点，兄弟节点中的一个值上移。
        * 如果兄弟节点是 `2节点`，父节点是 `3节点` 或 `4节点`，父节点中的值下移与兄弟节点合并为 `3节点`，父节点变为 `2节点` 或 `3节点`。
        * 如果兄弟节点是 `2节点`，父节点是 `2节点`，父节点中的值与兄弟节点中的值合并，形成一个 `3节点`，把此节点看成当前节点（此节点实际上是下一层的节点），重复步骤。

如果是在 `2节点`（叶子节点）中进行删除，每次删除会减少一个分支，如果删除操作导致根节点参与合并，则 `2-3-4` 树会降低一层。

![](https://raw.githubusercontent.com/Arthur940621/image/main/Project/RBTree/013.png)

`2-3-4` 树的查询操作像普通的二叉搜索树一样，非常简单，但由于其结点元素数不确定，在一些编程语言中实现起来并不方便，实现一般使用它的等同——红黑树。

# 红黑树

## 定义
红黑树是一种特殊的二叉查找树。每个节点上都有存储位表示节点的颜色，可以是红（`Red`）或黑（`Black`）。

红黑树是对概念模型 `2-3-4` 树的一种实现，由于直接进行不同节点间的转化会造成较大的开销，所以选择以二叉树为基础，在二叉树的属性中加入一个颜色属性来表示 `2-3-4` 树中不同的节点。

## 性质

* (1) 每个节点或者是黑色，或者是红色
* (2) 根节点是黑色
* (3) 每个叶子节点是黑色
* (4) 如果一个节点是红色的，则它的子节点必须是黑色的。
* (5) 从一个节点到该节点的子孙节点的所有路径上包含相同数目的黑节点

以上条件能保证任意同级子树高度差不超过 `2` 倍。

注意：
性质 `(3)` 中的叶子节点，是指为空（`NIL` 或 `null`）的节点。
性质 `(5)` 确保没有一条路径会比其他路径长 `2` 倍。因而，红黑树是相对平衡的二叉树，一棵含有 `n` 个节点的红黑树的高度至多为 `2log2(n+1)`。

## 旋转

### 左旋：

```
左旋示意图（对节点x进行左旋）：
    px                              px
    /                               /
   x                               y
  / \         --(左旋)-->         / \
 lx  y                          x  ry
    / \                        / \
   ly  ry                     lx  ly


    px                              px
     \                               \
      x                               y
     / \      --(左旋)-->            / \
    lx  y                           x  ry
       / \                         / \
      ly  ry                      lx  ly
```

实现代码：

```cpp
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
```

### 右旋：

```
右旋示意图（对节点y进行右旋）：
           py                              py
          /                               /
         y                               x
        / \         --(右旋)-->         / \
       x  ry                           lx  y
      / \                                 / \
     lx  rx                              rx  ry

          py                              py
           \                               \
            y                               x
           / \      --(右旋)-->             / \
          x  ry                           lx  y
         / \                                 / \
        lx  rx                              rx  ry
```

实现代码：

```cpp
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
```

## 插入

首先，将红黑树当作一颗二叉查找树，将节点插入；

然后，将节点着色为红色；

最后，通过旋转和重新着色等方法来修正该树，使之重新成为一颗红黑树。

实现代码：

实现代码：

```cpp
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
```

## 插入后调整
  
自底向上，一层一层的调整，直到父节点为黑色的时候，或者到根。

+ 插入后情况  
    - 不需要调整（父节点为黑色；或者插入的是根节点）  
        1. 父节点是黑色的情况：  
              因为rbt基于bst，所以插入的新节点只可能是叶子节点  
              所以插入的节点如果父节点是黑色，就满足rbt5条性质，不需要调整  
        2. 如果是根节点，直接把该节点设置为黑色  
    - 需要调整（父节点为红色）  
        （由于性质4，祖父节点必定是黑色）  
        叔叔节点（当前节点的祖父节点的另一个子节点）
        1. ·父节点·为·祖父节点·的左孩子的情况
            + case1:·叔叔节点·是红色。（把父层同时置黑，试满足第4性质，然后祖父可能又有冲突（冲突向上抛），所以继续递归）
                1. 将·父节点·和·叔叔节点·设为黑色
                2. 将·祖父节点·设为红色
                3. 从·祖父节点·进行递归调整
            + case2:叔叔节点是黑色。且当前节点是其父节点的右孩子。（旧父节点的树一直满足5条性质，把不满足的当前节点继续递归（冲突向上抛））
                1. 将·父节点·左旋
                2. 从·新父节点·执行case3
            + case3:叔叔节点是黑色。且当前节点是其父节点的左孩子。（因为父节点和叔叔节点都是黑色，所以右旋后，祖父节点必定是黑色，已经满足所有性质，不需要递归了）
                1. 将·父节点·设为黑色
                2. 将·祖父节点·设为红色
                3. 将·祖父节点·右旋
                4. 从·新当前节点的右节点·继续进行递归调整（其实到这里就结束了）
        2. ·父节点·为·祖父节点·的右孩子的情况  
            与上同理（镜像）  

实现代码：

```cpp
template<class K, class V>
void RBTree<K, V>::insertFixUp(RBTNode<K, V>*& root, RBTNode<K, V>* node) {
    RBTNode<K, V>* partent, *gparent;
    while ((partent = node->_parent) && (colorOf(partent) == Color::RED)) { // 若父节点存在且父节点颜色是红色
        gparent = partent->_parent; // 因为父节点是红色，所以必有祖先节点
        if (partent == gparent->_left) { // 父节点是祖先节点的左孩子
            // case1：叔叔节点是红色
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
            // case2：叔叔节点是黑色，且当前节点是右孩子
            if (partent->_right == node) {
                RBTNode<K, V>* tmp;
                leftRotate(root, partent);
                tmp = partent;
                partent = node;
                node = tmp;
            }
            // 无论是否执行了上面的if语句，此时叔叔节点一定是黑色，且当前节点是左孩子
            // case3：叔叔节点是黑色，且当前节点是左孩子
            partent->_color = Color::BLACK;
            gparent->_color = Color::RED;
            rightRotate(root, gparent);
        } else { // 父节点是祖先节点的右孩子
            // case1：叔叔节点是红色
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
            // case2：叔叔节点是黑色，且当前节点是左孩子
            if (partent->_left == node) {
                RBTNode<K, V>* tmp;
                rightRotate(root, partent);
                tmp = partent;
                partent = node;
                node = tmp;
            }
            // case3：叔叔节点是黑色，且当前节点是右孩子
            partent->_color = Color::BLACK;
            gparent->_color = Color::RED;
            leftRotate(root, gparent);
        }
    }
    root->_color = Color::BLACK;
}
```

## 删除

将删除红黑树中的节点大致分为两步：

第一步将红黑树当作一颗二叉查找树，将节点删除后，可能违反性质(2)、(4)、(5)三个性质。

第二步需要解决上面的三个问题，进而保持红黑树的全部性质。

实现代码：

```cpp
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
}
```

## 删除后调整

+ 删除后情况
    - 不需要调整（删除的是红色节点，上下都是黑色节点，黑高平衡） 
        1. 回溯时，如果·当前节点·是·根节点·或者是·红色节点·，直接置黑
    - 需要调整（删除的是黑色节点，黑高不平衡）
        兄弟节点（sib,sibling 当前节点的父节点的另一个子节点）
        左右侄子（nephew,ln,rn 当前节点的父节点的另一个子节点的左右子节点）
        1. 删除节点为·父节点·的左孩子情况（左黑高低）
            + case1:·兄弟节点·为红色。（右树的根节点为红色，所以它下面的两个子树黑高一定平衡。把它父节点左旋，不影响它黑高平衡）（最终右黑高还是比做黑高大）
                1. 将·兄弟节点·设为黑色
                2. 将·父节点·设为红色
                3. 将·父节点·左旋
            + case2:·兄弟节点·为黑色；·左右侄子节点·为黑色
                1. 将·兄弟节点·设为红色
                2. 从·父节点·进行递归调整。
            + case3:·兄弟节点·为黑色；·左侄子节点·为红色；·右侄子节点·为黑色。（兄弟子树的黑高被减，然后把多的黑高向上抛）（必定兄弟节点为黑色，右侄子节点为红色，后一步必定是case4）  
                1. 将·左侄子节点·设为黑色
                2. 将·兄弟节点·设为红色
                3. 将·兄弟节点·右旋
            + case4:·兄弟节点·为黑色；·右侄子节点·为红色。
                    （如果父节点为黑色，左旋的时候，带走了左侄子节点，然后右侄子节点又被置为了黑色（黑高加一，又因为父节点被左旋，黑高减一，所以不动）而原来黑高少的左子树因为被加了一个黑色的父节点，所以黑高和右子树一样了；
                     如果父节点是红色，左旋同时设置兄弟节点为红色（新父节点还是红色），右子树黑高被减一，左侄子节点被带到左子树（同样挂到黑节点下，黑高不变），左子树上方则加了一个黑色节点，最终左右平衡）  
                1. 将·兄弟节点·设为·父节点·的颜色
                2. 将·父节点·设为黑色
                3. 将·右侄子节点·设为黑色
                4. 将·父节点·左旋
                5. 结束（因为原本减去的黑高又被加回来了，所以没必要再继续调整了）
        执行意义{
            case2执行完后，如果执行case1，并且最后·父节点·是黑色（现在左右黑高已经相等，但是·父节点·是黑色，所以不能保证·父节点·还平衡，需要递归调整）  
            case2执行完后，如果执行case2，并且最后·父节点·是红色（直接把·父节点·置黑，刚好补全了因为删除和·兄弟节点·置红而降低的黑高，结束）  
        }
        2. 删除节点为·父节点·的右孩子情况
            + 与上同理（镜像）

实现代码：

```cpp
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
```