#include <stdio.h>
#include <string.h>
#include "stack.h"

void strfree(void *);

int main(int argc, const char *argv[])
{
  Stack s;
  StackNew(&s, sizeof(char *), strfree);

  int i, size;
  char *tricks[] = {"Ollie", "Shove-it", "Impossible"};
  
  // print each trick and push it in the stack
  for (i = 0; i < 3; i++) {
    printf("%-14s", tricks[i]);
    char *temp = strdup(tricks[i]);
    StackPush(&s, &temp);
  } printf("\n");

  // pop each element in stack and print it
  char *element;
  size = StackSize(&s);
  for (i = 0; i < size; i++) {
    StackPop(&s, &element);
    printf("%-14s", element);
    free(element);
  } printf("\n");

  // get rid of alloc'd
  StackDispose(&s);
  return 0;
}

void strfree(void *elemAddr)
{
  free(* (char **) elemAddr);
}

