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

int main(int argc, char *argv[])
{
  if(argc < 2) /*Se o utilizador nao chamar o programa com argumentos suficientes, apresenta erro*/
  {
    printf("Erro: Não há argumentos suficientes!\n");
    return -1;
  }
  int i, n;
  n = atoi(argv[1]); /*Passagem de char para int do elemento argv[1] que é o número de elementos que colocamos ao chamar o programa no terminal*/
  int *vetor_teste = malloc(n*sizeof(int));
  in_fibonacci(vetor_teste, n);
  printf("Sequência com alocação dinâmica de %d elementos: \n", n);
  for(i = 0; i < n; i++)
  {
    printf("%d ", vetor_teste[i]);
  }
  printf("\n");
  return 0;
}
