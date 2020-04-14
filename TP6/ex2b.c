#include "unsafestack.h"
#include "stdio.h"
#include "stdlib.h"

int main()
{
  stack *test;
  elemento el;
  el.str = "Elemento: ";
  int tamanho, i;
  printf("Qual o tamanho da stack?\n");
  scanf("%d", &tamanho);
  printf("\n");
  test = init(tamanho);
  for(i = 0; i < tamanho; i++)
  {
    el.n = i;
    push(test,&el);
  }
  show(test);
  if(push(test,&el) == 0)
  {
    printf("Stack is full!\n");
  }
  pop(test);
  pop(test);
  show(test);
  destroy(test);
  return 0;
}
