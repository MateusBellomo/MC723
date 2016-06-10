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

Também alterei o programa *ac_tlm_peripheral.cpp* para que utilizasse uma variável global como mecanismo de tratamento de concorrência (já que ela será compartilhada por todos os processos que a utilizarem).

       int v=0;
       ac_tlm_rsp_status ac_tlm_peripheral::writem( const uint32_t &a , const uint32_t &d ){
         cout << "addr: " <<  std::hex  << a << " data: " << d << endl;
         v = d;
         return SUCCESS;
       }

       ac_tlm_rsp_status ac_tlm_peripheral::readm( const uint32_t &a , uint32_t &d ){
         d = v;
         v = 1;
         return SUCCESS;
       }
	      


## Leituras em um periférico ##

O programa inicial foi modificado para que lesse várias posições de memória do periférico:

  	#include <stdio.h>
	#define START_ADRESS 0x6400000

	volatile int *lock = (volatile int *) START_ADRESS;

	int main(){
		int i;
		for(i = 0; i < 10; i++){
		    printf("value = %#010x   position = %d\n", *lock, lock);
		    lock++;
		}
		return 0;
	}


A saída obtida foi a seguinte:


  	ArchC: Reading ELF application file: hello.mips
	ArchC: -------------------- Starting Simulation --------------------

	value = 0000000000   position = 104857600
	value = 0x01000000   position = 104857604
	value = 0x01000000   position = 104857608
	value = 0x01000000   position = 104857612
	value = 0x01000000   position = 104857616
	value = 0x01000000   position = 104857620
	value = 0x01000000   position = 104857624
	value = 0x01000000   position = 104857628
	value = 0x01000000   position = 104857632
	value = 0x01000000   position = 104857636

	ArchC: -------------------- Simulation Finished --------------------

	Info: /OSCI/SystemC: Simulation stopped by user.
	ArchC: Simulation statistics
	    Times: 0.00 user, 0.00 system, 0.00 real
	    Number of instructions executed: 63816
	    Simulation speed: (too fast to be precise)

Embora o programa esteja avançando o ponteiro para impressão de uma posição seguinte, não foi feita nenhuma alteração em *ac_tlm_peripheral.cpp* para que guardasse um vetor com as posições do periférico. Como mostrado anteriormente, *ac_tlm_peripheral.cpp* só utiliza uma variável global que é utilizada para tratar concorrência na etapa seguinte.

Outra detalhe importante é o valor impresso em *hello.c*: achei melhor imprimí-lo em hexa para que ficasse mais evidente a troca de endianess depois de o valor ser armazenado na arquitetura do mips. Pelo fato de o mips trabalhar em big endian, a ordem de bytes dos valores são trocadas (de 00 00 00 01 para 01 00 00 00).  

## Plataforma multicore ##

Para realizar um processamento paralelo, precisei apenas de uma função *AcquireLock()* e uma *ReleaseLock()*. Isso pois a aplicação escolhida foi elevar uma matriz de tamanho 64x64 ao quadrado, logo podemos dividí-la em duas metades e cada um dos processadores pode preencher metade da matriz resultante. O mecanismo de *lock* somente foi necessário para contar e atribuir o número para cada processador e no final, na impressão da matriz resultante. Foi utilizada outra variável auxiliar *workN* para contabilizar os processadores que já terminaram de calcular a sua metade da matriz resultante. Isso é necessário para que a impressão (ou qualquer outra utilização) da matriz resultante tenha consistência, ou seja, que a matriz resultante esteja devidamente calculada antes de sua utilização.

Com a utilização de apenas um processador o resultado foi:

    Info: /OSCI/SystemC: Simulation stopped by user.
    ArchC: Simulation statistics
        Times: 0.74 user, 0.00 system, 0.75 real
	Number of instructions executed: 10369863
	Simulation speed: 14013.33 K instr/s
    ArchC: Simulation statistics
        Times: 0.74 user, 0.00 system, 0.75 real
	Number of instructions executed: 72
	Simulation speed: 0.10 K instr/s


Percebe-se que o primeiro processador realizou muito mais operações. O segundo processador ainda realizou algumas operações pois ele está em *busy waiting* na função *AcquireLock()* para numeração dos processadores.

Com a utilização de dois processadores o resultado foi:

    Info: /OSCI/SystemC: Simulation stopped by user.
    ArchC: Simulation statistics
        Times: 0.70 user, 0.00 system, 0.70 real
	Number of instructions executed: 8378838
	Simulation speed: 11969.77 K instr/s
    ArchC: Simulation statistics
        Times: 0.70 user, 0.00 system, 0.70 real
	Number of instructions executed: 1991146
	Simulation speed: 2844.49 K instr/s


Aqui percebemos que a divisão entre os processadores de fato atribuiu um grande número de instruções para o segundo processador. Além disso a soma total do número de instruções realizadas nos dois processadores é muito parecido tanto no caso em que só um processador é efetivamente utilizado quanto no segundo caso onde a tarefa é dividida entre os processadores.

Vale notar também que o primeiro processador realizou um número bem maior de operações que o segundo (em torno de 80% do número total de instruções). Isso acontece pois ele é o responsável por imprimir a resposta e como utilizei um mecanismo de *busy waiting* para contagem dos processadores que terminaram seu trabalho, o processador fica em *loop* até que possa imprimir a resposta utilizando assim um número maior de instruções.