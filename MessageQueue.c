//
// Created by Dongguaren on 2018/6/22.
//

#include <stdlib.h>
#include <pthread.h>
#include <bits/signum.h>
#include <signal.h>
#include <string.h>
#include "MessageQueue.h"
#include "MyLog.h"
#include "ErrorHandle.h"
#include "MessageTcpClient.h"
#include "MQ_Msg_What.h"

void MQM_destoryAtThread(MQM* mqm);
/**
 * tcp server 线程
 * @param ptr
 * @return
 */
void * MQM_TcpServerPthread(void *ptr){



    MQM* mqm = (MQM*)ptr;
    mqm->conId = MsgTS_acceptAndCreateConnection( mqm->tcpServer );

    static int recvMessTime = 0;

    Msg* recvMsg = NULL;
    for(;;){

//        sleep(1);
        recvMsg = MsgTS_recvMsg(mqm->tcpServer,mqm->conId);
        if( recvMsg == NULL ){

            TSQ_add( mqm -> threadSafeLinkQueue,MQ_Msg_newEndAll() );

            MsgTS_closeConnection( mqm->tcpServer,mqm->conId );
            MsgTS_destroy(mqm->tcpServer);
            break;

        } else if( recvMsg->flag == MsgWhat()->QuitMessageQueue ){

            Log_Info("TcpServerPthread recv quit message\n");
            MsgTS_closeConnection( mqm->tcpServer,mqm->conId );
            MsgTS_destroy(mqm->tcpServer);
            TSQ_add( mqm -> threadSafeLinkQueue,recvMsg );
            break;
        }
        // 安卓里面用不了
//        pthread_testcancel();

        Log_Info("-------------- TcpServer recv mess --------------\n");
        Log_Info("The %d Message:\n",++recvMessTime);
        MQ_Msg_print(recvMsg);
        TSQ_add( mqm -> threadSafeLinkQueue,recvMsg );
        Log_Info("The %d Message has added threadSafeLinkQueue\n",recvMessTime);
        Log_Info("-------------- /TcpServer recv mess --------------\n");

    }






//    pthread_cleanup_pop(0);
}



MQM* MQM_new(int port){
    if( port <= 1000){
        EH_logErrMsg("Para illegal.listen port must bigger than 1000!");
        return NULL;
    }

    MQM* res = (MQM*)malloc(sizeof(MQM));
    res -> defaultListenPort = port;
    res -> tcpServer = MsgTS_createServer(res->defaultListenPort);
    res -> threadSafeLinkQueue = TSQ_new();
    res -> conId = -1;
    pthread_create(&(res->tcpPthread), NULL, MQM_TcpServerPthread, res);
    return res;
}




/**
 * 被 雨航调用
 *
 * 向 myMQM 对应的消息队列询问有无消息
 * @param manager MessageQueueManager 指针
 * @return NULL -> 无消息  有消息则返回对应的 msg 指针
 */
Msg* MQM_getMsg( MQM* manager ){

    if( TSQ_getLen( manager -> threadSafeLinkQueue ) ){
        return TSQ_getTopAndPop(manager -> threadSafeLinkQueue);
    } else{
        return NULL;
    }
}


/**
 * 向 MessageQueueManager 发送消息
 * @param mqm
 * @param msgText   消息文本指针  最后不含 '/0'
 * @param msgLen    消息长度
 */
void MQM_sendMessge( MQM* mqm,char* msgText,int msgLen ){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",2,mqm,msgText) ){
        return;
    }

    if( msgLen <= 0){
        EH_logErrMsg("Para illegal.msgLen must be positive number!");
        return;
    }

    if( mqm->conId == -1){
        EH_logErrMsg("MessageQueueManager 's conId is -1.Tcp connection is not create!");
        return;
    }

    Msg* sendMsg = MQ_Msg_new( 0,0,0,NULL,msgLen,msgText );
    MsgTS_sendMsg( mqm->tcpServer,mqm->conId,sendMsg );
}


void MQM_destoryAtThread(MQM* mqm){
    Log_Info("thread destroy function is called!\n");
    MsgTS_closeConnection( mqm->tcpServer,mqm->conId );
    MsgTS_destroy(mqm->tcpServer);
    TSQ_dstory(mqm->threadSafeLinkQueue);
    free(mqm);
}


void MQM_destory( MQM* mqm ){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,mqm) ){
        return;
    }

//    pthread_cancel(mqm->tcpPthread);

    // free 消息队列
    TSQ_dstory(mqm->threadSafeLinkQueue);
    free(mqm);
    // free itself

}




void * test_MQM_TcpServerPthread(void *ptr){
    MQM* server = (MQM*)ptr;
    Msg* recvMsg = NULL;
    for(;;){
//        sleep(1);
        recvMsg = MQM_getMsg(server);
        if( recvMsg ){
            Log_Info("------------ Server recv mess ------------:\n");
            MQ_Msg_print(recvMsg);
            Log_Info("------------ /Server recv mess ------------:\n");

            if(recvMsg->flag == MsgWhat()->QuitMessageQueue){
                MQM_destory(server);
                Log_Info("MQM_destory\n");
                break;
            }
        }
    }
}


void MQM_test(){
    int port = 18904;
    MQM* server = MQM_new(port);

    pthread_t tcpPthread;
    pthread_create(&tcpPthread, NULL, test_MQM_TcpServerPthread, server);

    sleep(1);

    MsgTc* client = MsgTc_createClient("127.0.0.1",port);
    MsgTc_connectServer(client);
    Msg *msg=NULL;


    msg = MQ_Msg_new(1,1,0,0,0,0);
    Log_Info("------------ Client send mess ------------\n");
    MQ_Msg_print(msg);
    Log_Info("------------ /Client send mess ------------\n");
    MsgTC_sendMsg(client,msg);
    MQ_Msg_destroy(msg);
    Log_Info("\n\n");



    msg = MQ_Msg_new(1,MsgWhat()->QuitMessageQueue,0,0,0,0);
    Log_Info("------------ Client send mess ------------\n");
    MQ_Msg_print(msg);
    Log_Info("------------ /Client send mess ------------\n");
    MsgTC_sendMsg(client,msg);
    MQ_Msg_destroy(msg);
    Log_Info("\n\n");


//    MsgTc_closeClient( client );

    pthread_join(tcpPthread, NULL);



    MsgTc_closeClient( client );



}









