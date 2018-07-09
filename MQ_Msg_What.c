//
// Created by Dongguaren on 7/9/18.
//

#include <stdlib.h>
#include "MQ_Msg_What.h"


static MQ_Msg_What* MQ_Msg_What_gloalInstance=NULL;

MQ_Msg_What* MQ_Msg_What_getInstance(){
    if( MQ_Msg_What_gloalInstance == NULL ){
        MQ_Msg_What_gloalInstance = (MQ_Msg_What*)malloc(sizeof(MQ_Msg_What));
        MQ_Msg_What_gloalInstance -> QuitMessageQueue = -1;
    }
    return MQ_Msg_What_gloalInstance;
}