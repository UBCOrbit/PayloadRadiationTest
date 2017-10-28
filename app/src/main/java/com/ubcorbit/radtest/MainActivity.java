package com.ubcorbit.radtest;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends Activity
{
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        ServiceStarter.start(this, MemTestL1CacheEff.class, 1000, CPU.CPU_0);
        ServiceStarter.start(this, MemTestL2CacheEff.class, 1000, CPU.CPU_1);
        ServiceStarter.start(this, MemTestCacheIneff.class, 1000, CPU.CPU_2);
    }
}
