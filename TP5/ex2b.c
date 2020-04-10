#include "stdio.h"
#include "stdlib.h"
#include "unsafestack.h"

int main()
{
  elemento elem;
  begin(&elem);
  push(&elem, 4, ":)");
  push(&elem, 3, "Tal?");
  push(&elem, 2, "Que");
  push(&elem, 1, "Olá");
  show(&elem);
  pop(&elem);
  show(&elem);
  pop(&elem);
  pop(&elem);
  show(&elem);
  pop(&elem);
  show(&elem);
  pop(&elem);
}
