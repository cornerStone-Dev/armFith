// coroutine.c
#include "../localTypes.h"

/*e*/
void*
co_create(void *function)/*p;*/
{
	u32 *newCoroutine = allocStack();
	u32 *returnStack = newCoroutine + 4;
	u16 *code = (u16*)newCoroutine;
	u32 *expressionStack = newCoroutine + 128;
	mc_newCoroutine(code);
	expressionStack = expressionStack - 8; // make room for 7 things
	expressionStack[0] = (u32)returnStack;
	expressionStack[2] = (u32)function;
	expressionStack[3] = (u32)asm_wrapper;
	expressionStack[6] = (u32)asm_wrapper;
	newCoroutine[3] = (u32)expressionStack;
	return (void*)((u32)newCoroutine+1);
}
