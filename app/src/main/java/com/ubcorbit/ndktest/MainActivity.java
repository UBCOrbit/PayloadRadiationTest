package com.ubcorbit.ndktest;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends Activity
{
    TextView tv;

    // Used to load the 'native-lib' library on application startup.
    static
    {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        tv = (TextView) findViewById(R.id.sample_text);
    }

    @Override
    protected void onResume()
    {
        super.onResume();

        RAMTester tester = new RAMTester();
        tester.executeTest();

        /*long freeMemBefore = getFreeMemorySize();
        Log.d("ORBIT RAM TEST", "Before: " + Long.toString(freeMemBefore));

        int numBytes = 1024;

        RAMTester ramTester = new RAMTester();

        long ptr = ramTester.allocMem(numBytes, new OutOfMemoryError());
        Log.d("NDKTest Ptr", Long.toString(ptr));

        Long testResult = ramTester.memTestDevice(ptr, numBytes);

        ramTester.deallocMem(0);

        long freeMemAfter = getFreeMemorySize();
        Log.d("NDKTEST Mem", "After: " + Long.toString(freeMemAfter));

        Log.d("NDKTEST Mem", "Used: " + Double.toString((double)(freeMemBefore - freeMemAfter) / (1024 * 1024)) + " MB");

        if(testResult == null)
        {
            tv.setText("Passed!");
        }
        else
        {
            tv.setText("BITFLIP!! (at offset: " + (testResult - ptr) + ")");
        }*/
    }

    public static long getFreeMemorySize()
    {
        long freeSize = 0L;
        try
        {
            Runtime info = Runtime.getRuntime();
            freeSize = info.freeMemory();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return freeSize;
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    //public native int memAllocTest();
}
