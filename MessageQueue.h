//
// Created by Dongguaren on 2018/6/22.
//

#ifndef FIRST_TEST_MESSAGEQUEUE_H
#define FIRST_TEST_MESSAGEQUEUE_H

#include "MQ_Msg.h"

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
 * @param manager MessageQueueManager 指针
 * @return NULL -> 无消息  有消息则返回对应的 msg 指针
 */
Msg* MQM_getMsg( MQM* manager );


/**
 * 向 MessageQueueManager 发送消息
 * @param manager
 * @param msgText   消息文本指针  最后不含 '/0'
 * @param msgLen    消息长度
 */
void MQM_sendMessge( MQM* manager,char* msgText,int msgLen );



/**
 * 销毁 MQM
 * @param myMQM 指针
 */
void MQM_destory( MQM* myMQM );


#endif //FIRST_TEST_MESSAGEQUEUE_H
