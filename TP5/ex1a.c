#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "tfun.c"

int main(int argc, char *argv[])
{
  if(argc < 2)
  {
    printf("Not enough arguments!\n");
    return -1;
  }
  long counter = 0;
  int nvezes, i;
  pthread_t thread[3];
  targ_t argumentos[3];
  sscanf(argv[1], "%d", &nvezes);
  for(i = 0; i < 3; i++)
  {
    (argumentos+i)->cnt = &counter;
    (argumentos+i)->n = nvezes;
    (argumentos+i)->id = i;
    pthread_create(&(thread[i]), 0, tfun, &(argumentos[i]));
  }
  for(i = 0; i < 3; i++)
  {
    pthread_join(thread[i], 0);
  }
  printf("Resultado obtido: %ld - Resultado esperado - %d\n", counter, 3*nvezes);
  return 0;
}
