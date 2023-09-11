#!/bin/bash

# Defina as variáveis do LIKWID_HOME e PATH de acordo com o seu ambiente
export LIKWID_HOME="/home/soft/likwid"
export PATH="$PATH:${LIKWID_HOME}/bin:${LIKWID_HOME}/sbin"

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

# Compila o programa perfEG se necessário (certifique-se de que seu Makefile está correto)
make all

# Execute o programa perfEG com LIKWID e capture a saída
likwid-perfctr -C 3 -g FLOPS_DP -m ./perfEG < teste.txt > saida.txt
cat saida.txt | head -n 8 | tail -n 3
cat saida.txt | grep MFLOP/s | head -n 1

cat saida.txt | head -n 12 | tail -n 4
cat saida.txt | grep MFLOP/s | head -n 4 | tail -n -1

cat saida.txt | head -n 16 | tail -n 4
cat saida.txt | grep MFLOP/s | head -n 7 | tail -n -1


# Verifique se a execução foi bem-sucedida
if [ $? -eq 0 ]; then
   rm -rf saida.txt
   echo "Execução bem-sucedida"
else
    echo "Erro ao executar o programa perfEG"
fi
