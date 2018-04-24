/**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/
#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED
/**************************************************************
*	Debug switch Section
**************************************************************/

/**************************************************************
*	Include File Section
**************************************************************/
#include "main.h"

/**************************************************************
*	Macro Define Section
**************************************************************/
#define  m  3    // B树的阶，此设为3
#define NOT_INIT 0 // 没有初始化
#define HAVE_BEEN_INIT 1 // 已经初始化
/**************************************************************
*	Struct Define Section
**************************************************************/
typedef int KeyType;

typedef struct {
  KeyType  key;
  char     data;
} Record;

typedef struct BTNode {
  int             keynum;        // 结点中关键字个数，即结点的大小
  struct BTNode  *parent;        // 指向双亲结点
  KeyType         key[m+1];      // 关键字向量，0号单元未用
  struct BTNode  *ptr[m+1];      // 子树指针向量
  Record         *recptr[m+1];   // 记录指针向量，0号单元未用
} BTNode, *BTree;                // B树结点和B树的类型

typedef struct {
  BTree    pt;      // 指向找到的结点
  int      i;       // 1..m，在结点中的关键字序号
  int      tag;     // 1:查找成功，0:查找失败
} Result;           // 在B树的查找结果类型
/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**
 * 在B-树t查找关键字key，用r返回（pt, i, tag）
 * 若查找成功，则tag=1，指针pt所指结点中第i个关键字等于key
 * 否则tag=0，若要插入关键字key，应位于pt结点中第i-1和第i个关键字之间
 *
 * @param t B-树
 * @param key 待查找的关键字
 * @param r B-树的查找结果类型
 */
void SearchBTree(BTree t, KeyType key, Result &r);

/**
 * 在p->key[1 .. p->keynum]找key，并返回位序
 *
 * @param p B-树的结点p
 * @param key 关键字
 * @return key在p结点的位序
 */
int Search(BTree p, KeyType key);

/**
 * 在B-树t中q结点的key[i - 1]和key[i]之间插入关键字key
 * 若插入后结点关键字个数等于B-树的阶，则沿双亲指针链进行结点分裂
 *
 * @param t B-树
 * @param key 待插入的关键字
 * @param q 关键字插入的结点
 * @param i 插入位序
 */
void InsertBTree(BTree &t, KeyType key, BTree q, int i);

/**
 * 将q结点分裂成两个结点，前一半保留在原结点，后一半移入ap所指新结点
 *
 * @param q B-树结点
 * @param s 中间位序
 * @param ap 新结点，用来存放原结点的后一半关键字
 */
void split(BTree &q, int s, BTree &ap);

/**
 * 生成新的根结点
 *
 * @param t B-树
 * @param p B-树结点
 * @param key 关键字
 * @param ap B-树结点
 */
void newRoot(BTree &t, BTree p, KeyType key, BTree ap);

/**
 * 关键字key和新结点指针ap分别插入到q->key[i]和q->ptr[i]
 *
 * @param q 插入目标结点
 * @param i 插入位序
 * @param key 待插入的关键字
 * @param ap 新结点指针
 */
void Insert(BTree &q, int i, KeyType key, BTree ap);

/**
 * 删除B-树上p结点的第i个关键字
 *
 * @param t B-树
 * @param p 目标关键字所在结点
 * @param i 关键字位序
 */
void DeleteBTree(BTree &t, BTree &p, int i);

/**
 * 在Ai子树中找出最下层非终端结点的最小关键字代替Ki
 *
 * @param p B-树结点
 * @param i 关键字位序
 */
void Successor(BTree &p, int i);

/**
 * 从结点p移除关键字key[i]
 *
 * @param p B-树结点
 * @param i 关键字位序
 */
void Remove(BTree &p, int i);

/**
 * 调整B-树
 *
 * @param t B-树
 * @param p B-树结点
 */
void Restore(BTree &t, BTree &p);

/**
 * 向兄弟借关键字
 *
 * @param p B-树结点
 * @param leftBrother p结点的左兄弟结点
 * @param rightBrother p结点的右兄弟结点
 * @param parent p结点的父亲结点
 * @param i 位序
 */
void BorrowFromBrother(BTree &p, BTree &leftBrother, BTree &rightBrother, BTree &parent, int &i);

/**
 * 与左兄弟合并
 *
 * @param leftBrother p结点的左兄弟结点
 * @param parent p结点的父亲结点
 * @param p B-树结点
 * @param t B-树
 * @param i 位序
 */
void MegerWithLeftBrother(BTree &leftBrother, BTree &parent, BTree &p, BTree &t, int &i);

/**
 * 与右兄弟合并
 *
 * @param rightBrother p结点的右兄弟结点
 * @param parent p结点的父亲结点
 * @param p B-树结点
 * @param t B-树
 * @param i 位序
 */
void MegerWithRightBrother(BTree &rightBrother, BTree &parent, BTree &p, BTree &t, int &i);

/**
 * 按关键字大小升序输出B-树关键字
 *
 * @param t B-树
 */
void OrderTraverseBTree(BTree t);

/**
 * 以凹入表的形式打印B树
 *
 * @param t B-树
 * @param tab 缩进量
 */
void PrintBTree(BTree t, int tab);

/**
 * B-树关键字数量
 *
 * @param t B-树
 * @return 返回B树关键字数量，为空则返回0
 */
int BTreeKeyNumber(BTree t);

/**
 * 销毁B-树
 * @param t B-树
 */
void DestoryBTree(BTree &t);

/**
 * 初始化B树
 *
 * @param t B树
 */
void InitBTree(BTree &t);

/**
 * 随机数创建指定大小的B树
 *
 * @param t B树
 * @param keyNumbe 关键字数量
 */
void CreateBTreeRandom(BTree &t, int keyNumber);
/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif // BTREE_H_INCLUDED
