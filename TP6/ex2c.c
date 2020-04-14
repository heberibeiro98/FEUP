#include "stdio.h"
#include "stdlib.h"
#include "unsafestack.h"
#include <pthread.h>

typedef struct
{
  stack *stack;
  elemento *el;
  int cont;
}threadargs;

void *threadpush(void *arg)
{
  threadargs *aux = (threadargs *)arg;
  int i;
  for(i = 0; i < aux->cont; i++)
  {
    aux->el->n = i;
    push(aux->stack, aux->el);
  }
  return 0;
}

void *threadpop(void *arg)
{
  threadargs *aux = (threadargs *)arg;
  int i;
  for(i = 0; i < aux->cont; i++)
  {
    pop(aux->stack);
  }
  return 0;
}

int main(int argc, char *argv[])
{
  stack *test;
  elemento elem;
  pthread_t threads[4];
  int tamanho, i, n;
  printf("Qual o tamanho da stack?\n");
  scanf("%d", &tamanho);
  threadargs t[2];
  test = init(tamanho);
  threadargs *aux;
  elem.str = "Elemento: ";
  aux = &t[0];
  aux->stack = test;
  aux->el = &elem;
  aux->cont = tamanho + 1;
  pthread_create(&(threads[0]), 0, threadpush, aux);
  aux = &t[1];
  aux->stack = test;
  aux->el = &elem;
  aux->cont = tamanho - 9;
  pthread_create(&(threads[1]), 0, threadpop, aux);
  for(i = 0; i < 2; i++)
  {
    pthread_join(threads[i], 0);
  }
 show(test);
 destroy(test);
 return 0;
}
