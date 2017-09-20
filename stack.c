#if defined(__linux) || defined(__APPLE__)

#include <stdio.h>
#include <stdbool.h>

#define STACK_EMPTY -1
#define STACK_SIZE  10
#define STACK_LIMIT STACK_SIZE

typedef int element_t;

struct stack__s
{
	element_t stack_vector[STACK_SIZE];
	element_t stack_top;
};

__attribute__((noinline)) static void stack_initialize (struct stack__s *);
__attribute__((noinline)) static _Bool stack_empty (struct stack__s *);
__attribute__((noinline)) static _Bool stack_push (struct stack__s *, element_t);
__attribute__((noinline)) static _Bool stack_pop (struct stack__s *);
__attribute__((noinline)) static element_t stack_get_top (struct stack__s *);

int main (int argc, char *argv[], char *envp[])
{
	struct stack__s stack;
	stack_initialize (&stack);
	
	printf ("Stack empty: %d\n", stack_empty (&stack));
	
	stack_push (&stack, 0xffff);
	stack_push (&stack, 0xdffd);
	stack_push (&stack, 0xdbfd);
	stack_push (&stack, 0xcffd);
	stack_push (&stack, 0xebbf);
	stack_push (&stack, 0x64bd);
	stack_push (&stack, 0xafff);
	stack_push (&stack, 0xfdff);
	stack_push (&stack, 0xcccd);
	
	printf ("Stack empty: %d\n", stack_empty (&stack));
	printf ("Stack top: %#x - %d\n", stack_get_top (&stack), stack_get_top(&stack));
	
	for (int pop = 0; pop < STACK_LIMIT; pop++)
	{
		stack_pop (&stack);
	}
	
	printf ("Stack empty: %d\n", stack_empty (&stack));
	
	return 0;
}

void stack_initialize (struct stack__s *stack)
{
	stack->stack_top = STACK_EMPTY;
}

_Bool stack_empty (struct stack__s *stack)
{
	return stack->stack_top == STACK_EMPTY;
}

_Bool stack_push (struct stack__s *stack, element_t new_element)
{
	if (stack->stack_top == STACK_LIMIT)
	{
		return false;
	}
	
	stack->stack_vector[++stack->stack_top] = new_element;
	return true;
}

_Bool stack_pop (struct stack__s *stack)
{
	if (stack_empty (stack))
	{
		return false;
	}
	
	stack->stack_top--;
	return true;
}

element_t stack_get_top (struct stack__s *stack)
{
	if (stack_empty (stack))
	{
		return STACK_EMPTY;
	}
	
	return stack->stack_vector[stack->stack_top];
}

#else
	#error "This program run on linux or apple only"
#endif
