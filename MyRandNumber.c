//
// Created by Dongguaren on 7/6/18.
//

#include <wchar.h>
#include <stdlib.h>
#include "MyRandNumber.h"
#include "ErrorHandle.h"
#include "MyLog.h"



RND* RND_create( unsigned int seed ){
    RND* res = malloc(sizeof(RND));
    res -> randSeed = seed;
    return res;
}

void RND_free( RND* rnd ){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,rnd) ){
        return;
    }
    free(rnd);
}

unsigned int MRN_rand(RND *myRandNumberData)
{
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,myRandNumberData) ){
        return 0;
    }
    unsigned int r;
    /* 返回一个无符号32位整型的伪随机数. */
    myRandNumberData->randSeed = myRandNumberData->randSeed * 1103515245 + 12345;
    r = myRandNumberData->randSeed;
    return (r << 16) | ((r >> 16) & 0xFFFF);
}


int* getRandPosition( RND* randManager,int minRandNum,int maxRandNum,int numOfRand ){

    int isParaLegal = ( maxRandNum - minRandNum + 1 >= numOfRand );
    if( !isParaLegal ){
        EH_logErrMsg("parameter is not legal!");
        return NULL;
    }


    RND *myRandNumberData = randManager;
//    static int primeSeed = -1;
//    if( myRandNumberData==NULL ){
//        myRandNumberData = RND_create(seed);
//        primeSeed = seed;
//    }
//
//    if( primeSeed != seed ){
//        RND_free( myRandNumberData );
//        myRandNumberData = RND_create(seed);
//        primeSeed = seed;
//    }


    int randRange = maxRandNum - minRandNum + 1;
    short *posi = (short*)malloc(randRange* sizeof(short));
    int i,j;
    for( i=0;i<randRange;i++ ){
        *(posi+i) = 0;
    }

    for( i=1;i<=numOfRand;i++ ){
        int randNum = MRN_rand(myRandNumberData)%randRange;
        if( posi[randNum] ){
            for( j=1;;j+=2

                ){
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


void MRN_printRandArray( int *array,int len ){
    if( !EH_isArgsLegal("Para illegal.Pointer is null.",1,array) ){
        return;
    }
    Log_Info("------ rand array ------\n");
    Log_Info("         The len:%d\n",len);
    int i;
    for( i=0;i<len;i++ ){
        Log_Info("           The %dth:%d\n",i,array[i]);
    }
    Log_Info("------ /rand array ------\n");
}


void MRN_test(){

    RND* seed = RND_create(5);

    int *randArray;
    randArray = getRandPosition( seed,0,40,10 );
    MRN_printRandArray(randArray,10);free(randArray);
    randArray = getRandPosition( seed,0,40,10 );
    MRN_printRandArray(randArray,10);free(randArray);

    RND_free(seed);seed = RND_create(10);
    randArray = getRandPosition( seed,0,40,10 );
    MRN_printRandArray(randArray,10);free(randArray);

    RND_free(seed);seed = RND_create(5);
    randArray = getRandPosition( seed,0,40,10 );
    MRN_printRandArray(randArray,10);free(randArray);

    RND_free(seed);

}

