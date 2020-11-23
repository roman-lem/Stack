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
#include <ctype.h>
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
Push(n) \n \
Pop      \n \
Dump     \n \
Exit     \n:");
	}

	char command[100];
  scanf("%s", command);

  while(strcmp(command, "Exit") != 0){

  	if(strcmp(command, "Dump") == 0){

  		StackDump(&stack);
  	}

  	else if(strcmp(command, "Pop") == 0){

  		int number = 0;

  		if(StackPop(&stack, &number) == 0){

  			printf(">>> %d\n", number);  			
  		}

  	}                       
  													//12345
  	else if(strncmp(command, "Push(", 5) == 0){

  		int number = 0;
  		int i;
  		
  		if(isdigit(command[5])){

  			for(i = 5; isdigit(command[i]); i++){

  				number = number * 10 + (command[i] - '0');
  			}
  		}

  		if(strcmp((command + i), ")") == 0){

  			StackPush(&stack, number);
  		}
  	}

  	else{

  		printf(">>> Try again\n");
  	}

  	printf(":");
  	scanf("%s", command);
  }

  printf("End of program\n");

	return 0;
}

//==========================================================================