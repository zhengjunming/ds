#include <iostream>
#include "main.h"
#include "AVLTree.h"

using namespace std;

int flag = NOT_CREATED; // 全局变量，用来判断平衡二叉树是否已经创建

/**
 * 平衡二叉树演示功能菜单
 */
void AVLMenu() {
    system("color 0D");
    printf("**************************************************************************\n");
    printf("*                                                                        *\n");
    printf("************************平衡二叉树演示功能选择菜单************************\n");
    printf("*                                                                        *\n");
    printf("****************制作人：郑俊铭（3116005120）16级软件卓越******************\n");
    printf("*                                                                        *\n");
    printf("*                         1. 创建一棵平衡二叉树                          *\n");
    printf("*                         2. 插入结点                                    *\n");
    printf("*                         3. 删除结点                                    *\n");
    printf("*                         4. 查找结点                                    *\n");
    printf("*                         5. 遍历输出平衡二叉树                          *\n");
    printf("*                         6. 显示平衡二叉树                              *\n");
    printf("*                         7. 分裂一棵平衡二叉树                          *\n");
    printf("*                         8. 合并两棵平衡二叉树                          *\n");
    printf("*                         9. 销毁平衡二叉树                              *\n");
    printf("*                         0. 退出                                        *\n");
    printf("*                                                                        *\n");
    printf("**************************************************************************\n");
}

/**
 * 创建平衡二叉树操作
 *
 * @param T 平衡二叉树
 */
void InitBBSTreeOperation(BBSTree &T) {
    if (flag == HAVE_BEEN_CREATED) {
        // 如果已经有一颗平衡二叉树被创建
        printf("您之前已经创建了一颗平衡二叉树，是否销毁之前创建的重新创建？（Y/y：是, 其他任意键为否）");
        char choice = getchar();
        fflush(stdin);
        if (toupper(choice) == 'Y') {
            DestroyBBST(T);
            printf("平衡二叉树已经被销毁，现在可以创建一棵新的平衡二叉树。");
        } else {
            return;
        }
    }
    printf("\n1. 创建一棵空平衡二叉树，2. 创建一棵非空平衡二叉树：");
    int createOption;
    while (1) {
        scanf("%d", &createOption);
        getchar();
        fflush(stdin);
        if (createOption == 1) {
            T = NULL;
            printf("空平衡二叉树创建成功.\n");
            flag = HAVE_BEEN_CREATED;
            break;
        } else if (createOption == 2) {
            T = NULL;
            int AVLSize = 0; // AVL树大小，即结点数
            printf("\n请输入要创建的平衡二叉树的结点数（只支持1-100的输入）: ");
            while (1) {
                int result = scanf("%d", &AVLSize);
                getchar();
                fflush(stdin);
                if (result == 1) {
                    if (AVLSize >= 1 && AVLSize <= 100) {
                        break;
                    }
                }
                printf("请输入正确的值！\n");
                printf("\n请输入要创建的平衡二叉树的结点数（只支持1-100的输入）: ");
            }
            srand((unsigned int) time(NULL));
            int i;
            KeyType key;
            RcdType rcd;
            Status taller = FALSE;
            for (i = 1; i <= AVLSize; i++) {
                key = rand() % 1000;
                rcd.key = key;
                InsertAVL(T, rcd, taller);
            }
            flag = HAVE_BEEN_CREATED;
            printf("----------------------------------------------------\n");
            printf("随机数创建后的平衡二叉树如下所示：\n");
            printf("凹入表表示法：\n\n");
            ConcaveTablePrintBBST(T, 1);
            printf("\n\n");
            printf("括号表示法：");
            ParenthesisPrintBBST(T);
            printf("\n----------------------------------------------------\n");
            break;
        } else {
            printf("请输入正确的值\n");
            printf("\n1. 创建一棵空平衡二叉树，2. 随机数创建一棵非空平衡二叉树：");
        }
    }
}

/**
 * 插入结点操作
 *
 * @param T 平衡二叉树
 */
void InsertAVLOperation(BBSTree &T) {
    if (flag == NOT_CREATED) {
        // 平衡二叉树还未创建
        printf("您还未创建平衡二叉树，无法插入结点，请先创建。");
        return;
    } else if (flag == HAVE_BEEN_CREATED) {
        if (NULL == T) {
            printf("您的平衡二叉树是空的，快为它插入结点吧！\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\n您的平衡二叉树为：");
            ParenthesisPrintBBST(T);
            printf("\n凹入表显示如下：\n\n");
            ConcaveTablePrintBBST(T, 1);
            printf("\n----------------------------------------------------\n\n");
        }
        while (1) {
            printf("请输入要插入结点的关键字: ");
            KeyType key;
            RcdType rcd;
            while (1 != scanf("%d", &key)) {
                getchar();
                fflush(stdin);
                fprintf(stderr, "请输入正确的值！\n");
                printf("请输入要插入结点的关键字: ");
            }
            rcd.key = key;
            Status taller = FALSE;
            if (SearchBBST(T, key) != NULL) {
                printf("插入失败了，因为您输入的关键字已经存在了，下次请输入正确的值。\n\n");
            } else {
                InsertAVL(T, rcd, taller);
                printf("\n----------------------------------------------------");
                printf("\n插入后的平衡二叉树为：");
                ParenthesisPrintBBST(T);
                printf("\n凹入表显示如下：\n\n");
                ConcaveTablePrintBBST(T, 1);
                printf("\n----------------------------------------------------\n\n");
            }
            printf("是否继续插入？（Y/y：是, 其他任意键为否）：");
            char c;
            getchar();
            scanf("%c", &c);
            fflush(stdin);
            if (toupper(c) != 'Y') {
                break;
            }
            printf("\n");
        }
    }
}

/**
 * 删除结点操作
 *
 * @param T 平衡二叉树
 */
void DeleteAVLOperation(BBSTree &T) {
    if (flag == NOT_CREATED) {
        // 平衡二叉树还未创建
        printf("您还未创建平衡二叉树，无法删除结点，请先创建。");
    } else if (flag == HAVE_BEEN_CREATED) {
        if (NULL == T) {
            printf("您的平衡二叉树是空的，无法删除结点，请先插入结点！\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\n您的平衡二叉树为：");
            ParenthesisPrintBBST(T);
            printf("\n凹入表显示如下：\n\n");
            ConcaveTablePrintBBST(T, 1);
            printf("\n----------------------------------------------------");
            printf("\n\n");
            while (1) {
                printf("请输入要删除结点的关键字: ");
                KeyType key;
                while (1 != scanf("%d", &key)) {
                    getchar();
                    fflush(stdin);
                    fprintf(stderr, "请输入正确的值！\n");
                    printf("请输入要删除结点的关键字: ");
                }
                if (NULL == SearchBBST(T, key)) {
                    // 关键字不在平衡二叉树里面
                    printf("您输入的关键字不在平衡二叉树中。\n\n");
                } else {
                    Status shorter = FALSE;
                    DeleteAVL(T, key, shorter);
                    if (NULL == T) {
                        printf("平衡二叉树已经被您删除干净了，不用继续删除了\n");
                        break;
                    } else {
                        printf("\n----------------------------------------------------");
                        printf("\n删除后的平衡二叉树为：");
                        ParenthesisPrintBBST(T);
                        printf("\n凹入表显示如下：\n\n");
                        ConcaveTablePrintBBST(T, 1);
                        printf("\n----------------------------------------------------\n\n");
                    }
                }
                printf("是否继续删除？（Y/y：是, 其他任意键为否）：");
                char c;
                getchar();
                scanf("%c", &c);
                fflush(stdin);
                if (toupper(c) != 'Y') {
                    break;
                }
                printf("\n");
            }
        }
    }
}

/**
 * 查找结点操作
 *
 * @param T 平衡二叉树
 */
void SearchBBSTOperation(BBSTree &T) {
    KeyType key;
    BBSTree p;
    if (NOT_CREATED == flag) {
        printf("您还未创建平衡二叉树，无法进行查找，请先创建。\n");
        return;
    }
    if (NULL == T) {
        printf("您的平衡二叉树是空的！\n");
        return;
    } else {
        printf("\n----------------------------------------------------");
        printf("\n您的平衡二叉树为：");
        ParenthesisPrintBBST(T);
        printf("\n凹入表显示如下：\n\n");
        ConcaveTablePrintBBST(T, 1);
        printf("\n----------------------------------------------------\n\n");
        printf("请输入您要查找的关键字：");
        while (scanf("%d", &key) != 1) {
            printf("请输入正确的值!\n");
            printf("请输入您要查找的关键字：");
        }
        p = SearchBBST(T, key);
        if (NULL == p) {
            printf("没有找到该关键字。\n");
        } else {
            printf("以关键字所在结点的子树如下：\n");
            printf("------------------------------------------------------\n");
            ParenthesisPrintBBST(p);
            printf("\n\n凹入表显示如下：\n\n");
            ConcaveTablePrintBBST(p, 1);
            printf("\n----------------------------------------------------\n\n");
        }
    }
}

/**
 * 遍历平衡二叉树操作
 *
 * @param T 平衡二叉树
 */
void VisitOperation(BBSTree T) {
    if (flag == NOT_CREATED) {
        // 平衡二叉树还未创建
        printf("您还未创建平衡二叉树，无法遍历输出，请先创建。\n");
    } else if (flag == HAVE_BEEN_CREATED) {
        if (NULL == T) {
            printf("您的平衡二叉树是空的请先插入结点！\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\n您的平衡二叉树为：");
            ParenthesisPrintBBST(T);
            printf("\n凹入表显示如下：\n\n");
            ConcaveTablePrintBBST(T, 1);
            printf("\n\n前序遍历输出为：");
            PreOrderTraverse(T, visit);
            printf("\n中序遍历输出为：");
            InOrderTraverse(T, visit);
            printf("\n后序遍历输出为：");
            PostOrderTraverse(T, visit);
            printf("\n层次遍历输出为：");
            PrintNodeByLevel(T);
            printf("\n----------------------------------------------------\n\n");
        }
    }
}

/**
 * 打印平衡二叉树操作
 *
 * @param T 平衡二叉树
 */
void PrintBBSTOperation(BBSTree T) {
    if (flag == NOT_CREATED) {
        // 平衡二叉树还未创建
        printf("您还未创建平衡二叉树，无法显示，请先创建。\n");
    } else if (flag == HAVE_BEEN_CREATED) {
        if (NULL == T) {
            printf("您的平衡二叉树是空的请先插入结点！\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\n您的平衡二叉树为：");
            ParenthesisPrintBBST(T);
            printf("\n凹入表显示如下：\n\n");
            ConcaveTablePrintBBST(T, 1);
            printf("\n----------------------------------------------------\n\n");
        }
    }
}

/**
 * 分裂平衡二叉树操作
 *
 * @param T 平衡二叉树
 */
void SpiltBBSTOperation(BBSTree T) {
    if (flag == NOT_CREATED) {
        // 平衡二叉树还未创建
        printf("您还未创建平衡二叉树，无法分裂，请先创建。\n");
    } else if (flag == HAVE_BEEN_CREATED) {
        if (NULL == T) {
            printf("您的平衡二叉树是空的请先插入结点！\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\n您的平衡二叉树为：");
            ParenthesisPrintBBST(T);
            printf("\n凹入表显示如下：\n\n");
            ConcaveTablePrintBBST(T, 1);
            printf("\n----------------------------------------------------\n\n");
            printf("请输入要分裂的关键字: ");
            KeyType key;
            while (1) {
                while (1 != scanf("%d", &key)) {
                    getchar();
                    fflush(stdin);
                    fprintf(stderr, "请输入正确的值！\n");
                    printf("请输入要分裂的关键字: ");

                }
                if (NULL == SearchBBST(T, key)) {
                    // 关键字不在平衡二叉树里面
                    printf("您输入的关键字不在平衡二叉树中。\n\n");
                    printf("请重新输入要分裂的关键字: ");
                } else {
                    BBSTree T1 = NULL;
                    BBSTree T2 = NULL;
                    SpiltBBST(T, key, T1, T2);
                    printf("\n----------------------------------------------------\n");
                    printf("1. 关键字比%d大的子树为：", key);
                    ParenthesisPrintBBST(T1);
                    printf("\n凹入表显示如下：\n\n");
                    ConcaveTablePrintBBST(T1, 1);
                    printf("\n----------------------------------------------------\n\n");

                    printf("\n----------------------------------------------------\n");
                    printf("2. 关键字小于等于%d的子树为：", key);
                    ParenthesisPrintBBST(T2);
                    printf("\n凹入表显示如下：\n\n");
                    ConcaveTablePrintBBST(T2, 1);
                    printf("\n----------------------------------------------------\n\n");
                    break;
                }
            }
        }
    }
}

/**
 * 合并平衡二叉树操作
 *
 * @param T 平衡二叉树
 */
void MergeBBSTOperation(BBSTree &T) {
    if (flag == NOT_CREATED) {
        // 平衡二叉树还未创建
        printf("您还未创建平衡二叉树，请先创建。\n");
    } else if (flag == HAVE_BEEN_CREATED) {
        if (NULL == T) {
            printf("您的平衡二叉树是空的，现在你可以创建一棵平衡二叉树合并到此二叉树中\n");
        } else {
            printf("\n----------------------------------------------------");
            printf("\n现在您的平衡二叉树为：");
            ParenthesisPrintBBST(T);
            printf("\n凹入表显示如下：\n\n");
            ConcaveTablePrintBBST(T, 1);
            printf("\n----------------------------------------------------");
            printf("\n现在你可以创建一棵平衡二叉树合并到此二叉树中\n\n");
        }
        BBSTree T1 = NULL;
        int AVLSize = 0; // AVL树大小，即结点数
        printf("\n请输入要创建的平衡二叉树的结点数（只支持1-100的输入）: ");
        while (1) {
            int result = scanf("%d", &AVLSize);
            getchar();
            fflush(stdin);
            if (result == 1) {
                if (AVLSize >= 1 && AVLSize <= 100) {
                    break;
                }
            }
            printf("请输入正确的值！\n");
            printf("\n请输入要创建的平衡二叉树的结点数（只支持1-100的输入）: ");
        }
        srand((unsigned int) time(NULL));
        int i;
        KeyType key;
        RcdType rcd;
        Status taller = FALSE;
        for (i = 1; i <= AVLSize; i++) {
            key = rand() % 1000;
            rcd.key = key;
            InsertAVL(T1, rcd, taller);
        }
        printf("\n----------------------------------------------------");
        printf("\n新创建的平衡二叉树为：");
        ParenthesisPrintBBST(T1);
        printf("\n凹入表显示如下：\n\n");
        ConcaveTablePrintBBST(T1, 1);
        printf("\n----------------------------------------------------\n\n");
        MergeBBST(T, T1);
        DestroyBBST(T1);
        printf("\n----------------------------------------------------");
        printf("\n合并后的平衡二叉树为：");
        ParenthesisPrintBBST(T);
        printf("\n凹入表显示如下：\n\n");
        ConcaveTablePrintBBST(T, 1);
        printf("\n----------------------------------------------------\n\n");
    }
}

/**
 * 销毁平衡二叉树操作
 *
 * @param T 平衡二叉树
 */
void DestroyBBSTOperation(BBSTree &T) {
    if (flag == NOT_CREATED) {
        // 平衡二叉树还未创建
        printf("您还未创建平衡二叉树，不用销毁。\n");
    } else if (flag == HAVE_BEEN_CREATED) {
        if (NULL == T) {
            printf("您的平衡二叉树是空的，不用销毁\n");
        } else {
            printf("\n是否销毁？（Y/y：是, 其他任意键为否）");
            char option;
            option = getchar();
            fflush(stdin);
            if (toupper(option) == 'Y') {
                DestroyBBST(T);
                flag = NOT_CREATED;
            }
        }
    }
}

/**
 * 测试主函数
 */
int main()
{
    system("color 0F");
    int selectNum; // 菜单选择
    BBSTree T;
    while (1) {
        AVLMenu();
        printf("请输入您想进行的操作：");
        scanf("%d", &selectNum);
        getchar();
        fflush(stdin);
        if (0 == selectNum) {
            printf("\n是否退出？（Y/y：是, 其他任意键为否）");
            char option;
            option = getchar();
            fflush(stdin);
            if (toupper(option) == 'Y') {
                if (flag == HAVE_BEEN_CREATED) {
                    DestroyBBST(T);
                }
                // 选择退出，大小写皆可
                exit(EXIT_SUCCESS);
            }
        } else {
            switch (selectNum) {
                case 1: InitBBSTreeOperation(T); break; // 初始化创建平衡二叉树
                case 2: InsertAVLOperation(T); break; // 插入
                case 3: DeleteAVLOperation(T); break; // 删除
                case 4: SearchBBSTOperation(T); break; // 查找
                case 5: VisitOperation(T); break; // 遍历
                case 6: PrintBBSTOperation(T); break; // 打印
                case 7: SpiltBBSTOperation(T); break; // 分裂
                case 8: MergeBBSTOperation(T); break; // 合并
                case 9: DestroyBBSTOperation(T); break; // 销毁
                default: fprintf(stderr, "请输入正确的值！\n"); break;
            }
        }
        system("PAUSE");
        system("CLS"); // 清屏操作
    }
    system("PAUSE");
    getch();
    return 0;
}
