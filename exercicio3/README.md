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


## Susan edges - small ##


   ArchC: -------------------- Simulation Finished --------------------
   number of memory access = 2752695 cycles = 27526950
   number of jumps = 961478 cycles = 2884434
   number of others = 4378976 cycles =  4378976


## sha - small ##

   ArchC: -------------------- Simulation Finished --------------------
   number of memory access = 2579546 cycles = 25795460
   number of jumps = 606891 cycles = 1820673
   number of others = 9989203 cycles = 9989203

## sha - large ##

   ArchC: -------------------- Simulation Finished --------------------
   number of memory access = 26817990 cycles = 268179900
   number of jumps = 6307427 cycles = 18922281
   number of others = 103960168 cycles = 103960168

Para definir um tamanho para a cache L1 realizei alguns testes (tanto para cache de instrução quanto de dados) com número de vias fixo (1-way) e tamanho de bloco 32B. Verifiquei como se comportava a taxa de miss quando o tamanho da cache aumentava.  

	bash:$./../../dinero4sbc/dineroIV -informat s -trname vortex_m2b -maxtrace 20 -l1-dsize $iK -l1-dbsize 32 -l1-dassoc 1 -l1-isize $iK -l1-ibsize 32 -l1-iassoc 1

![alt text](/exercicio2/cacheL1-tamanho.png "Fig 1")

Pela observação do gráfico podemos dizer que quanto maior o tamanho da cache L1, menor será sua taxa de miss. Isso era esperado mas quando temos uma cache L1 muito grande sofremos com o tempo de busca. Então é necessário que seja estabelecido um trade-off vantajoso. Decidi por manter o tamanho da L1 em 64Kb pois esse é o tamanho real da cache L1 do processador Intel i7 e também pelo fato de o resultado dos testes começarem a demorar mais para caches de tamanho superior a 64Kb.  

## Avaliando cache L1 de dados ##

Com o tamanho da cache L1 fixado (64Kb) realizei alguns exeperimentos variando o tamanho do  bloco e número de vias:  

	for ((i=2; i<=64; i=i*2))  
	do  
		for ((j=1; j<=8; j=j*2))  
		do  
			./../../dinero4sbc/dineroIV -informat s -trname vortex_m2b -maxtrace 20 -l1-dsize 64K -l1-dbsize $i -l1-dassoc $j  
		done  
	done  

![alt text](/exercicio2/cacheL1-dados.png "Fig 1")

Defini como máximo de associatividade o valor de 8. Em [1] vemos que quanto maior a associativade mais é reduzido a taxa de miss, porém para uma alta associativade se paga o custo de maior tempo nos hits. Além disso é possivel perceber que quanto maior o tamanho do bloco menor é a taxa de miss.  


## Avaliando cache L1 de instruções ##

Novamente com o tamanho da cache L1 fixado (64Kb) foram realizados alguns exeperimentos variando o tamanho do  bloco e número de vias para a cache L1 de instruções:  

	for ((i=2; i<=64; i=i*2))  
	do  
		for ((j=1; j<=8; j=j*2))  
		do  
			./../../dinero4sbc/dineroIV -informat s -trname vortex_m2b -maxtrace 20 -l1-isize 64K -l1-ibsize $i -l1-iassoc $j  
		done  
	done  

![alt text](/exercicio2/cacheL1-instrucoes.png "Fig 1")

Aqui também percebemos uma melhora na taxa de miss tanto no aumento do tamanho do bloco quanto no aumento do número de vias. Algo interessante é que a taxa de miss para a cache L1 de instruções foi bem menor que na de dados: enquanto a cache de dados teve uma variação entre 0.0409-0.0091, a cache de instruções teve uma variação entre 0.012-0.0004. Isso pode ser explicado pelo fato de programas possuírem quantidade elevada de laços o que garante um maior número de hits no que se refere à instruções.  


## Avaliando cache L2 unificada ##

Agora escolhendo a melhor configuração obtida até então para a cache L1 (tamanho de 64Kb, bloco de 64B e 8-way), realizei alguns experimentos com a cache L2. O tamanho de L2 foi fixado em 256Kb (novamente a configuração do processador i7) pois aqui também temos que balancear o tamanho da cache com o tempo gasto para cada hit o que justifica a limitação de seu tamanho.  

	for ((i=2; i<=64; i=i*2))  
	do  
		for ((j=1; j<=8; j=j*2))  
		do  
			./../../dinero4sbc/dineroIV -informat s -trname vortex_m2b -maxtrace 20 -l1-usize 64K -l1-ubsize 64 -l1-uassoc 8 -l2-usize 256K -l2-ubsize $i -l2-uassoc $j
		done  
	done  

![alt text](/exercicio2/cacheL2.png "Fig 1")

É interessante observar aqui que o aumento no tamanho do bloco não inflenciou na taxa de miss. O fator determinante foi o número de vias sendo uma cache L2 8-way a de melhor taxa de miss. Outro fato interessante é que a taxa de miss da cache L2 está maior que da cache L1. Isso não era para ter acontecido pois a cache L2 está um nivel acima da L1 sendo maior e portanto guardando maior quantidade de dados logo possui uma taxa de miss menor que a L1. Talvez tenha havido algum erro de medição pelo próprio dinero.  

## Referências ##

[1] David A. Patterson and John L. Hennessy. 2008. Computer Organization and Design, Fourth Edition, Fourth Edition: The Hardware/Software Interface (The Morgan Kaufmann Series in Computer Architecture and Design) (4th ed.). Morgan Kaufmann Publishers Inc., San Francisco, CA, USA. 


