//
// Created by 61603 on 2018/6/22.
//

#ifndef FIRST_TEST_MESSAGEQUEUE_H
#define FIRST_TEST_MESSAGEQUEUE_H
typedef struct {
    int insert_rate;
    int flag;
    int length;
    void *extraData;
    unsigned char* message;
}Msg;


//typedef struct {
//
//}MessageQueueManager;

typedef struct messageQueueManager MessageQueueManager;

typedef MessageQueueManager MQM;
//------------------------------------------ function -----------------------------------------------//

/**
 * 新建一个 消息队列 manager
 * @return  manager 指针
 */
MQM* MQM_new();

/**
 * 向 myMQM 对应的消息队列询问有无消息
 * @param myMQM myMQM 指针
 * @return NULL -> 无消息  有消息则返回对应的 msg 指针
 */
Msg* MQM_getMsg( MQM* myMQM );

/**
 * 释放消息
 * @param msg 消息指针
 */
void MQM_freeMes( Msg* msg );

/**
 * 销毁 MQM
 * @param myMQM 指针
 */
void MQM_destory( MQM* myMQM );


#endif //FIRST_TEST_MESSAGEQUEUE_H
