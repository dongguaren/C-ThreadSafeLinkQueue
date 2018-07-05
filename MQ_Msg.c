//
// Created by Dongguaren on 7/4/18.
//
#include <stdlib.h>
#include "MQ_Msg.h"

struct MessageQueueMessage{
    int insert_rate;
    int flag;

    int sizeofExtraData;
    void *extraData;

    int sizeofMessage;
    unsigned char* message;
};

MQ_Msg* MQ_Msg_new(int insert_rate,int flag,int sizeofExtraData,void *extraData,int sizeofMessage,unsigned char* message){
    MQ_Msg* res = malloc(sizeof(MQ_Msg));
    res->insert_rate = insert_rate;
    res->flag = flag;

    res->sizeofExtraData = sizeofExtraData;
    res->extraData = extraData;

    res->sizeofMessage = sizeofMessage;
    res->message = message;
    return res;
}

void MQ_Msg_destroy(MQ_Msg* t){
    free(t);
}

