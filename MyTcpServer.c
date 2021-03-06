//
// Created by Dongguaren on 6/23/18.
//
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include "MyTcpServer.h"
#include "ErrorHandle.h"
#include "MyLog.h"


MyTcpServer* MyTcpServer_createServer(int listen_port){


    MyTcpServer* tcpStruct = (MyTcpServer*)malloc(sizeof(MyTcpServer));

    // 创建socket描述符
    if ((tcpStruct -> sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        EH_logErrMsg("create socket error.");
        free(tcpStruct);
        return NULL;
    }

//    tcpStruct->server_addr = (SockAddrIn *)malloc(sizeof(SockAddrIn));
//    memset(&(tcpStruct->server_addr),0,sizeof(SockAddrIn));

    Log_Info("listen_port:%d\n",listen_port);
    // 填充sockaddr_in结构
    bzero(&(tcpStruct->server_addr), sizeof(struct sockaddr_in));
    tcpStruct->server_addr.sin_family = AF_INET;
    tcpStruct->server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    tcpStruct->server_addr.sin_port = htons(listen_port);


    // 绑定sock_fd描述符
    if (bind(tcpStruct->sock_fd, (struct sockaddr *)(&(tcpStruct->server_addr)), sizeof(struct sockaddr)) == -1) {
        EH_logErrMsg("bind socket error.");
        free(tcpStruct);
//        free(tcpStruct->server_addr);
        return NULL;
    }

    // 监听sock_fd描述符
    if(listen(tcpStruct->sock_fd, 20) == -1) {
        EH_logErrMsg("listen socket error.");
        free(tcpStruct);
//        free(tcpStruct->server_addr);
        return NULL;
    }


    return tcpStruct;
}

void MyTcpServer_closeSocket(MyTcpServer *tcpStruct){


    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tcpStruct) ){
        return;
    }

    close(tcpStruct -> sock_fd);
}

int MyTcpServer_acceptAndCreateConnection(MyTcpServer *tcpStruct){

    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tcpStruct) ){
        return -1;
    }

//    Log_Info("789\n");

    int conn_fd = accept(tcpStruct -> sock_fd, (struct sockaddr *)NULL, NULL);
    if( conn_fd == -1 ){
        EH_logErrMsg("accept return value is -1.");
        return -1;
    }

    return conn_fd;
}

int MyTcpServer_closeConnection(MyTcpServer *tcpStruct, int conn_fileId){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tcpStruct) ){
        return -1;
    }

    return close(conn_fileId);
}

ssize_t MyTcpServer_recvData(MyTcpServer *tcpStruct, int fd, void *dataBuff, size_t buffLen){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tcpStruct) ){
        return -1;
    }

    return recv(fd, dataBuff, buffLen, 0);
}

ssize_t MyTcpServer_sendData(MyTcpServer *tcpStruct, int fd, void *dataBuff, size_t buffLen){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tcpStruct) ){
        return -1;
    }

    return send(fd, dataBuff, buffLen, 0);
}


void MyTcpServer_destroy( MyTcpServer *tcpStruct ){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tcpStruct) ){
        return;
    }

    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,tcpStruct->server_addr) ){
        return;
    }

//    free(tcpStruct->server_addr);
    free(tcpStruct);
}

