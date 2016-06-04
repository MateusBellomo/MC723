#include <stdio.h>
#define START_ADRESS 0x6400000

volatile int *lock = (volatile int *) START_ADRESS;
static int procCounter = 0;

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

int f(int procNumber){
  int j;
  for(j = 0; j < 10; j++){
    printHello(procNumber);
  }
}

int main(int ac, char *av[]){
  int procNumber;

  /* AcquireLock(); */
  /* procNumber = procCounter; */
  /* procCounter ++; */
  /* ReleaseLock(); */

  /* f(procNumber); */
  
  *lock = 1234;
  printf("Hello World! %d\n", *lock);
  return 0;

  
  /* if (procNumber % 2) { */
  /*   for (j = 0; j < 1000; j ++); */
  /* } */
  //  RecursiveHello(10, procNumber); 

  return 0;
}
