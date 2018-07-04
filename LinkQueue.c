//
// Created by 61603 on 2018/6/22.
//
#include <stdio.h>
#include <stdlib.h>
#include "LinkQueue.h"
#include "ErrorHandle.h"

typedef struct lq_node LQ_Node;

struct lq_node{
    void *data;
    LQ_Node *next;
};

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


struct linkQueue{
    LQ_Node* head;
    LQ_Node* tail;
    int len;
};

LinkQueue* LQ_new(){
    LinkQueue* lq = (LinkQueue*)malloc(sizeof(LinkQueue));
    lq -> len = 0;
    lq -> tail = LQ_Node_new( NULL,NULL );
    lq -> head = LQ_Node_new( NULL,lq -> tail );
    return lq;
}

void LQ_push( LinkQueue* lq,void* data ){

    if( !EH_isArgsLegal("Para illegal.Pointer is null.",2,lq,data) ){
        return;
    }

    LQ_Node* newNode = LQ_Node_new( data,lq->head->next );
    lq->head->next = newNode;
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

    lq -> len--;
}

int LQ_getLen( LinkQueue* lq ){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,lq) ){
        return 0;
    }
    return lq -> len;
}

void LQ_dstory( LinkQueue* lq ){
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



