//
// Created by Dongguaren on 7/4/18.
//

#ifndef MYTEST_MQ_MSG_H
#define MYTEST_MQ_MSG_H

typedef struct MessageQueueMessage MQ_Msg;

/**
 * 本函数 申请空间，逐项赋值
 * @param insert_rate
 * @param flag
 * @param sizeofExtraData
 * @param extraData
 * @param sizeofMessage
 * @param message
 * @return 指针
 */
MQ_Msg* MQ_Msg_new(int insert_rate,int flag,int sizeofExtraData,void *extraData,int sizeofMessage,unsigned char* message);

/**
 * 目前本函数只有 free(t)
 *
 * @param t
 */
void MQ_Msg_destroy(MQ_Msg* t);

#endif //MYTEST_MQ_MSG_H
