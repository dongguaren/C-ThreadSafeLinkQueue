#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "ThreadSafeLinkQueue.h"
#include "ErrorHandle.h"
#include "GlobalPara.h"
#include "LinkQueue.h"
#include "MyRandNumber.h"
#include "MQ_Msg.h"


int main()
{
//    TSQ_test();
//    MRN_test();


    MQ_Msg_test();


    return 0;


} 