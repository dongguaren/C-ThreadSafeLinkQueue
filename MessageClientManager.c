//
// Created by Dongguaren on 7/10/18.
//

#include "MessageClientManager.h"
#include "MQ_Msg_What.h"


MCM* MCM_new(const char *address, int connect_port,
             void (*connectMyTcpServerCallBack)(int state),
             void (*connectOtherTcpServerSucc)() ){

    MCM* res = (MCM*)malloc(sizeof(MCM));
    res -> state = 0;
    res -> msgClient = MsgTc_createClient( address,connect_port );
    res -> connectMyTcpServerCallBack = connectMyTcpServerCallBack;
    res -> connectOtherTcpServerSucc = connectOtherTcpServerSucc;
    return res;
}


void MCM_connectWeChat(MCM* mcm){
    MsgTc_connectServer( mcm -> msgClient );
    mcm -> state = 1;

    Msg* helloMsg = MsgTC_recvMsg(mcm->msgClient);
    if( helloMsg->flag == MsgWhat()->FirstHello ){
        mcm -> state = 2;
    }

    if( mcm -> state == 1 ){
        // 连接自己的 tcp server 失败
        (*(mcm->connectMyTcpServerCallBack))(-1);
        return;
    } else{
        // 连接自己的 tcp server 成功
        (*(mcm->connectMyTcpServerCallBack))(0);
    }

}


void MCM_sendMess( MCM* mcm,char* mess,int messLen,int rate ){
    // todo  支持大于50字节的数据传送
    MsgTC_sendMsg( mcm -> msgClient,MQ_Msg_new(rate,0,0,0,messLen,mess) );

}


Msg* MCM_recvMess( MCM* mcm ){
    Msg* recvMsg = MsgTC_recvMsg(mcm->msgClient);
//    char* strMsg = recvMsg->message;
    return recvMsg;
}


void MCM_disConnectWeChat(MCM* mcm){

}

