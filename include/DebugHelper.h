#ifndef DEBUG_HELPER_H
#define DEBUG_HELPER_H

#include "config.h"

#if ENABLE_DEBUG
    #define DBG_ASSERT(cond, msg) \
    do {\
        if (!(cond)) {\
            if(strlen(msg))\
                printf("Assert failed: %s\n", msg);\
            assert(cond);\
        }\
    }while(0)
#else
    #define DBG_ASSERT(cond, msg)
#endif

#endif
