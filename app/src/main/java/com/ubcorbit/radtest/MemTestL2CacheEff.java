package com.ubcorbit.radtest;

import android.app.IntentService;
import android.content.Context;
import android.content.Intent;
import android.support.annotation.Nullable;

public class MemTestL2CacheEff extends IntentService
{
    static
    {
        System.loadLibrary("native-lib");
    }

    public MemTestL2CacheEff()
    {
        super("MemTestL2CacheEff");
    }

    public static void start(Context context)
    {
        Intent intent = new Intent(context, MemTestL2CacheEff.class);
        context.startService(intent);
    }

    @Override
    protected void onHandleIntent(@Nullable Intent intent)
    {
        main();
        stopSelf();
    }

    public native int main();
}
