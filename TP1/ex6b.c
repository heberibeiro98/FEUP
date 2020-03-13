#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int no_months(char *mon1, char *mon2)
{
  int i, m1, m2, dif;
  char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  for(i = 0; i<12; i++)
  {
    if(strncasecmp(mon1, *(months+i), 3) == 0) /*Esta funçao vai comparar o mês 1 que foi passado à funçao com o mês atual no char *months, e se forem iguais o contador m1 toma o valor de i + 1 (por exemplo, se fosse fevereiro, i seria igual a 1 e m1 = 1 + 1 = 2*/
    {
      m1 = i + 1;
    }
    if(strncasecmp(mon2, *(months+i), 3) == 0) /*Mesma logica que o de cima, a soma por 1 permite obter o numero do mes*/
    {/*A funçao strncasecmp compara duas strings e retorna 0 se forem iguais, o terceiro argumento (que neste caso é 3), indica quantos elementos da string comparar(e neste caso so quero os primeiros 3 que sao as primeiras 3 letras dos meses)*/
      m2 = i + 1;
    }
  }
  dif = abs(m2-m1); /*Modulo da diferença entre os numeros dos meses obtidos, o que significa que nao precisas de inserir os meses por ordem crescente quanto te é pedido (exemplo, primeiro junho e depois março funciona na mesma)*/
  return dif;
}

int main()
{
  int n;
  char mes1[4], mes2[4];
  printf("Insira o mes 1: \n"); /*É suposto inserires so as 3 primeiras letras do mes, tal como na string *months, se inserires mais que isso ou se inserires algo que nao corresponda com o que esta em *months, o programa dá merda e nao me apetece por mensagens de erros, mas tu entendes a ideia*/
  fgets(mes1, 5, stdin);
  printf("Insira o mes 2: \n");
  fgets(mes2, 5, stdin);
  n = no_months(mes1, mes2) - 1;
  if(n < 0)
  {
    n = 0;
  }
  printf("Existem %d meses entre eles.\n", n);
  return 0;
}
