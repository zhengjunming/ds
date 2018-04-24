# 平衡二叉树之C语言实现

实现了以下功能

```c
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
```

相关博文：http://minsming.com/2018/01/26/%E5%B9%B3%E8%A1%A1%E4%BA%8C%E5%8F%89%E6%A0%91%E4%B9%8BC%E8%AF%AD%E8%A8%80%E5%AE%9E%E7%8E%B0/