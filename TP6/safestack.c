#include "unsafestack.h"
#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

stack *init(int size)
{
  stack *newstack;
  newstack = malloc(sizeof(stack));
  newstack->sp = malloc(size*sizeof(elemento*));
  for(int i = 0; i < size; i++)
  {
    newstack->sp[i] = malloc(sizeof(elemento));
  }
  newstack->size = size;
  newstack->top = 0;
  newstack->len = -1;
  return newstack;
}

int push(stack *stack, elemento *el)
{
  int space = 0;
  stack->len = stack->len + 1;
  if(stack->len < stack->size)
  {
    stack->top = stack->len;
    stack->sp[stack->top]->str = el->str;
    stack->sp[stack->top]->n = el->n;
  }
  else
  {
    while(space == 0)
    {
      pthread_mutex_lock(&mutex);
      if(stack->len < stack->size)
      {
        stack->top = stack->len;
        stack->sp[stack->top]->str = el->str;
        stack->sp[stack->top]->n = el->n;
        space = 1;
      }
      pthread_mutex_unlock(&mutex);
    }
  }
  return 1;
}

elemento *pop(stack *stack)
{
  int el = 0;
  elemento *point;
  if(stack->len > 0)
  {
    point = stack->sp[stack->len];
    stack->top = stack->len - 1;
    stack->len = stack->len - 1;
  }
  else
  {
    while(el == 0)
    {
      pthread_mutex_lock(&mutex);
      if(stack->len > 0)
      {
        point = stack->sp[stack->len];
        stack->top = stack->len - 1;
        stack->len = stack->len - 1;
        el = 1;
      }
      pthread_mutex_unlock(&mutex);
    }
  }
  return point;
}

void show(stack *stack)
{
  pthread_mutex_lock(&mutex);
  for(int i = stack->top; i >= 0 ; i--)
  {
    printf("%s %d\n", stack->sp[i]->str, stack->sp[i]->n);
  }
  pthread_mutex_unlock(&mutex);
  printf("\n");
}

void destroy(stack *stack)
{
  pthread_mutex_lock(&mutex);
  for(int i = 0; i < stack->size; i++)
  {
    free(stack->sp[i]);
  }
  free(stack->sp);
  free(stack);
  pthread_mutex_unlock(&mutex);
}
