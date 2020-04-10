#ifndef UNSAFESTACK_H
#define UNSAFESTACK_H

typedef struct stack_el
{
  char *str;              /* String to be printed in show() */
	int n;                  /* Integer to be printed in show() */
	struct stack_el *next;  /* Link to next stack element */
  struct stack_el *first;
}elemento;

void begin(elemento *arg);
void push(elemento *arg, int i, char *s);
void pop(elemento *arg);
void show(elemento *arg);
int counter(elemento *arg);

#endif
