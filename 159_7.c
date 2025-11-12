//找出二叉树中同一层结点数据之和最大的层
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_LEVEL 100

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
// 计算每层节点值之和，并找出最大和所在的层
int FindMaxSumLevel(BiTree T) {
    if (!T) return 0;
    
    // 使用数组存储每层的和
    int levelSum[MAX_LEVEL] = {0};
    int maxLevel = 0;
    
    // 使用队列进行层次遍历
    BiTree queue[1000];
    int level[1000];  // 记录每个节点所在的层
    int front = 0, rear = 0;
    
    // 根节点入队
    queue[rear] = T;
    level[rear] = 1;
    rear++;
    
    while (front < rear) {
        // 出队
        BiTree node = queue[front];
        int curLevel = level[front];
        front++;
        
        // 累加当前层的值
        levelSum[curLevel] += node->data;
        if (curLevel > maxLevel) maxLevel = curLevel;
        
        // 左右子节点入队
        if (node->lchild) {
            queue[rear] = node->lchild;
            level[rear] = curLevel + 1;
            rear++;
        }
        if (node->rchild) {
            queue[rear] = node->rchild;
            level[rear] = curLevel + 1;
            rear++;
        }
    }
    
    // 找出和最大的层
    int maxSum = INT_MIN;
    int maxSumLevel = 1;
    for (int i = 1; i <= maxLevel; i++) {
        if (levelSum[i] > maxSum) {
            maxSum = levelSum[i];
            maxSumLevel = i;
        }
    }
    
    // 输出各层的和用于验证
    printf("各层节点和:\n");
    for (int i = 1; i <= maxLevel; i++) {
        printf("第%d层: %d\n", i, levelSum[i]);
    }
    
    return maxSumLevel;
}
int main() {
    BiTree root;
    printf("示例输入：123##4##5#6##\n");
    printf("请按先序遍历方式输入二叉树节点值（空节点用#表示）:\n");
    CreateBiTree(&root);
    if (!root) {
        printf("空树\n");
        return 0;
    }
    int maxLevel = FindMaxSumLevel(root);
    printf("节点和最大的层是第%d层\n", maxLevel);
    return 0;
}