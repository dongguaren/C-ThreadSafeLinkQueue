//
// Created by liuhao on 6/23/18.
//

#ifndef MYTEST_THREADSAFELINKQUEUE_H
#define MYTEST_THREADSAFELINKQUEUE_H

typedef struct threadSafeLinkQueue ThreadSafeLinkQueue;

typedef ThreadSafeLinkQueue TSQ;

TSQ* TSQ_new();

void TSQ_push( TSQ* tsq,void *data );

void* TSQ_getTop( TSQ* tsq );

void TSQ_pop( TSQ* tsq );

void* TSQ_getTopAndPop( TSQ* tsq  );

int TSQ_getLen( TSQ* tsq );

void TSQ_dstory( TSQ* tsq );



#endif //MYTEST_THREADSAFELINKQUEUE_H
