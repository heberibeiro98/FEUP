#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "sfun.c"

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
  targ_t args[3], *aux;
  sscanf(argv[1], "%d", &nvezes);
  for(i = 0; i < 3; i++)
  {
    aux = &args[i];
    aux->cnt = &counter;
    aux->n = nvezes;
    aux->id = i;
    pthread_create(&(thread[i]), 0, sfun, aux);
  }
  for(i = 0; i < 3; i++)
  {
    pthread_join(thread[i], 0);
  }
  pthread_mutex_destroy(&mutex);
  printf("Resultado obtido: %ld - Resultado esperado - %d\n", counter, 3*nvezes);
  return 0;
}
