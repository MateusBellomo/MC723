# Trabalho 3 - Contagem de ciclos

Mateus Augusto Bellomo Agrello Ruivo	RA: 147338  

## Criação de um hello.c ##

A princípio criei um programa *hello.c* para testar a quantidade de instruções **add** usadas.

	#include <stdio.h>

	int main(){
	  int a = 1, b =2;
	  int c= a+b;

	  printf("Hello World! %d\n", c);
	  return 0;
	}

Utilizando o comando 

	   mips-newlib-elf-objdump -d hello.mips > objdump_out

obtive o assembly de meu *hello.c*:

       00000128 <main>:
	 128:       27bdffd8        addiu   sp,sp,-40
	 12c:       afbf0024        sw      ra,36(sp)
	 130:       afbe0020        sw      s8,32(sp)
	 134:       03a0f021        move    s8,sp
	 138:       24020001        li      v0,1
	 13c:       afc20010        sw      v0,16(s8)
	 140:       24020002        li      v0,2
	 144:       afc20014        sw      v0,20(s8)
	 148:       8fc30010        lw      v1,16(s8)
	 14c:       8fc20014        lw      v0,20(s8)
	 150:       00000000        nop
	 154:       00621021        addu    v0,v1,v0
	 158:       afc20018        sw      v0,24(s8)
	 15c:       3c020001        lui     v0,0x1
	 160:       24444a58        addiu   a0,v0,19032
	 164:       8fc50018        lw      a1,24(s8)
	 168:       0c00007f        jal     1fc <printf>
	 16c:       00000000        nop
	 170:       00001021        move    v0,zero
	 174:       03c0e821        move    sp,s8
	 178:       8fbf0024        lw      ra,36(sp)
	 17c:       8fbe0020        lw      s8,32(sp)
	 180:       27bd0028        addiu   sp,sp,40
	 184:       03e00008        jr      ra
	 188:       00000000        nop


Olhando a linha 154 vemos que ocorre um **addu** e que o valor é guardado em *v0*. Depois esse valor é transferido para *a0* e isso ocorre por causa da chamada do *printf*. Occorre um outro **addiu** também no início e fim do programa mas está relacionado à pilha.


## Avaliando desempenho de *benchmarks* ##

Utilizando a seguinte tabela com CPI médio de instruções

Categoria | CPI médio
------------ | -------------
Acesso à memória | 10
Controle (branch/jump) | 3
Outras | 1

obtive os seguintes resultados:


## Susan edges - small ##


    ArchC: -------------------- Simulation Finished --------------------
    number of memory access = 2752695 cycles = 27526950
    number of jumps = 961478 cycles = 2884434
    number of others = 4378976 cycles =  4378976
    total cycles = 34790360


## sha - small ##

    ArchC: -------------------- Simulation Finished --------------------
    number of memory access = 2579546 cycles = 25795460
    number of jumps = 606891 cycles = 1820673
    number of others = 9989203 cycles = 9989203
    total cycles = 37605336

## sha - large ##

    ArchC: -------------------- Simulation Finished --------------------
    number of memory access = 26817990 cycles = 268179900
    number of jumps = 6307427 cycles = 18922281
    number of others = 103960168 cycles = 103960168
    total cycles = 391062349

