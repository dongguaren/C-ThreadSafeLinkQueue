//
// Created by Dongguaren on 7/8/18.
//

#ifndef MYTEST_MESSAGETCPCLIENT_H
#define MYTEST_MESSAGETCPCLIENT_H

#include <stdlib.h>
#include "MyTcpClient.h"
#include "MQ_Msg.h"

typedef struct MessageTcpClient{
    MyTcpClient *tcpClient;
}MsgTc;

MsgTc* MsgTc_createClient(const char *address, int connect_port);

void MsgTc_connectServer(MsgTc* tcpStruct);

void MsgTC_sendMsg( MsgTc* tcpStruct,Msg *msg );

Msg* MsgTC_recvMsg( MsgTc *tcpStruct );

void MsgTc_closeClient(MsgTc* tcpStruct);


#endif //MYTEST_MESSAGETCPCLIENT_H
