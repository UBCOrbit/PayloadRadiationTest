package com.ubcorbit.radtest;

import android.app.IntentService;
import android.content.Intent;
import android.content.Context;
import android.support.annotation.Nullable;

public class MemTestCacheIneff extends IntentService
{
    static
    {
        System.loadLibrary("native-lib");
    }

    public MemTestCacheIneff()
    {
        super("MemTestCacheIneff");
    }

    @Override
    protected void onHandleIntent(@Nullable Intent intent)
    {
        if(intent != null)
        {
            main(intent.getLongExtra(ServiceStarter.EXTRA_SLEEP_TIME_US, ServiceStarter.DEFAULT_SLEEP_TIME_US),
                    intent.getIntExtra(ServiceStarter.EXTRA_CPU, CPU.CPU_DEFAULT.cpu));
            stopSelf();
        }
    }

    public native int main(long sleepTimeUS, int cpu);
}
