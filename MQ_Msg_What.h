//
// Created by Dongguaren on 7/9/18.
//

#ifndef MYTEST_MQ_MSG_WHAT_H
#define MYTEST_MQ_MSG_WHAT_H

typedef struct _MQ_Msg_What{
    int QuitMessageQueue;
}MQ_Msg_What;

#define MsgWhat() MQ_Msg_What_getInstance()

MQ_Msg_What* MQ_Msg_What_getInstance();


#endif //MYTEST_MQ_MSG_WHAT_H
