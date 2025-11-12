//二叉树中查找值为x的结点，试设计打印值为x的结点的所有祖先结点算法
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// 定义二叉树节点结构
typedef struct BiTNode {
    int data;                      // 数据域
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
//查找值为x的结点打印值为x的结点的所有祖先结点
bool Findnodex(BiTree T, int x) {
    if (T == NULL) {
        return false;
    }
    
    // 如果当前节点就是目标节点
    if (T->data == x) {
        return true;
    }
    
    // 如果在左子树或右子树中找到目标节点
    if (Findnodex(T->lchild, x) || Findnodex(T->rchild, x)) {
        printf("%c ", T->data);  // 打印当前节点（祖先）
        return true;
    }
    
    return false;
}
// 测试程序
int main() {
    BiTree root;
    char target;
    printf("示例输入: ABC##D##E#F##\n");
    printf("请按先序遍历方式输入二叉树节点值（空节点用#表示）:\n");

    CreateBiTree(&root);
    
    // 清空输入缓冲区
    while (getchar() != '\n');
    
    printf("请输入要查找的节点值: ");
    scanf("%c", &target);
    printf("值为%c的节点的祖先节点是: ", target);
    if (!Findnodex(root, target)) {
        printf("未找到该节点");
    }
    printf("\n");
    return 0;
}