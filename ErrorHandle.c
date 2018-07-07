//
// Created by Dongguaren on 6/23/18.
//
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "ErrorHandle.h"
#include "GlobalPara.h"
#include "MyLog.h"


/**
 * 我不知道怎么把 变长参数 从一个函数传递到另一个函数中。
 * 所以我把此函数的内容复制到了 “EH_testParaLegalAndPrintErrMsg” 中。
 * 所以这个函数不会被调用。
 *
 * judge input pointer arguments are all NULL
 * @param numOfPara     number of pointer.  if numOfPara < 0,function will return -233
 * @param ...           variable-length parameter
 * @return              1 -> all pointer aren't NULL
 *                      0 -> at least one of pointer is NULL
 */
int EH_isParaLegal( int numOfPara,... ){
    if( numOfPara<0 )return -233;

    va_list argp;
    va_start( argp, numOfPara );

    int i;
    void* p;
    int isLegal=1;

    for( i=0;i<numOfPara;i++ ){
        p=va_arg( argp,void*);
        if( p == NULL ){
            isLegal=0;
            break;
        }
    }

    va_end( argp );

    return isLegal;
}


/**
 * 打印 出错信息
 * @param fileName  出错文件名
 * @param funcName  出错函数名
 * @param lineNum   出错行数
 * @param errReason     出错原因
 */
void EH_printErrorMsg( const char* fileName,const char* funcName,int lineNum,char* errReason ){

    Log_Info("***** Error *****\n");
    Log_Info("      File Name:%s\n",fileName);
    Log_Info("      Function Name:%s\n",funcName);
    Log_Info("      Line Number:%d\n",lineNum);
    Log_Info("      Error Reason:%s\n",errReason);
    Log_Info("***** /Error *****\n");

}

/**
 * 判断 通过 “变长参数” 传入的指针变量是否有 NULL
 *      如果有 NULL
 *          打印出错信息
 *
 * 返回结果 isLegal
 *     1 -> 代表参数合法，指针变量中无 NULL
 *     0 -> 代表参数不合法，指针变量中有 NULL
 *
 *
 * 此函数中使用了宏 GLOBAL_debug_para_check
 *      如果定义了此宏，进行参数检查
 *      否则，跳过参数检查，返回 1（参数合法）
 *
 *
 * @param fileName      调用 EH_printErrorMsg
 * @param funcName      调用 EH_printErrorMsg
 * @param lineNum       调用 EH_printErrorMsg
 * @param errReason     调用 EH_printErrorMsg
 * @param numOfPara     指针变量数量 一定需要和传入的指针数量一致
 * @param ...           变长参数
 * @return              1 -> 代表参数合法    0 -> 代表参数不合法
 */
int EH_testParaLegalAndPrintErrMsg( const char* fileName,const char* funcName,int lineNum,char* errReason,int numOfPara,... ){
#ifdef GLOBAL_debug_para_check
    if( numOfPara<0 )return -233;

    va_list argp;
    va_start( argp, numOfPara );

    int i;
    void* p;
    int isLegal=1;

    for( i=0;i<numOfPara;i++ ){

        va_arg( argp,void*);
        if( p == NULL ){
            isLegal=0;
            break;
        }
    }

    va_end( argp );

    if( !isLegal ){
        EH_printErrorMsg( fileName,funcName,lineNum,errReason );
    }

    return isLegal;
#else
    return 1;
#endif

}
