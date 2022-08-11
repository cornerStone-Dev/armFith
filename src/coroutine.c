// coroutine.c
#include "../localTypes.h"

/*e*/
void*
co_create(void *function)/*p;*/
{
	u32 *newCoroutine = allocStack();
	u32 *returnStack = newCoroutine;
	u32 *expressionStack = newCoroutine + 128;
	expressionStack = expressionStack - 7; // make room for 7 things
	expressionStack[0] = (u32)returnStack;
	expressionStack[6] = (u32)function;
	return expressionStack;
}

/*e*/
void
co_destroy(void *coroutine)/*p;*/
{
	u32 *base = (u32*)((u32)coroutine & (-512));
	free(base);
}
