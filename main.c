#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "ThreadSafeLinkQueue.h"
#include "ErrorHandle.h"
#include "GlobalPara.h"
#include "LinkQueue.h"
#include "MyRandNumber.h"
#include "MQ_Msg.h"
#include "CodeTest/CodeTest.h"
#include "CodeTest/Test_MessageServerAndClient.h"


int main()
{
//    TSQ_test();
//    MRN_test();
//    MQ_Msg_test();
//    CodeTest_sendMsgByTcpClient();
    TestMassge_test();
    return 0;


} 