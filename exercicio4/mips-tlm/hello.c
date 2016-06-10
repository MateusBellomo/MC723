#include <stdio.h>
#include "data.h"
#define START_ADRESS 0x6400000

volatile int *lock = (volatile int *) START_ADRESS;
volatile int procCounter = 0;
volatile int workN = 0;

int res[MAX][MAX];

void AcquireLock();
void ReleaseLock();

void printHello(int procNumber){
  AcquireLock();
  printf("Hi from processor PowerPC %d!\n", procNumber);
  ReleaseLock();
}

void RecursiveHello(int n, int procNumber){
  if (n) {
    printHello(procNumber);
    RecursiveHello(n - 1, procNumber);
  }
}

void AcquireLock(){
  while(*lock);
}

void ReleaseLock(){
  *lock = 0;
}

void f(int procNumber){
  int j;
  for(j = 0; j < 10; j++){
    printHello(procNumber);
  }
}

void printmatrix(int procNumber, int m[MAX][MAX]){
  printf("proc = %d\n", procNumber);
  int i, j;
  for(i = 0; i < n; i++){
    printf("%d", m[i][0]);
    for(j = 1; j < n; j++){
      printf(" %d", m[i][j]);
    }
    printf("\n");
  }
}

void matrixmult(int procNumber){
  int i,j,k;
  
  if(procNumber == 0){
    for(i = 0; i < n/2; i++){
      for(j = 0; j < n; j++){
	res[i][j] = 0;
	for(k = 0; k < n; k++){
	  res[i][j] += v[i][k] + v[k][j];
	}
      }
    }
    AcquireLock();
    workN++;
    ReleaseLock();
  } else{
    
    for(i = n/2; i < n; i++){
      for(j = 0; j < n; j++){
    	res[i][j] = 0;
    	for(k = 0; k < n; k++){
    	  res[i][j] += v[i][k] + v[k][j];
    	}
      }
    }
    AcquireLock();
    workN++;
    ReleaseLock();
  }
}


int g(){
  int procNumber;

  AcquireLock();
  procNumber = procCounter++;
  ReleaseLock();

  matrixmult(procNumber);
  if(procNumber == 1){
    while(workN < 2);
    printmatrix(procNumber, res);
  }
}

int main(int ac, char *av[]){

  g();
  
  /* int i; */
  /* for(i = 0; i < 10; i++){ */
  /*   printf("value = %#010x   position = %d\n", *lock, lock); */
  /*   lock++; */
  /* } */

  
  /* if (procNumber % 2) { */
  /*   for (j = 0; j < 1000; j ++); */
  /* } */
  //  RecursiveHello(10, procNumber); 

  return 0;
}
