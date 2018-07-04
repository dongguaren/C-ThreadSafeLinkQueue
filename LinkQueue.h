//
// Created by 61603 on 2018/6/22.
//

#ifndef FIRST_TEST_LINKQUEUE_H
#define FIRST_TEST_LINKQUEUE_H


typedef struct linkQueue LinkQueue;

typedef LinkQueue LQ;

LinkQueue* LQ_new();

void LQ_push( LinkQueue* lq,void* data );

void* LQ_getTop( LinkQueue* lq );

void LQ_pop( LinkQueue* lq );

int LQ_getLen( LinkQueue* lq );

void LQ_dstory( LinkQueue* lq );


//void test(){
//    LinkQueue* lq = LQ_new();
//    int i,sz[100];
//    for( i=0;i<100;i++ ){
//        sz[i]=i;
//        LQ_push( lq,&sz[i] );
//    }
//
//    int *t;
//    for( i=0;i<100;i++ ){
//        t = LQ_getTop( lq );
//        printf("number:%d The len:%d\n",*t,LQ_getLen(lq));
//        LQ_pop(lq);
//    }
//    LQ_dstory(lq);
//}

#endif //FIRST_TEST_LINKQUEUE_H
