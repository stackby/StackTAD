#if defined(__linux) || defined(__APPLE__)

#include <stdio.h>
#include <stdbool.h>

#define STACKSIZ 10
#define STACKTOP -1

struct stack__t
{
	int stackmem [STACKSIZ];
	int stacktop;
};

__attribute__((noinline)) static void setstacktop (struct stack__t *);
__attribute__((noinline)) static _Bool stackempty (struct stack__t *);
__attribute__((noinline)) static void stackpush (struct stack__t *, int);
__attribute__((noinline)) static void stackpop (struct stack__t *);
__attribute__((noinline)) static int stackgetop (struct stack__t *);
__attribute__((noinline)) static void stackaddr (struct stack__t *);

int main (int argc, char *argv[])
{
	struct stack__t stack_s;
	setstacktop (&stack_s);
	
		for (int push = 0; push < STACKSIZ; push++)
		{
			stackpush (&stack_s, push);
			printf ("stack[%d] = %d", push, stackgetop (&stack_s));
			stackaddr (&stack_s);
			putc ('\n', stdout);
		}
		
		putc ('\n', stdout);
		
		for (int pop = -1; pop < STACKSIZ; pop++)
		{
			stackpop (&stack_s);
		}
		
		printf ("%d\n", stackgetop (&stack_s));
		
	return 0;
}

void setstacktop (struct stack__t *stack_s)
{
	stack_s->stacktop = STACKTOP;
}

_Bool stackempty (struct stack__t *stack_s)
{
	return (stack_s->stacktop == STACKTOP);
}

void stackpush (struct stack__t *stack_s, int element)
{
	if (stack_s->stacktop == STACKSIZ)
		fprintf (stderr, "%s", "\nStack full\n");
	else stack_s->stackmem[++stack_s->stacktop] = element;
}

void stackpop (struct stack__t *stack_s)
{
	if (stackempty (stack_s)) 
		fprintf (stderr, "%s", "\nStack is empty\n");
	else stack_s->stacktop--;
}

int stackgetop (struct stack__t *stack_s)
{
	if (stackempty (stack_s))
		return STACKTOP;
	else return stack_s->stackmem[stack_s->stacktop];   
}

void stackaddr (struct stack__t *stack_s)
{
	printf (" -> %p", &stack_s->stackmem[stack_s->stacktop]);
}

#else
	#error "This program run on linux or apple only"
#endif
