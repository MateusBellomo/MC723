# Trabalho 1

Mateus Augusto Bellomo Agrello Ruivo	RA: 147338  

## Benchmark Genetic ##

![alt text](/trabalho1/genetic_tempo.png "Fig 1")
![alt text](/trabalho1/genetic_performceDisco.png "Fig 1")

Pela análise do gráfico percebe-se claramente que a máquina Pedro Vasconcellos possui o pior desempenho tanto em tempo de execução quanto performance de disco. Isso pode ser justificado pelas suas especifações: é uma Raspberry Pi com 900 MHz e 1GB de RAM. Ao removermos essa máquina do gráfico conseguimos comparar melhor as outras máquinas:  

![alt text](/trabalho1/genetic_tempo_Pedro.png "Fig 1")
![alt text](/trabalho1/genetic_performanceDisco_Pedro.png "Fig 1")

As melhores máquinas no quesito tempo são Pedro Meireles, Klaus Rollman, Renan Gomes, debios, Gabriel Bueno, João Fidelis, Pedro Grijó, Matheus Figueiredo. Isso era esperado pois todas essas máquinas possuem especificações semelhantes (processador i5 ou i7 com mais de 2.2GHz).  

Com relação a performance de disco a melhor máquina é Klaus Rollman.

## Benchmark ffmpeg ##

![alt text](/trabalho1/ffmpeg_tempo.png "Fig 1")
![alt text](/trabalho1/ffmpeg_pageFault.png "Fig 1")
![alt text](/trabalho1/ffmpeg_stalledCycles.png "Fig 1")
![alt text](/trabalho1/ffmpeg_L1_dcache.png "Fig 1")


## Benchmark convolução ##

![alt text](/trabalho1/convolucao_tempo.png "Fig 1")
![alt text](/trabalho1/convolucao_escrita.png "Fig 1")
![alt text](/trabalho1/convolucao_leitura.png "Fig 1")

## Benchmark gnuplot ##

![alt text](/trabalho1/gnuplot_tempo.png "Fig 1")
![alt text](/trabalho1/gnuplot_cpuClock.png "Fig 1")
![alt text](/trabalho1/gnuplot_memStores.png "Fig 1")
![alt text](/trabalho1/gnuplot_busCycles.png "Fig 1")


## Benchmark ordenação ##

![alt text](/trabalho1/ordenacao_piorCasoLento.png "Fig 1")
![alt text](/trabalho1/ordenacao_piorCasoRapido.png "Fig 1")
![alt text](/trabalho1/ordenacao_casoMedioLento.png "Fig 1")
![alt text](/trabalho1/ordenacao_casoMedioRapido.png "Fig 1")
![alt text](/trabalho1/ordenacao_melhorCasoLento.png "Fig 1")
![alt text](/trabalho1/ordenacao_melhorCasoRapido.png "Fig 1")


## Benchmark imagemagick ##

![alt text](/trabalho1/imageMagick_tempo.png "Fig 1")
![alt text](/trabalho1/imageMagick_taskClock.png "Fig 1")
![alt text](/trabalho1/imageMagick_cycles.png "Fig 1")
![alt text](/trabalho1/imageMagick_instructions.png "Fig 1")

## Benchmark tcc ##

![alt text](/trabalho1/tcc_tempo.png "Fig 1")

## Benchmark FFTW ##

![alt text](/trabalho1/fftw_DFT1D.png "Fig 1")
![alt text](/trabalho1/fftw_DFT1D_IO.png "Fig 1")


