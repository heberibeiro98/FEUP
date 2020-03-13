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
  char *ptr;
  n = strtol(argv[1], &ptr, 10); /*A funçao strtol vai buscar a parte númerica de uma string. O apontador *ptr está a apontar para o primeiro caracter na string depois do valor numerico (por exemplo, se a string fosse "5a", estaria a apontar para "a". Finalmente, o 10 indica que estamos a trabalhar em base 10)*/
  if(ptr == argv[1]) /*Se o ptr for igual a argv[1], ou seja, se argv[1] não tiver números e apenas letras ou outros caracteres, nao temos nada para usar como dimensao e imprime-se uma mensagem de erro*/
  {
    printf("Erro: O argumento tem de ser um número inteiro!\n");
    return -1;
  }
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
