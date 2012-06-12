#include <stdio.h>
#include "stack.h"

int main(int argc, int *argv[])
{
  Stack s;
  StackNew(&s, sizeof(int), NULL);

  int i,
      val,
      size = 20, 
      nos[size];

  // populate and print nos
  for (i = 0; i < size; i++) {
    nos[i] = i + 1;
    printf("%4d", nos[i]);
  } printf("\n");

  // push nos in the stack
  for (i = 0; i < size; i++) {
    StackPush(&s, nos+i);
  }

  // pop vals from stack to nos
  for (i = 0; i < size; i++) {
    StackPop(&s, nos+i);
  }

  // print nos
  for (i = 0; i < size; i++) {
    printf("%4d", nos[i]);
  } printf("\n");

  StackDispose(&s);
  return 0;
}

