//
// Created by Dongguaren on 2018/6/22.
//

#ifndef FIRST_TEST_LINKQUEUE_H
#define FIRST_TEST_LINKQUEUE_H

typedef struct lq_node LQ_Node;
struct lq_node{
    void *data;
    LQ_Node *next;
};

typedef struct linkQueue{
    LQ_Node* head;
    LQ_Node* tail;
    LQ_Node* secTail;
    int len;
} LinkQueue;

typedef LinkQueue LQ;

/**
 * 新建一个单向链表
 * @return 链表指针
 */
LinkQueue* LQ_new();

/**
 * 向链表尾部添加数据指针
 * @param lq        链表指针
 * @param data      数据指针
 */
void LQ_add(LinkQueue *lq, void *data);

/**
 * 获取链表头部的数据指针
 * @param lq        链表指针
 * @return          数据指针
 */
void* LQ_getTop( LinkQueue* lq );

/**
 * 删除链表头部的一个数据指针
 * @param lq
 */
void LQ_pop( LinkQueue* lq );

/**
 * 获取链表的长度
 * @param lq
 * @return
 */
int LQ_getLen( LinkQueue* lq );

/**
 * 销毁一个链表
 * @param lq
 */
void LQ_destroy(LinkQueue *lq);

/**
 * 打印链表数据
 * 把 void *data 看作 int* data 打印
 * @param lq
 */
void LQ_print( LinkQueue* lq );

/**
 * 测试代码
 */
void LQ_test();

#endif //FIRST_TEST_LINKQUEUE_H
