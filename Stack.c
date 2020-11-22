/**
	*	@mainpage Stack task
	*
	* @author Roman Lem
	*
	* @brief This program is emulating stack
	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./library/source/StackStruct.h"
#include "./library/source/StackFunc.h"

//==========================================================================

int main(){

	stack_t stack = {};
	int cap;

	printf("Let's get started. Enter the capacity of stack:\nn = ");
	scanf("%d", &cap);

	if(StackConstruct(&stack, cap) == 0){

		printf("Stack is ready. Pleas, enter the command :\n \
			      StackPush(n);\n \
			      StackPop();  \n \
			      StackDump(); \n \
			      Exit();      \n:");
	}

	char command[100];
  scanf("%s", command);

  while(strcmp(command, "Exit();") != 0){

  	if(strcmp(command, "StackDump();") == 0){

  		StackDump(&stack);
  	}

  	if(strcmp(command, "StackDump();") == 0){

  		StackDump(&stack);
  	}

  	printf(":");
  	scanf("%s", command);
  }

  printf("End of prog\n");

	return 0;
}

//==========================================================================