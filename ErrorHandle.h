//
// Created by Dongguaren on 6/23/18.
//

#ifndef MYTEST_ERRORHANDLE_H
#define MYTEST_ERRORHANDLE_H


/**
 * 打印 出错信息
 * @param fileName  出错文件名
 * @param funcName  出错函数名
 * @param lineNum   出错行数
 * @param errReason     出错原因
 */
void EH_printErrorMsg( const char* fileName,const char* funcName,int lineNum,char* errReason );

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
int EH_testParaLegalAndPrintErrMsg( const char* fileName,const char* funcName,int lineNum,char* errReason,int numOfPara,... );


/**
 * 宏定义
 * 对 函数：EH_testParaLegalAndPrintErrMsg 的包裹
 * 为了获取 __FILE__,__FUNCTION__,__LINE__ 三个参数
 */
#define EH_isArgsLegal(errReason,numOfPara,args...) (EH_testParaLegalAndPrintErrMsg(__FILE__,__FUNCTION__,__LINE__,errReason,numOfPara,args))


/**
 * 宏定义
 * 对 函数：EH_printErrorMsg 的包裹
 * 为了获取 __FILE__,__FUNCTION__,__LINE__ 三个参数
 */
#define  EH_logErrMsg( errReason ) EH_printErrorMsg(__FILE__,__FUNCTION__,__LINE__,errReason)

//--------------------------------- example -----------------------------------------------//

//int test(int a){
//
//    if( !EH_isArgsLegal("233",1,a) ){
//        return -345;
//    }
//
//
//    return 233;
//}


//--------------------------------- /example -----------------------------------------------//

#endif //MYTEST_ERRORHANDLE_H
