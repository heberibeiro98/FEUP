#include <pthread.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct                                //Da muito trabalho comentar isto em condiçoes
{                                             //se nao perceberem o funcionamento do programa digam-me
  int *arr;                                   //e eu explico
  int partit;
  int remainingpartit;
  int indice;
  int flag;
} tamanhos;

void* ArrayInitializer(void* arg)
{
  tamanhos *s = (tamanhos*)arg;
  int i;
  if(s->flag == 1)
  {
    for(i = s->indice; i < s->remainingpartit; i++)
    {
      s->arr[i] = i;
    }
  }
  for(i = s->indice; i < s->partit; i++)
  {
    s->arr[i] = i;
  }
}

int main(int argc, char *argv[])
{
  if(argc < 3)
  {
    printf("Not enough arguments!\n");
    return -1;
  }
  int tamanhoarray, numerothreads, tamanhopartit, i, idc = 0, flg = 0;
  tamanhos *t;
  sscanf(argv[1], "%d", &tamanhoarray);
  sscanf(argv[2], "%d", &numerothreads);
  int *array = malloc(sizeof(int)*tamanhoarray);
  pthread_t *threads = malloc(sizeof(pthread_t)*numerothreads);
  if(array == NULL || threads == NULL)
  {
    printf("Error allocating memory!\n");
    return -1;
  }
  tamanhopartit = tamanhoarray / numerothreads;
  if(tamanhopartit == 0)
  {
    numerothreads = tamanhoarray;
    tamanhopartit = 1;
  }
  if((tamanhopartit * numerothreads) < tamanhoarray)
  {
    int aux;
    aux = tamanhoarray - ((numerothreads - 1)*tamanhopartit);
    t->remainingpartit = aux;
    flg = 1;
  }
  else
  {
    int aux;
    aux = (tamanhopartit * numerothreads) - tamanhoarray;
    t->remainingpartit = aux;
    flg = 1;
  }
  t->arr = array;
  t->partit = tamanhoarray;
  for(i = 0; i < numerothreads; i++)
  {
    t->indice = idc;
    pthread_create(&(threads[i]), 0, ArrayInitializer, t);
    if(i == (numerothreads - 1) || (flg == 1))
    {
      t->flag = flg;
    }
  }
  for(i = 0; i < numerothreads; i++)
  {
    pthread_join(threads[i], 0);
  }
  printf("Array: \n");
  for(i = 0; i < tamanhoarray; i++)
  {
    printf("%d ", array[i]);
  }
  printf("\n");
  return 0;
}
