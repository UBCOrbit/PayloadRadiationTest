#include <jni.h>
#include "memtest.h"

extern "C" {

JNIEXPORT jint JNICALL
Java_com_ubcorbit_radtest_Test_main(JNIEnv *env, jobject thisObject)
{
    memtest_cacheCompare(1000 /* 1 ms */);
    return 0;
}

/************************ Memory Test: L1 Cache Effective ************************/

JNIEXPORT jint JNICALL
Java_com_ubcorbit_radtest_MemTestL1CacheEff_main(JNIEnv *env, jobject thisObject, jlong sleepTimeUS, jint cpu)
{
    memtest_L1cacheEff((useconds_t)sleepTimeUS, cpu);
    return 0;
}

/************************ Memory Test: L2 Cache Effective ************************/

JNIEXPORT jint JNICALL
Java_com_ubcorbit_radtest_MemTestL2CacheEff_main(JNIEnv *env, jobject thisObject, jlong sleepTimeUS, jint cpu)
{
    memtest_L2cacheEff((useconds_t)sleepTimeUS, cpu);
    return 0;
}

/************************ Memory Test: Cache Ineffective ************************/

JNIEXPORT jint JNICALL
Java_com_ubcorbit_radtest_MemTestCacheIneff_main(JNIEnv *env, jobject thisObject, jlong sleepTimeUS, jint cpu)
{
    memtest_cacheIneff((useconds_t)sleepTimeUS, cpu);
    return 0;
}

}