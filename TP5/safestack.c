#include "unsafestack.h"
#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void begin(elemento *arg)
{
  arg->first = 0;
}

void push(elemento *arg, int i, char *s)
{
  elemento *elem = malloc(sizeof(elemento));
  pthread_mutex_lock(&mutex);
  elem->next = arg->first;
  arg->first = elem;
  pthread_mutex_unlock(&mutex);
  elem->n = i;
  elem->str = s;
}

void pop(elemento *arg)
{
  elemento *elem;
  if(!arg->first)
  {
    return;
  }
  pthread_mutex_lock(&mutex);
  elem = arg->first;
  arg->first = elem->next;
  pthread_mutex_unlock(&mutex);
  free(elem);
}

void show(elemento *arg)
{
  elemento *elem;
  pthread_mutex_lock(&mutex);
  elem = arg->first;
  while(elem)
  {
    printf("%s %d\n", elem->str, elem->n);
    elem = elem->next;
  }
  pthread_mutex_unlock(&mutex);
  printf("\n");
}

int counter(elemento *arg)
{
  elemento *elem;
  int cont = 0;
  pthread_mutex_lock(&mutex);
  elem = arg->first;
  while(elem)
  {
    cont++;
    elem = elem->next;
  }
  pthread_mutex_unlock(&mutex);
  return cont;
}
