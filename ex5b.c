#include "stdio.h"
#include "string.h"

int my_strlen(char *str)
{
  int i;
  for(i = 0; str[i] != '\0'; i++);
  return i;
}

int main()
{
  int i;
  char *c = "Hello, World!\0";
  printf("Tamanho da string com my_strlen: %d\n", my_strlen(c));
  printf("Tamanho da string com strlen: %ld\n", strlen(c));
}
