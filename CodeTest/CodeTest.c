//
// Created by Dongguaren on 7/7/18.
//
#include <pthread.h>
#include "CodeTest.h"
#include "../MyTcpServer.h"
#include "../MyTcpClient.h"
#include "../MQ_Msg.h"
#include "../MyLog.h"


void *ServerThread(void *ptr){
    MyTcpServer *tcpServer = (MyTcpServer*)ptr;

    int conId = MyTcpServer_acceptAndCreateConnection(tcpServer);

    Msg *msg = MQ_Msg_newNULL();

    MyTcpServer_recvData(tcpServer,conId,msg, sizeof(Msg));

    MQ_Msg_print(msg);

    MQ_Msg_destroy(msg);


    MyTcpServer_closeConnection(tcpServer,conId);
    MyTcpServer_closeSocket(tcpServer);
}


void CodeTest_sendMsgByTcpClient(){
    int port = 10009;

    MyTcpServer *tcpServer = MyTcpServer_createServer(port);

    MyTcpClient *tcpClient = MyTcpServer_createClient("127.0.0.1",port);

    pthread_t tid_tcpServer;

    pthread_create(&tid_tcpServer, NULL, ServerThread, tcpServer);


//    sleep(1);
    MyTcpClient_connectServer(tcpClient);


    Msg *msg = MQ_Msg_new(1,1,1,0,1,0);
    MQ_Msg_print(msg);

    MyTcpClient_sendData(tcpClient,msg, sizeof(Msg));
    MyTcpClient_closeClient(tcpClient);

    MQ_Msg_destroy(msg);


    pthread_join(tid_tcpServer, NULL);
}
