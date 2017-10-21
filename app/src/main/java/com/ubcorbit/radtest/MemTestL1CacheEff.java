package com.ubcorbit.radtest;

import android.app.IntentService;
import android.content.Context;
import android.content.Intent;
import android.support.annotation.Nullable;

public class MemTestL1CacheEff extends IntentService
{
    static
    {
        System.loadLibrary("native-lib");
    }

    public MemTestL1CacheEff()
    {
        super("MemTestL1CacheEff");
    }

    public static void start(Context context)
    {
        Intent intent = new Intent(context, MemTestL1CacheEff.class);
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
