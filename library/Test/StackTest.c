#include "StackTest.h"

#define MAKE_STACK_RIGHT                     \
  stack.capacity = 5;                        \
  stack.top = 0;                             \
  stack.buf = (int*) calloc(5, sizeof(int)); \
                                             \
  for(i = 0; i < 5; i++){                    \
                                             \
    *(stack.buf + i) = POISON_NUMBER;        \
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

  printf("<<<TEST#1 &stack = NULL>>>\n");

  if(StackOK(NULL) == 1){

    $g 
    printf("OK\n");
    $d
  }

  else{

    $r
    printf("ERROR\n");
    $d
  }

  stack_t stack;
  int i;
  
  //------------------

  MAKE_STACK_RIGHT

  stack.capacity = 0;

  printf("<<<TEST#2 capacity = 0>>>\n");

  if(StackOK(&stack) == 2){

    $g 
    printf("OK\n");
    $d
  }

  else{

    $r
    printf("ERROR\n");
    $d
  }

  //------------------

  MAKE_STACK_RIGHT

  stack.top = 6;

  printf("<<<TEST#3 top > capacity>>>\n");

  if(StackOK(&stack) == 3){

    $g 
    printf("OK\n");
    $d
  }

  else{

    $r
    printf("ERROR\n");
    $d
  }

  //------------------

  MAKE_STACK_RIGHT

  stack.top = -1;

  printf("<<<TEST#4 top < 0>>>\n");

  if(StackOK(&stack) == 4){

    $g 
    printf("OK\n");
    $d
  }

  else{

    $r
    printf("ERROR\n");
    $d
  }

  //------------------

  MAKE_STACK_RIGHT

  stack.buf = NULL;

  printf("<<<TEST#5 buf = NULL>>>\n");

  if(StackOK(&stack) == 5){

    $g 
    printf("OK\n");
    $d
  }

  else{

    $r
    printf("ERROR\n");
    $d
  }

  //------------------

  MAKE_STACK_RIGHT

  stack.buf[4] = 0;

  printf("<<<TEST#6 stack isn't poisioned>>>\n");

  if(StackOK(&stack) == 6){

    $g 
    printf("OK\n");
    $d
  }

  else{

    $r
    printf("ERROR\n");
    $d
  }

  //------------------

  MAKE_STACK_RIGHT

  printf("<<<TEST#7 stack is right>>>\n");

  if(StackOK(&stack) == 0){

    $g 
    printf("OK\n");
    $d
  }

  else{

    $r
    printf("ERROR\n");
    $d
  }

  return;
}

//--------------------------------------------------------------------------

void T_StackConstruct(){

  printf("<<<TEST#1 &stack = NULL>>>\n");

  if(StackConstruct(NULL, 10) == -1){

    $g 
    printf("OK\n");
    $d
  }

  else{

    $r
    printf("ERROR\n");
    $d
  }

  stack_t stack;
  
  //------------------

  printf("<<<TEST#2 capacity = 0>>>\n");

  if(StackConstruct(&stack, 0) == -2){

    $g 
    printf("OK\n");
    $d
  }

  else{

    $r
    printf("ERROR\n");
    $d
  }

  printf("<<<TEST#3 all is right>>>\n");

  if(StackConstruct(&stack, 10) == 0){

    $g 
    printf("OK\n");
    $d
  }

  else{

    $r
    printf("ERROR\n");
    $d
  }

  return;
}

//--------------------------------------------------------------------------

void T_StackPush(){

  printf("   <==Test StackOK()==>\n"); // This function use StackOK() to check that stack is right. Then this test use T_StackOK()

  T_StackOK();

  printf("===========================\n");

  printf("<<<Test#1 top = capacity>>>\n");

  stack_t stack;
  int i;
  
  //------------------

  MAKE_STACK_RIGHT

  stack.top = stack.capacity;

  if(StackPush(&stack, 123) == -1){

    $g 
    printf("OK\n");
    $d
  }

  else{

    $r
    printf("ERROR\n");
    $d
  }

  //------------------

  MAKE_STACK_RIGHT

  printf("<<<TEST#2 stack is right>>>\n");

  if(StackPush(&stack, 123) == 0){

    $g 
    printf("OK\n");
    $d
  }

  else{

    $r
    printf("ERROR\n");
    $d
  }

  return;
}

//--------------------------------------------------------------------------

void T_StackPop(){

  printf("   <==Test StackOK()==>\n"); // This function use StackOK() to check that stack is right. Then this test use T_StackOK()

  T_StackOK();

  printf("===========================\n");

  printf("<<<Test#1 top = 0>>>\n");

  stack_t stack;
  int i;
  int element;
  
  //------------------

  MAKE_STACK_RIGHT

  stack.top = 0;

  if(StackPop(&stack, &element) == -1){

    $g 
    printf("OK\n");
    $d
  }

  else{

    $r
    printf("ERROR\n");
    $d
  }

  //------------------

  MAKE_STACK_RIGHT

  stack.top = 1;

  printf("<<<TEST#2 stack is right>>>\n");

  if(StackPop(&stack, &element) == 0){

    $g 
    printf("OK\n");
    $d
  }

  else{

    $r
    printf("ERROR\n");
    $d
  }

  return;
}

//--------------------------------------------------------------------------

void T_StackDestruct(){

  printf("   <==Test StackOK()==>\n"); // This function use StackOK() to check that stack is right. Then this test use T_StackOK()

  T_StackOK();

  printf("===========================\n");

  stack_t stack;
  int i;
  
  //------------------

  MAKE_STACK_RIGHT

  printf("<<<TEST#1 stack is right>>>\n");

  if(StackDestruct(&stack) == 0){

    $g 
    printf("OK\n");
    $d
  }

  else{

    $r
    printf("ERROR\n");
    $d
  }
}

//==========================================================================

#undef MAKE_STACK_RIGHT