cmake_minimum_required(VERSION 3.10)
project(MyTest C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(MyTest main.c
        MessageQueue.h MessageQueue.c
        MyFunction.h MyFunction.c
        LinkQueue.h LinkQueue.c
        ThreadSafeLinkQueue.h ThreadSafeLinkQueue.c
        ErrorHandle.h ErrorHandle.c
        GlobalPara.h
        MyTcpServer.h MyTcpServer.c
        MyTcpClient.h MyTcpClient.c MyLog.h)