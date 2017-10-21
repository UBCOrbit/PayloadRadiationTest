#include <jni.h>
#include "memtest.h"

extern "C" {

/************************ Memory Test: L1 Cache Effective ************************/

JNIEXPORT jint JNICALL
Java_com_ubcorbit_radtest_MemTestL1CacheEff_main(JNIEnv *env, jobject thisObject)
{
    memtest_L1cacheEff(1000 /* 1 ms */);
    return 0;
}

/************************ Memory Test: L2 Cache Effective ************************/

JNIEXPORT jint JNICALL
Java_com_ubcorbit_radtest_MemTestL2CacheEff_main(JNIEnv *env, jobject thisObject)
{
    memtest_L2cacheEff(1000 /* 1 ms */);
    return 0;
}

/************************ Memory Test: Cache Ineffective ************************/

JNIEXPORT jint JNICALL
Java_com_ubcorbit_radtest_MemTestCacheIneff_main(JNIEnv *env, jobject thisObject)
{
    memtest_cacheIneff(1000 /* 1 ms */);
    return 0;
}

}