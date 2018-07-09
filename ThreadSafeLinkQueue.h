//
// Created by Dongguaren on 6/23/18.
//

#ifndef MYTEST_THREADSAFELINKQUEUE_H
#define MYTEST_THREADSAFELINKQUEUE_H

#include <pthread.h>
#include "LinkQueue.h"

/**
 * 线程安全消息队列
 *  在 LinkQueue 的基础上加入了 互斥量
 */

typedef struct threadSafeLinkQueue{
    LQ* lq;
    pthread_mutex_t mutex;
} ThreadSafeLinkQueue;

typedef ThreadSafeLinkQueue TSQ;

/**
 * 新建一个消息队列
 * @return 指针
 */
TSQ* TSQ_new();

/**
 * 向消息队列尾部加入一个数据指针
 * @param tsq       消息队列指针
 * @param data      数据指针
 */
void TSQ_add(TSQ *tsq, void *data);

/**
 * 获取消息队列头部的一个数据指针
 * @param tsq
 * @return
 */
void* TSQ_getTop( TSQ* tsq );

/**
 * 删除队列头部的一个数据指针
 * @param tsq
 */
void TSQ_pop( TSQ* tsq );

/**
 * 获取消息队列头部的一个数据指针 并 删除队列头部的一个数据指针
 * @param tsq
 * @return
 */
void* TSQ_getTopAndPop( TSQ* tsq  );

/**
 * 获取队列长度
 * @param tsq
 * @return
 */
int TSQ_getLen( TSQ* tsq );

/**
 * 销毁队列
 * @param tsq
 */
void TSQ_dstory( TSQ* tsq );

void TSQ_print(TSQ* tsq);

void TSQ_test();



#endif //MYTEST_THREADSAFELINKQUEUE_H
