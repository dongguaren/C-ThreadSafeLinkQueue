//
// Created by liuhao on 6/23/18.
//

#ifndef MYTEST_TCPCLIENT_H
#define MYTEST_TCPCLIENT_H

#include <unistd.h>

typedef struct{
    int sock_fd;
    struct sockaddr_in server_addr;

}MyTcpClient;

/**
 * 建立一个 tcp client
 * @param address         目标 ip
 * @param connect_port    目标 端口
 * @return                client 指针
 */
MyTcpClient* MyTcpServer_createClient(const char *address, int connect_port);

/**
 * 连接目标 ip
 * @param tcpClient       client 指针 ( get by MyTcpServer_createClient )
 */
void MyTcpClient_connectServer( MyTcpClient* tcpClient );

/**
 * 发送数据
 * @param tcpClient        client 指针 ( get by MyTcpServer_createClient )
 * @param dataBuff
 * @param buffLen
 * 把 dataBuff 指向的长度为 buffLen 数据发送出去
 * @return  发送了多少数据
 */
ssize_t MyTcpClient_sendData(MyTcpClient *tcpClient, const void *dataBuff, size_t buffLen);

/**
 * 接收数据
 * @param tcpClient         client 指针 ( get by MyTcpServer_createClient )
 * @param dataBuff
 * @param buffLen
 * 上述两个参数的意思是：把 buffLen 字节的数据 copy 至 dataBuff 指向的内存
 * @return   实际上 copy 了多少数据
 *
 * 比如 只有 50 字节的数据未复制 传入 buffLen = 1000
 * 此时向 dataBuff 复制50字节的数据，返回 50
 *
 * 可以通过判断 返回数据 的值确定是否复制完毕
 */
ssize_t MyTcpClient_recvData(MyTcpClient *tcpClient, void *dataBuff, size_t buffLen);

/**
 * 关闭 Client
 * @param tcpStruct
 */
void MyTcpClient_closeClient(MyTcpClient *tcpStruct);


#endif //MYTEST_TCPCLIENT_H
