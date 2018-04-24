#include "BTree.h"

/**
 * 在B-树t查找关键字key，用r返回（pt, i, tag）
 * 若查找成功，则tag=1，指针pt所指结点中第i个关键字等于key
 * 否则tag=0，若要插入关键字key，应位于pt结点中第i-1和第i个关键字之间
 *
 * @param t B-树
 * @param key 待查找的关键字
 * @param r B-树的查找结果类型
 */
void SearchBTree(BTree t, KeyType key, Result &r) {
    int i = 0;
    int found = 0;
    BTree p = t; // 一开始指向根结点，之后指向待查结点
    BTree q = NULL; // 指向待查结点的双亲
    while (p != NULL && found == 0) {
        i = Search(p, key);
        if (i <= p->keynum && p->key[i] == key) {
            found = 1;
        } else {
            q = p;
            p = p->ptr[i - 1]; // 指针下移
        }
    }
    if (1 == found) { // 查找成功，返回key的位置p和i
        r.pt = p;
        r.i = i;
        r.tag = 1;
    } else { // 查找失败，返回key的插入位置q和i
        r.pt = q;
        r.i = i;
        r.tag = 0;
    }
}

/**
 * 在p->key[1 .. p->keynum]找key，并返回位序
 *
 * @param p B-树的结点p
 * @param key 关键字
 * @return key在p结点的位序
 */
int Search(BTree p, KeyType key) {
    int i = 1;
    while (i <= p->keynum && key > p->key[i]) {
        i++;
    }
    return i;
}

/**
 * 在B-树t中q结点的key[i - 1]和key[i]之间插入关键字key
 * 若插入后结点关键字个数等于B-树的阶，则沿双亲指针链进行结点分裂
 *
 * @param t B-树
 * @param key 待插入的关键字
 * @param q 关键字插入的结点
 * @param i 插入位序
 */
void InsertBTree(BTree &t, KeyType key, BTree q, int i) {
    KeyType x;
    int s;
    int finished = FALSE;
    int needNewRoot = FALSE;
    BTree ap;
    if (NULL == q) {
        newRoot(t, NULL, key, NULL);
    } else {
        x = key;
        ap = NULL;
        while (FALSE == needNewRoot && FALSE == finished) {
            Insert(q, i, x, ap); // x和ap分别插入到q->key[i]和q->ptr[i]
            if (q->keynum < m) {
                finished = TRUE;
            } else {
                // 分裂q结点
                s = (m + 1) / 2; // 得到中间结点位置
                split(q, s, ap);
                x = q->key[s];
                // 在双亲位置插入关键字x
                if (q->parent != NULL) {
                    q = q->parent;
                    i = Search(q, x); // 寻找插入的位置
                } else {
                    needNewRoot = TRUE;
                }
            }
        }
        if (TRUE == needNewRoot) {
            newRoot(t, q, x, ap);
        }
    }
}

/**
 * 将q结点分裂成两个结点，前一半保留在原结点，后一半移入ap所指新结点
 *
 * @param q B-树结点
 * @param s 中间位序
 * @param ap 新结点，用来存放原结点的后一半关键字
 */
void split(BTree &q, int s, BTree &ap) {
    int i, j;
    int n = q->keynum; // 关键字数量
    ap = (BTree)malloc(sizeof(BTNode));
    ap->ptr[0] = q->ptr[s];
    for (i = s + 1, j = 1; i <= n; i++, j++) {
        ap->key[j] = q->key[i];
        ap->ptr[j] = q->ptr[i];
    }
    ap->keynum = n - s;
    ap->parent = q->parent;
    for (i = 0; i <= n - s; i++) {
        // 修改新结点的子结点的parent域
        if (ap->ptr[i] != NULL) {
            ap->ptr[i]->parent = ap;
        }
    }
    q->keynum = s - 1; // 修改q结点的关键字数量
}

/**
 * 生成新的根结点
 *
 * @param t B-树
 * @param p B-树结点
 * @param key 关键字
 * @param ap B-树结点
 */
void newRoot(BTree &t, BTree p, KeyType key, BTree ap) {
    t = (BTree)malloc(sizeof(BTNode));
    t->keynum = 1;
    t->ptr[0] = p;
    t->ptr[1] = ap;
    t->key[1] = key;
    if (p != NULL) {
        p->parent = t;
    }
    if (ap != NULL) {
        ap->parent = t;
    }
    t->parent = NULL;
}

/**
 * 关键字key和新结点指针ap分别插入到q->key[i]和q->ptr[i]
 *
 * @param q 插入目标结点
 * @param i 插入位序
 * @param key 待插入的关键字
 * @param ap 新结点指针
 */
void Insert(BTree &q, int i, KeyType key, BTree ap) {
    int j;
    int n = q->keynum;
    for (j = n; j >= i; j--) {
        // 后移
        q->key[j + 1] = q->key[j];
        q->ptr[j + 1] = q->ptr[j];
    }
    q->key[i] = key;
    q->ptr[i] = ap;
    if (ap != NULL) {
        ap->parent = q;
    }
    q->keynum++;
}

/**
 * 删除B-树上p结点的第i个关键字
 *
 * @param t B-树
 * @param p 目标关键字所在结点
 * @param i 关键字位序
 */
void DeleteBTree(BTree &t, BTree &p, int i) {
    if (p->ptr[i] != NULL) {
        // 不是最下层非终端结点
        Successor(p, i); // 找到后继最下层非终端结点的最小关键字代替它
        DeleteBTree(t, p, 1); // 删除最下层非终端结点中的最小关键字
    } else {
        Remove(p, i); // 从结点p中删除key[i]
        if (p->keynum < (m - 1) / 2) {
            Restore(t, p); // 调整B树
        }
    }
}

/**
 * 在Ai子树中找出最下层非终端结点的最小关键字代替Ki
 *
 * @param p B-树结点
 * @param i 关键字位序
 */
void Successor(BTree &p, int i) {
    BTree leaf = p;
    if (NULL == p) {
        return;
    }
    leaf = leaf->ptr[i]; // 指向子树
    while (NULL != leaf->ptr[0]) {
        // 找到最下层非终端结点
        leaf = leaf->ptr[0];
    }
    p->key[i] = leaf->key[1];
    p = leaf;
}

/**
 * 从结点p移除关键字key[i]
 *
 * @param p B-树结点
 * @param i 关键字位序
 */
void Remove(BTree &p, int i) {
    int k;
    // 指针与key都向左移
    for (k = i; k < p->keynum; k++) {
        p->key[k] = p->key[k + 1];
        p->ptr[k] = p->ptr[k + 1];
    }
    p->keynum--;
}

/**
 * 调整B-树
 *
 * @param t B-树
 * @param p B-树结点
 */
void Restore(BTree &t, BTree &p) {
    BTree parent, leftBrother, rightBrother; // 被删结点的父结点、左右兄弟
    parent = p->parent;
    if (parent != NULL) { // 父结点不为空
        // 寻找左右兄弟
        int i;
        for (i = 0; i <= parent->keynum; i++) {
            if (parent->ptr[i] == p) {
                break;
            }
        }
        if (i > 0) {
            leftBrother = parent->ptr[i - 1];
        } else {
            leftBrother = NULL;
        }
        if (i < parent->keynum) {
            rightBrother = parent->ptr[i + 1];
        } else {
            rightBrother = NULL;
        }

        // 左兄弟或右兄弟有富余关键字
        if ((leftBrother != NULL && leftBrother->keynum >= (m + 1) / 2) ||
            (rightBrother != NULL && rightBrother->keynum >= (m + 1) / 2)) {
            BorrowFromBrother(p, leftBrother, rightBrother, parent, i);
        } else {
            // 左右兄弟都没富余关键字，需要合并
            if (leftBrother != NULL) {
                MegerWithLeftBrother(leftBrother, parent, p, t, i); // 与左兄弟合并
            } else if (rightBrother != NULL) {
                MegerWithRightBrother(rightBrother, parent, p, t, i);
            } else  {
                //当左右子树不存在时改变根结点
                for (int j = 0; j <= p->keynum + 1; j++) {
                    if (p->ptr[j] != NULL) {
                        t = p->ptr[j];
                        break;
                    }
                }
                t->parent = NULL;
            }
        }
    } else {
        //根节点，去掉根节点，使树减一层
        BTree a;
        for (int j = 0; j <= p->keynum + 1; j++) {
            if (p->ptr[j] != NULL) {
                a = p;
                p = p->ptr[j];
                a->ptr[j] = NULL;
                free(a);
                break;
            }
        }
        t = p;
        t->parent = NULL;
    }
}

/**
 * 向兄弟借关键字
 *
 * @param p B-树结点
 * @param leftBrother p结点的左兄弟结点
 * @param rightBrother p结点的右兄弟结点
 * @param parent p结点的父亲结点
 * @param i 位序
 */
void BorrowFromBrother(BTree &p, BTree &leftBrother, BTree &rightBrother, BTree &parent, int &i) {
    // 左兄弟有富余关键字，向左兄弟借
    if (leftBrother != NULL && leftBrother->keynum >= (m + 1) / 2) {
        for (int j = p->keynum + 1; j > 0; j--) {
            // 关键字与指针后移，腾出第一个位置
            if (j > 1) {
                p->key[j] = p->key[j - 1];
            }
            p->ptr[j] = p->ptr[j - 1];
        }
        p->ptr[0] = leftBrother->ptr[leftBrother->keynum];
        if (p->ptr[0] != NULL) {
            p->ptr[0]->parent = p;
        }
        leftBrother->ptr[leftBrother->keynum] = NULL;
        p->key[1] = parent->key[i]; // 被删结点存父结点关键字
        parent->key[i] = leftBrother->key[leftBrother->keynum]; // 父结点的key变为被删结点左兄弟的最大关键字
        leftBrother->keynum--;
        p->keynum++;
    } else if (rightBrother != NULL && rightBrother->keynum >= (m + 1) / 2) { // 右兄弟有富余关键字
        p->key[p->keynum + 1] = parent->key[i + 1];
        p->ptr[p->keynum + 1] = rightBrother->ptr[0];    // 子树指针指向右兄弟最左边的子树指针
        if (p->ptr[p->keynum + 1] != NULL) {
            p->ptr[p->keynum + 1]->parent = p;
        }
        p->keynum++;
        parent->key[i + 1] = rightBrother->key[1];        // 父结点从右兄弟借关键字
        for (int j = 0; j < rightBrother->keynum; j++) {
            if (j > 0) {
                rightBrother->key[j] = rightBrother->key[j + 1];
            }
            rightBrother->ptr[j] = rightBrother->ptr[j + 1];
        }
        rightBrother->ptr[rightBrother->keynum] = NULL;
        rightBrother->keynum--;
    }
}

/**
 * 与左兄弟合并
 *
 * @param leftBrother p结点的左兄弟结点
 * @param parent p结点的父亲结点
 * @param p B-树结点
 * @param t B-树
 * @param i 位序
 */
void MegerWithLeftBrother(BTree &leftBrother, BTree &parent, BTree &p, BTree &t, int &i) {
    // 与左兄弟合并
    leftBrother->key[leftBrother->keynum + 1] = parent->key[i];    // 从父结点拿下分割本节点与左兄弟的关键字
    leftBrother->ptr[leftBrother->keynum + 1] = p->ptr[0];
    if (leftBrother->ptr[leftBrother->keynum + 1] != NULL) {
        leftBrother->ptr[leftBrother->keynum + 1]->parent = leftBrother;    // 给左兄弟的结点，当此结点存在时需要把其父亲指向指向左结点
    }
    leftBrother->keynum++; //左兄弟关键数加1
    for (int j = 1; j <= p->keynum; j++) {
        // 把本结点的关键字和子树指针赋给左兄弟
        leftBrother->key[leftBrother->keynum + j] = p->key[j];
        leftBrother->ptr[leftBrother->keynum + j] = p->ptr[j];
        if (leftBrother->ptr[leftBrother->keynum + j] != NULL) {
            leftBrother->ptr[leftBrother->keynum + j]->parent = leftBrother;
        }
    }
    leftBrother->keynum += p->keynum;
    parent->ptr[i] = NULL;
    free(p);    // 释放p结点
    for (int j = i;j < parent->keynum; j++) {
        // 左移
        parent->key[j] = parent->key[j + 1];
        parent->ptr[j] = parent->ptr[j + 1];
    }
    parent->ptr[parent->keynum] = NULL;
    parent->keynum--;        // 父结点关键字个数减1
    if (t == parent) {
        // 如果此时父结点为根，则当父结点没有关键字时才调整
        if (0 == parent->keynum) {
            for (int j = 0;j <= parent->keynum + 1; j++) {
                if (parent->ptr[j] != NULL) {
                    t = parent->ptr[j];
                    break;
                }
                t->parent = NULL;
            }
        }
    } else {
        // 如果父结点不为根，则需要判断是否需要重新调整
        if (parent->keynum < (m - 1) / 2) {
            Restore(t, parent);
        }
    }
}
/**
 * 与右兄弟合并
 *
 * @param rightBrother p结点的右兄弟结点
 * @param parent p结点的父亲结点
 * @param p B-树结点
 * @param t B-树
 * @param i 位序
 */
void MegerWithRightBrother(BTree &rightBrother, BTree &parent, BTree &p, BTree &t, int &i) {
    // 与右兄弟合并
    for (int j = (rightBrother->keynum); j > 0; j--) {
        if (j > 0) {
            rightBrother->key[j + 1 + p->keynum] = rightBrother->key[j];
        }
        rightBrother->ptr[j + 1 + p->keynum] = rightBrother->ptr[j];
    }
    rightBrother->key[p->keynum + 1] = parent->key[i + 1];    // 把父结点的分割两个本兄弟和右兄弟的关键字拿下来使用
    for (int j = 0; j <= p->keynum; j++) {
        // 把本结点的关键字及子树指针移动右兄弟中去
        if (j > 0) {
            rightBrother->key[j] = p->key[j];
        }
        rightBrother->ptr[j] = p->ptr[j];
        if (rightBrother->ptr[j] != NULL) {
            rightBrother->ptr[j]->parent = rightBrother;    // 给右兄弟的结点需要把其父结点指向右兄弟
        }
    }
    rightBrother->keynum += (p->keynum + 1);
    parent->ptr[i] = NULL;
    free(p); // 释放p结点
    for (int j = i;j < parent->keynum;j++) {
        if (j > i) {
            parent->key[j] = parent->key[j + 1];
        }
        parent->ptr[j] = parent->ptr[j + 1];
    }
    if (1 == parent->keynum) {
        // 如果父结点在关键字减少之前只有一个结点，那么需要把父结点的右孩子赋值给左孩子
        parent->ptr[0] = parent->ptr[1];
    }
    parent->ptr[parent->keynum] = NULL;
    parent->keynum--;                    // 父结点关键字数减1
    if (t == parent) {
        //如果此时父结点为根，则当父结点没有关键字时才调整
        if (0 == parent->keynum) {
            for (int j = 0; j <= parent->keynum + 1; j++) {
                if (parent->ptr[j] != NULL) {
                    t = parent->ptr[j];
                    break;
                }
            }
            t->parent = NULL;
        }
    } else {
        //如果父结点不为根，则需要判断是否需要重新调整
        if (parent->keynum < (m - 1) / 2) {
            Restore(t, parent);
        }
    }
}
/**
 * 按关键字大小升序输出B-树关键字
 *
 * @param t B-树
 */
void OrderTraverseBTree(BTree t) {
    int i;
    if (NULL == t) {
        return;
    }
    for (i = 0; i <= t->keynum; i++) {
        if (i > 0) {
            printf("%d  ", t->key[i]);
        }
        if (t->ptr[i] != NULL) {
            OrderTraverseBTree(t->ptr[i]);
        }
    }
}

/**
 * 以凹入表的形式打印B树
 *
 * @param t B-树
 * @param tab 缩进量
 */
void PrintBTree(BTree t, int tab) {
    if (NULL == t) {
        return;
    }
    int i;
    for (i = 1; i <= tab; i++) {
        printf("    ");
    }
    for (i = 1; i <= t->keynum; i++) {
        printf("%d", t->key[i]);
        if (i != t->keynum) {
            printf(", ");
        }
    }
    printf("\n");
    for (i = 0; i <= t->keynum; i++) {
        PrintBTree(t->ptr[i], tab + 1);
    }
}

/**
 * B-树关键字数量
 *
 * @param t B-树
 * @return 返回B树关键字数量，为空则返回0
 */
int BTreeKeyNumber(BTree t) {
    int i;
    int keyNumber = 0;
    if (NULL == t) {
        return 0;
    }
    keyNumber += t->keynum;
    for (i = 0; i<= t->keynum; i++) {
        if (t->ptr[i] != NULL) {
            keyNumber += BTreeKeyNumber(t->ptr[i]);
        }
    }
    return keyNumber;
}

/**
 * 销毁B-树
 * @param t B-树
 */
void DestoryBTree(BTree &t) {
    if (NULL == t) {
        return;
    }
    for (int i = 0; i <= t->keynum; i++) {
        if (t->ptr[i] != NULL) {
            DestoryBTree(t->ptr[i]);
        }
    }
    free(t);
}

/**
 * 初始化B树
 *
 * @param t B树
 */
void InitBTree(BTree &t) {
    t = NULL;
}

/**
 * 随机数创建指定大小的B树
 *
 * @param t B树
 * @param keyNumbe 关键字数量
 */
void CreateBTreeRandom(BTree &t, int keyNumber) {
    KeyType key;
    Result r;
    srand((unsigned int) time(NULL));
    t = NULL;
    for (int i = 0; i < keyNumber; i++) {
        key = rand() % 1000;
        SearchBTree(t, key, r);
        if (r.tag == 0) {
            InsertBTree(t, key, r.pt, r.i);
        }
    }
}
