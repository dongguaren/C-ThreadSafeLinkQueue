//
// Created by Dongguaren on 7/7/18.
//

#ifndef MYTEST_MESSAGETCPSERVER_H
#define MYTEST_MESSAGETCPSERVER_H

#include "MyTcpServer.h"
#include "MQ_Msg.h"

typedef struct MessageTcpServer{
    MyTcpServer *tcpServer;
}MsgTS;

MsgTS* MsgTS_createServer(int listen_port);

int MsgTS_acceptAndCreateConnection(MsgTS *tcpStruct);

void MsgTS_sendMsg( MsgTS *tcpStruct,int con_id,Msg *msg );

Msg* MsgTS_recvMsg( MsgTS *tcpStruct,int con_id );

int MsgTS_closeConnection(MsgTS *tcpStruct, int conn_fileId);

void MsgTS_destroy( MsgTS *tcpStruct );


#endif //MYTEST_MESSAGETCPSERVER_H
