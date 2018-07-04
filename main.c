#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "ThreadSafeLinkQueue.h"
#include "ErrorHandle.h"
#include "GlobalPara.h"


int sz[100]={0};
TSQ* tsq = NULL;



void * produce(void *ptr)
{
    for (int i = 0; i < 3; i++)
    {
        sz[i]=i;
        TSQ_push( tsq,&sz[i]);
        printf("produce the %d data:%d\n",i,sz[i]);
        sleep(1);
    }
}

void * consume(void *ptr)
{
//    printf("--------------- consume start ---------------\n");
    for (int i = 0; i < 3;)
    {
        if( !TSQ_getLen(tsq) ){
            continue;
        }

        i++;
        int* data = TSQ_getTopAndPop(tsq);
        printf("consume the %d data:%d\n",i,*data);

    }
//    printf("--------------- consume end ---------------\n");
}


int main()
{

    tsq = TSQ_new();
    printf("1\n");
    pthread_t tid1, tid2;
    printf("2\n");
    pthread_create(&tid1, NULL, consume, NULL);
    pthread_create(&tid2, NULL, produce, NULL);
    printf("3\n");
    void *retVal=NULL;


    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("4\n");



//    int err = pthread_create(&main_tid, NULL, func, NULL);
//    pthread_join(main_tid, NULL);




    return 0;
} 