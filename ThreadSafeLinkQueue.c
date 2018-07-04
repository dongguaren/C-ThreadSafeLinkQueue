//
// Created by Dongguaren on 6/23/18.
//

#include "ThreadSafeLinkQueue.h"
#include "LinkQueue.h"
#include "ErrorHandle.h"
#include "MyLog.h"

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

struct threadSafeLinkQueue{
    LQ* lq;
    pthread_mutex_t mutex;
};

TSQ* TSQ_new(){
    TSQ* res = (TSQ*)malloc(sizeof(TSQ));
    res->lq = LQ_new();
    pthread_mutex_init(&(res->mutex), NULL);
    return res;
}

void TSQ_add(TSQ *tsq, void *data){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",2,tsq,data) ){
        return;
    }

    pthread_mutex_lock(&(tsq->mutex));
    LQ_add(tsq->lq, data);
    pthread_mutex_unlock(&(tsq->mutex));
}

void* TSQ_getTop( TSQ* tsq ){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tsq) ){
        return NULL;
    }

    void* res=NULL;
    pthread_mutex_lock(&(tsq->mutex));
    res = LQ_getTop(tsq->lq);
    pthread_mutex_unlock(&(tsq->mutex));
    return res;
}

void TSQ_pop( TSQ* tsq ){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tsq) ){
        return;
    }

    pthread_mutex_lock(&(tsq->mutex));
    LQ_pop(tsq->lq);
    pthread_mutex_unlock(&(tsq->mutex));
}

void* TSQ_getTopAndPop( TSQ* tsq  ){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tsq) ){
        return NULL;
    }

    void* res=NULL;
    pthread_mutex_lock(&(tsq->mutex));
    res = LQ_getTop(tsq->lq);
    LQ_pop(tsq->lq);
    pthread_mutex_unlock(&(tsq->mutex));
    return res;
}

int TSQ_getLen( TSQ* tsq ){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tsq) ){
        return 0;
    }

    return LQ_getLen(tsq->lq);
}

void TSQ_dstory( TSQ* tsq ){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tsq) ){
        return;
    }

    LQ_destroy(tsq->lq);
    free(tsq);
}


void TSQ_print(TSQ* tsq){
    LQ_print( tsq->lq );
}



/**
 *  生产者线程
 * @param ptr
 * @return
 */
void * TSQ_test_produce(void *ptr)
{
    TSQ* tsq=(TSQ*)ptr;
    for (int i = 0; i < 3; i++)
    {
        int *t = malloc(sizeof(int));
        *t=i;
        TSQ_add(tsq, t);
        Log_Info("produce the %d data:%d\n",i,*t);
        //休眠 1s
        sleep(1);
    }
}

/**
 * 消费者线程
 * @param ptr
 * @return
 */
void * TSQ_test_consume(void *ptr)
{
    TSQ* tsq=(TSQ*)ptr;
    for (int i = 0; i < 3;)
    {
        if( !TSQ_getLen(tsq) ){
            continue;
        }

        i++;
        int* data = TSQ_getTopAndPop(tsq);
        Log_Info("consume the %d data:%d\n",i,*data);
        free(data);
    }
}


void TSQ_test(){
    TSQ* tsq = TSQ_new();
    Log_Info("step 1\n");
    pthread_t tid1, tid2;
    Log_Info("step 2\n");
    pthread_create(&tid1, NULL, TSQ_test_consume, tsq);
    pthread_create(&tid2, NULL, TSQ_test_produce, tsq);
    Log_Info("step 3\n");

    // 等待 TSQ_test_consume TSQ_test_produce 对应线程结束后，结束本线程
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    Log_Info("step 4\n");
}




