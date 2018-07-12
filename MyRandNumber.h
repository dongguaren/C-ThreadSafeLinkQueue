//
// Created by Dongguaren on 7/6/18.
//

#ifndef MYTEST_MYRANDNUMBER_H
#define MYTEST_MYRANDNUMBER_H

typedef struct {
    unsigned int randSeed;
}MyRandNumberData;

typedef MyRandNumberData RND;

/**
 * 返回一个 int 指针，指向一个数组，里面升序存放 最小值为 minRandNum，最大值为 maxRandNum 的 数量为 numOfRand 的随机数
 *
 * @param randManager       RND* 实例  for 线程安全
 * @param minRandNum        随机数最小值
 * @param maxRandNum        随机数最大值
 * @param numOfRand         随机数 数量
 * @return                  数组指针，需要调用者使用 free（） 释放
 *                           如果参数不合法，则返回 NULL
 */
int* getRandPosition( RND* randManager,int minRandNum,int maxRandNum,int numOfRand );


RND* RND_create( unsigned int seed );

void RND_free( RND* rnd );






void MRN_test();

#endif //MYTEST_MYRANDNUMBER_H
