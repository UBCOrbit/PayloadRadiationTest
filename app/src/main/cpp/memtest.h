#ifndef RADTEST_MEMTEST_H
#define RADTEST_MEMTEST_H

#include <stdint.h>
#include <unistd.h>

struct memtest_results
{
    size_t zeroToOneFlips;
    size_t oneToZeroFlips;
};

void memtest_L1cacheEff(useconds_t sleepTime);
void memtest_L2cacheEff(useconds_t sleepTime);
void memtest_cacheIneff(useconds_t sleepTime);

#endif //RADTEST_MEMTEST_H