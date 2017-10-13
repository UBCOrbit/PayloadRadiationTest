#ifndef RADTEST_RAMTEST_H
#define RADTEST_RAMTEST_H

typedef unsigned char datum;

datum **allocateAllBlocks(unsigned int nBlocks, unsigned long blockSize);
void deallocateAllBlocks(datum **blocks, unsigned int nBlocks);

void fillPattern(volatile datum *baseAddress, unsigned long nBytes);
datum *checkAndInvert(volatile datum *baseAddress, unsigned long nBytes);
datum *checkInvertedAndZero(volatile datum *baseAddress, unsigned long nBytes);

#endif //RADTEST_RAMTEST_H
