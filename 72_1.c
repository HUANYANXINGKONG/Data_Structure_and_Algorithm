//Josephus环问题
//设编号为1, 2, ..., n的n个人按顺时针方向围坐一圈，约定编号为k（1≤k≤n）的人按顺时针方向从1开始报数，数到m的那个人出列，它的下一位又从1开始报数，数到m的那个人又出列，依次类推，直到所有人出列为止，由此产生一个出队编号的序列。试设计算法求出n个人的出列顺序。
//基本要求：程序运行时，首先要求用户指定人数n，第一个开始报数的人的编号k及报数上限值m。然后，按照出列的顺序打印出相应的编号序列。
//算法思路：先创建一个含有n个结点的单循环链表，然后由第一个结点起从1开始计数（此时假设k=1），计到m时，对应结点从链表中删除，接下来从被删除结点的下一个结点重新开始从1开始计数，计到m时，从链表中删除对应结点，如此循环，直至最后一个结点从链表中删除，算法结束。
//选作内容1）在顺序结构上实现本算法。需要考虑如何实现循环的顺序结构。2）m不再固定。假设n个人每人持有一个密码（正整数），从编号为k的人开始从1开始顺序报数，报到m的人出列，此时将他的密码作为新的m值，从他顺时针方向上的下一个人开始重新从1报数，报到m的人出列，而后将他的密码作为新的m值，如此循环下去，直到所有人全部出列为止。3）显示仿真的运行界面。
#include <stdio.h>
#include <stdlib.h>
// 定义链表节点结构
typedef struct Node {
    int data;           // 存储编号
    struct Node* next;  // 指向下一个节点
} Node;
// 创建循环链表
Node* createCircularList(int n)
{
    if (n <= 0) return NULL;
    
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = 1;
    head->next = head;
    
    if (n == 1) return head;
    
    Node* tail = head;
    for (int i = 2; i <= n; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = i;
        newNode->next = head;
        tail->next = newNode;
        tail = newNode;
    }
    
    return head;
}
// 约瑟夫环问题函数
void jp(int n, int k, int m) {
    if (n <= 0 || k <= 0 || k > n || m <= 0)
    {
        printf("输入参数无效！\n");
        return;
    }
    printf("\n=== 约瑟夫环问题（链表实现） ===\n");
    printf("参数：总人数 n=%d,起始位置 k=%d,报数上限 m=%d\n", n, k, m);
    printf("出列顺序：");
    
    // 创建循环链表
    Node* head = createCircularList(n);
    Node* current = head;
    Node* prev = NULL;
    
    // 移动到第k个人
    for (int i = 1; i < k; i++) 
    {
        prev = current;
        current = current->next;
    }
    
    // 开始报数出列
    while (n > 0)
    {
        // 报数m-1次，找到要出列的前一个节点
        for (int i = 1; i < m; i++)
        {
            prev = current;
            current = current->next;
        }
        
        // 输出出列者编号
        printf("%d", current->data);
        if (n > 1) printf(" -> ");
        
        // 删除当前节点
        if (current == head && n > 1)
        {
            head = current->next;
        }
        prev->next = current->next;
        
        Node* temp = current;
        current = current->next;
        free(temp);
        n--;
    }
    printf("\n");
}
//在顺序结构上实现
void sxjp(int n, int k, int m) {
    if (n <= 0 || k <= 0 || k > n || m <= 0)
    {
        printf("输入参数无效！\n");
        return;
    }
    printf("\n=== 约瑟夫环问题（顺序结构实现） ===\n");
    printf("参数：总人数 n=%d, 起始位置 k=%d, 报数上限 m=%d\n", n, k, m);
    printf("出列顺序：");
    int* circle = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        circle[i] = i + 1;  // 编号从1开始
    }
    
    int current = k - 1;  // 转换为0-based索引
    int count = n;
    
    while (count > 0)
    {
        // 计算要出列的位置
        current = (current + m - 1) % count;
        
        // 输出出列者
        printf("%d", circle[current]);
        if (count > 1) printf(" -> ");
        
        // 删除该元素，后面的元素前移
        for (int i = current; i < count - 1; i++)
        {
            circle[i] = circle[i + 1];
        }
        count--;
    }
    printf("\n");
    free(circle);
}
// 动态m值版本
// 扩展节点结构（包含密码）
typedef struct AdvancedNode {
    int data;           // 编号
    int password;       // 密码
    struct AdvancedNode* next;
} AdvancedNode;

// 创建带密码的循环链表
AdvancedNode* createAdvancedList(int n, int* passwords)
{
    if (n <= 0) return NULL;
    AdvancedNode* head = (AdvancedNode*)malloc(sizeof(AdvancedNode));
    head->data = 1;
    head->password = passwords[0];
    head->next = head;
    
    if (n == 1) return head;
    AdvancedNode* tail = head;
    for (int i = 2; i <= n; i++) {
        AdvancedNode* newNode = (AdvancedNode*)malloc(sizeof(AdvancedNode));
        newNode->data = i;
        newNode->password = passwords[i-1];
        newNode->next = head;
        tail->next = newNode;
        tail = newNode;
    }
    return head;
}

// 动态m值的约瑟夫环问题实现
void nmjp(int n, int k, int initialM, int* passwords)
{
    if (n <= 0 || k <= 0 || k > n || initialM <= 0)
    {
        printf("输入参数无效！\n");
        return;
    }
    
    printf("=== 动态m值的约瑟夫环问题 ===\n");
    printf("参数：总人数 n=%d, 起始位置 k=%d, 初始m=%d\n", n, k, initialM);
    printf("密码序列：");
    for (int i = 0; i < n; i++) {
        printf("%d ", passwords[i]);
    }
    printf("\n出列顺序：");
    
    // 创建带密码的循环链表
    AdvancedNode* head = createAdvancedList(n, passwords);
    AdvancedNode* current = head;
    AdvancedNode* prev = NULL;
    
    int m = initialM;
    
    // 移动到第k个人
    for (int i = 1; i < k; i++)
    {
        prev = current;
        current = current->next;
    }
    // 开始报数出列
    while (n > 0)
    {
        // 报数m-1次
        for (int i = 1; i < m; i++)
        {
            prev = current;
            current = current->next;
        }
        // 输出出列者信息
        printf("%d(密码:%d)", current->data, current->password);
        if (n > 1) printf(" -> ");
        
        // 更新m值为出列者的密码
        m = current->password;
        // 删除当前节点
        if (current == head && n > 1)
        {
            head = current->next;
        }
        prev->next = current->next;
        AdvancedNode* temp = current;
        current = current->next;
        free(temp);
        
        n--;
    }
    printf("\n");
}
//运行界面实现
void display()
{
    printf("\n");
    printf("=========================================\n");
    printf("          约瑟夫环问题仿真系统           \n");
    printf("=========================================\n");
    printf("1. 经典约瑟夫环问题（链表实现）\n");
    printf("2. 顺序结构实现版本\n");
    printf("3. 动态m值版本（密码作为新m值）\n");
    printf("4. 退出系统\n");
    printf("=========================================\n");
    printf("请选择功能（1-4）：");
}

int main() {
    int choice;
    int n, k, m;
    while (1) {
        display();
        scanf("%d", &choice);
        if (choice == 4)
        {
            printf("退出系统。再见！\n");
            break;
        }
        switch (choice)
        {
            case 1:
                printf("请输入总人数n，起始位置k，报数上限m（空格分隔）：");
                scanf("%d %d %d", &n, &k, &m);
                jp(n, k, m);
                break;
            case 2:
                printf("请输入总人数n，起始位置k，报数上限m（空格分隔）：");
                scanf("%d %d %d", &n, &k, &m);
                sxjp(n, k, m);
                break;
            case 3: {
                printf("请输入总人数n，起始位置k，初始报数上限m（空格分隔）：");
                scanf("%d %d %d", &n, &k, &m);
                int* passwords = (int*)malloc(n * sizeof(int));
                printf("请输入每个人的密码（空格分隔）：");
                for (int i = 0; i < n; i++) {
                    scanf("%d", &passwords[i]);
                }
                nmjp(n, k, m, passwords);
                free(passwords);
                break;
            }
            default:
                printf("无效选择，请重新输入。\n");
        }
    }
    return 0;
}