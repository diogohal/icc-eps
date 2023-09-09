#!/bin/bash

# Defina as variáveis do LIKWID_HOME e PATH de acordo com o seu ambiente
export LIKWID_HOME="/home/soft/likwid"
export PATH="$PATH:${LIKWID_HOME}/bin:${LIKWID_HOME}/sbin"

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

# Compila o programa perfEG se necessário (certifique-se de que seu Makefile está correto)
make all 

# Execute o programa perfEG com LIKWID e capture a saída
likwid-perfctr -C 3 -g FLOPS_DP -m ./perfEG < teste.txt > temp_output.txt

# Verifique se a execução foi bem-sucedida
if [ $? -eq 0 ]; then
    # Use grep e awk para extrair a quantidade de MFLOPS da saída
    mflops=$(grep "DP MFLOP/s" temp_output.txt | awk 'NR==2{print $3}')
    echo "Quantidade de MFLOPS: $mflops MFLOP/s"
else
    echo "Erro ao executar o programa perfEG"
fi

# Remova o arquivo temporário


