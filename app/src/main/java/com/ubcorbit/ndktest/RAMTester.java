package com.ubcorbit.ndktest;

import android.util.Log;

public class RAMTester
{
    private static final String TAG = "ORBIT RAM TEST";

    public RAMTester()
    {
    }

    public void executeTest()
    {
        long result = testRAM(1, 1024*1024*50);
        if(result == 0)
        {
            Log.d(TAG, "Passed!");
        }
        else
        {
            Log.d(TAG, "BITFLIP at address: " + result);
        }
    }

    public native long testRAM(int numBlocks, long bytesPerBlock);
}
