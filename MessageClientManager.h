//
// Created by Dongguaren on 7/10/18.
//

#ifndef MYTEST_MESSAGECLIENTMANAGER_H
#define MYTEST_MESSAGECLIENTMANAGER_H

//interface GetMessListener{
//    void getMessage( String inMess );
//}
//
//interface ConnectManager{
//    void connectSucc();
//    void disconnected();
//}



//void setConnectManagerListener( ConnectManager connectManagerListener );
//
//void sendMess( String outMess );
//void setGetMessListener(GetMessListener getMessListener);
//
//void test_sendMessToMe( String mess );
//
//
//void connectWeChat();
//
//void disConnectWeChat();

#include "MessageTcpClient.h"

typedef struct {
    MsgTc* msgClient;
    int state;
    void (*connectMyTcpServerCallBack)(int state);
    void (*connectOtherTcpServerSucc)();
}MCM;



MCM* MCM_new(const char *address, int connect_port,
             void (*connectMyTcpServerCallBack)(int state),
             void (*connectOtherTcpServerSucc)() );

void MCM_connectWeChat(MCM* mcm);

void MCM_sendMess( MCM* mcm,char* mess,int messLen,int rate );

Msg* MCM_recvMess( MCM* mcm );

void MCM_disConnectWeChat(MCM* mcm);




#endif //MYTEST_MESSAGECLIENTMANAGER_H
