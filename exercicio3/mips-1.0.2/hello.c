#include <stdio.h>

int main(){
  int a = 1, i;
  for(i = 0; i < 1000; i++){
    a += i;
  }
  printf("Hello World!...%d\n", a);
  return 0;
}
