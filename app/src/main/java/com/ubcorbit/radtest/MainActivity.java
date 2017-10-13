package com.ubcorbit.radtest;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends Activity
{
    TextView tv;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        tv = (TextView) findViewById(R.id.sample_text);
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
}
