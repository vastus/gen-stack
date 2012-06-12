#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define DEFAULTSIZE 4

typedef struct {
  void *elems;
  int loglen;
  int elemSize;
  int alloclen;
  void (*freefn)(void *);
} Stack;

void StackNew(Stack *, int, void (*)(void *));
void StackDispose(Stack *);
void StackPush(Stack *, void *);
void StackPop(Stack *, void *);
static bool isFull(Stack *);
static void StackGrow(Stack *);

void StackNew(Stack *s, int elemSize, void (*freefn)(void *))
{
  s->loglen = 0;
  s->elemSize = elemSize;
  s->alloclen = DEFAULTSIZE;
  s->freefn = freefn;
  s->elems = malloc(s->alloclen * s->elemSize);
  assert(s->elems != NULL);
}

void StackDispose(Stack *s)
{
  if (s->freefn != NULL) {
    int i; for (i = 0; i < s->loglen; i++) {
      s->freefn((char *) s->elems + (i * s->elemSize));
    }
  }

  free(s->elems);
}

void StackPush(Stack *s, void *elemAddr)
{
  if (isFull(s)) {
    StackGrow(s);
  }

  void *targetAddr = (char *) s->elems + (s->loglen * s->elemSize);
  memcpy(targetAddr, elemAddr, s->elemSize);
  s->loglen += 1;
}

void StackPop(Stack *s, void *elemAddr)
{
  assert(s->loglen > 0);
  s->loglen -= 1;
  void *sourceAddr = (char *) s->elems + (s->loglen * s->elemSize);
  memcpy(elemAddr, sourceAddr, s->elemSize);
}

int StackSize(Stack *s)
{
  return s->loglen;
}

static bool isFull(Stack *s)
{
  if (s->loglen == s->alloclen) {
    return true;
  }

  return false;
}

static void StackGrow(Stack *s)
{
  s->alloclen *= 2;
  s->elems = realloc(s->elems, s->alloclen * s->elemSize);
  assert(s->elems != NULL);
}

