//
// Created by Dongguaren on 2018/6/22.
//
#include <stdio.h>
#include <stdlib.h>
#include "LinkQueue.h"
#include "ErrorHandle.h"
#include "MyLog.h"

//typedef struct lq_node LQ_Node;
//
//
//struct lq_node{
//    void *data;
//    LQ_Node *next;
//};

LQ_Node* LQ_Node_new(void* data,LQ_Node* next ){
    LQ_Node* newNode = (LQ_Node*)malloc(sizeof(LQ_Node));
    newNode -> data = data;
    newNode -> next = next;
    return newNode;
}

void LQ_Node_free( LQ_Node* lq_node ){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,lq_node) ){
        return;
    }
    free(lq_node);
}


//struct linkQueue{
//    LQ_Node* head;
//    LQ_Node* tail;
//    LQ_Node* secTail;
//    int len;
//};

LinkQueue* LQ_new(){
    LinkQueue* lq = (LinkQueue*)malloc(sizeof(LinkQueue));
    lq -> len = 0;
    lq -> tail = LQ_Node_new( NULL,NULL );
    lq -> head = LQ_Node_new( NULL,lq -> tail );
    lq -> secTail = lq -> head;
    return lq;
}

void LQ_add(LinkQueue *lq, void *data){

    if( !EH_isArgsLegal("Para illegal.Pointer is null.",2,lq,data) ){
        return;
    }

    LQ_Node* newNode = LQ_Node_new( data,lq->tail);
    lq->secTail->next = newNode;
    lq->secTail = newNode;
    lq -> len++;
}

void* LQ_getTop( LinkQueue* lq ){

    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,lq) ){
        return NULL;
    }

    if( lq -> len > 0 ){
        return lq -> head -> next -> data;
    } else{
        return NULL;
    }
}

void LQ_pop( LinkQueue* lq ){

    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,lq) ){
        return;
    }

    if( lq -> len <= 0 ){
        return;
    }


    LQ_Node* firstHead = lq -> head -> next;
    lq -> head -> next = lq -> head -> next -> next;
    LQ_Node_free( firstHead );

    if( lq -> len == 1 ){
        lq -> secTail = lq -> head;
    }

    lq -> len--;
}

int LQ_getLen( LinkQueue* lq ){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,lq) ){
        return 0;
    }
    return lq -> len;
}

void LQ_destroy(LinkQueue *lq){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,lq) ){
        return;
    }

    while ( lq->len ){
        LQ_pop(lq);
    }

    LQ_Node_free(lq->head);
    LQ_Node_free(lq->tail);

    free( lq );
}


void LQ_print( LinkQueue* lq ){
    Log_Info("------ queue message ------\n");
    Log_Info("lq len:%d\n",lq->len);
    int i=1;
    LQ_Node* t = lq->head->next;

    while( t!=lq->tail ){
        Log_Info("The %d:%d\n",i++,*(int*)(t->data));
        t=t->next;
    }
    Log_Info("------ /queue message ------\n");
}


void LQ_test(){
    LinkQueue* lq = LQ_new();
    int i,sz[100];
    for( i=0;i<100;i++ ){
        sz[i]=i;
        LQ_add( lq,&sz[i] );
    }

    LQ_print(lq);
    LQ_destroy(lq);
}



