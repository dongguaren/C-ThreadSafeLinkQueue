//
// Created by Dongguaren on 7/7/18.
//
#include <pthread.h>
#include "CodeTest.h"
#include "../MyTcpServer.h"
#include "../MyTcpClient.h"
#include "../MQ_Msg.h"
#include "../MyLog.h"


void *CodeTest_ServerThread(void *ptr){
    MyTcpServer *tcpServer = (MyTcpServer*)ptr;

    int conId = MyTcpServer_acceptAndCreateConnection(tcpServer);
    Msg *msg=NULL;

    // ------- Server recv data -------//
    msg = MQ_Msg_newNULL();
    MyTcpServer_recvData(tcpServer,conId,msg, sizeof(Msg));
    Log_Info("Server recv data:\n");
    MQ_Msg_print(msg);
    MQ_Msg_destroy(msg);
    Log_Info("\n\n");
    // ------- /Server recv data -------//


    // ------- Server send data -------//
    msg = MQ_Msg_new(1,1,0,0,0,0);
    Log_Info("Server send data:\n");
    MQ_Msg_print(msg);
    MyTcpServer_sendData(tcpServer,conId,msg,sizeof(Msg));
    MQ_Msg_destroy(msg);
    Log_Info("\n\n");
    // ------- /Server send data -------//



    MyTcpServer_closeConnection(tcpServer,conId);
    MyTcpServer_closeSocket(tcpServer);
}


void CodeTest_sendMsgByTcpClient(){
    int port = 10009;

    //init
    MyTcpServer *tcpServer = MyTcpServer_createServer(port);
    MyTcpClient *tcpClient = MyTcpServer_createClient("127.0.0.1",port);
    //server thread
    pthread_t tid_tcpServer;
    pthread_create(&tid_tcpServer, NULL, CodeTest_ServerThread, tcpServer);


//    sleep(1);
    MyTcpClient_connectServer(tcpClient);
    Msg *msg=NULL;

    // ------- Client send data -------//
    msg = MQ_Msg_new(1,1,0,0,0,0);
    Log_Info("Client send mess:\n");
    MQ_Msg_print(msg);
    MyTcpClient_sendData(tcpClient,msg, sizeof(Msg));
    MQ_Msg_destroy(msg);
    Log_Info("\n\n");
    // ------- /Client send data -------//


    // ------- Client recv data -------//
    msg = MQ_Msg_newNULL();
    MyTcpClient_recvData( tcpClient,msg, sizeof(Msg));
    Log_Info("Client recv mess:\n");
    MQ_Msg_print(msg);
    MQ_Msg_destroy(msg);
    Log_Info("\n\n");
    // ------- /Client recv data -------//




    MyTcpClient_closeClient(tcpClient);



    pthread_join(tid_tcpServer, NULL);
}
