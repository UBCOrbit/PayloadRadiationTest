#include <jni.h>
#include <android/log.h>

extern "C" {

typedef unsigned char datum;

datum* allocateBlock(unsigned long nBytes)
{
    return new datum[nBytes];
}

void deallocateBlock(datum* ptr)
{
    delete []  ptr;
}

datum** allocateAllBlocks(unsigned int nBlocks, unsigned long blockSize)
{
    datum** blocks = new datum*[nBlocks];
    for(int i = 0; i < nBlocks; i++)
    {
        blocks[i] = allocateBlock(blockSize);
    }
    return blocks;
}

void deallocateAllBlocks(datum** blocks, unsigned int nBlocks)
{
    for(int i = 0; i < nBlocks; i++)
    {
        delete [] blocks[i];
    }
    delete [] blocks;
}

/**********************************************************************
 *
 * Function:    memTestDevice()
 *
 * Description: Test the integrity of a physical memory device by
 *              performing an increment/decrement test over the
 *              entire region.  In the process every storage bit
 *              in the device is tested as a zero and a one.  The
 *              base address and the size of the region are
 *              selected by the caller.
 *
 * Notes:
 *
 * Returns:     NULL if the test succeeds.
 *
 *              A non-zero result is the first address at which an
 *              incorrect value was read back.  By examining the
 *              contents of memory, it may be possible to gather
 *              additional information about the problem.
 *
 **********************************************************************/

void fillPattern(volatile datum* baseAddress, unsigned long nBytes)
{
    unsigned long offset;
    unsigned long nWords = nBytes / sizeof(datum);

    datum pattern;

    // Fill memory with a known pattern.
    for (pattern = 1, offset = 0; offset < nWords; pattern++, offset++)
    {
        baseAddress[offset] = pattern;
    }
}

datum* checkAndInvert(volatile datum* baseAddress, unsigned long nBytes)
{
    unsigned long offset;
    unsigned long nWords = nBytes / sizeof(datum);

    datum pattern;
    datum antipattern;

    // Check each location and invert it for the second pass.
    for (pattern = 1, offset = 0; offset < nWords; pattern++, offset++)
    {
        if (baseAddress[offset] != pattern)
        {
            return (datum*)&baseAddress[offset];
        }

        antipattern = ~pattern;
        baseAddress[offset] = antipattern;
    }

    return NULL;
}

datum* checkInvertedAndZero(volatile datum* baseAddress, unsigned long nBytes)
{
    unsigned long offset;
    unsigned long nWords = nBytes / sizeof(datum);

    datum pattern;
    datum antipattern;

    // Check each location for the inverted pattern and zero it.
    for (pattern = 1, offset = 0; offset < nWords; pattern++, offset++)
    {
        antipattern = ~pattern;
        if (baseAddress[offset] != antipattern)
        {
            return (datum*)&baseAddress[offset];
        }
    }

    return NULL;
}

void flipBit(volatile datum* baseAddress, unsigned long offset, datum bitMask)
{
    baseAddress[offset] = baseAddress[offset] ^ bitMask;
}

JNIEXPORT jlong JNICALL
Java_com_ubcorbit_ndktest_RAMTester_testRAMAllocate(JNIEnv *env, jobject thisObject, jint numBlocks, jlong bytesPerBlock)
{
    unsigned int nBlocks = (unsigned int)numBlocks;
    unsigned long blockSize = (unsigned long)bytesPerBlock;

    datum** blocks = allocateAllBlocks(nBlocks, blockSize);
    return (jlong)blocks;
}

JNIEXPORT void JNICALL
Java_com_ubcorbit_ndktest_RAMTester_testRAMWrite(JNIEnv *env, jobject thisObject, jlong blocksPtr, jint numBlocks, jlong bytesPerBlock)
{
    unsigned int nBlocks = (unsigned int)numBlocks;
    unsigned long blockSize = (unsigned long)bytesPerBlock;
    datum** blocks = (datum**)blocksPtr;

    for(int i = 0;i < nBlocks; i++)
    {
        datum* baseAddress = blocks[i];

        fillPattern(baseAddress, blockSize);
    }
}

JNIEXPORT jlong JNICALL
Java_com_ubcorbit_ndktest_RAMTester_testRAMRead1(JNIEnv *env, jobject thisObject, jlong blocksPtr, jint numBlocks, jlong bytesPerBlock)
{
    unsigned int nBlocks = (unsigned int)numBlocks;
    unsigned long blockSize = (unsigned long)bytesPerBlock;

    datum** blocks = (datum**)blocksPtr;

    datum* addressError = NULL;

    for(int i = 0;i < nBlocks; i++)
    {
        datum* baseAddress = blocks[i];

        addressError = checkAndInvert(baseAddress, blockSize);
        if(addressError != NULL) break;
    }

    return (jlong)addressError;
}

JNIEXPORT jlong JNICALL
Java_com_ubcorbit_ndktest_RAMTester_testRAMRead2(JNIEnv *env, jobject thisObject, jlong blocksPtr, jint numBlocks, jlong bytesPerBlock)
{
    unsigned int nBlocks = (unsigned int)numBlocks;
    unsigned long blockSize = (unsigned long)bytesPerBlock;

    datum** blocks = (datum**)blocksPtr;

    datum* addressError = NULL;

    for(int i = 0;i < nBlocks; i++)
    {
        datum* baseAddress = blocks[i];

        addressError = checkInvertedAndZero(baseAddress, blockSize);
        if(addressError != NULL) break;
    }

    return (jlong)addressError;
}

JNIEXPORT jlong JNICALL
Java_com_ubcorbit_ndktest_RAMTester_testRAMDeAllocate(JNIEnv *env, jobject thisObject, jlong blocksPtr, jint numBlocks, jlong bytesPerBlock)
{
    unsigned int nBlocks = (unsigned int)numBlocks;
    datum** blocks = (datum**)blocksPtr;
    deallocateAllBlocks(blocks, nBlocks);
}

}