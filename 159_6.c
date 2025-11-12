//给定一颗用二叉链表表示的二叉树，其根指针为root，试写出二叉树中所有节点的左右子树相互交换的算法
#include <stdio.h>
#include <stdlib.h>

// 题目：编写算法交换二叉树中所有结点的左右子树
// 方法：通过递归遍历二叉树，对每个节点交换其左右子树
typedef struct BiTNode {
    char data;                     // 数据域
    struct BiTNode *lchild, *rchild; // 左右孩子指针
} BiTNode, *BiTree;

// 创建二叉树
// 按前序遍历的顺序输入节点，用'#'表示空节点
void CreateBiTree(BiTree *T) {
    char ch;
    scanf("%c", &ch);

    if(ch == '#') {
        *T = NULL;
    } else {
        *T = (BiTNode *)malloc(sizeof(BiTNode));
        (*T)->data = ch;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
}

// 交换二叉树中所有节点的左右子树
void ExchangeTree(BiTree T) {
    if(T == NULL) {
        return;
    }

    // 交换左右子树
    BiTree temp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = temp;

    // 递归交换左子树
    ExchangeTree(T->lchild);
    // 递归交换右子树
    ExchangeTree(T->rchild);
}

// 前序遍历二叉树
void PreOrderTraverse(BiTree T) {
    if(T == NULL) {
        return;
    }
    printf("%c ", T->data);
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}

// 中序遍历二叉树
void InOrderTraverse(BiTree T) {
    if(T == NULL) {
        return;
    }
    InOrderTraverse(T->lchild);
    printf("%c ", T->data);
    InOrderTraverse(T->rchild);
}

// 测试程序：创建二叉树，输出交换前后遍历结果进行对比
int main() {
    BiTree root;
    printf("示例输入：ABD##E##C#F##\n");
    printf("请按前序遍历顺序输入二叉树节点(空节点用#表示):\n");
    CreateBiTree(&root);

    printf("\n交换前的二叉树前序遍历: ");
    PreOrderTraverse(root);
    printf("\n交换前的二叉树中序遍历: ");
    InOrderTraverse(root);

    // 交换左右子树
    ExchangeTree(root);

    printf("\n\n交换后的二叉树前序遍历: ");
    PreOrderTraverse(root);
    printf("\n交换后的二叉树中序遍历: ");
    InOrderTraverse(root);
    printf("\n");

    return 0;
}