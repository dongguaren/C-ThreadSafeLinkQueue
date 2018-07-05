//
// Created by Dongguaren on 7/4/18.
//
#include <stdlib.h>
#include "MQ_Msg.h"

struct MessageQueueMessage{
    int insert_rate;
    int flag;

    int extra_length;
    void *extraData;

    int msg_length;
    unsigned char* message;
};



//typedef struct {
//    int insert_rate;        //嵌入率
//    int flag;               //标志位
//    int msg_length;             //数据信息长度
//    int extra_length;
//    void *extraData;        //指针
//    unsigned char* message; //待传输秘密信息
//}Msg;


Msg* MQ_Msg_new(int insert_rate,int flag,int extra_length,void *extraData,int msg_length,unsigned char* message){
    Msg* res = malloc(sizeof(Msg));
    res->insert_rate = insert_rate;
    res->flag = flag;

    res-> extra_length = extra_length;
    res->extraData = extraData;

    res-> msg_length = msg_length;
    res->message = message;
    return res;
}

void MQ_Msg_destroy(Msg* t){
    free(t);
}

