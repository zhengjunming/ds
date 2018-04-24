#include <iostream>
#include "main.h"
#include "BTree.h"

using namespace std;

int btreeStatus = NOT_INIT; // B树状态，初始值为未初始化

/**
 * 初始化一棵B树
 *
 * @param t B树
 */
void InitBTreeOperation(BTree &t) {
    if (btreeStatus == HAVE_BEEN_INIT) {
        printf("您有一棵B树已经创建，是否销毁它重新创建？（Y：是, 其他任意键为否）");
        char choice = getchar();
        fflush(stdin);
        if (toupper(choice) == 'Y') {
            DestoryBTree(t);
            btreeStatus = NOT_INIT;
        } else {
            return;
        }
    }
    InitBTree(t);
    btreeStatus = HAVE_BEEN_INIT;
}

/**
 * 插入结点操作
 *
 * @param t B树
 */
void InsertKeyOperation(BTree &t) {
    Result r;
    KeyType key;
    if (NOT_INIT == btreeStatus) {
        printf("B树还未初始化，请先初始化！\n");
        return;
    }
    if (NULL == t) {
        printf("现在B树是空的，");
    } else {
        printf("B树的凹入表显示如下：\n\n");
        printf("------------------------------------------------------\n");
        PrintBTree(t, 1);
        printf("\n------------------------------------------------------\n");
    }
    while (1) {
        printf("请输入您想插入的关键字：");
        while (1 != scanf("%d", &key)) {
            getchar();
            fflush(stdin);
            printf("请输入正确的值！\n");
            printf("请输入您想插入的关键字：");
        }
        SearchBTree(t, key, r);
        if (1 == r.tag) {
            printf("该关键字已经存在于B-树中。\n");
        } else if (0 == r.tag) {
            InsertBTree(t, key, r.pt, r.i);
            printf("插入成功，插入后的B-树如下：\n");
            printf("------------------------------------------------------\n");
            PrintBTree(t, 1);
            printf("\n------------------------------------------------------\n");
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

/**
 * 删除结点操作
 *
 * @param t B树
 */
void DeleteKeyOperation(BTree &t) {
    Result r;
    KeyType key;
    if (NOT_INIT == btreeStatus) {
        printf("B树还未初始化，请先初始化！\n");
        return;
    }
    if (NULL == t) {
        printf("现在B树是空的，无法进行删除操作！\n");
        return;
    } else {
        printf("B树的凹入表显示如下：\n\n");
        printf("------------------------------------------------------\n");
        PrintBTree(t, 1);
        printf("\n------------------------------------------------------\n");
        while (1) {
            printf("请输入您想删除的关键字：");
            while (1 != scanf("%d", &key)) {
                getchar();
                fflush(stdin);
                printf("请输入正确的值！\n");
                printf("请输入您想删除的关键字：");
            }
            SearchBTree(t, key, r);
            if (1 == r.tag) {
                DeleteBTree(t, r.pt, r.i);
                if (BTreeKeyNumber(t) == 0) {
                    t = NULL;
                    printf("删除成功B树的关键字已经全部被删除了！\n");
                    break;
                } else {
                    printf("删除成功，删除后的B-树如下：\n");
                    printf("------------------------------------------------------\n");
                    PrintBTree(t, 1);
                    printf("\n------------------------------------------------------\n");
                }
            } else if (0 == r.tag) {
                printf("该关键字不在B树中，无法删除！\n");
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

/**
 * 查找结点操作
 *
 * @param t B树
 */
void SearchOperation(BTree t) {
    KeyType key;
    Result r;
    if (NOT_INIT == btreeStatus) {
        printf("B树还未初始化，请先初始化！\n");
        return;
    }
    if (NULL == t) {
        printf("现在B树是空的，无法进行查找操作！\n");
        return;
    } else {
        printf("B树的凹入表显示如下：\n\n");
        printf("------------------------------------------------------\n");
        PrintBTree(t, 1);
        printf("\n------------------------------------------------------\n");
        printf("请输入您要查找的关键字：");
        scanf("%d", &key);
        SearchBTree(t, key, r);
        if (0 == r.tag) {
            printf("没有查到该关键字。\n");
        } else {
            printf("以关键字所在结点的子树如下：\n");
            printf("------------------------------------------------------\n");
            PrintBTree(r.pt, 1);
            printf("\n------------------------------------------------------\n");
        }
    }
}

/**
 * 随机生成指定大小的B树
 *
 * @param t B树
 */
void CreateBTreeRandomOperation(BTree &t) {
    if (btreeStatus == HAVE_BEEN_INIT) {
        printf("您有一棵B树已经创建，是否销毁它重新创建？（Y：是, 其他任意键为否）");
        char choice = getchar();
        fflush(stdin);
        if (toupper(choice) == 'Y') {
            DestoryBTree(t);
            btreeStatus = NOT_INIT;
        } else {
            return;
        }
    }
    printf("输入您想生成的B树关键字数量（只支持1-1000的输入）：");
    int keyNumber;
    while (1) {
        int result = scanf("%d", &keyNumber);
        getchar();
        fflush(stdin);
        if (result == 1) {
            if (keyNumber >= 1 && keyNumber <= 1000) {
                break;
            }
        }
        printf("请输入正确的值！\n");
        printf("请输入您想生成的B树关键字数量（只支持1-1000的输入）：");
    }
    CreateBTreeRandom(t, keyNumber);
    printf("\n生成成功，下面是B树的凹入表显示：\n");
    printf("------------------------------------------------------\n");
    PrintBTree(t, 1);
    printf("\n------------------------------------------------------\n");
    btreeStatus = HAVE_BEEN_INIT;
}

/**
 * 顺序输出B树操作
 *
 * @param t B树
 */
void OrderTraverseBTreeOperation(BTree t) {
    if (NOT_INIT == btreeStatus) {
        printf("B树还没初始化！请先初始化\n");
    } else if (NULL == t) {
        printf("B树为空\n");
    } else {
        printf("B树的关键字数量为%d，顺序输出如下：\n", BTreeKeyNumber(t));
        OrderTraverseBTree(t);
        printf("\n");
    }
}

/**
 * 凹入表打印B树操作
 *
 * @param t B树
 */
void PrintBTreeOperation(BTree t) {
    if (NOT_INIT == btreeStatus) {
            printf("B树还没初始化！请先初始化\n");
    } else if (NULL == t) {
        printf("B树为空\n");
    } else {
        printf("B树的凹入表显示如下：\n\n");
        printf("------------------------------------------------------\n");
        PrintBTree(t, 1);
        printf("\n------------------------------------------------------\n");
    }
}

/**
 * 销毁B树操作
 *
 * @param t B树
 */
void DestoryBTreeOperation(BTree &t) {
    if (btreeStatus == NOT_INIT) {
        printf("B树还没创建，不用销毁\n");
    } else if (t == NULL) {
        printf("B树为空，不用销毁\n");
    } else {
        DestoryBTree(t);
        btreeStatus = NOT_INIT;
        printf("销毁成功\n");
    }
}

/**
 * B-树功能演示选择菜单
 */
void BTreeMenu() {
    system("color 0D");
    printf("**************************************************************************\n");
    printf("*                                                                        *\n");
    printf("***************************B-树功能选择菜单*******************************\n");
    printf("*                                                                        *\n");
    printf("****************制作人：郑俊铭（3116005120）16级软件卓越******************\n");
    printf("*                                                                        *\n");
    printf("*                         1. 创建一棵空B-树                              *\n");
    printf("*                         2. 随机生成一棵B-树                            *\n");
    printf("*                         3. 插入关键字                                  *\n");
    printf("*                         4. 删除关键字                                  *\n");
    printf("*                         5. 查找关键字                                  *\n");
    printf("*                         6. 关键字数量                                  *\n");
    printf("*                         7. 升序输出B-树关键字                          *\n");
    printf("*                         8. 凹入表打印B-树                              *\n");
    printf("*                         9. 销毁B-树                                    *\n");
    printf("*                         0. 退出                                        *\n");
    printf("*                                                                        *\n");
    printf("**************************************************************************\n");
}

/**
 * 主函数
 */
int main()
{
    BTree t;
    int selectNum;
    while (1) {
        BTreeMenu();
        printf("请输入您的选择：");
        scanf("%d", &selectNum);
        getchar();
        fflush(stdin);
        if (0 == selectNum) {
            printf("\n是否退出？（Y：是, 其他任意键为否）");
            char option;
            option = getchar();
            fflush(stdin);
            if (toupper(option) == 'Y') {
                if (btreeStatus == HAVE_BEEN_INIT) {
                    DestoryBTree(t);
                }
                exit(EXIT_SUCCESS);
            }
        } else {
            switch (selectNum) {
                case 1: InitBTreeOperation(t); break;
                case 2: CreateBTreeRandomOperation(t); break;
                case 3: InsertKeyOperation(t); break;
                case 4: DeleteKeyOperation(t); break;
                case 5: SearchOperation(t); break;
                case 6: {
                    if (NOT_INIT == btreeStatus) {
                        printf("B树还没初始化！请先初始化\n");
                    } else {
                        printf("\n关键字数量为: %d\n\n", BTreeKeyNumber(t));
                    }
                    break;
                }
                case 7: OrderTraverseBTreeOperation(t); break;
                case 8: PrintBTreeOperation(t); break;
                case 9: DestoryBTreeOperation(t); break;
                default: printf("您输入的选择不正确，请重新输入！\n"); break;
            }
        }
        system("PAUSE");
        system("cls"); // 清屏操作
    }
    system("PAUSE");
    getch();
    return 0;
}
