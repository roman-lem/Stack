
#ifndef STACK

#define STACK

#define POISON_NUMBER -666

struct stack{

	int capacity;

	int top;

	int* buf;
};

typedef struct stack stack_t;

#endif

//==========================================================================