#include "stdio.h"

int main()
{
  int a[10];
  printf("Size of array a[10]: %ld\n", sizeof(a));
  struct complex
  {
    double re, im;
  }z;
  printf("Size of structure complex: %ld\n", sizeof(z));
  char *hello = "Hello, World!";
  printf("Size of string *hello: %ld\n", sizeof(hello));
}
