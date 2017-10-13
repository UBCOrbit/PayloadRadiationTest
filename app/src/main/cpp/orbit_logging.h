#ifndef RADTEST_ORBIT_LOGGING_H
#define RADTEST_ORBIT_LOGGING_H

#include <android/log.h>

#define  LOG_TAG    "ORBIT RAD TEST"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#endif //RADTEST_ORBIT_LOGGING_H
