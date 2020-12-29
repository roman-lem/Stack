#include "Print.h"

#define TYPE int
#include "StackFunc.h"
#undef TYPE

//--------------------------------------------------------------------------

int main(){

	struct Stack_int stack;

	StackConstruct_int(&stack, 5);

	StackPush_int(&stack, 11);

	StackPush_int(&stack, -666);

	StackDump_int(&stack);

	int n;
	StackPop_int(&stack, &n);

	printf("%d\n", n);

	StackDump_int(&stack);

	StackDestruct_int(&stack);

	return 0;
}

//==========================================================================