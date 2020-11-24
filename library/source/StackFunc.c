#include "StackFunc.h"

//==========================================================================

void StackDump(const stack_t* stack){

#ifdef DEBUG

	assert(stack != NULL);

#endif

	if(stack == NULL){

		printf("&stack == NULL\n");

		return;
	}

	switch(StackOK(stack)){

		case 0:
			printf("stack (%s) [%p]{\n", "OK", &stack);
			break;

		case 1:
			printf("stack (%s) [%p]{\n", "1 <&stack == NULL>", &stack);
			break;

		case 2:
			printf("stack (%s) [%p]{\n", "2 <capacity == 0>", &stack);
			break;

		case 3:
			printf("stack (%s) [%p]{\n", "3 <stack overflow>", &stack);
			break;

		case 4:
			printf("stack (%s) [%p]{\n", "4 <top < 0>", &stack);
			break;

		case 5:
			printf("stack (%s) [%p]{\n", "5 <&buf == NULL>", &stack);
			return;
			break;

		case 6:
			printf("stack (%s) [%p]{\n", "6 <stack isn't poisioned>", &stack);
			break;
	}

	printf("\tcapacity = %d\n", stack->capacity);

	printf("\t     top = %d\n", stack->top);

	printf("\tbuf [%p]{\n", stack->buf);

	int i;
	for(i = 0; i < stack->capacity; i++){

		if(i < stack->top){

			printf("\t\t*[%d]: %d\n", i, stack->buf[i]);
		}

		else if(stack->buf[i] == POISON_NUMBER){

			printf("\t\t![%d]: %d (POISON)\n", i, stack->buf[i]);
		}

		else{

			printf("\t\t![%d]: %d\n", i, stack->buf[i]);
		}
	}
	printf("\t}\n");

	printf("}\n");
}

//--------------------------------------------------------------------------

int StackOK(const stack_t* stack){

	if(stack == NULL)
		return 1;

	if(stack->capacity == 0)
		return 2;

	if(stack->top > stack->capacity)
		return 3;

	if(stack->top < 0)
		return 4;

	if(stack->buf == NULL)
		return 5;

	int i;
	for(i = stack->top + 1; i < stack->capacity; i++){

		if(stack->buf[i] != POISON_NUMBER)
			return 6;
	}

	return 0;
}

//--------------------------------------------------------------------------

int StackConstruct(stack_t* stack, int capacity){

#ifdef DEBUG

	assert(stack != NULL);

	assert(capacity > 0);

#endif

	if(stack == NULL)
		return -1;

	if(capacity == 0)
		return -2;

	stack->capacity = capacity;

	stack->top = 0;

	stack->buf = (int*) calloc(capacity, sizeof(int));

	int i;
	for(i = 0; i < capacity; i++){

		*(stack->buf + i) = POISON_NUMBER;
	}

	return StackOK(stack);
}

//--------------------------------------------------------------------------

int StackPush(stack_t* stack, int element){

	if(StackOK(stack) != 0)
	  return StackOK(stack);

#ifdef DEBUG

	assert(stack->top < stack->capacity);

#endif

	if(stack->top == stack->capacity)
		return -1;

	stack->top++;

	*(stack->buf + stack->top - 1) = element;

	if(StackOK(stack) == 0){

		return 0;
	}

	else{

		return StackOK(stack);
	}
}

//--------------------------------------------------------------------------

int StackPop(stack_t* stack, int* element){

	assert(element);

	if(StackOK(stack) != 0)
	  return StackOK(stack);

#ifdef DEBUG

	assert(stack->top > 0);

#endif

	if(stack->top <= 0)
		return -1;

	*element = *(stack->buf + stack->top - 1);

	*(stack->buf + stack->top - 1) = POISON_NUMBER;

	stack->top--;

	if(StackOK(stack) == 0){

		return 0;
	}

	else{

		return StackOK(stack);
	}
}

//--------------------------------------------------------------------------

int StackDestruct(stack_t* stack){

	if(StackOK(stack) != 0)
	  return StackOK(stack);

	free(stack->buf);

	stack->top = 0;

	stack->capacity = 0;

	return 0;
}

//==========================================================================