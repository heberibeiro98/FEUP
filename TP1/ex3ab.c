#include "stdio.h"
#include "stdlib.h"

void in_fibonacci(int *fib, int n)
{
  int i;
  if(n == 1) /*Se só for pedido um elemento, esse elemento é o primeiro que é 0*/
  {
    fib[0] = 0;
  }
  if(n == 2) /*Se só forem pedidos dois, sao os dois primeiros, 0 e 1*/
  {
    fib[0] = 0;
    fib[1] = 1;
  }
  if(n > 2) /*Se forem pedidos mais que 2, os dois primeiros sao 0 e 1 e os restantes sao obtidos no ciclo for*/
  {
    fib[0] = 0;
    fib[1] = 1;
    for(i = 2; i < n; i++) /*Iniciando em i=2 pois já sabemos fib[0] e fib[1]*/
    {
      fib[i] = fib[i-1] + fib[i - 2]; /*O valor atual fib[i] é dado pela soma dos dois ultimos fib[i-1] e fib[i-2]*/
    }
  }
}

int main()
{
  int i, n;
  printf("Quantos elementos da sequência?\n");
  scanf("%d", &n);
  int vetor_teste1[10]; /*Alocação estatica*/
  int *vetor_teste2 = malloc(n*sizeof(int)); /*Alocação dinamica*/
  in_fibonacci(vetor_teste1, 10);
  in_fibonacci(vetor_teste2, n);
  printf("Sequência com alocação estatica de 10 elementos: \n");
  for(i = 0; i < 10; i++)
  {
    printf("%d ", vetor_teste1[i]);
  }
  printf("\n");
  printf("Sequência com alocação dinâmica de %d elementos: \n", n);
  for(i = 0; i < n; i++)
  {
    printf("%d ", vetor_teste2[i]);
  }
  printf("\n");
  return 0;
}
