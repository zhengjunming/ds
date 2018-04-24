#include "main.h"
#include "AVLTree.h"

/**
 * 对最小失衡子树p作右旋调整
 *
 * @param p 最小失衡子树
 */
void R_Rotate(BBSTree &p) {
    BBSTree lc = p->lchild; // lc指向p结点的左孩子
    p->lchild = lc->rchild; // lc结点的右子树置为p结点的左子树
    lc->rchild = p; // 置p结点为lc结点的右孩子
    p = lc; // p指向新的根结点
}

/**
 * 对最小失衡子树p作左旋调整
 *
 * @param p 最小失衡子树
 */
void L_Rotate(BBSTree &p) {
    BBSTree rc = p->rchild;
    p->rchild = rc->lchild;
    rc->lchild = p;
    p = rc;
}

/**
 * 树T的左平衡处理
 *
 * @param T 树T
 */
void LeftBalance(BBSTree &T) {
    BBSTree lc, rd;
    lc = T->lchild;
    switch (lc->bf) {
        case LH: {
            T->bf = lc->bf = EH;
            R_Rotate(T);
            break;
        } case RH: {
            rd = lc->rchild;
            switch (rd->bf) {
                case LH: {
                    T->bf = RH;
                    lc->bf = EH;
                    break;
                } case EH: {
                    T->bf = lc->bf = EH;
                    break;
                } case RH: {
                    T->bf = EH;
                    lc->bf = LH;
                    break;
                }
            }
            rd->bf = EH;
            L_Rotate(T->lchild);
            R_Rotate(T);
            break;
        }
    }
}

/**
 * 树T的右平衡处理
 *
 * @param T 树T
 */
void RightBalance(BBSTree &T) {
    BBSTree rc, ld;
    rc = T->rchild;
    switch (rc->bf) {
        case RH:
            T->bf = rc->bf = EH;
            L_Rotate(T);
            break;
        case LH:
            ld = rc->lchild;
            switch (ld->bf) {
                case RH:
                    T->bf = LH;
                    rc->bf = EH;
                    break;
                case EH:
                    T->bf = rc->bf = EH;
                    break;
                case LH:
                    T->bf = EH;
                    rc->bf = RH;
                    break;
            }
            ld->bf = EH;
            R_Rotate(T->rchild);
            L_Rotate(T);
            break;
    }
}

/**
 * 平衡二叉树的插入操作
 *
 * @param T 平衡二叉树T
 * @param e 待插入元素
 * @param taller 左子树是否高过右子树
 * @return 成功返回TRUE
 */
Status InsertAVL(BBSTree &T, RcdType e, Status &taller) {
    if (NULL == T) {
        // T为空，树长高
        T = (BBSTree)malloc(sizeof(BBSTNode));
        T->data = e;
        T->bf = EH;
        T->lchild = NULL;
        T->rchild = NULL;
        taller = TRUE;
    } else if (e.key == T->data.key) {
        // 已经存在该点
        taller = FALSE;
        return FALSE;
    } else if (e.key < T->data.key) {
        // 插入到左子树
        if (FALSE == InsertAVL(T->lchild, e, taller)) {
            return FALSE;
        }
        if (TRUE == taller) {
            switch (T->bf) {
                case LH: {
                    LeftBalance(T);
                    taller = FALSE;
                    break;
                } case EH: {
                    T->bf = LH;
                    taller = TRUE;
                    break;
                } case RH: {
                    T->bf = EH;
                    taller = FALSE;
                    break;
                }
            }
        }
    } else {
        if (FALSE == InsertAVL(T->rchild, e, taller)) {
            return FALSE;
        }
        if (TRUE == taller) {
            switch (T->bf) {
                case LH: {
                    T->bf = EH;
                    taller = FALSE;
                    break;
                } case EH: {
                    T->bf = RH;
                    taller = TRUE;
                    break;
                } case RH: {
                    RightBalance(T);
                    taller = FALSE;
                    break;
                }
            }
        }
    }
    return TRUE;
}

/**
 * 在AVL树查找key
 *
 * @param T AVL树
 * @param key 待查找的关键字
 * @return 找到则返回该关键字的结点，找不到则返回NULL
 */
BBSTree SearchBBST(BBSTree T, KeyType key) {
    if (NULL == T) {
        return NULL;
    }
    if (T->data.key == key) {
        return T;
    }
    if (T->data.key > key) {
        return SearchBBST(T->lchild, key);
    }
    return SearchBBST(T->rchild, key);
}

/**
 * 凹入表表示法打印AVL树
 *
 * @param T AVL树
 */
void ConcaveTablePrintBBST(BBSTree T, int m) {
    int i;
    for (i = 1; i < m; i++) {
        printf("    ");
    }
    printf("%5d<bf:%d>", T->data.key, T->bf);
    if (T->lchild != NULL) {
        printf("\n");
        ConcaveTablePrintBBST(T->lchild, m + 1);
    }
    if (T->rchild != NULL) {
        printf("\n");
        ConcaveTablePrintBBST(T->rchild, m + 1);
    }
}

/**
 * 括号表示法打印AVL树
 *
 * @param T AVL树
 */
void ParenthesisPrintBBST(BBSTree T) {
    if (NULL == T) {
        return;
    }
    printf("%d", T->data.key);
    if (T->lchild != NULL || T->rchild != NULL) {
        printf("(");
        if (T->lchild != NULL) {
            ParenthesisPrintBBST(T->lchild);
        } else if (T->rchild != NULL) {
            printf("#");
        }
        printf(",");
        if (T->rchild != NULL) {
            ParenthesisPrintBBST(T->rchild);
        } else if (T->lchild != NULL){
            printf("#");
        }
        printf(")");
    }
}

/**
 * 平衡二叉树的删除操作
 *
 * @param T
 * @param key
 * @param shorter
 * @return
 */
Status DeleteAVL(BBSTree &T, KeyType key, Status &shorter) {
    if (NULL == T) {
        // 树为空
        return FALSE;
    } else if (T->data.key == key) {
        // 找到元素结点
        BBSTree p = NULL;
        if (NULL == T->lchild) {
            // 左子树为空
            p = T;
            T = T->rchild;
            free(p);
            shorter = TRUE; // 高度变矮
        } else if (T->rchild == NULL) {
            // 右子树为空
            p = T;
            T = T->lchild;
            free(p);
            shorter = TRUE; // 高度变矮
        } else {
            // 左右子树都存在
            p = T->lchild;
            while (p->rchild != NULL) {
                p = p->rchild;
            }
            T->data = p->data;
            // 在左子树中删除前驱结点
            DeleteAVL(T->lchild, p->data.key, shorter);
        }
    } else if (T->data.key > key) {
        if (DeleteAVL(T->lchild, key, shorter) == FALSE) {
            return FALSE;
        }
        if (shorter == TRUE) {
            switch (T->bf) {
                case LH: {
                    T->bf = EH;
                    shorter = TRUE;
                    break;
                } case EH: {
                    T->bf = RH;
                    shorter = FALSE;
                    break;
                } case RH: {
                    RightBalance(T);
                    if (T->rchild->bf == EH) {
                        shorter = FALSE;
                    } else {
                        shorter = TRUE;
                    }
                    break;
                }
            }
        }
    } else {
        if (DeleteAVL(T->rchild, key, shorter) == FALSE) {
            return FALSE;
        }
        if (shorter == TRUE) {
            switch (T->bf) {
                case LH: {
                    LeftBalance(T);
                    if (T->lchild->bf == EH) {
                        shorter = FALSE;
                    } else {
                        shorter = TRUE;
                    }
                    break;
                } case EH: {
                    T->bf = LH;
                    shorter = FALSE;
                    break;
                } case RH: {
                    T->bf = EH;
                    shorter = TRUE;
                    break;
                }
            }
        }
    }
    return TRUE;
}

/**
 * 输出平衡二叉树关键字
 * @param key 关键字
 */
void visit(KeyType key) {
    printf("%d  ", key);
}

/**
 * 前序遍历平衡二叉树
 *
 * @param T 平衡二叉树
 * @param visit 函数指针
 */
void PreOrderTraverse(BBSTree T, void( *visit)(KeyType)) {
    if (NULL == T) {
        return;
    }
  	visit(T->data.key);
    PreOrderTraverse(T->lchild, visit);
    PreOrderTraverse(T->rchild, visit);
}

/**
 * 中序遍历平衡二叉树
 *
 * @param T 平衡二叉树
 * @param visit 函数指针
 */
void InOrderTraverse(BBSTree T, void( *visit)(KeyType)) {
    if (NULL == T) {
        return;
    }
    InOrderTraverse(T->lchild, visit);
    visit(T->data.key);
    InOrderTraverse(T->rchild, visit);
}

/**
 * 后序遍历平衡二叉树
 *
 * @param T 平衡二叉树
 * @param visit 函数指针
 */
void PostOrderTraverse(BBSTree T, void( *visit)(KeyType)) {
    if (NULL == T) {
      	return;
    }
    PostOrderTraverse(T->lchild, visit);
    PostOrderTraverse(T->rchild, visit);
    visit(T->data.key);
}

/**
 * 层次遍历平衡二叉树
 *
 * @param T 平衡二叉树
 * @param visit 函数指针
 * @param level 层次
 * @return
 */
Status LevelOrderTraverse(BBSTree T, void( *visit)(KeyType), int level) {
    if (!T || level < 0) {
        return ERROR;
    }
    if (level == 0) {
        visit(T->data.key);
        return OK;
    }
    return LevelOrderTraverse(T->lchild, visit, level - 1) +
    		LevelOrderTraverse(T->rchild, visit, level - 1);
}

/**
 * 按层打印
 *
 * @param T 平衡二叉树
 */
void PrintNodeByLevel(BBSTree T) {
    if (NULL == T) {
        return;
    }
    int level;
    for (level = 0; ; level++) {
        if (!LevelOrderTraverse(T, visit, level)) {
            break;
        }
    }
}

/**
 * 分裂平衡二叉树，分成大于key和小于key两棵树
 *
 * @param T 待分裂的平衡二叉树
 * @param key 分裂的关键字
 * @param T1 关键字全部小于key的平衡二叉树
 * @param T2 关键字全部大于key的平衡二叉树
 */
void SpiltBBST(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2) {
    Status taller = FALSE;
	if (T != NULL) {
		SpiltBBST(T->lchild, key, T1, T2); // 递归访问左子树
		if(T->data.key > key) {
            InsertAVL(T1, T->data, taller);
		} else {
            InsertAVL(T2, T->data, taller);
		}
		SpiltBBST(T->rchild, key, T1, T2);
	}
}

/**
 * 合并平衡二叉树
 *
 * @param T1 合并后的平衡二叉树
 * @param T2 待合并的平衡二叉树
 */
void MergeBBST(BBSTree &T1, BBSTree T2) {
    Status taller = FALSE;
    if (T2 != NULL) {
        MergeBBST(T1, T2->lchild);
        InsertAVL(T1, T2->data, taller);
        MergeBBST(T1, T2->rchild);
    }
}

/**
 * 销毁平衡二叉树
 *
 * @param T 平衡二叉树
 */
void DestroyBBST(BBSTree &T) {
    if (T != NULL) {
        DestroyBBST(T->lchild);
        DestroyBBST(T->rchild);
        free(T);
    }
}
