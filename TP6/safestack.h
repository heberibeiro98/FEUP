#ifndef UNSAFESTACK_H
#define UNSAFESTACK_H

typedef struct stack_el
{  // element of a stack
	char *str;
	int n;
}elemento;

typedef struct stack
{    // a stack
	elemento **sp;  // pointer to array to store stack elements
	int size;             // size of the array
	int top;			  // array index of the element at the top of the stack,
	int len;			  //  i.e. the first free position on the stack -- initially 0
}stack;

stack *init(int size);	// initialize stack. Returns pointer to
								//  to initialized stack of desired size
int push(stack *stack, elemento *el); // returns 0 if the stack is full, and 1 otherwise
elemento *pop(stack *stack); // returns NULL if the stack is empty
void show(stack *stack);
void destroy(stack *stack);	// frees all data structures allocated

#endif
