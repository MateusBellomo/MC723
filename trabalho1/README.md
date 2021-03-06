# Trabalho 1

Mateus Augusto Bellomo Agrello Ruivo	RA: 147338  

## Benchmark Genetic ##

![alt text](/trabalho1/genetic_tempo.png "Fig 1")
![alt text](/trabalho1/genetic_performceDisco.png "Fig 1")

Pela análise do gráfico percebe-se claramente que a máquina Pedro Vasconcellos possui o pior desempenho tanto em tempo de execução quanto performance de disco. Isso pode ser justificado pelas suas especifações: é uma Raspberry Pi com 900 MHz e 1GB de RAM. Ao removermos essa máquina do gráfico conseguimos comparar melhor as outras máquinas:  

![alt text](/trabalho1/genetic_tempo_Pedro.png "Fig 1")
![alt text](/trabalho1/genetic_performanceDisco_Pedro.png "Fig 1")

As melhores máquinas no quesito tempo são Pedro Meireles, Klaus Rollman, Renan Gomes, debios, Gabriel Bueno, João Fidelis, Pedro Grijó, Matheus Figueiredo. Isso era esperado pois todas essas máquinas possuem especificações semelhantes (processador i5 ou i7 com mais de 2.2GHz).  

Com relação a performance de disco a melhor máquina é Klaus Rollman. Como só é escrita em disco a imagem final talvez essa não seja a melhor forma de se medir performance de disco. Algo mais interessante seria escrever várias imagens em disco em passos intermediários e obter uma média dessa performance obtendo um dado de melhor qualidade.  

## Benchmark ffmpeg ##

![alt text](/trabalho1/ffmpeg_tempo.png "Fig 1")
![alt text](/trabalho1/ffmpeg_pageFault.png "Fig 1")
![alt text](/trabalho1/ffmpeg_stalledCycles.png "Fig 1")
![alt text](/trabalho1/ffmpeg_L1_dcache.png "Fig 1")

Claramente a máquina com pior desempenho de tempo é Luiz Sekijima e isso era esperado pois ela possui um processador de modelo antigo (Intel Core 2 Duo). Novamente o melhor tempo fica entre aquelas máquinas de configuração semelhante: processadores Intel Core i5/i7 com mais de 2.2GHz (com exceção de um AMD PhenomII com 3.2GHz e um Intel Core 2 Quad com 2.66GHz).  

As máquinas com maior numero de Page-Fauts foram Klaus Rollman e debios mas isso pode estar relacionado com processos correndo em paralelo com bastante utilização de memória. A máquina com menor número de Page-Faults foi Luiz Sekijima.  

Das máquinas que fizeram a medição de Stalled cycles, não houve grande diferença entre Klaus Rollman, debios e Gabriel Magalhães. Porém a máquina yk0 teve uma quantidade de Stalled cycles bem menor que as outras que pode estar relacionado com uma cache maior (essa informação não se encontra na planilha de dados).  

Com relação à load misses da cache L1 as máquinas tiveram desempenho semelhante com exceção da máquina Klaus Rollman que obteve uma quantidade bem maior que as outras (de 10 a 20 vezes mais).  


## Benchmark convolução ##

![alt text](/trabalho1/convolucao_tempo.png "Fig 1")
![alt text](/trabalho1/convolucao_escrita.png "Fig 1")
![alt text](/trabalho1/convolucao_leitura.png "Fig 1")

Com relação ao quesito tempo as máquinas tiveram desempenho semelhante (com exceção das máquinas Renan Castro e Victor Souza) o que era esperado devido as especificações semelhantes. A máquina Renan Castro pode ter sido prejudica pois era uma máquina virtual logo nem toda capacidade do processador é dedicada à ela. Já a máquina Victor Souza possuiu um resultado inesperado comparado ao benchmark anterior (ffmpeg) o qual ficou com desempenho semelhante às outras máquinas. Talvez o usuário estivesse rodando algum outro processo em paralelo.

Com relação à escrita as melhores máquinas foram yk0, Victor Souza e Gustavo Basso. A máquina yk0 possui um disco com RPM maior (7200rpm) o que pode justificar o seu melhor desempenho. As outras duas máquinas não possuem essa informação em sua descrição.  

Com relação à leitura as melhore máquinas foram yk0 e Victor Souza. Isso era esperado pois elas também tiveram as melhores escritas e a velocidade no barramento de dados do disco costuma ser a mesma para leitura e escrita. Já a máquina Gustavo Basso teve um desempenho ruim nesse quesito o que causa certa estranheza já que ela obteve boa taxa de escrita.  


## Benchmark gnuplot ##

![alt text](/trabalho1/gnuplot_tempo.png "Fig 1")
![alt text](/trabalho1/gnuplot_cpuClock.png "Fig 1")
![alt text](/trabalho1/gnuplot_memStores.png "Fig 1")
![alt text](/trabalho1/gnuplot_busCycles.png "Fig 1")

A máquina Pedro Vasconcellos novamente obteve pior desempenho nos quesitos tempo, cpu-clock e bus-cycles e o motivo já foi citado anteriormente. Como os valores obtidos pela máquina Pedro Grijó estão muito abaixo das outras (na ordem de 1000 vezes menor) provavelmente houve algum erro na obtenção do dado logo fica mais claro se removermos ambas as máquinas, obtendo:  

![alt text](/trabalho1/gnuplot_tempo_PedroGrijo.png "Fig 1")
![alt text](/trabalho1/gnuplot_cpuClock_PedroGrijo.png "Fig 1")
![alt text](/trabalho1/gnuplot_memStores_PedroGrijo.png "Fig 1")
![alt text](/trabalho1/gnuplot_busCycles_PedroGrijo.png "Fig 1")

Com relação ao quesito tempo as máquinas obtiveram desempenho semelhante (com exceção das máquinas Pedro Meireles, Matheus Pinheiro e Felipe Emos). A máquina Pedro Meireles obteve um desempenho ruim se comparado com o benchmark Genetic, o que não era esperado. Já as máquinas Matheus Pinheiro e Felipe Emos realmente possuem especificação um pouco pior dos que as outras máquinas: Matheus Pinheiro possui um processador com 1.60GHz e Felipe Emos um netbook com Intel Atom.  

No quesito CPU-clock as máquinas de antes que possuiram pior desempenho aqui também o fizeram, o que era esperado.  

Poucas pessoas conseguiram medir os MEM-stores. Além do mais esse quesito sozinho não é muito útil e deveria ser combinado com cache misses (que não medimos) e tempo de execução, mas descobrimos isso após definir o nosso método de análise. Sendo assim não é possível analisá-lo de maneira significativa.


Algo semelhante ocorreu com o quesito bus-cycles. O bus-cycle juntamente com o número de instruções executadas poderia ser usado para calcular a quantidade de ciclos por instrução (CPI). Como não pedimos a medição de instruções executadas (e só soubemos depois que seria necessário esse dado), não é possível fazer uma análise que tenha sentido sobre esse dado.  


## Benchmark ordenação ##


![alt text](/trabalho1/ordenacao_piorCasoLento.png "Fig 1")
![alt text](/trabalho1/ordenacao_piorCasoRapido.png "Fig 1")
![alt text](/trabalho1/ordenacao_casoMedioLento.png "Fig 1")
![alt text](/trabalho1/ordenacao_casoMedioRapido.png "Fig 1")
![alt text](/trabalho1/ordenacao_melhorCasoLento.png "Fig 1")
![alt text](/trabalho1/ordenacao_melhorCasoRapido.png "Fig 1")


Como era de se esperar, as máquinas no geral obtiveram desempenho parecido, com exceção da máquina Pedro Vasconcellos e Felipe Emos, que possuem processadores com menor frequência o obtiveram os piores desempenhos. A melhor máquina em todas as análises foi a Pedro Meireles (que possui maior frequência de clock).  


## Benchmark imagemagick ##

![alt text](/trabalho1/imageMagick_tempo.png "Fig 1")
![alt text](/trabalho1/imageMagick_taskClock.png "Fig 1")
![alt text](/trabalho1/imageMagick_cycles.png "Fig 1")
![alt text](/trabalho1/imageMagick_instructions.png "Fig 1")

Para a medida de tempo de execução, novamente a máquina Felipe Emos obteve pior desempenho. As melhore máquinas foram Titouan Thibaud (Intel Core i5 3.3GHz) e Cygnus X-1 (Intel Core i7 x 4).  

Quanto a task-clock a máquina Cygnus X-1 obteve maior paralelização mas não diferindo muito das outras já que todas processadores com 4 núcleos (a menos da máquina Gabriel Magalhães que possui 8 núcleos).  

Quanto a cycles as máquinas não tiveram muita variação. Da mesma forma o número de instruções por ciclo de máquina (Instructions) não diferiu muito entre as máquinas. Esse resultado é esperado pois as máquinas são de mesma arquitetura.  


## Benchmark tcc ##

![alt text](/trabalho1/tcc_tempo.png "Fig 1")

As máquinas Renan Gomes, Renan Castro e João Fidélis obtiveram o melhor desempenho com relação ao tempo de execução o que era esperado pois são as máquinas com os melhores processadores (Intel Core i7). Uma surpresa é a máquina Renan Castro que no benchmark Convolução obteve desempenho pior comparado com as outras. Como é uma máquina virtual é dificil medir o seu desempenho já que o processador está concorrendo com dois sistemas operacionais operantes.  


## Benchmark FFTW ##

![alt text](/trabalho1/fftw_DFT1D.png "Fig 1")
![alt text](/trabalho1/fftw_DFT1D_IO.png "Fig 1")

Para o primeiro teste (DFT1D) a máquina Mateus Ruivo obteve o pior desempenho e como foi bem inferior às outras máquinas então seria melhor analisarmos os desempenhos sem essa máquina no conjunto de dados:  

![alt text](/trabalho1/fftw_DFT1D_Mateus.png "Fig 1")

A máquina com pior desempenho foi a Bruno Hori o que é justificável por possuir um pior processador (Intel Core 2 Quad) comparado às outras máquinas (Intel Core i7).  

Vale notar que ao rodar esse teste (DFT1D) na máquina Mateus Ruivo, e manter um terminal com a visualização do consumo em processamento e memória (comando top), observou-se que o processo consumia mais memória (em torno de 70%) do que processamento (em torno de 3%). Assim parece que todo o consumo do programa se dava na grande quantidade de escrita e leitura em memória. Ainda mais curioso é que ocorreu o contrário que planejava o benchmark: o programa foi mais rápido quando executado no teste DFT1D do que no DFT1D_IO. Não fui capaz de explicar o que causou tal comportamento, mas a máquina Mateus Ruivo ficava inutilizável após rodar DFT1D e inclusive foi necessário reiniciá-la após a execução do programa.  

Para o teste DFT1D_IO a máquina Gustavo Basso obteve melhor desempenho mesmo assim não a diferindo muito das outras. A máquina Bruno Hori obteve o pior desempenho o que já era esperado.  

Talvez fosse interssante incluir nesse benchmark uma medida de acesso a memória para que as diferenças causadas pela escrita e leitura em arquivo entre DFT1D e DFT1D_IO fossem melhor observadas como gostaria o grupo autor de tal benchmark.  


