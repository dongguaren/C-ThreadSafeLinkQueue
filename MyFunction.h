//
// Created by 61603 on 2018/6/22.
//

#ifndef FIRST_TEST_MYFUNCTION_H
#define FIRST_TEST_MYFUNCTION_H

#include <stdio.h>
#include <stdlib.h>
/**
 * 返回一个 int 指针，指向一个数组，里面升序存放 最小值为 minRandNum，最大值为 maxRandNum 的 数量为 numOfRand 的随机数
 *
 * @param seed              随机数种子。需要在 [1,65535]
 *                          如果此次 seed 跟上一次不同，则返回使用此次 seed 生成的随机数，否则 继续 使用上一次的 seed 生成随机数
 * @param minRandNum        随机数最小值
 * @param maxRandNum        随机数最大值
 * @param numOfRand         随机数 数量
 * @return                  数组指针，需要调用者使用 free（） 释放
 *                           如果参数不合法，则返回 NULL
 */
int* getRandPosition( unsigned int seed,int minRandNum,int maxRandNum,int numOfRand );
#endif //FIRST_TEST_MYFUNCTION_H
