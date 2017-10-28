package com.ubcorbit.radtest;

public class Test
{
    static
    {
        System.loadLibrary("native-lib");
    }

    public native int main();
}
