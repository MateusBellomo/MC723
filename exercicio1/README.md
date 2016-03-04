# Exercicio 1

Mateus Augusto Bellomo Agrello Ruivo

RA: 147338


Tempo gasto sem nenhuma otimização: 0m0.403s

Tempo gasto com otimização -O0: 0m0.395s

Tempo gasto com otimização -O1: 0m0.347s

Tempo gasto com otimização -O2: 0m0.387s

Tempo gasto com otimização -O3: 0m0.395s

A com melhor tempo foi a otimização -O1. Mesmo assim a diferença não foi muito grande (13,89% melhor que sem nenhuma otimização).


Tempo gasto com otimização -mtune=native: 0m0.381s

A flag -mtune tem o intuito de gerar instruções otimizadas relativas ao processador sendo utilizado. Utilizando -mtune=native o processador de onde o código está sendo compilado é procurado e as intruções são gerados para aquela máquina especificamente (logo o executável pode não rodar em máquinas diferentes). O tempo não foi melhor do que com a otimazação -O1.

Com a utilização do makefile e dois arquivos separados o resultado variava entre melhor e pior do que o obtido anteriormente (comigo mesmo rodando o gcc no terminal e a flag -O1): 0m0.310s - 0m0.350s. Como o tempo de execução do programa é muito pequeno, essa diferença pode estar relacionada a tarefas executadas pelo sistema operacional que estão fora de nosso controle ou pelo fato de estarmos executando o mesmo programa várias vezes e o sistema operacional recuperar esse programa que já esta na memória.

n = 100000

Apenas um arquivo: 0m5.242s

Dois arquivos: 0m5.245s

Executei diversas vezes com 1 e 2 arquivos fonte e o tempo não mudou muito do descrito anteriormente. Creio que esse resultado era esperado pois o código não muda, apenas é dividido em dois arquivos logo as instruções geradas para cada um de fato deveriam ser as mesmas.


Otimização no cálculo dos primos (teste somente com divisores ímpares e n = 100000): 0m5.217s - 0m5.263s. Embora reduzimos o número de testes pela metade, a complexidade do algoritmo não foi alterada (O(n)) logo não se espera uma grande melhora na execução (pelo menos para casos pequenos).


O programa gasta mais tempo na função primo() que testa se um número é primo (gprof retornou que 100% do tempo foi gasto lá). Isso já era esperado pois no main() apenas iteramos nos números que queremos testar e a função primo() que realiza todo o trabalho de cálculo.


Se fosse paralelizar o código, paralelizaria a função primo() pois calcular se dois números 'x' e 'y' são primos pode ser feito de maneira independente (da maneira que o código está escrito atualmente).


Paralelizando:

A média sem paralelização foi de 0m5.200s enquanto com a paralelização foi para 0m0.280s (o que representa uma melhora de 94,61%). Vale notar que é necessário a utilização do comando '#pragma omp atomic' na variável que conta a quantidade de primos para que seu valor esteja correto já que várias threads irão acessá-la ao mesmo tempo.


Melhorando ainda mais o desempenho:

Para melhorar a eficiência do programa teríamos que melhorar a complexidade do algoritmo de cálculo de números primos. Uma primeira otimização seria procurar algum divisor até raiz do número. Isso melhoraria a eficiência mas para cada valor calculado sozinho.
Um algoritmo melhor para cálculo de números primos seria o crivo de Eratostenes em que uma tabela é preenchida marcando-se os múltiplos de cada primo como não primos. A complexidade do algoritmo é O(n log log n) sendo n o maior número buscado enquanto a complexidade do algoritmo fornecido é O(n^2).
