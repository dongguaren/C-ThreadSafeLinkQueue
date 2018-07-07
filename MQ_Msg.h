//
// Created by Dongguaren on 7/4/18.
//

#ifndef MYTEST_MQ_MSG_H
#define MYTEST_MQ_MSG_H

typedef struct MessageQueueMessage {
    int insert_rate;    //嵌入率
    int flag;           //标志位

    int extra_length;   //额外数据长度
    void *extraData;    //额外数据

    int msg_length;     //数据信息长度
    unsigned char* message; //待传输秘密信息
}Msg;


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
Msg* MQ_Msg_new(int insert_rate,int flag,int sizeofExtraData,void *extraData,int sizeofMessage,unsigned char* message);


Msg* MQ_Msg_newNULL();

/**
 * 目前本函数只有 free(t)
 *
 * @param t
 */
void MQ_Msg_destroy(Msg* t);



/**
 * 打印一个 msg
 * @param m
 */
void MQ_Msg_print( Msg* m );



void MQ_Msg_test();

#endif //MYTEST_MQ_MSG_H
