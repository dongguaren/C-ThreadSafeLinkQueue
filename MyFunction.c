//
// Created by 61603 on 2018/6/22.
//
#include "MyFunction.h"

int* getRandPosition( unsigned int seed,int minRandNum,int maxRandNum,int numOfRand ){

    int isParaLegal = ( 0 < seed && seed <= 65535 ) &&
                      ( maxRandNum - minRandNum + 1 >= numOfRand );
    if( !isParaLegal ){
        return NULL;
    }

    static unsigned int mySeed = 0;
    if( mySeed != seed ){
        mySeed = seed;
        srand(seed);
    }


    int randRange = maxRandNum - minRandNum + 1;
    short *posi = (short*)malloc(randRange* sizeof(short));
    int i,j;
    for( i=0;i<randRange;i++ ){
        *(posi+i) = 0;
    }

    for( i=1;i<=numOfRand;i++ ){
        int randNum = rand()%randRange;
        if( posi[randNum] ){
            for( j=1;;j++ ){
                if( !posi[(randNum+j)%randRange] ){
                    posi[(randNum+j)%randRange] = 1;
                    break;
                }
            }
        } else{
            posi[randNum] = 1;
        }
    }

    int *res = (int*)malloc(numOfRand* sizeof(int));

    j=0;
    for( i=0;i<randRange;i++ ){
        if( posi[i] ){
            res[j]=i+minRandNum;
            j++;
        }
    }
    free(posi);
    return res;
}

void test_printArray(int *array, int arrayLen){
    int i;
    for( i=0;i<arrayLen;i++ ){
        printf("%d ",array[i]);
    }
}

void test_getRandArray(){
    int *array;

    //seed:223 生成 The 1-5 的随机数
    array = getRandPosition( 223,0,10,5 );
    test_printArray(array, 5);free(array);printf("\n");
    //seed:223 生成 The 6-10 的随机数
    array = getRandPosition( 223,0,10,5 );
    test_printArray(array, 5);free(array);printf("\n");

    //seed:123 生成 The 1-5 的随机数
    array = getRandPosition( 123,0,10,5 );
    test_printArray(array, 5);free(array);printf("\n");
    //seed:123 生成 The 6-10 的随机数
    array = getRandPosition( 123,0,10,5 );
    test_printArray(array, 5);free(array);printf("\n");

    //seed:223 生成 The 1-5 的随机数
    array = getRandPosition( 223,0,10,5 );
    test_printArray(array, 5);free(array);printf("\n");
    //seed:223 生成 The 6-10 的随机数
    array = getRandPosition( 223,0,10,5 );
    test_printArray(array, 5);free(array);printf("\n");
}

