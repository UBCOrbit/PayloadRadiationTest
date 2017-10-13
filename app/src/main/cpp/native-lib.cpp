#include <jni.h>
#include "orbit_logging.h"
#include <unistd.h>
#include "ramtest.h"

extern "C" {

void flipBit(volatile datum* baseAddress, unsigned long offset, datum bitMask)
{
    baseAddress[offset] = baseAddress[offset] ^ bitMask;
}

int main()
{
    unsigned int sleepTime = 1; // seconds

    unsigned int numBlocks = 1;
    unsigned long blockSize = 1024 * 1024 * 100; // 100 MB

    LOGD("RAM: Allocating...");
    datum** blocks = allocateAllBlocks(numBlocks, blockSize);

    long count = 0;
    while(count < 2)
    {
        count++;
        LOGD("--------------------------------------------------------------");

        datum *addressError = NULL;

        LOGD("RAM: Filling...");
        for (int i = 0; i < numBlocks; i++)
        {
            fillPattern(blocks[i], blockSize);
        }

        LOGD("Clearing Cache...");
        //TODO

        LOGD("RAM: Sleeping...");
        sleep(sleepTime);

        LOGD("RAM: Check #1 / Invert");
        for (int i = 0; i < numBlocks; i++)
        {
            addressError = checkAndInvert(blocks[i], blockSize);
            if (addressError != NULL)
            {
                LOGD("Address Error: %ld", (long) addressError);
                break;
            }
        }
        if(addressError != NULL) continue;

        LOGD("RAM: Sleeping...");
        sleep(sleepTime);

        LOGD("RAM: Check #2 / Zero");
        for (int i = 0; i < numBlocks; i++)
        {
            addressError = checkInvertedAndZero(blocks[i], blockSize);
            if (addressError != NULL)
            {
                LOGD("Address Error: %ld", (long) addressError);
                break;
            }
        }
        if(addressError != NULL) continue;

        LOGD("RAM: No Errors");
    }

    LOGD("--------------------------------------------------------------");

    LOGD("RAM: Deallocating...");
    deallocateAllBlocks(blocks, numBlocks);

    LOGD("RAM: Complete");
    return 0;
}

JNIEXPORT jint JNICALL
Java_com_ubcorbit_radtest_RAMTestService_main(JNIEnv *env, jobject thisObject)
{
    return main();
}

}