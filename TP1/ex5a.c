#include "stdio.h"

int my_strlen(char *str)
{
  int i;
  for(i = 0; str[i] != '\0'; i++);
  return i - 1; /*Esta subtraçao por 1 é usada porque o fgets funciona armazenando o carater de new line na string, e isso nao tem interesse para sabermos o tamanho da string em si*/
}               /*Se a string nao fosse obtida atraves do fgets, apenas se faria return i, tal como no ex5b.c*/

int main()
{
  int i;
  char c[50];
  printf("Escreva uma frase: \n");
  fgets(c, 50, stdin);
  printf("Tamanho da string: %d\n", my_strlen(c));
}
