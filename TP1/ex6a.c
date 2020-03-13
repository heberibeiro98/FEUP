#include "stdio.h"
#include "string.h"

int main()
{
  int i;
  char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  for(i = 0; i<12; i++)
  {
    printf("%s\n", *(months+i)); /*O apontador *months está a apontar para um elemento do vetor, logo se incrementarmos da forma *(months+i) estamos a percorrer o vetor (é como se fizessemos months[0 + i])*/
  }
}
