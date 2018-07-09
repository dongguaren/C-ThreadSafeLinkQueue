//
// Created by Dongguaren on 7/8/18.
//

#include <pthread.h>
#include "Test_MessageServerAndClient.h"
#include "../MessageTcpServer.h"
#include "../MessageTcpClient.h"
#include "../MyLog.h"


void *TestMassge_ServerThread(void *ptr){
    MsgTS *server = (MsgTS*)ptr;

    int conId = MsgTS_acceptAndCreateConnection(server);

    Log_Info("Server 1\n");
    Msg *msg=NULL;



    //---------- Server recv mess ----------//
    msg = MsgTS_recvMsg(server,conId);
    Log_Info("Server 2\n");
    Log_Info("Server recv mess:\n");
    MQ_Msg_print(msg);
    MQ_Msg_destroy(msg);
    Log_Info("\n\n");
    //---------- /Server recv mess ----------//



    //---------- Server send mess ----------//
    msg = MQ_Msg_new(2,2,0,0,0,0);
    Log_Info("Server send mess:\n");

    MQ_Msg_print(msg);
    MsgTS_sendMsg(server,conId,msg);

    MQ_Msg_destroy(msg);
    Log_Info("\n\n");
    //---------- /Server send mess ----------//


    Log_Info("Server 3\n");

    MsgTS_closeConnection(server,conId);
    MsgTS_destroy(server);
}


void TestMassge_test(){
    int port = 10009;

    //init
    MsgTS* server = MsgTS_createServer(port);
    MsgTc* client = MsgTc_createClient("127.0.0.1",port);

    //start server thread
    pthread_t tid_tcpServer;
    pthread_create(&tid_tcpServer, NULL, TestMassge_ServerThread, server);


    MsgTc_connectServer(client);
    Msg *msg=NULL;



    //---------- client send mess ----------//
    msg = MQ_Msg_new(1,1,0,0,0,0);
    Log_Info("Client send mess:\n");
    MQ_Msg_print(msg);

//    MsgTC_sendMsg(client,msg);
    MQ_Msg_destroy(msg);
    Log_Info("\n\n");
    //---------- /client send mess ----------//


    //---------- client recv mess ----------//

    msg = MsgTC_recvMsg(client);
    Log_Info("Client recv mess:\n");
    MQ_Msg_print(msg);
    MQ_Msg_destroy(msg);
    Log_Info("\n\n");
    //---------- /client recv mess ----------//



    MsgTc_closeClient( client );
    pthread_join(tid_tcpServer, NULL);

}
