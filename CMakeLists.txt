cmake_minimum_required(VERSION 3.10)
project(MyTest C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(MyTest main.c
        MessageQueue.h
        MessageQueue.c
        LinkQueue.h
        LinkQueue.c
        ThreadSafeLinkQueue.h
        ThreadSafeLinkQueue.c
        ErrorHandle.h
        ErrorHandle.c
        GlobalPara.h
        MyTcpServer.h
        MyTcpServer.c
        MyTcpClient.h
        MyTcpClient.c
        MyLog.h
        MQ_Msg.c
        MQ_Msg.h
        MyRandNumber.h
        MyRandNumber.c
        CodeTest/CodeTest.h
        CodeTest/CodeTest.c
        MessageTcpServer.h
        MessageTcpServer.c
        MessageTcpClient.h
        MessageTcpClient.c
        CodeTest/Test_MessageServerAndClient.h
        CodeTest/Test_MessageServerAndClient.c
        MQ_Msg_What.h MQ_Msg_What.c MessageClientManager.c MessageClientManager.h)