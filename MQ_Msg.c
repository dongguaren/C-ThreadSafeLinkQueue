//
// Created by Dongguaren on 7/4/18.
//
#include <stdlib.h>
#include <string.h>
#include "MQ_Msg.h"
#include "MyLog.h"
#include "ErrorHandle.h"

//struct MessageQueueMessage{
//    int insert_rate;    //嵌入率
//    int flag;           //标志位
//
//    int extra_length;   //额外数据长度
//    void *extraData;    //额外数据
//
//    int msg_length;     //数据信息长度
//    unsigned char* message; //待传输秘密信息
//};



Msg* MQ_Msg_new(int insert_rate,int flag,int extra_length,void *extraData,int msg_length,unsigned char* message){
    Msg* res = malloc(sizeof(Msg));
    res->insert_rate = insert_rate;
    res->flag = flag;

    res-> extra_length = extra_length;

    res->extraData = extraData;

    res-> msg_length = msg_length;
    res->message = message;
    return res;
}

Msg* MQ_Msg_newNULL(){
    return MQ_Msg_new(0,0,0,0,0,0);
}


void MQ_Msg_destroy(Msg* t){
    free(t);
}


//---------------------- 二进制数据转字符串 ----------------------//
/**
 * 把 data 指向的一个 byte 的数据转化为 8 个 0/1 字符写到 str 指向的位置
 * @param str
 * @param data
 */
void MQ_Msg_wordData2Char( char* str,void *data ){
    int i;
    unsigned int inData = *(unsigned int*)data;
    for( i=0;i<8;i++,inData >>= 1 ){
        str[7-i]=(((inData & 1) == 0)?'0':'1');
    }
}

/**
 * 测试楼上的函数
 */
void test_MQ_Msg_wordData2Char(){
    char str[]="99999999";
    char data = 2;
    MQ_Msg_wordData2Char(str,&data);
    Log_Info("At test_MQ_Msg_wordData2Char:%s\n",str);
}


/**
 * 二进制数据 转 字符串
 * @param data              二进制数据
 * @param dataByteLen       数据长度   单位：byte
 * @return                  字符串指针 里面存储转好的 0/1 字符串     每8个用一个空格打开   需要用户使用 free 函数释放
 */
char* MQ_Msg_binaryData2Str( void *data,int dataByteLen ){

    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,data) ){
        return NULL;
    }

    size_t res_len = (size_t)8*dataByteLen+(dataByteLen-1)+1;
    char *res = (char*)malloc(sizeof(char)*res_len);
    memset(res,' ',res_len);
    res[res_len-1] = 0;

    int i;
    for(i=0;i<dataByteLen;i++){
        MQ_Msg_wordData2Char( res+(9*i),data+i );
//        Log_Info("The %d:%s\n",i,res);
    }

    return res;
}
//---------------------- /二进制数据转字符串 ----------------------//


/**
 * 打印一个 msg
 * @param m
 */
void MQ_Msg_print( Msg* m ){
    Log_Info("----- msg ------\n");

    Log_Info("      insert_rate:%d\n",m->insert_rate);
    Log_Info("      flag:%d\n",m->flag);
    Log_Info("      extra_length:%d\n",m->extra_length);
    if( !(m->extra_length) ){
        char *binStr = MQ_Msg_binaryData2Str(m->extraData,m->extra_length);
        Log_Info("      extraData:%s\n",binStr);
        free(binStr);

    }


    Log_Info("      msg_length:%d\n",m->msg_length);
    if( !(m->msg_length) ){
        char *binStr = MQ_Msg_binaryData2Str(m->message,m->msg_length);
        Log_Info("      extraData:%s\n",binStr);
        free(binStr);
    }

    Log_Info("----- /msg ------\n");
}




void MQ_Msg_test(){
//    test_MQ_Msg_wordData2Char();


    unsigned int num = 0xfffffff0;
    char* str = MQ_Msg_binaryData2Str( &num,4 );
    Log_Info("%s\n",str);
    free(str);

};
