#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "ThreadSafeLinkQueue.h"
#include "ErrorHandle.h"
#include "GlobalPara.h"
#include "LinkQueue.h"




int main()
{
    TSQ_test();
    return 0;
} 