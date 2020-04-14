#include "unsafestack.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

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
  stack->len = stack->len + 1;
  if(stack->len < stack->size)
  {
    stack->top = stack->len;
    stack->sp[stack->top]->str = el->str;
    stack->sp[stack->top]->n = el->n;
  }
  else
  {
    stack->len = stack->len - 1;
    return 0;
  }
  return 1;
}

elemento *pop(stack *stack)
{
  elemento *point;
  if(stack->len > 0)
  {
    point = stack->sp[stack->len];
    stack->top = stack->len - 1;
    stack->len = stack->len - 1;
  }
  else
  {
    printf("Stack is already empty!\n");
    return NULL;
  }
  return point;
}

void show(stack *stack)
{
  for(int i = stack->top; i >= 0 ; i--)
  {
    printf("%s %d\n", stack->sp[i]->str, stack->sp[i]->n);
  }
  printf("\n");
}

void destroy(stack *stack)
{
  for(int i = 0; i < stack->size; i++)
  {
    free(stack->sp[i]);
  }
  free(stack->sp);
  free(stack);
}
