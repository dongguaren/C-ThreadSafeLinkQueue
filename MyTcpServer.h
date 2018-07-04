//
// Created by Dongguaren on 6/23/18.
//

#ifndef MYTEST_MYTCPSERVER_H
#define MYTEST_MYTCPSERVER_H

#include <unistd.h>

typedef struct{
    int sock_fd;
    struct sockaddr_in server_addr;

}MyTcpServer;

/**
 * 创建一个本地 tcp 服务器
 * @param listen_port    监听的端口号
 * @return               tcp 服务器的 point
 */
MyTcpServer* MyTcpServer_createSocket(int listen_port);

/**
 * 等待一个连接，并建立这个连接，返回 conn_fileId 连接id
 * @param tcpStruct   tcp 服务器的 point  ( 由 MyTcpServer_createSocket 生成)
 * @return            conn_fileId 代表一个连接
 */
int MyTcpServer_acceptAndCreateConnection(MyTcpServer *tcpStruct);

/**
 * 关闭一个连接
 * @param tcpStruct         tcp 服务器的 point  ( 由 MyTcpServer_createSocket 生成)
 * @param conn_fileId       conn_fileId         ( 由 MyTcpServer_acceptAndCreateConnection 生成 )
 * @return                  状态码               0 正常
 */
int MyTcpServer_closeConnection(MyTcpServer *tcpStruct, int conn_fileId);

/**
 * 从一个连接 接收数据
 * @param tcpStruct          tcp 服务器的 point  ( 由 MyTcpServer_createSocket 生成)
 * @param fd                 conn_fileId         ( 由 MyTcpServer_acceptAndCreateConnection 生成 )
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
ssize_t MyTcpServer_recvData(MyTcpServer *tcpStruct, int fd, void *dataBuff, size_t buffLen);

/**
 * 从一个连接 发送数据
 * @param tcpStruct          tcp 服务器的 point  ( 由 MyTcpServer_createSocket 生成)
 * @param fd                 conn_fileId         ( 由 MyTcpServer_acceptAndCreateConnection 生成 )
 * @param dataBuff
 * @param buffLen
 * 上述两个参数的意思是：把 dataBuff 指向的 buffLen 字节的数据发送出去
 * @return 成功发送了多少数据
 */
ssize_t MyTcpServer_sendData(MyTcpServer *tcpStruct, int fd, void *dataBuff, size_t buffLen);

/**
 * 关闭 tcp server
 * @param tcpStruct
 */
void MyTcpServer_closeSocket(MyTcpServer *tcpStruct);


#endif //MYTEST_MYTCPSERVER_H
