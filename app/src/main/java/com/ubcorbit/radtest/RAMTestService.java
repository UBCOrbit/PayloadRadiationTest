package com.ubcorbit.radtest;

import android.app.IntentService;
import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.support.annotation.Nullable;
import android.util.Log;

public class RAMTestService extends IntentService
{
    static
    {
        System.loadLibrary("native-lib");
    }

    /**
     * Creates an IntentService.  Invoked by your subclass's constructor.
     */
    public RAMTestService()
    {
        super("RadTestRAM");
    }

    @Override
    protected void onHandleIntent(@Nullable Intent intent)
    {
        main();
        stopSelf();
    }

    public native int main();
}
