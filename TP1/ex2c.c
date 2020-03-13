#include "stdio.h"

int main()
{
  int a[10];
  char *hello = "Hello, World!";
  printf("Size of a[0]: %ld\n", sizeof(a[0]));
  printf("Size of *hello: %ld\n", sizeof(*hello)); /* *hello é um apontador para os elementos da string, logo sizeof(*hello) é 1 byte (porque cada elemento de uma string é 1 byte)*/
}
