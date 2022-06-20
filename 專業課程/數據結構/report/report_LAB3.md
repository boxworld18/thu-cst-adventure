## LAB3 BBST  解题报告 ##

#### 容逸朗 2020010869 ####

### 1  BBST实现

本次实验实现了 AVL 和 splay 两种 BBST。

#### 1.1 公共部分

##### 1.1.1 节点

节点部分包含高度、数值、父节点与孩子节点，提供了两种创造新节点方法和寻找后继节点的 `succ` 方法。

```c++
using BinNodePosi = BinNode*;
struct BinNode {
    int data, height;
    BinNodePosi parent, lc, rc;
    BinNode(): parent(nullptr), lc(nullptr), rc(nullptr), data(0), height(0) {}
    BinNode(int e, BinNodePosi p = nullptr, BinNodePosi lc = nullptr,BinNodePosi rc = nullptr, int h = 0):
            data(e), parent(p), lc(lc), rc(rc), height(h) {}
    BinNodePosi succ();
};
```

其中 `succ` 方法用于查找中序遍历下的后续节点。

- 若节点有右子，则遍历右子的左子树，左侧链上最深的节点为所求。

- 节点无右子，先判断节点自身是否为右子，若是则不断向上回溯，直至结点不再为右子，此时节点的父节点为所求节点。

```c++
#define IsRoot(x) (!((x).parent))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))
#define HasLChild(x) ((x).lc)
BinNodePosi BinNode::succ() {
    BinNodePosi s = this;
    if (rc) { // 若有右子树
        s = rc; // 先向右走
        while (HasLChild(*s)) s = s->lc; // 不断向左探，最深的节点为后继节点
    } else {
        while (IsRChild(*s)) s = s->parent; // 若节点为右子，则向上回溯
        s = s->parent; // 直至节点不为右子，则后继节点为此时s的父节点
    }
    return s;
}
```

##### 1.1.2 二叉查找树

二叉查找树包含了树的大小 `_size` ，根节点 `_root` 和查找路径上最后一个节点 `_hot` 的指针。同时提供了节点高度更新和节点查找方法。

```c++
class BST {
protected:
    int _size;
    BinNodePosi _root;
    BinNodePosi _hot;
    virtual int updateHeight(BinNodePosi x);
    void updateHeightAbove(BinNodePosi x);
public:
  	BST(): _size(0), _root(nullptr), _hot(nullptr) {}
    virtual BinNodePosi &search(const int &e);
};
```

维护节点高度的代码如下：

```c++
#define stature(p) ((p) ? (p)->height : -1) // 空树的高度为1
int BST::updateHeight(BinNodePosi x) {
    return x->height = 1 + std::max(stature(x->lc), stature(x->rc));
}
void BST::updateHeightAbove(BinNodePosi x) {
    while (x) {updateHeight(x); x = x->parent;}
}
```

节点查找由根节点开始，若命中或节点为空，则直接返回指针的引用，否则 `_hot` 记为节点（以便后续实现节点的插入和移除操作），并根据查找值与节点值的大小选择向下查找的方向，直至节点命中或为空才返回节点的指针引用。

```c++
BinNodePosi &BST::search(const int &e) { //在BST中查找关键码e
    if (!_root || e == _root->data) {
        _hot = nullptr;
        return _root;
    } //空树，或恰在树根命中
    for (_hot = _root; ; ) { //否则，自顶而下
        BinNodePosi &v = (e < _hot->data) ? _hot->lc : _hot->rc; //确定方向
        if (!v || e == v->data) return v;
        _hot = v; //一旦命中或抵达叶子，随即返回
    } //返回目标节点位置的引用，以便后续插入、删除操作
}
```

查找函数与高度相关，时间复杂度为 $O(\log n)$ 。

#### 1.2 AVL

AVL 类中包含了节点旋转（和重构）、插入、移除和查找的方法。

```c++
class AVL: public BST {
protected:
    BinNodePosi rotateAt(BinNodePosi);
  	BinNodePosi connect34(BinNodePosi, BinNodePosi, BinNodePosi, BinNodePosi, 													BinNodePosi, BinNodePosi, BinNodePosi);
public:
    BinNodePosi insert(const int &e);
    bool remove(const int &e);
    int find(const int &e);
};
```

为简化程序，将部分常用操作以宏定义。

* `FromParentTo(x)` 用于判断被旋转节点 `x` 旋转后，新子树的根节点应连接到原树的位置。（若被旋转节点为根，则 `_root` 记为新的根节点，否则若节点为左子树，则新树也需要接入到左子树的位置，即 `(x).parent->lc` ，右子树同理。
* `BalFac(x)` 用于计算节点 `x` 的左右节点高度差，若子树为空，高度记为 `-1` 。
* `AvlBalanced(x)` 用于判断节点 `x` 是否平衡。（节点高度差的绝对值不大于 `1` ）
* `tallerChild(x)` 用于找出节点 `x` 较高的那棵子树，若高度相同，则优先选择与 `x` 同侧的节点（例如节点 `x` 为左子，则返回左子节点，原因在于 `zig-zig` 和 `zag-zag` 操作可以降低树的高度）。

```c++
#define FromParentTo(x) (IsRoot(x) ? _root : \
		(IsLChild(x) ? (x).parent->lc : (x).parent->rc))
#define BalFac(x) (stature((x).lc) - stature((x).rc))
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))
#define tallerChild(x) (stature((x)->lc) > stature((x)->rc) ? (x)->lc : \
    (stature((x)->lc) < stature((x)->rc) ? (x)->rc :                    \
    (IsLChild(*(x)) ? (x)->lc : (x)->rc )))
```

##### 1.2.1 节点旋转

每次操作会旋转两层节点，根据祖父节点，父节点和子节点的左右位置关系决定最终的子树排佈，然后利用 `connect34` 方法重新连接，最后返回新的根节点以便在函数调用处重新接入树中。

```c++
BinNodePosi AVL::rotateAt(BinNodePosi v) {
    BinNodePosi p = v->parent;
    BinNodePosi g = p->parent;
    if (IsLChild(*p))
        if (IsLChild(*v)) { // zig-zig
            p->parent = g->parent;
            return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
        } else { // zig-zag
            v->parent = g->parent;
            return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
        }
    else
    if (IsRChild(*v)) { // zag-zag
        p->parent = g->parent;
        return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
    } else { // zag-zig
        v->parent = g->parent;
        return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
    }
}
```

利用"3+4重构方法"可以简便地实现双层节点的旋转操作。具体来说，可以先把三个要旋转的根节点及他们的四棵子树按顺序排列好，然后连接（两个）子节点及其子树，最后连接新的父节点与两个新的子节点（注意此时父节点并没有和上级节点相连，在函数返回后需要重新连接），每次重构需时 $O(1)$ 。

```c++
BinNodePosi BST::connect34(BinNodePosi a, BinNodePosi b, BinNodePosi c,
                           BinNodePosi T0, BinNodePosi T1, BinNodePosi T2, BinNodePosi T3) {
    a->lc = T0; if (T0) T0->parent = a;
    a->rc = T1; if (T1) T1->parent = a;
    updateHeight(a);
    c->lc = T2; if (T2) T2->parent = c;
    c->rc = T3; if (T3) T3->parent = c;
    updateHeight(c);
    b->lc = a; a->parent = b;
    b->rc = c; c->parent = b;
    updateHeight(b);
    return b;
}
```

由于重构操作 `connect34` 时间复杂度为 $O(1)$ ，故 `rotateAt` 的时间复杂度为 $O(1)$ 。

##### 1.2.2 插入新节点

先查找插入的值是否已存在，若存在则无需操作，否则在此位置创建新节点，插入节点后向上更新高度，若有节点失衡，则在此节点调用 `rotateAt` 进行旋转，当此局部复衡后，全树便会复衡，此时停止回溯。

由于调用 `search` 需时 $O(\log n)$ ，而树复衡时的最坏情况下可回溯至根，故时间复杂度为 $O(\log n)$ 。

```c++
BinNodePosi AVL::insert(const int &e) {
    BinNodePosi &x = search(e); // 查找目标值 e
    if (x) return x; // 存在则不需要操作
    BinNodePosi xx = x = new BinNode(e, _hot); _size++; // 否则插入新节点
    for (BinNodePosi g = _hot; g; g = g->parent) { // 向上回溯
        if (!AvlBalanced(*g)) { // 若节点失衡，则旋转
            BinNodePosi &tmp = FromParentTo(*g); // 新的根节点要接入的位置
            tmp = rotateAt(tallerChild(tallerChild(g))); // 将新的根节点接入树中
            break; // 局部复衡后全树复衡，停止回溯
        }
        updateHeight(g); // 否则，更新树高
    }
    return xx; // 返回插入节点的位置
}
```

##### 1.2.3 移除节点

和插入节点类似，先查找欲移除的值是否存在，若不存在则无需操作。否则调用 `removeAt` 移除结点，移除节点后向上更新高度，若有节点失衡，则在此节点调用 `rotateAt` 进行旋转，然后继续回溯至根节点。

调用 `search` 需时 $O(\log n)$ ，每次局部复衡需时 $O(1)$ ，由于要回溯至根，故总体时间复杂度为 $O(\log n)$ 。

```c++
bool AVL::remove(const int & e) {
    BinNodePosi &x = search(e); // 查找目标值 e
    if (!x) return false; // 若不存在则不需要操作
    removeAt(x, _hot); _size--; // 否则移除节点
    for (BinNodePosi g = _hot; g; g = g->parent) { // 向上回溯
        if (!AvlBalanced(*g)) { // 若节点失衡，则旋转
            BinNodePosi &tmp = FromParentTo(*g); // 新的根节点要接入的位置
            g = tmp = rotateAt(tallerChild(tallerChild(g))); // 新节点接入树中
        }
        updateHeight(g); // 更新树高
    }
    return true; // 删除成功
}
```

对于节点移除操作，首先要判断节点的子树情况，若无左子树，则利用右子树替代被删除节点即可（若右子树为空，则子节点为叶节点，用空指针表示是合适的）。同样地，若无右子树，则用左子树替代被删除节点。需要讨论的是左右子树均存在的情况，此时需要利用 `BinNode::succ()` 查到欲删除节点的直接后继（显然地，后继节点无左子树，否则左子树的值比此节点的值更接近欲删除节点的值），交换两节点数值，然后按单子树的方法接入后继节点的右子树（需要特判后继节点是否为被删除节点的孩子），此方法的时间复杂度为 $O(1)$ 。

```c++
static BinNodePosi removeAt(BinNodePosi &x, BinNodePosi &hot) {
    BinNodePosi w = x; //实际被摘除的节点，初值同x
    BinNodePosi succ = nullptr; //实际被删除节点的接替者
    if (!HasLChild (*x)) succ = x = x->rc; // 若无左子树，则用右子替代
    else if (!HasRChild ( *x )) succ = x = x->lc; // 若无右子树，则用左子替代
        else { //若左右子树均存在，则选择x的直接后继作为实际被摘除节点
            w = w->succ(); // 寻找*x的直接后继*w
            std::swap(x->data, w->data); //交换*x和*w的数据元素
            BinNodePosi u = w->parent; 
            ((u == x) ? u->rc : u->lc) = succ = w->rc; //删除节点*w
        }
    hot = w->parent; //记录实际被删除节点的父亲
    if (succ) succ->parent = hot; //并将被删除节点的接替者与hot相联
    return succ; //释放被摘除节点，返回接替者
}
```

##### 1.2.4 查找节点

与公用的查找函数 `BST::search` 类似，不过在查找时需要记下可行的答案。

```c++
int AVL::find(const int &e) {
    int ans = -1; // 初始值为 -1
    if (!_root) return -1; // 空树，返回 -1
    if (e == _root->data) return e; // 命中，直接返回命中值
    BinNodePosi tmp = _root; // 从根部开始查找
    for (;;) {
        if (e < tmp->data) { // 查找值比根节点小，向左查找
            tmp = tmp->lc;
        } else { // 查找值比根节点大，向右查找
            ans = tmp->data; // 根节点比查找值小，是可行解
            tmp = tmp->rc;
        }
        if (!tmp) return ans; // 空树，返回路径上最后一个符合条件的节点
        if (e == tmp->data) return e; // 命中，直接返回命中值
    }
}
```

查找时的时间复杂度与树高相关，为 $O(\log n)$ 。

#### 1.3 splay

Splay 类包含了节点查找、插入、移除和伸展操作。

```c++
class Splay: public BST { //由BST派生的Splay树模板类
protected:
    BinNodePosi splay(BinNodePosi v);
public:
    BinNodePosi &search(const int &e);
    BinNodePosi insert(const int &e);
    int find(const int &e);
    bool remove(const int &e);
};
```

##### 1.3.1 伸展

对于 splay 而言，最重要的功能就是伸展，伸展操作每次操作双层节点。与 AVL 不同的地方在于，若旋转操作为 `zig-zig` 或 `zag-zag` ，则应当旋转父节点，再旋转子节点，以降低树高。若节点旋转到根节点的孩子处，则进行一次单旋便可，否则结点已到根的位置，此时返回此节点的指针以便更新树的根节点。

此操作复杂度与节点深度（树高）相关，但 splay 的高度是没有被限制旳，因此在本节的最后再一併讨论此问题。

##### 1.3.2 节点查找

与共用的 `BST::search` 相比，splay 的节点查找增加了一个伸展被查找节点的功能：

```c++
BinNodePosi &Splay::search(const int &e) { //在伸展树中查找e
    BinNodePosi p = BST::search(e);
    _root = splay(p ? p : _hot); //将最后一个被访问的节点伸展至根
    return _root;
}
```

##### 1.3.3 节点插入

首先处理空树的情况，若树非空，则查找插入的值是否已存在，若存在则进行一次伸展操作（在 `Splay::search` 处已经完成此伸展操作），否则根据查找值与根节点值的大小决定原来根节点及其子树在新树的相对位置。然后创建新节点，连接原来的树根和左（右）子树，并更新树高。

```c++
BinNodePosi Splay::insert(const int &e) { //将关键码e插入伸展树中
    if (!_root) {
        _size++;
        return _root = new BinNode(e);
    } //处理原树为空的退化情况
    if (e == search(e)->data) return _root; //确认目标节点不存在
    _size++; BinNodePosi t = _root; //创建新节点。
    if (_root->data < e) { //插入新根，以t和t->rc为左、右孩子
           t->parent = _root = new BinNode( e, nullptr, t, t->rc );
           if (HasRChild(*t)) { t->rc->parent = _root; t->rc = nullptr; } 
        } else { //插入新根，以t->lc和t为左、右孩子
           t->parent = _root = new BinNode( e, nullptr, t->lc, t );
           if (HasLChild(*t)) { t->lc->parent = _root; t->lc = nullptr; } 
        }
    updateHeightAbove ( t ); //更新t及其祖先（实际上只有_root一个）的高度
    return _root; //新节点必然置于树根，返回之
} //无论e是否存在于原树中，返回时总有_root->data == e
```

##### 1.3.4 移除节点

对于节点移除操作，首先要判断节点的子树情况，若无左子树，则利用右子树替代；若无右子树，则用左子树替代被删除节点。当左右子树均存在时，可先移除左子树，然后将右子树接入树根，此时可以利用 `Splay::search` 找出树中值最小的结点并将其置为根，最后将左子树接入，完成删除操作。

```c++
bool Splay::remove(const int &e) {
    if (!_root || (e != search(e)->data)) return false; // 节点不存在，退出
    BinNodePosi w = _root; // 否则被删除节点冒泡至根节点
    if (!HasLChild(*_root)) { // 若无左子树
        _root = _root->rc; if (_root) _root->parent = nullptr; // 将右子记为根
    } else if (!HasRChild(*_root)) { // 若无右子树
        _root = _root->lc; if (_root) _root->parent = nullptr; // 将左子记为根
    } else { // 同时出现左右子树
        BinNodePosi lTree = _root->lc; //移除左子树
        lTree->parent = nullptr; _root->lc = nullptr;
        _root = _root->rc; _root->parent = nullptr; // 右子树替代根
        search(w->data); // 找出右子树中最小节点，以此节点为根
        _root->lc = lTree; lTree->parent = _root; // 左子树重新接入
    }
    _size--; // 树的规模减少
    if (_root) updateHeight (_root); // 更新根节点高度
    return true;
}
```

##### 1.3.5 查找不大于目标值的节点

与 `1.2.4` 类似，在记下符合条件值的同时记下该节点的指针，以便后续伸展。

```c++
int Splay::find(const int &e) {
    int ans = -1; // 初始值为 -1
    if (!_root) return -1; // 空树返回 -1
    if (e == _root->data) return e; // 命中
    BinNodePosi tmp = _root, hot = _root; // 否则以 tmp 为当前节点，hot 为可行的最大值节点，从根部开始查找
    for (;;) {
        if (e < tmp->data) { // 查找值比根节点小，向左查找
            tmp = tmp->lc;
        } else { // 查找值比根节点大，向右查找
            ans = tmp->data; // 更新可行值
            hot = tmp; // 待伸展节点
            tmp = tmp->rc;
        }
        if (!tmp) { // 子树非空
            _root = splay(hot); // 伸展路径上最后一个符合条件的节点
            return ans;
        }
        if (e == tmp->data) { // 命中
            _root = splay(tmp); // 伸展此节点
            return e;
        }
    }
}
```

##### 1.3.6 复杂度分析

当访问次数远大于节点总数时，每次查找和伸展的分摊时间复杂度均为 $O(\log n)$ ，因此插入、移除和查找操作的时间复杂度也为 $O(\log n)$ 。

### 2  效能分析

#### 2.1 测例设计思路

我们约定，$p_A,p_B,p_C$ 分別为插入、删除、查找操作出现的次数比例。每个形如 ` X a` 操作中 `a` 的范围为 $[0,N)$ ，其中 $N = 10^7$ 。

##### 2.1.1 随机

仅对各种操作（插入、删除、查找）的比例作调整，不对数据的其他形式作任何的限制。

##### 2.1.2 顺序

对于插入操作 `A`，保证每次插入的数值都大于上一次操作所插入的值。

对于查找操作 `C`，又可以细分为以下其种情况：

- 随机查找 `[0, 最近插入值 + 10)` 内任意数值
- 顺序查找刚插入的数值
- 每次查找不小于树中最大值的数（如： `N-1` ）

##### 2.1.3 密集访问局部节点

每次移除和查询操作仅集中在末 $K$ 个节点中。

#### 2.2 测例生成

测例生成器可以分为以下几个部分。

##### 2.2.1 参数

测例生成器包含以下参数：

```c++
const int maxT = 20; // 测例组数

const int N = 10000; // 数值生成区间
const int n = 1000000; // 操作次数
const int M = 2; // 数据生成方法 , 0 = 随机, 1 = 顺序, 2 = 部分数据多次访问

int B = 0; // 访问策略(仅当 M = 1 时需要调用): 0 = 随机, 1 = 有条件随机,
					 // 2 = 最近插入, 3 = 查询大数, 4 = 插入查询相互交替, 5 = 末尾K个节点
const int K = 10; // 局部节点数, 仅当 M = 2 时调用

const double PA = 12; // 插入操作比例
const double PB = 12; // 移除操作比例
const double PC = 17; // 查找操作比例
```

##### 2.2.2 运作原理

对于插入操作，首先生成一个符合条件的值，然后检查这个值是否在向量中。若已存在，则再生成一个值，重复上述操作，直至值不在向量中。那么在集合和向量加入此数值，并输出操作。

对于移除操作，可以生成一个小于向量大小的数值，然后把向量中对应位置的值作为被删节点。

查询操作限制较少，具体根据调用的 `B` 值缺定查询的数值。

##### 2.2.3 生成数据

欲生成符合 `2.1` 节所述的数据，可以使用如下配置：

```c++
/*随机测例*/ M = 0, B = 0; N, n, PA, PB, PC 任取
```

```c++
/*顺序测例*/ M = 1, B = 1/2/3, PB = 0; N, n, PA, PC 任取
```

```c++
/*局部测例*/ M = 2, B = 5; N, n, PA, PB, PC 任取
```

#### 2.3 实验结果

以下表格数据范围为 $[0,N)$ ，每次生成测例 $20$ 组，操作总数为 $n$，时间单位为毫秒 (ms)。

##### 2.3.1 随机测例

- $N = 10^6,n= 10^5$

| $p_A/p_B/p_C$ |  $0.6/0.4/0.0$   |  $0.6/0.2/0.2$   |  $0.5/0.0/0.5$   |
| :-----------: | :--------------: | :--------------: | :--------------: |
|    **AVL**    | $472.32\pm86.58$ | $462.82\pm45.58$ | $447.31\pm56.21$ |
|   **splay**   | $589.11\pm76.59$ | $577.90\pm42.30$ | $545.93\pm99.57$ |

##### 2.3.2 顺序测例

对于顺序测例，取 $p_a=0.5,p_b=0,p_c=0.5$ （无删除操作），同时保证每次插入的数据都比上一次插入的数据更大，对于查询操作作如下分类讨论：

1. 每次查找操作区间为 `[0, 最近插入值 + 10)` 的任意数值
2. 每次查找操作都查找刚插入的数值
3. 每次查找不小于树中最大值的数（如： `N-1` ）

- $N = 10^6,n= 10^5$

|   策略    |        1         |        2         |        3         |
| :-------: | :--------------: | :--------------: | :--------------: |
|  **AVL**  | $409.83\pm50.57$ | $404.98\pm49.22$ | $403.40\pm46.90$ |
| **splay** | $455.35\pm51.15$ | $399.17\pm57.43$ | $400.83\pm53.07$ |

- $N = 10^5,n= 10^5$

|   策略    |        1         |        2         |        3         |
| :-------: | :--------------: | :--------------: | :--------------: |
|  **AVL**  | $396.16\pm13.36$ | $393.96\pm11.06$ | $395.73\pm10.03$ |
| **splay** | $417.44\pm35.96$ | $344.33\pm5.73$  | $344.29\pm5.29$  |

##### 2.3.3 局部数据

- $N = 10^6,n= 10^5$

|    $K$    |      $10^2$      |      $10^3$      |      $10^4$      |
| :-------: | :--------------: | :--------------: | :--------------: |
|  **AVL**  | $396.66\pm11.16$ | $397.88\pm5.22$  | $396.52\pm8.22$  |
| **splay** | $398.96\pm5.06$  | $401.95\pm11.25$ | $450.84\pm12.44$ |

#### 2.4 结果分析

##### 2.4.1 随机测例

对于随机生成的数据，AVL 的效率明显比 splay 更高。原因在于 splay 的缓存策略在随机数据下失效，此时没有后备策略保持树的高度，导致各种操作需要探访的节点变多，因此速度会比高度平衡的 AVL 慢。

##### 2.4.2 顺序测例

对于顺序策略1，本质上仍是随机数据，因此 AVL 的效率较 splay 为高。对于较离散的顺序数据，AVL 与 splay 的效率相当，对于紧湊的顺序数据，splay 的效率比 AVL 更高，造成这种结果的原因在于順序操作时，splay 只需要查找根部附近的节点，但 AVL 较为保守的平衡策略在这些特殊情况下往往需要更深入的搜索才能完成操作。

##### 2.4.3 局部数据

当数据局部性较强（$K=10^2,10^3$）时，两者效率相若，但当数据局部性下降时，splay 的缓存策略的效果变差，效能便会下降。

##### 2.4.4 总结

由上面的讨论知，大部分情况（数据随机）下 AVL 的效率会比 splay 更好。在极小数情况（数据紧湊且局部性强）的情况下，splay 会比 AVL 更好。因此在一般情况下，选择 AVL 树是较为恰当的选择。

