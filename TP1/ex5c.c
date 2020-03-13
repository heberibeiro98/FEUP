#include "stdio.h"
#include "string.h"

int my_strlen(char *str)
{
  int i;
  for(i = 0; str[i] != '\0'; i++);
  return i;
}

int main(int argc, char *argv[])
{
  printf("Tamanho da string com my_strlen: %d\n", my_strlen(argv[1])); /*argv[1] é o que contem a string escrita como argumento (ver guiao)*/
  printf("Tamanho da string com strlen: %ld\n", strlen(argv[1]));
}
