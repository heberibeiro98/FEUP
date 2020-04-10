#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *inc(void *arg)
{
  int a = *(int*)arg;
  int i;
  for(i = 0; i < a; i++)
  {
    pthread_mutex_lock(&mutex);
    counter++;
    pthread_mutex_unlock(&mutex);
  }
  return 0;
}

int main(int argc, char *argv[])
{
  if(argc < 2)
  {
    printf("Not enough arguments!\n");
    return -1;
  }
  int nvezes, i;
  pthread_t thread[3];
  sscanf(argv[1], "%d", &nvezes);
  for(i = 0; i < 3; i++)
  {
    pthread_create(&(thread[i]), 0, inc, &nvezes);
  }
  for(i = 0; i < 3; i++)
  {
    pthread_join(thread[i], 0);
  }
  pthread_mutex_destroy(&mutex);
  printf("Resultado obtido: %d - Resultado esperado - %d\n", counter, 3*nvezes);
}
