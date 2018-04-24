/***************************************************************************************
 *	File Name				:	AVLTree.h
 *	ModuleName				:
 *	SYSTEM					:   Windows 10 X64
 *	Create Date				:	2017/12/14
 *  Time                    :   16:40
 *	Author/Corportation		:	郑俊铭
 *	Abstract Description	:	this will be used for
 ***************************************************************************************/


/**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/
#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

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
#define LH        +1     // 左子树比右子树高
#define EH         0     // 左、右子树等高
#define RH        -1     // 右子树比左子树高
#define HAVE_BEEN_CREATED 1    // 平衡二叉树已经创建
#define NOT_CREATED -1         // 平衡二叉树未创建
/**************************************************************
*	Struct Define Section
**************************************************************/
typedef int KeyType;    // 关键字类型为整数类型

typedef struct {
    KeyType key;   // 关键字项
} RecordType, RcdType;    // 记录类型

typedef struct BBSTNode {
    RcdType data;
    int bf;         // 结点平衡因子
    struct BBSTNode *lchild, *rchild;  // 左右孩子
} * BBSTree;  // 平衡二叉树

/**************************************************************
*	Prototype Declare Section
**************************************************************/
/**
 * 对最小失衡子树p作右旋调整
 *
 * @param p 最小失衡子树
 */
void R_Rotate(BBSTree &p);

/**
 * 对最小失衡子树p作左旋调整
 *
 * @param p 最小失衡子树
 */
void L_Rotate(BBSTree &p);

/**
 * 树T的左平衡处理
 *
 * @param T 树T
 */
void LeftBalance(BBSTree &T);

/**
 * 树T的右平衡处理
 *
 * @param T 树T
 */
void RightBalance(BBSTree &T);

/**
 * 平衡二叉树的插入操作
 *
 * @param T 平衡二叉树T
 * @param e 待插入元素
 * @param taller 高度是否变高
 * @return 成功返回TRUE
 */
Status InsertAVL(BBSTree &T, RcdType e, Status &taller);

/**
 * 在AVL树查找key
 *
 * @param T AVL树
 * @param key 待查找的关键字
 * @return 找到则返回该关键字的结点，找不到则返回NULL
 */
BBSTree SearchBBST(BBSTree T, KeyType key);

/**
 * 凹入表表示法打印AVL树
 *
 * @param T AVL树
 */
void ConcaveTablePrintBBST(BBSTree T, int m);

/**
 * 括号表示法打印AVL树
 *
 * @param T AVL树
 */
void ParenthesisPrintBBST(BBSTree T);

/**
 * 平衡二叉树的删除操作
 *
 * @param T
 * @param key
 * @param shorter
 * @return
 */
Status DeleteAVL(BBSTree &T, KeyType key, Status &lower);

/**
 * 输出平衡二叉树关键字
 * @param key 关键字
 */
void visit(KeyType key);

/**
 * 前序遍历平衡二叉树
 *
 * @param T 平衡二叉树
 * @param visit 函数指针
 */
void PreOrderTraverse(BBSTree T, void( *visit)(KeyType));

/**
 * 中序遍历平衡二叉树
 *
 * @param T 平衡二叉树
 * @param visit 函数指针
 */
void InOrderTraverse(BBSTree T, void( *visit)(KeyType));

/**
 * 后序遍历平衡二叉树
 *
 * @param T 平衡二叉树
 * @param visit 函数指针
 */
void PostOrderTraverse(BBSTree T, void( *visit)(KeyType));

/**
 * 层次遍历平衡二叉树
 *
 * @param T 平衡二叉树
 * @param visit 函数指针
 * @param level 层次
 * @return
 */
Status LevelOrderTraverse(BBSTree T, void( *visit)(KeyType), int level);

/**
 * 按层打印
 *
 * @param T 平衡二叉树
 */
void PrintNodeByLevel(BBSTree T);

/**
 * 分裂平衡二叉树，分成大于key和小于key两棵树
 *
 * @param T 待分裂的平衡二叉树
 * @param key 分裂的关键字
 * @param T1 关键字全部小于key的平衡二叉树
 * @param T2 关键字全部大于key的平衡二叉树
 */
void SpiltBBST(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2);

/**
 * 合并平衡二叉树
 *
 * @param T1 合并后的平衡二叉树
 * @param T2 待合并的平衡二叉树
 */
void MergeBBST(BBSTree &T1, BBSTree T2);

/**
 * 销毁平衡二叉树
 *
 * @param T 平衡二叉树
 */
void DestroyBBST(BBSTree &T);
/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif // AVLTREE_H_INCLUDED
