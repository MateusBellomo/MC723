#include <stdio.h>

int primo(int n)
{
  int i;

  for(i = 2; i < n; i ++)
    if (n % i == 0)
      return 0;
  
  return 1;
}


int main(int argc, char *argv[])
{
  int n = 0, i = 0;  
  while(argv[1][i] != '\0')
    n = (n*10) + (argv[1][i++]-'0');
  
  printf("n = %d\n", n);

  for(i = 1; i <= n; i++){
    if (primo(i))
      printf("%d é primo.\n", i);
    else
      printf("%d não é primo.\n", i);
  }

  return 0;
}
