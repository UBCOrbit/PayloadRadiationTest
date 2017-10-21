#include <stdint.h>
#include <limits.h>
#include <unistd.h>
#include "orbit_logging.h"
#include "orbit_timing.h"
#include "memtest.h"

size_t count1Bits(char value)
{
    size_t numOnes = 0;
    for(size_t i = 0; i < CHAR_BIT * sizeof value; ++i, value >>= 1)
    {
        if ((value & 1) == 1)
        {
            ++numOnes;
        }
    }
    return numOnes;
}

size_t count0Bits(char value)
{
    return (CHAR_BIT * sizeof value) - count1Bits(value);
}

void cacheEff_setZeros(char** matrix, const size_t dim)
{
    size_t i, j;

    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

size_t cacheEff_checkZerosAndFlip(char** matrix, const size_t dim)
{
    size_t i, j;
    size_t zeroToOneFlips = 0;

    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            if(matrix[i][j] != 0)
            {
                zeroToOneFlips += count1Bits(matrix[i][j]);
            }
            matrix[i][j] = 1;
        }
    }

    return zeroToOneFlips;
}

size_t cacheEff_checkOnesAndFlip(char** matrix, const size_t dim)
{
    size_t i, j;
    size_t oneToZeroFlips = 0;

    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            if(matrix[i][j] != 1)
            {
                oneToZeroFlips += count0Bits(matrix[i][j]);
            }
            matrix[i][j] = 0;
        }
    }

    return oneToZeroFlips;
}

void cacheIneff_setZeros(char** matrix, const size_t dim)
{
    size_t i, j;

    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            matrix[j][i] = 0;
        }
    }
}

size_t cacheIneff_checkZerosAndFlip(char** matrix, const size_t dim)
{
    size_t i, j;
    size_t zeroToOneFlips = 0;

    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            if(matrix[j][i] != 0)
            {
                zeroToOneFlips += count1Bits(matrix[j][i]);
            }
            matrix[j][i] = 1;
        }
    }

    return zeroToOneFlips;
}

size_t cacheIneff_checkOnesAndFlip(char** matrix, const size_t dim)
{
    size_t i, j;
    size_t zeroToOneFlips = 0;

    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            if(matrix[j][i] != 1)
            {
                zeroToOneFlips += count0Bits(matrix[j][i]);
            }
            matrix[j][i] = 0;
        }
    }

    return zeroToOneFlips;
}

char** allocateMatrix(const size_t dim)
{
    char** matrix = new char *[dim];
    for (size_t i = 0; i < dim; ++i)
    {
        matrix[i] = new char[dim];
    }
    return matrix;
}

void deallocateMatrix(char** matrix, size_t dim)
{
    for (size_t a = 0; a < dim; ++a)
    {
        delete [] matrix[a];
    }
    delete [] matrix;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void memtest_cacheEff(useconds_t sleepTime, size_t dim, const char *logTag)
{
    long double millisecs;

    char** matrix = allocateMatrix(dim);

    size_t tmpResult;
    memtest_results totalResults = {0,0};

    while(true)
    {
        timestamp_t t0 = get_timestamp();

        //------------------------------------------------------

        // Set 0's
        LOGD("%s: Setting 0's", logTag);
        cacheEff_setZeros(matrix, dim);

        // Let radiation do its thing
        usleep(sleepTime);

        // Check 0's, Set 1's
        LOGD("%s: Checking 0's, Setting 1's", logTag);
        tmpResult = cacheEff_checkZerosAndFlip(matrix, dim);
        totalResults.zeroToOneFlips += tmpResult;

        // Let radiation do its thing
        usleep(sleepTime);

        // Check 1's, Set 0's
        LOGD("%s: Checking 1's, Setting 0's", logTag);
        tmpResult = cacheEff_checkOnesAndFlip(matrix, dim);
        totalResults.oneToZeroFlips += tmpResult;

        // Let radiation do its thing
        usleep(sleepTime);

        //------------------------------------------------------

        LOGD("%s: Zero to One Flips = %ld", logTag, totalResults.zeroToOneFlips);
        LOGD("%s: One to Zero Flips = %ld", logTag, totalResults.oneToZeroFlips);

        timestamp_t t1 = get_timestamp();

        millisecs = (t1 - t0) / 1000.0L;
        LOGD("%s: Time = %Lf (ms)", logTag, millisecs);
    }
}
#pragma clang diagnostic pop

void memtest_L1cacheEff(useconds_t sleepTime)
{
    memtest_cacheEff(sleepTime, 96, "MemTestL1CacheEff"); //  9 KB matrix < 16 KB L1 Cache
}

void memtest_L2cacheEff(useconds_t sleepTime)
{
    memtest_cacheEff(sleepTime, 1024, "MemTestL2CacheEff"); //  1 MB matrix < 2 MB L2 Cache
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void memtest_cacheIneff(useconds_t sleepTime)
{
    const char* logTag = "MemTestCacheIneff";
    const const size_t dim = 2048; //  4 MB matrix > 2 MB L2 Cache

    long double millisecs;

    char** matrix = allocateMatrix(dim);

    size_t tmpResult;
    memtest_results totalResults = {0,0};

    while(true)
    {
        timestamp_t t0 = get_timestamp();

        //------------------------------------------------------

        // Set 0's
        LOGD("%s: Setting 0's", logTag);
        cacheIneff_setZeros(matrix, dim);

        // Let radiation do its thing
        usleep(sleepTime);

        // Check 0's, Set 1's
        LOGD("%s: Checking 0's, Setting 1's", logTag);
        tmpResult = cacheIneff_checkZerosAndFlip(matrix, dim);
        totalResults.zeroToOneFlips += tmpResult;

        // Let radiation do its thing
        usleep(sleepTime);

        // Check 1's, Set 0's
        LOGD("%s: Checking 1's, Setting 0's", logTag);
        tmpResult = cacheIneff_checkOnesAndFlip(matrix, dim);
        totalResults.oneToZeroFlips += tmpResult;

        // Let radiation do its thing
        usleep(sleepTime);

        //------------------------------------------------------

        timestamp_t t1 = get_timestamp();

        millisecs = (t1 - t0) / 1000.0L;
        LOGD("%s: Time = %Lf (ms)", logTag, millisecs);
    }
}
#pragma clang diagnostic pop