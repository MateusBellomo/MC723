#include <stdio.h>
#define START_ADRESS 0x6400000
#define MAX 1000

volatile int *lock = (volatile int *) START_ADRESS;
static int procCounter = 0;
int mat[MAX][MAX];
int res[MAX][MAX];
int n;

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

void printmatrix(int procNumber, int m[][MAX]){
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
    for(i = 0; i < n; i++){
      for(j = 0; j < n; j++){
	res[i][j] = 0;
	for(k = 0; k < n; k++){
	  res[i][j] += mat[i][k] + mat[k][j];
	}
      }
    }
    printf("proc = %d\n", procNumber);
  } else{
    printf("proc = %d\n", procNumber);
  }
}

void readFromFile(int procNumber){
  int i,j;
  FILE *fp = fopen("data.txt", "r");
  fscanf(fp, " %d", &n);
  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++)
      fscanf(fp, " %d", &mat[i][j]);

  printmatrix(procNumber, mat);
  
  fclose(fp);
}

int main(int ac, char *av[]){
  int procNumber;

  AcquireLock();
  procNumber = procCounter;
  if(procNumber==0) readFromFile(procNumber);
  procCounter++;
  ReleaseLock();

  AcquireLock();
  matrixmult(procNumber);
  if(procNumber == 0)
    printmatrix(procNumber, res);
  ReleaseLock();
  
  //  f(procNumber);

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
