#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//==========================================================================

#define POISON_NUMBER -666

#define CANARY_NUMBER 0xABADBABE5AFEF00D

#define CAT(x, y) x##_##y
#define TEMPLATE(x, y) CAT(x, y)

struct TEMPLATE(Stack, TYPE){

	unsigned long long canary1;

	int capacity;

	int top;

	TYPE *buf;

	unsigned int hash;
};

//==========================================================================

/**
	*	@brief This function prints all info about stack
	*
	*	@param stack Pointer on stack
	*/

void TEMPLATE(StackDump, TYPE)(const struct TEMPLATE(Stack, TYPE)* stack);

/**
	*	@brief This function checks does stack is correct
	*
	*	@param stack Pointer on stack
	*
	*	@return Code of error. If there are no errors, return 0
	*/

int TEMPLATE(StackOK, TYPE)(const struct TEMPLATE(Stack, TYPE)* stack);

/**
	*	@brief This function initializes a stack
	*
	*	@param stack Pointer on stack
	*
	*	@param capacity Number of elements, that we need
	*
	*	@return 0, or code of error
	*/

int TEMPLATE(StackConstruct, TYPE)(struct TEMPLATE(Stack, TYPE)* stack, int capacity);

/**
	*	@brief This function pushes element into stack
	*
	*	@param stack Pointer on stack
	*
	* @param element Element that should be pushed
	*
	*	@return If stack is full return -1, else return 0, or code of error
	*/

int TEMPLATE(StackPush, TYPE)(struct TEMPLATE(Stack, TYPE)* stack, TYPE element);

/**
	*	@brief This function pops element from stack
	*
	*	@param stack Pointer on stack
	*
	* @param element Element that should be poped
	*
	*	@return If stack is empty return -1, else return 0, or code of error
	*/

int TEMPLATE(StackPop, TYPE)(struct TEMPLATE(Stack, TYPE)* stack, TYPE* element);

/**
	*	@brief This function destructs a stack
	*
	*	@param stack Pointer on stack
	*
	*	@return 0, or code of error
	*/

int TEMPLATE(StackDestruct, TYPE)(struct TEMPLATE(Stack, TYPE)* stack);

/**
	*	@brief this function calculate stack hash
	*
	*	@param key Pointer on stack
	*
	* @return hash
	*/

unsigned int StackHash(const void* key);

/**
	*	@brief This function calculate bufer hash
	*
	* @param key Pointer on buf
	*
	*	@param len Length of buf
	*
	*	@return hash
	*/

unsigned int BufHash(const void* key, int len);

//==========================================================================

void TEMPLATE(StackDump, TYPE) (const struct TEMPLATE(Stack, TYPE)* stack){

#ifdef DEBUG

	assert(stack != NULL);

#endif

	if(stack == NULL){

		printf("&stack == NULL\n");

		return;
	}

	switch(TEMPLATE(StackOK, TYPE)(stack)){

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

		case 7:
			printf("stack (%s) [%p]{\n", "7 <canary1 != CANARY_NUMBER>", &stack);
			break;

		case 8:
			printf("stack (%s) [%p]{\n", "8 <wrong hash>", &stack);
			break;

		case 9:
			printf("stack (%s) [%p]{\n", "9 <left buf canary was damaged>", &stack);
			break;

		case 10:
			printf("stack (%s) [%p]{\n", "10 <right buf canary was damaged>", &stack);
			break;
	}

	printf("\tcapacity = %d\n", stack->capacity);

	printf("\t     top = %d\n", stack->top);

	printf("\t    hash = %u\n", stack->hash);

	printf("\tbuf [%p]{\n", stack->buf);

	int i;
	for(i = 0; i < stack->capacity; i++){

		if(i < stack->top){

			printf("\t\t*[%d]: ", i);
			TEMPLATE(Print, TYPE) (stack->buf[i + sizeof(CANARY_NUMBER) / sizeof(TYPE)]);
			printf("\n");
		}

		else if(stack->buf[i + sizeof(CANARY_NUMBER) / sizeof(TYPE)] == POISON_NUMBER){

			printf("\t\t![%d]: ", i);
			TEMPLATE(Print, TYPE) (stack->buf[i + sizeof(CANARY_NUMBER) / sizeof(TYPE)]);
			printf(" (POISON)\n");
		}

		else{

			printf("\t\t![%d]: ", i);
			TEMPLATE(Print, TYPE) (stack->buf[i + sizeof(CANARY_NUMBER) / sizeof(TYPE)]);
			printf("\n");
		}
	}
	printf("\t}\n");

	printf("}\n");

	return;
}

//--------------------------------------------------------------------------

int TEMPLATE(StackOK, TYPE)(const struct TEMPLATE(Stack, TYPE)* stack){

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

	if(stack->canary1 != CANARY_NUMBER)
		return 7;

	if(StackHash(stack) != stack->hash)
		return 8;

	if(( (unsigned long long*) stack->buf )[0] != CANARY_NUMBER)
		return 9;

	if(( (unsigned long long*) (stack->buf + sizeof(CANARY_NUMBER) / sizeof(TYPE) + stack->capacity) )[0] != CANARY_NUMBER)
		return 10;

	int i;
	for(i = stack->top + 1; i < stack->capacity; i++){

		if(stack->buf[i + sizeof(CANARY_NUMBER) / sizeof(TYPE)] != POISON_NUMBER)
			return 6;
	}

	return 0;
}

//--------------------------------------------------------------------------

int TEMPLATE(StackConstruct, TYPE)(struct TEMPLATE(Stack, TYPE)* stack, int capacity){

#ifdef DEBUG

	assert(stack != NULL);

	assert(capacity > 0);

#endif

	if(stack == NULL)
		return -1;

	if(capacity == 0)
		return -2;

	stack->canary1 = CANARY_NUMBER;

	stack->capacity = capacity;

	stack->top = 0;

	stack->buf = (TYPE*) calloc(capacity * sizeof(TYPE) + 2 * sizeof(CANARY_NUMBER), 1);

	( (unsigned long long*)stack->buf )[0] = CANARY_NUMBER;

	stack->buf += capacity + sizeof(CANARY_NUMBER) / sizeof(TYPE);

	( (unsigned long long*)stack->buf )[0] = CANARY_NUMBER;

	stack->buf -= capacity;

	int i;
	for(i = 0; i < capacity; i++){

		*(stack->buf + i) = POISON_NUMBER;
	}

	stack->buf -= sizeof(CANARY_NUMBER) / sizeof(TYPE);

	stack->hash = StackHash(stack);

	return TEMPLATE(StackOK, TYPE)(stack);
}

//--------------------------------------------------------------------------

int TEMPLATE(StackPush, TYPE)(struct TEMPLATE(Stack, TYPE)* stack, int element){

	if(TEMPLATE(StackOK, TYPE)(stack) != 0)
	  return TEMPLATE(StackOK, TYPE)(stack);

#ifdef DEBUG

	assert(stack->top < stack->capacity);

#endif

	if(stack->top == stack->capacity)
		return -1;

	stack->top++;

	stack->buf = (TYPE*) ((unsigned long long*) stack->buf + 1);

	*(stack->buf + stack->top - 1) = element;

	stack->buf = (TYPE*) ((unsigned long long*) stack->buf - 1);

	stack->hash = StackHash(stack);

	if(TEMPLATE(StackOK, TYPE)(stack) == 0){

		return 0;
	}

	else{

		return TEMPLATE(StackOK, TYPE)(stack);
	}
}

//--------------------------------------------------------------------------

int TEMPLATE(StackPop, TYPE)(struct TEMPLATE(Stack, TYPE)* stack, TYPE* element){

	assert(element);

	if(TEMPLATE(StackOK, TYPE)(stack) != 0)
	  return TEMPLATE(StackOK, TYPE)(stack);

#ifdef DEBUG

	assert(stack->top > 0);

#endif

	if(stack->top <= 0)
		return -1;

	stack->buf = (TYPE*) ((unsigned long long*) stack->buf + 1);

	*element = *(stack->buf + stack->top - 1);

	*(stack->buf + stack->top - 1) = POISON_NUMBER;

	stack->top--;

	stack->buf = (TYPE*) ((unsigned long long*) stack->buf - 1);

	stack->hash = StackHash(stack);

	if(TEMPLATE(StackOK, TYPE)(stack) == 0){

		return 0;
	}

	else{

		return TEMPLATE(StackOK, TYPE)(stack);
	}
}

//--------------------------------------------------------------------------

int TEMPLATE(StackDestruct, TYPE)(struct TEMPLATE(Stack, TYPE)* stack){

	if(TEMPLATE(StackOK, TYPE)(stack) != 0)
	  return TEMPLATE(StackOK, TYPE)(stack);

	free(stack->buf);

	stack->top = 0;

	stack->capacity = 0;

	return 0;
}

//--------------------------------------------------------------------------

unsigned int BufHash(const void* key, int len){

#ifdef DEBUG

	assert(key != NULL);

#endif

	if(key == NULL)
		return 0;

	char* ptr = (char*) key;
	unsigned int hash;
	int i;

	for(hash = i = 0; i < len; i++){

		hash += ptr[i];

		hash += (hash << 10);

		hash ^= (hash >> 6);          // "^" it is XOR
	}

	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

return hash;	
}

//--------------------------------------------------------------------------

unsigned int StackHash(const void* key){

#ifdef DEBUG

	assert(key != NULL);

#endif

	if(key == NULL)
		return 0;

	char* ptr = (char*) key;
	unsigned int hash;
	int i;

	for(hash = i = 0; &ptr[i] != (char*) &(((struct TEMPLATE(Stack, TYPE)*) key)->buf); i++){

		hash += ptr[i];

		hash += (hash << 10);

		hash ^= (hash >> 6);          // "^" it is XOR
	}

	struct TEMPLATE(Stack, TYPE) *ptr2 = (struct TEMPLATE(Stack, TYPE)*) key;

	hash += BufHash(ptr2->buf, ptr2->capacity + 2 * sizeof(CANARY_NUMBER));

	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	return hash;
}