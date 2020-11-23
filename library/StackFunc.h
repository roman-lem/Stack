//#define DEBUG 1

#include "StackStruct.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//==========================================================================

/**
	*	@brief This function prints all info about stack
	*
	*	@param stack Pointer on stack
	*/

void StackDump(const stack_t* stack);

/**
	*	@brief This function checks does stack is correct
	*
	*	@param stack Pointer on stack
	*
	*	@return Code of error. If there are no errors, return 0
	*/

int StackOK(const stack_t* stack);

/**
	*	@brief This function initializes a stack
	*
	*	@param stack Pointer on stack
	*
	*	@param capacity Number of elements, that we need
	*
	*	@return 0, or code of error like StackOK()
	*/

int StackConstruct(stack_t* stack, int capacity);

/**
	*	@brief This function pushes element into stack
	*
	*	@param stack Pointer on stack
	*
	* @param element Element that should be pushed
	*
	*	@return If stack is full return -1, else return 0, or code of error like StackOK()
	*/

int StackPush(stack_t* stack, int element);

/**
	*	@brief This function pops element from stack
	*
	*	@param stack Pointer on stack
	*
	* @param element Element that should be poped
	*
	*	@return If stack is empty return -1, else return 0, or code of error like StackOK()
	*/

int StackPop(stack_t* stack, int* element);

/**
	*	@brief This function destructs a stack
	*
	*	@param stack Pointer on stack
	*
	*	@return 0, or code of error like StackOK()
	*/

int StackDestruct(stack_t* stack);

//==========================================================================