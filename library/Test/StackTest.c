#include "StackTest.h"

#define MAKE_STACK_RIGHT \
	stack.capacity = 5;		 \
	stack.top = 0;         \
	stack.buf = (int*) calloc(5, sizeof(int)); \
	\
	for(i = 0; i < 5; i++){\
\
		*(stack.buf + i) = POISON_NUMBER;\
	}

//==========================================================================

void T_StackDump(){

	printf("<<<TEST#1 &stack = NULL>>>\n");

	StackDump(NULL);

	stack_t stack;
	int i;
	
	//------------------

	MAKE_STACK_RIGHT

	stack.capacity = 0;

	printf("<<<TEST#2 capacity = 0>>>\n");

	StackDump(&stack);

	//------------------

	MAKE_STACK_RIGHT

	stack.top = 6;

	printf("<<<TEST#3 top > capacity>>>\n");

	StackDump(&stack);

	//------------------

	MAKE_STACK_RIGHT

	stack.top = -1;

	printf("<<<TEST#4 top < 0>>>\n");

	StackDump(&stack);

	//------------------

	MAKE_STACK_RIGHT

	stack.buf = NULL;

	printf("<<<TEST#5 buf = NULL>>>\n");

	StackDump(&stack);

	//------------------

	MAKE_STACK_RIGHT

	stack.buf[4] = 0;

	printf("<<<TEST#6 stack isn't poisioned>>>\n");

	StackDump(&stack);

	//------------------

	MAKE_STACK_RIGHT

	printf("<<<TEST#7 stack is right>>>\n");

	StackDump(&stack);

	return;
}

//--------------------------------------------------------------------------

void T_StackOK(){



	return 0;
}

//--------------------------------------------------------------------------

int main(int argc, char const *argv[])
{
	
	T_StackDump();

	return 0;
}

//==========================================================================

#undef MAKE_STACK_RIGHT