//编写算法判断一颗二叉链表表示的二叉树是否是完全二叉树
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
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
// 判断二叉树是否为完全二叉树
// 算法思路：使用层次遍历，一旦出现空节点，之后就不应该再有非空节点
int IsCompleteBinaryTree(BiTree T) {
    if (T == NULL) {
        return 1; // 空树被认为是完全二叉树
    }
    
    BiTree queue[MAXSIZE];
    int front = 0, rear = 0;
    int reachNull = 0; // 标记是否遇到了空节点
    
    // 根节点入队
    queue[rear] = T;
    rear = (rear + 1) % MAXSIZE;
    
    while (front != rear) {
        // 出队
        BiTree node = queue[front];
        front = (front + 1) % MAXSIZE;
        
        if (node == NULL) {
            reachNull = 1; // 遇到了空节点
        } else {
            // 如果已经遇到了空节点，但又出现了非空节点，则不是完全二叉树
            if (reachNull) {
                return 0;
            }
            
            // 将左右子节点加入队列（即使是空节点也要加入）
            queue[rear] = node->lchild;
            rear = (rear + 1) % MAXSIZE;
            queue[rear] = node->rchild;
            rear = (rear + 1) % MAXSIZE;
        }
    }
    
    return 1; // 是完全二叉树
}
// 前序遍历（用于测试）
void PreOrderTraverse(BiTree T) {
    if (T) {
        printf("%c ", T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}
// 主函数
int main() {
    BiTree root;
    printf("示例输入：123##4##5#6##\n");
    printf("请按前序遍历顺序输入二叉树节点（用#表示空节点）：\n");
    CreateBiTree(&root);
    
    printf("\n前序遍历结果：");
    PreOrderTraverse(root);
    printf("\n");
    if (IsCompleteBinaryTree(root)) {
        printf("\n该二叉树是完全二叉树。\n");
    } else {
        printf("\n该二叉树不是完全二叉树。\n");
    }
    
    return 0;
}