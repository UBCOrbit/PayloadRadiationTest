package com.ubcorbit.radtest;

import android.content.Context;
import android.content.Intent;

public class ServiceStarter
{
    public static final String EXTRA_SLEEP_TIME_US = "com.ubcorbit.radtest.EXTRA_SLEEP_TIME_US";
    public static final String EXTRA_CPU = "com.ubcorbit.radtest.EXTRA_CPU";

    public static final long DEFAULT_SLEEP_TIME_US = 1000;

    public static <T> void start(Context context, Class<T> _class, long sleepTimeUS, CPU cpu)
    {
        Intent intent = new Intent(context, _class);
        intent.putExtra(EXTRA_SLEEP_TIME_US, sleepTimeUS);
        intent.putExtra(EXTRA_CPU, cpu.cpu);
        context.startService(intent);
    }
}