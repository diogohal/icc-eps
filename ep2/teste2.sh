#!/bin/bash

METRICA="FLOPS_DP"
CPU=3

LIKWID_HOME=/home/soft/likwid
CFLAGS="-I${LIKWID_HOME}/include -DLIKWID_PERFMON"
LFLAGS="-L${LIKWID_HOME}/lib -llikwid"

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

make
for k in $METRICA
do
    likwid-perfctr -C ${CPU} -g ${k} -m ./perfEG < teste.txt > ${k}_SemOtimiz.log
done

rm -f perfEG
gcc ${CFLAGS} -O3 perfEG.c -o perfEG ${LFLAGS}
for k in $METRICA
do
    likwid-perfctr -C ${CPU} -g ${k} -m ./perfEG < teste.txt > ${k}_Otimiz.log
done
