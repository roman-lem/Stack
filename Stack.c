#include <stdio.h>
#include <stdlib.h>
#include "./library/source/StackStruct.h"
#include "./library/source/StackFunc.h"

//==========================================================================

int main(){

	stack_t stack = {};

	StackConstruct(&stack, 5);

	StackPush(&stack, 10);

	StackPush(&stack, 20);

	StackPush(&stack, 30);

	StackPush(&stack, 40);

	int elem;
	StackPop(&stack, &elem);

	printf("Last element = %d\n", elem);

	StackDump(&stack);

	StackDestruct(&stack);

	return 0;
}

//==========================================================================