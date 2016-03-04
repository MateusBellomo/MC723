#include <stdio.h>
#include <omp.h>
#include "calc_primo.h"

int main(int argc, char *argv[])
{
  int n = 0, i = 0, count = 0;
  while(argv[1][i] != '\0')
    n = (n*10) + (argv[1][i++]-'0');
  
  printf("n = %d\n", n);

#pragma omp parallel for
  for(i = 1; i <= n; i++){
    if (primo(i)){
      #pragma omp atomic
      count++;
      //    printf("%d é primo.\n", i);
    }else{
      //      printf("%d não é primo.\n", i);
    }
  }
  printf("Quantidade de primos: %d\n", count);
  
  return 0;
}	
	
