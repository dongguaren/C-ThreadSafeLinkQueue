//
// Created by Dongguaren on 6/23/18.
//

#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include "MyTcpClient.h"
#include "MyLog.h"
#include "ErrorHandle.h"


MyTcpClient* MyTcpServer_createClient(const char *address, int connect_port){

    MyTcpClient* tcpStruct = (MyTcpClient*)malloc(sizeof(MyTcpClient));

//    // 创建socket描述符
//    if ((tcpStruct -> sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
//        __MyTcpStruct_handleErrorInCreateClient(tcpStruct, "创建socket描述符出错.");
//        return NULL;
//    }
//
//    // 填充sockaddr_in结构
//    bzero(&(tcpStruct ->server_addr),sizeof(tcpStruct ->server_addr));
//    tcpStruct ->server_addr.sin_family = AF_INET;
//    tcpStruct ->server_addr.sin_port = htons(connect_port);
//    //set ip address
//    if( inet_pton(AF_INET, address, &(tcpStruct ->server_addr.sin_addr)) < 0){
//        __MyTcpStruct_handleErrorInCreateClient(tcpStruct, "address 不合法。");
//        return NULL;
//    }

    tcpStruct -> sock_fd = socket(AF_INET, SOCK_STREAM, 0);    //ipv4,TCP数据连接
    Log_Info("step1");

    //remote server address
    bzero(&tcpStruct ->server_addr,sizeof(tcpStruct ->server_addr));
    tcpStruct ->server_addr.sin_family = AF_INET;
    tcpStruct ->server_addr.sin_port = htons(connect_port);

    Log_Info("step2");

    if( inet_pton(AF_INET, address, &tcpStruct ->server_addr.sin_addr) < 0){    //set ip address
        EH_logErrMsg("set ip address error.");
        return NULL;
    }

    return tcpStruct;

}


void MyTcpClient_connectServer( MyTcpClient* tcpClient ){

    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tcpClient) ){
        return;
    }

    int conn_fd = connect(tcpClient->sock_fd,(struct sockaddr*)(&(tcpClient->server_addr)), sizeof(tcpClient->server_addr)); //连接到服务器
    if( conn_fd == -1 ){
        EH_logErrMsg("accept return value is -1.");
        return ;
    }
}

ssize_t MyTcpClient_sendData(MyTcpClient *tcpClient, const void *dataBuff, size_t buffLen){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tcpClient) ){
        return -1;
    }

    return send(tcpClient->sock_fd, dataBuff, buffLen, 0);
}

ssize_t MyTcpClient_recvData(MyTcpClient *tcpClient, void *dataBuff, size_t buffLen){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tcpClient) ){
        return -1;
    }

    return recv(tcpClient->sock_fd, dataBuff, buffLen, 0);
}

void MyTcpClient_closeClient(MyTcpClient *tcpStruct){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tcpStruct) ){
        return;
    }

    close(tcpStruct -> sock_fd);
    free(tcpStruct);
}

