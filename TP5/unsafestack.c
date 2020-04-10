#include "unsafestack.h"
#include "stdio.h"
#include "stdlib.h"

void begin(elemento *arg)
{
  arg->first = 0;
}

void push(elemento *arg, int i, char *s)
{
  elemento *elem = malloc(sizeof(elemento));
  elem->next = arg->first;
  elem->n = i;
  elem->str = s;
  arg->first = elem;
}

void pop(elemento *arg)
{
  elemento *elem;
  if(!arg->first)
  {
    return;
  }
  elem = arg->first;
  arg->first = elem->next;
  free(elem);
}

void show(elemento *arg)
{
  elemento *elem;
  elem = arg->first;
  while(elem)
  {
    printf("%s %d\n", elem->str, elem->n);
    elem = elem->next;
  }
  printf("\n");
}

int counter(elemento *arg)
{
  elemento *elem;
  int cont = 0;
  elem = arg->first;
  while(elem)
  {
    cont++;
    elem = elem->next;
  }
  return cont;
}
