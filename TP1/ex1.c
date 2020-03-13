#include <stdio.h>

int main()
{
  int n1, n2, i, aux;
  n1 = 0; /*Primeiro valor da sequência de fibonacci é 0*/
  printf("%d ", n1);
  n2 = 1; /*Segundo valor é 1*/
  printf("%d ", n2);
  for(i = 2; i < 10; i++)
  {
    aux = n1 + n2; /*O próximo termo da sequência é o número anterior (n1) + o número atual (n2)*/
    n1 = n2; /*O número anterior é atualizado*/
    n2 = aux; /*O número atual é atualizado*/
    printf("%d ", aux);
  }
  printf("\n");
  return 0;
}
