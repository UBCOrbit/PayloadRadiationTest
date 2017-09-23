#include <jni.h>
#include <android/log.h>

extern "C"

JNIEXPORT jint JNICALL
Java_com_ubcorbit_ndktest_MainActivity_memAllocTest(JNIEnv *env, jobject /* this */)
{
    const int length = 1024*1024*100;
    auto* data = new int[length];

    for(int i = 0; i < length; i++)
    {
        data[i] = i;
    }

    int lastValue = data[length - 1];

    delete [] data;

    __android_log_print(ANDROID_LOG_VERBOSE, "NDKTEST", "RAM Test Result: %d", lastValue);

    return lastValue;
}
