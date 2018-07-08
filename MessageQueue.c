//
// Created by Dongguaren on 2018/6/22.
//

#include <stdlib.h>
#include <pthread.h>
#include "ThreadSafeLinkQueue.h"
#include "MessageQueue.h"
#include "MyTcpServer.h"

struct messageQueueManager{

    int defaultListenPort;
    MyTcpServer *myTcpServer;
    ThreadSafeLinkQueue *threadSafeLinkQueue;
    pthread_t tcpPthread;

};


/**
 * tcp server 线程
 * @param ptr
 * @return
 */
void * MQM_TcpServerPthread(void *ptr){
    MQM* mqm = (MQM*)ptr;
    int con_id = MyTcpServer_acceptAndCreateConnection( mqm -> myTcpServer );
}


MQM* MQM_new(){
    MQM* res = (MQM*)malloc(sizeof(MQM));
    res -> defaultListenPort = 12345;
    res -> myTcpServer = MyTcpServer_createServer(res->defaultListenPort);
    res -> threadSafeLinkQueue = TSQ_new();
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
 * @param manager
 * @param msgText   消息文本指针  最后不含 '/0'
 * @param msgLen    消息长度
 */
void MQM_sendMessge( MQM* manager,char* msgText,int msgLen ){




}

/**
 * test
 * tcp server 线程
 * @param ptr
 * @return
 */
void * MQM_test_TcpServerPthread(void *ptr){
    MyTcpServer *myTcpServer = (MyTcpServer*)ptr;
    int con_id = MyTcpServer_acceptAndCreateConnection( myTcpServer );
}


void MQM_test(){

    pthread_t tcpPthread;
    MyTcpServer *myTcpServer = MyTcpServer_createServer(12345);
    pthread_create(&tcpPthread, NULL, MQM_test_TcpServerPthread, myTcpServer);
}









