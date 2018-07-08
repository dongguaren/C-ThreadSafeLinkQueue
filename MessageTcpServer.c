//
// Created by Dongguaren on 7/7/18.
//
#include <stdlib.h>
#include <syslog.h>
#include "MessageTcpServer.h"
#include "MyLog.h"
#include "ErrorHandle.h"

MsgTS* MsgTS_createServer(int listen_port){

    MsgTS* res = (MsgTS*)malloc(sizeof(MsgTS));
    res -> tcpServer = MyTcpServer_createServer( listen_port );
    return res;
}

int MsgTS_acceptAndCreateConnection(MsgTS *tcpStruct){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tcpStruct) ){
        return 0;
    }
    return MyTcpServer_acceptAndCreateConnection(tcpStruct->tcpServer);

}


void MsgTS_sendMsg( MsgTS *tcpStruct,int con_id,Msg *msg ){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",2,tcpStruct,msg) ){
        return;
    }

    MyTcpServer_sendData( tcpStruct->tcpServer,con_id,msg, sizeof(Msg));

    if( msg->msg_length != 0 ){
        MyTcpServer_sendData( tcpStruct->tcpServer,con_id,msg->message, (size_t)msg->msg_length );
    }

    if( msg->extra_length != 0 ){
        MyTcpServer_sendData( tcpStruct->tcpServer,con_id,msg->extraData, (size_t)msg->extra_length );
    }
}


Msg* MsgTS_recvMsg( MsgTS *tcpStruct,int con_id ){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tcpStruct) ){
        return 0;
    }

    Msg* res = MQ_Msg_newNULL();

    MyTcpServer_recvData( tcpStruct->tcpServer,con_id,res, sizeof(Msg));

    if( res->msg_length != 0 ){
        Log_Info("%d\n",res->msg_length);
        res->message = malloc((size_t)res->msg_length);
        MyTcpServer_recvData( tcpStruct->tcpServer,con_id,res->message,(size_t)res->msg_length );
    }

    if( res->extra_length != 0 ){
        res->extraData = malloc((size_t)res->extra_length);
        MyTcpServer_recvData( tcpStruct->tcpServer,con_id,res->extraData,(size_t)res->extra_length );
    }

    return res;
}



int MsgTS_closeConnection(MsgTS *tcpStruct, int conn_fileId){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tcpStruct) ){
        return 0;
    }
    return MyTcpServer_closeConnection( tcpStruct->tcpServer,conn_fileId );
}


void MsgTS_destroy( MsgTS *tcpStruct ){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tcpStruct) ){
        return;
    }
    MyTcpServer_destroy(tcpStruct->tcpServer);
    free(tcpStruct);
}





