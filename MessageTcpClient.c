//
// Created by Dongguaren on 7/8/18.
//



#include "MessageTcpClient.h"
#include "ErrorHandle.h"

MsgTc* MsgTc_createClient(const char *address, int connect_port){
    MsgTc* res = malloc(sizeof(MsgTc));
    res->tcpClient = MyTcpServer_createClient( address,connect_port );
    return res;
}

void MsgTc_connectServer(MsgTc* tcpStruct){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tcpStruct) ){
        return;
    }
    MyTcpClient_connectServer(tcpStruct->tcpClient);
}

void MsgTC_sendMsg( MsgTc* tcpStruct,Msg *msg ){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",2,tcpStruct,msg) ){
        return;
    }
    MyTcpClient_sendData(tcpStruct->tcpClient,msg, sizeof(Msg));

    if( msg->msg_length != 0 ){
        MyTcpClient_sendData( tcpStruct->tcpClient,msg->message, (size_t)msg->msg_length );
    }

    if( msg->extra_length != 0 ){
        MyTcpClient_sendData( tcpStruct->tcpClient,msg->extraData, (size_t)msg->extra_length );
    }

}

Msg* MsgTC_recvMsg( MsgTc *tcpStruct ){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tcpStruct) ){
        return NULL;
    }

    Msg* res = MQ_Msg_newNULL();

    MyTcpClient_recvData( tcpStruct->tcpClient,res, sizeof(Msg));

    if( res->msg_length != 0 ){
        res->message = malloc((size_t)res->msg_length);
        MyTcpClient_recvData( tcpStruct->tcpClient,res->message,(size_t)res->msg_length );
    }

    if( res->extra_length != 0 ){
        res->extraData = malloc((size_t)res->extra_length);
        MyTcpClient_recvData( tcpStruct->tcpClient,res->extraData,(size_t)res->extra_length );
    }

    return res;

}

void MsgTc_closeClient(MsgTc* tcpStruct){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tcpStruct) ){
        return;
    }

    MyTcpClient_closeClient(tcpStruct->tcpClient);
    free(tcpStruct);
}