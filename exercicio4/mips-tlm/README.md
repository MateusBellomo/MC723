# Trabalho 4 - Plataformas e perfiércios

Mateus Augusto Bellomo Agrello Ruivo	RA: 147338  

## Criação de um hello.c ##

A princípio criei um programa *hello.c* para escrever no endereço base do periférico:

  	#include <stdio.h>
	#define START_ADRESS 0x6400000

	volatile int *lock = (volatile int *) START_ADRESS;

	int main(){
	  *lock = 1234;
	  printf("Hello World! %d\n", *lock);
	  return 0;
	}

Obtendo a seguinte saída:

 	ArchC: Reading ELF application file: hello.mips
 	ArchC: -------------------- Starting Simulation --------------------

	addr: 6400000 data: d2040000
	Hello World! 1234
	ArchC: -------------------- Simulation Finished --------------------

	Info: /OSCI/SystemC: Simulation stopped by user.
	ArchC: Simulation statistics
	    Times: 0.00 user, 0.00 system, 0.00 real
	    Number of instructions executed: 4350
	    Simulation speed: (too fast to be precise)

É interessante observar que o valor escrito dentro da função **writem** de *ac_tlm_peripheral.cpp* imprime o valor passado como parâmetro em hexa (0x04D2) e em big endian.

Existe um cuidade a ser tomado na declaração do ponteiro de acesso ao periférico: é necessário que o ponteiro seja especificado como *volatile*. Isso avisa o compilador que o valor da variável pode mudar durante acessos diferentes evitando assim que ele realize otimizações como não escrever o valor da variável em memória durante escritas e leituras seguidas. Isso poderia causar inconsitência em programas que compartilham uma mesma variável.  


## Leituras em um periférico ##

O programa inicial foi modificado para que lesse várias posições de memória do periférico:

  	#include <stdio.h>
	#define START_ADRESS 0x6400000

	volatile int *lock = (volatile int *) START_ADRESS;

	int main(){
		int i;
		for(i = 0; i < 10; i++){
		    printf("value = %d   position = %d\n", *lock, lock);
		    lock++;
		}
		return 0;
	}


A saída obtida foi a seguinte:


  	ArchC: Reading ELF application file: hello.mips
	ArchC: -------------------- Starting Simulation --------------------

	value = 0   position = 104857600
	value = 16777216   position = 104857604
	value = 16777216   position = 104857608
	value = 16777216   position = 104857612
	value = 16777216   position = 104857616
	value = 16777216   position = 104857620
	value = 16777216   position = 104857624
	value = 16777216   position = 104857628
	value = 16777216   position = 104857632
	value = 16777216   position = 104857636
	ArchC: -------------------- Simulation Finished --------------------

	Info: /OSCI/SystemC: Simulation stopped by user.
	ArchC: Simulation statistics
	    Times: 0.00 user, 0.00 system, 0.00 real
	    Number of instructions executed: 63816
	    Simulation speed: (too fast to be precise)

Utilizando a seguinte tabela com CPI médio de instruções

Categoria | CPI médio
------------ | -------------
Acesso à memória | 10
Controle (branch/jump) | 3
Outras | 1

obtive os seguintes resultados:

