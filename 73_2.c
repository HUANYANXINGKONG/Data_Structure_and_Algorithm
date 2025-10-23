//模拟停车场管理（教材73页题目二）
//设停车场只有一个可停放几辆汽车的狭长通道，且只有一个大门可供汽车进出。汽车在停车场内按车辆到达的先后顺序依次排列，若车场内已停满几辆汽车，则后来的汽车只能在门外的便道上等候，一旦停车场内有车开走，则排在便道上的第一辆车即可进入；当停车场内某辆车要离开时，由于停车场是狭长的通道，在它之后开入的车辆必须先退出车场为它让路，待该辆车开出大门后，为它让路的车辆再按原次序进入车场。在这里假设汽车不能从便道上开走。
//按照从终端输入数据序列进行模拟管理。1）栈用顺序结构实现，队列用链式结构实现。2）每一组输入数据包括3个数据项：汽车“到达”或“离去”的信息、汽车牌照号码、汽车到达或离去的时刻。3）对每一组输入数据进行操作后的输出信息：若是车辆到达，则输出车辆在停车场内或便道上的停车位置；若是车辆离去，则输出车辆在停车场内停留的时间和应缴纳的费用。
//选作内容1）汽车有不同种类，则它们的占地面积不同，收费标准也不同。例如1辆客车和2辆小汽车的占地面积相同，1辆十轮卡车占地面积相当于4辆小汽车的占地面积。2）汽车可以直接从便道上开走，此时排在它前面的汽车要先开走让路，然后再依次排到队尾。3）停放在便道上的汽车也收费，收费标准比停放在停车场内的车要少。4）采用友好的图形界面显示。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 1  // 停车场最大容量
#define PRICE 2     // 停车场每小时收费

// 车辆信息结构体
typedef struct {
    char license[20];        // 车牌号
    struct tm arrive_time;   // 到达时间，使用tm结构体
} Car;

// 栈结构（停车场）
typedef struct {
    Car data[MAX_SIZE];
    int top;
} Stack;

// 队列节点（便道）
typedef struct Node {
    Car data;
    struct Node* next;
} Node;

// 队列结构
typedef struct {
    Node* front;
    Node* rear;
} Queue;

// 初始化栈
void initStack(Stack* s) {
    s->top = -1;
}

// 初始化队列
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

// 判断栈是否为空
int isStackEmpty(Stack* s) {
    return s->top == -1;
}

// 判断栈是否已满
int isStackFull(Stack* s) {
    return s->top == MAX_SIZE - 1;
}

// 入栈（车辆进入停车场）
void push(Stack* s, Car car) {
    if (!isStackFull(s)) {
        s->data[++s->top] = car;
    }
}

// 出栈（车辆离开停车场）
Car pop(Stack* s) {
    Car empty = {"", -1};
    if (!isStackEmpty(s)) {
        return s->data[s->top--];
    }
    return empty;
}

// 入队（车辆进入便道）
void enqueue(Queue* q, Car car) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = car;
    newNode->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// 出队（车辆离开便道）
Car dequeue(Queue* q) {
    Car empty = {"", -1};
    if (q->front == NULL) {
        return empty;
    }
    
    Node* temp = q->front;
    Car car = temp->data;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    return car;
}

// 获取停车场当前车辆数
int getParkingCount(Stack* s) {
    return s->top + 1;
}

// 获取便道当前车辆数
int getWaitingCount(Queue* q) {
    int count = 0;
    Node* current = q->front;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// 处理车辆到达
void handleArrival(Stack* parking, Queue* waiting, Car car) {
    if (!isStackFull(parking)) {
        push(parking, car);
        printf("车辆 %s 已进入停车场，位置：%d\n", 
               car.license, getParkingCount(parking));
    } else {
        enqueue(waiting, car);
        printf("停车场已满，车辆 %s 在便道等待，位置：%d\n", 
               car.license, getWaitingCount(waiting));
    }
}

// 处理车辆离开
void handleDeparture(Stack* parking, Queue* waiting, Car car, struct tm current_time) {
    Stack temp;
    initStack(&temp);
    Car current;
    int found = 0;
    
    // 在停车场中查找要离开的车辆
    while (!isStackEmpty(parking)) {
        current = pop(parking);
        if (strcmp(current.license, car.license) == 0) {
            found = 1;
            // 计算时间差（秒）
            double diff_seconds = difftime(mktime(&current_time), mktime(&current.arrive_time));
            double diff_hours = diff_seconds / 3600.0;
            int fee = (int)(diff_hours * PRICE + 0.5);  // 四舍五入
            printf("车辆 %s 已离开，停车时间：%.1f小时，费用：%d元\n", 
                   current.license, diff_hours, fee);
            break;
        }
        push(&temp, current);
    }
    
    // 将临时栈中的车辆重新停回停车场
    while (!isStackEmpty(&temp)) {
        push(parking, pop(&temp));
    }
    
    // 如果找到车辆且便道有车等待，让第一辆车进入停车场
    if (found && waiting->front != NULL) {
        Car waiting_car = dequeue(waiting);
        // 不修改原始到达时间
        push(parking, waiting_car);
        printf("车辆 %s 从便道进入停车场，位置：%d\n", 
               waiting_car.license, getParkingCount(parking));
    }
    
    if (!found) {
        printf("未找到车辆 %s\n", car.license);
    }
}

// 显示停车场状态
void showParkingStatus(Stack* parking) {
    if (isStackEmpty(parking)) {
        printf("停车场内没有车辆。\n");
        return;
    }
    
    printf("当前停车场内所有车辆信息：\n");
    for (int i = 0; i <= parking->top; i++) {
        Car car = parking->data[i];
        char time_str[20];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M", &car.arrive_time);
        printf("位置 %d: 车牌号 %s, 到达时间 %s\n", i + 1, car.license, time_str);
    }
    printf("共停放 %d 辆车。\n", getParkingCount(parking));
}


int main()
{
    Stack parking;
    Queue waiting;
    initStack(&parking);
    initQueue(&waiting);
    
    printf("------停车场管理系统------\n");
    printf("输入格式：动作 车牌号 年 月 日 时 分 例如: A 京A12345 2025 10 22 9 15\n");
    printf("动作说明: A-到达 D-离开 C-查看停车场车辆 Q-退出\n");
    
    char action;
    Car car;
    struct tm current_time = {0};
    while (1) {
        printf("\n请输入操作：");
        scanf(" %c", &action);
        
        if (action == 'Q') {
            break;
        }
        
        if (action == 'C') {
            showParkingStatus(&parking);
            continue;
        }
        
        if (action == 'A' || action == 'D') {
            if (action == 'A') {
                scanf("%s %d %d %d %d %d", car.license, 
                      &car.arrive_time.tm_year, &car.arrive_time.tm_mon, 
                      &car.arrive_time.tm_mday, &car.arrive_time.tm_hour, 
                      &car.arrive_time.tm_min);
                // 调整tm结构体：年份从1900开始，月份从0开始
                car.arrive_time.tm_year -= 1900;
                car.arrive_time.tm_mon -= 1;
                car.arrive_time.tm_sec = 0;
                car.arrive_time.tm_isdst = -1;
                
                handleArrival(&parking, &waiting, car);
            }
            else if (action == 'D') {
            scanf("%s %d %d %d %d %d", car.license, 
                  &current_time.tm_year, &current_time.tm_mon, 
                  &current_time.tm_mday, &current_time.tm_hour, 
                  &current_time.tm_min);
            // 调整tm结构体：年份从1900开始，月份从0开始
            current_time.tm_year -= 1900;
            current_time.tm_mon -= 1;
            current_time.tm_sec = 0;
            current_time.tm_isdst = -1;
            
            handleDeparture(&parking, &waiting, car, current_time);
            }
            else {
            printf("无效的操作！\n");
            }
        }
    }
    return 0;
}