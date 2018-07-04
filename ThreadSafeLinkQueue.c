//
// Created by liuhao on 6/23/18.
//

#include "ThreadSafeLinkQueue.h"
#include "LinkQueue.h"
#include "ErrorHandle.h"

#include <pthread.h>

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

void TSQ_push( TSQ* tsq,void *data ){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",2,tsq,data) ){
        return;
    }

    pthread_mutex_lock(&(tsq->mutex));
    LQ_push( tsq->lq,data );
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

    LQ_dstory(tsq->lq);
    free(tsq);
}




