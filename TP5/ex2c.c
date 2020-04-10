#include "stdio.h"
#include "stdlib.h"
#include "unsafestack.h"
#include <pthread.h>

typedef struct
{
  elemento *el;
  char *str;
  char n;
  int cont;
}threadargs;

void *threadpush(void *arg)
{
  threadargs *aux = (threadargs *)arg;
  int i;
  for(i = 0; i < aux->cont; i++)
  {
    push(aux->el, aux->n, aux->str);
  }
  return 0;
}

void *threadpop(void *arg)
{
  threadargs *aux = (threadargs *)arg;
  int i;
  for(i = 0; i < aux->cont; i++)
  {
    pop(aux->el);
  }
  return 0;
}

int main(int argc, char *argv[])
{
  if(argc < 2)
  {
    printf("Not enough arguments!\n);
    return -1;
  }
  elemento elem;
  pthread_t threads[4];
  int nvezes, i, n, defice;
  sscanf(argv[1], "%d", &nvezes);
  threadargs t[4];
  for(i = 0; i < 4; i++)
  {
    threadargs *aux = &t[i];
    aux->el = &elem;
    aux->str = "Thread number: ";
    aux->n = i;
    aux->cont = nvezes;
    pthread_create(&(threads[i]), 0, threadpush, aux);
  }
  for(i = 0; i < 4; i++)
  {
    pthread_join(threads[i], 0);
  }
  show(&elem);
  n = counter(&elem);
  printf("Elements added in the stack: %d - Expect number of elements: %d\n", n, nvezes*4);
  defice = n/4;
  for(i = 0; i < 4; i++)
  {
    threadargs *aux = &t[i];
    aux->el = &elem;
    aux->cont = defice;
    pthread_create(&(threads[i]), 0, threadpop, aux);
  }
  for(i = 0; i < 4; i++)
  {
    pthread_join(threads[i], 0);
  }
  printf("Elements still in the stack: %d - Expected number of elements: %d\n", counter(&elem), (n - defice*4));
}
