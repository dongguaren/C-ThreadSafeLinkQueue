#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../LinkQueue.h"


pthread_mutex_t mutex;

int sz[100]={0};
LinkQueue* lq = NULL;
pthread_t main_tid;


void print_ids(const char *str)
{
    pid_t pid;      //进程id
    pthread_t tid;  //线程id
    pid = getpid();       //获取当前进程id
    tid = pthread_self(); //获取当前线程id
    printf("%s pid: %u tid: %u (0x%x)/n",
           str,
           (unsigned int)pid,
           (unsigned int)tid,
           (unsigned int)tid);
}

void *func(void *arg)
{
    printf("1\n");
    print_ids("new  thread:");
    return ((void *)0);
}

void * produce(void *ptr)
{
    for (int i = 0; i < 3; i++)
    {
//        printf( "produce:%d",i );
        pthread_mutex_lock(&mutex);

        sz[i]=i;
        LQ_push(lq,&sz[i]);
        printf("produce:%d\n",i);

        pthread_mutex_unlock(&mutex);

        sleep(1);

    }
}

void * consume(void *ptr)
{
    printf("--------------- consume start ---------------\n");
    for (int i = 0; i < 3;)
    {
//        printf("*** consume The %d loop start ***\n",i);
        pthread_mutex_lock(&mutex);
//        printf("consume 1 step:\n");
        if (!LQ_getLen(lq))
        {
            pthread_mutex_unlock(&mutex);
//            printf("consume 2 step:\n");
            continue;
        }

        ++i;
        printf("consume:%d\n",*((int*)LQ_getTop(lq)));
        printf("consume 3 step:\n");
        LQ_pop(lq);
        pthread_mutex_unlock(&mutex);
        printf("consume 4 step:\n");
        //sleep(1);
        printf("*** consume The %d loop end ***\n",i);
    }
    printf("--------------- consume end ---------------\n");
}

int main1()
{
    pthread_mutex_init(&mutex, NULL);

    lq = LQ_new();

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