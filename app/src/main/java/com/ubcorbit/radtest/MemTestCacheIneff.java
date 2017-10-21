package com.ubcorbit.radtest;

import android.app.IntentService;
import android.content.Intent;
import android.content.Context;

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

    public static void start(Context context)
    {
        Intent intent = new Intent(context, MemTestCacheIneff.class);
        context.startService(intent);
    }

    @Override
    protected void onHandleIntent(Intent intent)
    {
        main();
        stopSelf();
    }

    public native int main();
}
