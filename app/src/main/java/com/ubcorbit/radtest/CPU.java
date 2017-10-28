package com.ubcorbit.radtest;

public enum CPU
{
    CPU_DEFAULT(-1),
    CPU_0(0),
    CPU_1(1),
    CPU_2(2),
    CPU_3(3);

    public final int cpu;

    CPU(int cpu)
    {
        this.cpu = cpu;
    }
}
