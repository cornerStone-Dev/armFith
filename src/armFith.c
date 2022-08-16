// armFith.c
#include "../localTypes.h"
#include "../inc/armFith_i.h"

CompilerContext c;

//~ typedef long long (*fithFunc)(u32 tosValue, u32 *returnStackPointer, u32 *exprStackPointer, void *target);

/*e*/
void
armFithInit(void)/*p;*/
{
	c.compileBase     = (void*)__bss_end__;
	c.compileCursor   = (void*)__bss_end__;
	//~ c.returnStackBase = (void*)FITH_RETURN_STACK;
	//~ c.exprStackBase   = (void*)FITH_EXPR_STACK;
	//~ c.exprStack       = (void*)FITH_EXPR_STACK;
	c.returnStackBase = allocStack();
	c.exprStackBase   = c.returnStackBase + (512/4);
	c.exprStack       = c.exprStackBase;
	io_prints("armFithInit!\n> ");
	mc_wordStart();
}

#define CLASS1 0x04
#define WORD_BODY 1
#define MULTI_OP 7

#define COND_BEQ 0x0
#define COND_BNE 0x1
#define COND_BGE 0xA
#define COND_BLT 0xB
#define COND_BGT 0xC
#define COND_BLE 0xD

enum{
	WORD_FUNCTION,
	WORD_INLINE_FUNCTION1,
	WORD_INLINE_FUNCTION2,
	WORD_GLOBAL,
	WORD_CONSTANT,
	WORD_LOCAL,
};

enum{
	BLOCK_NONE,
	BLOCK_WORD,
	BLOCK_COND,
	BLOCK_ELSE,
	BLOCK_WHILE,
	BLOCK_DO,
	BLOCK_CASE,
	BLOCK_CASE_COND,
	BLOCK_RETURN,
	BLOCK_ONCE,
};

enum{
	DIV=0*CLASS1, // DIVISION OR FORWARD SLASH
	PRC=1*CLASS1, // PERCENT
	STA=2*CLASS1, // STAR
	LIN=3*CLASS1, // VERTICLE LINE
	CAR=4*CLASS1, // CARROT
	TIL=5*CLASS1, // TILDA
	PLU=6*CLASS1, // PLUS
	AMP=7*CLASS1, // AMPERSAND
	MIN=8*CLASS1+WORD_BODY, // MINUS
	SCO=9*CLASS1, // SEMI-COLON *ONLY AFTER WORD
	COL=10*CLASS1, // COLON *ONLY AFTER WORD
	ATS=11*CLASS1, // AT SIGN *ONLY AFTER WORD
	LPA=12*CLASS1, // LEFT PAREN *ONLY AFTER WORD?
	LTH=13*CLASS1, // LESS THAN START OF COMPARATOR
	GTH=14*CLASS1, // GREATER THAN START OF COMPARATOR
	EQU=15*CLASS1, // EQUALS START OF COMPARATOR
	LBL=16*CLASS1, // LEFT BLOCK START OF ANON WORD
	HAS=17*CLASS1, // HASH OR POUND
	TIC=18*CLASS1, // TICK
	COM=19*CLASS1, // COMMA
	RBL=20*CLASS1, // RIGHT BLOCK END OF BLOCK
	DOL=21*CLASS1, // DOLLAR START OF DEREFERNCE OPERATOR
	LBR=22*CLASS1, // LEFT BRACKET START OF IMMEDIATE MODE
	BNG=23*CLASS1+WORD_BODY, // BANG(!) START OF COMPARATOR
	QMK=24*CLASS1+WORD_BODY, // QUESTION MARK
	DIG=25*CLASS1+WORD_BODY, // DIGIT
	ALP=26*CLASS1+WORD_BODY, // ALPHABET
	DQO=27*CLASS1, // DOUBLE QUOTE START OF STRING
	SQO=28*CLASS1, // SINGLE QUOTE START OF CHAR LITERAL
	RPA=29*CLASS1, // RIGHT PAREN
	RBR=30*CLASS1, // RIGHT BRACKET END OF IMMEDIATE MODE
	BSL=31*CLASS1, // BACK SLASH
	WSP=32*CLASS1, // WHITE SPACE
	NUL=33*CLASS1, // NULL
	BAD=34*CLASS1, // BAD CHARACTER
	TYP=35*CLASS1, // TYPE FOR PRINTING
	//DOT=15*CLASS1, // DOT OR PERIOD
};

static const unsigned char class[] = {
/*         x0  x1  x2  x3  x4  x5  x6  x7  x8  x9  xa  xb  xc  xd  xe  xf */
/* 0x */  NUL,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,WSP,WSP,BAD,WSP,WSP,BAD,BAD,
/* 1x */  BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
/* 2x */  WSP,BNG,DQO,HAS,DOL,PRC,AMP,SQO,LPA,RPA,STA,PLU,COM,MIN,ALP,DIV,
/* 3x */  DIG,DIG,DIG,DIG,DIG,DIG,DIG,DIG,DIG,DIG,COL,SCO,LTH,EQU,GTH,QMK,
/* 4x */  ATS,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,
/* 5x */  ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,LBR,BSL,RBR,CAR,ALP,
/* 6x */  TIC,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,
/* 7x */  ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,LBL,LIN,RBL,TIL,BAD,
/* 8x */  ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,
/* 9x */  ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,
/* Ax */  ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,
/* Bx */  ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,
/* Cx */  ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,
/* Dx */  ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,
/* Ex */  ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,
/* Fx */  ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,ALP,TYP,TYP,TYP
};

/*e*/
void
armFith(u8 *string)/*p;*/
{
	u8 *cursor = string;
	u8 byte;
	StringBuff *current = 0;
	if (c.lockArmFith == 0)
	{
		c.lockArmFith = 1;
	} else {
		// armFith is already running concurrently.
		u32 length = st_len(cursor);
		StringBuff *new = zalloc(sizeof(StringBuff) + length - 3);
		rom_func.memcpy(new->string, cursor, length);
		c.nextLines = list_append(new, c.nextLines);
		return;
	}
	
	loop:
	byte = class[*cursor++] >> 2;
	switch (byte)
{
	case DIV>>2: { mc_stackDiv(); goto loop; }
	case PRC>>2: { mc_stackMod(); goto loop; }
	case STA>>2: { mc_stackMul(); goto loop; }
	case LIN>>2: { mc_stackOr(); goto loop; }
	case CAR>>2: { mc_stackXor(); goto loop; }
	case TIL>>2: { mc_stackNot(); goto loop; }
	case PLU>>2: { mc_stackAdd(); goto loop; }
	case AMP>>2: { cursor = compileAmp(cursor); goto loop; }
	case MIN>>2: { cursor = compileMinus(cursor); goto loop; }
	case SCO>>2: { io_prints("Invalid starting character, aborting\n"); break; }
	case COL>>2: { io_prints("Invalid starting character, aborting\n"); break; }
	case ATS>>2: { io_prints("Invalid starting character, aborting\n"); break; }
	case LPA>>2: { io_prints("Invalid starting character, aborting\n"); break; }
	case LTH>>2: { cursor = compileLth(cursor); goto loop; }
	case GTH>>2: { cursor = compileGth(cursor); goto loop; }
	case EQU>>2: { cursor = compileEqu(cursor); goto loop; }
	case LBL>>2: { advComileStub(0); goto loop; }
	case HAS>>2: { cursor = compileHas(cursor); goto loop; }
	case TIC>>2: { io_prints("Invalid starting character, aborting\n"); break; }
	case COM>>2: { io_prints("Invalid starting character, aborting\n"); break; }
	case RBL>>2: { cursor = compileRbl(cursor); goto loop; }
	case DOL>>2: { cursor = compileDol(cursor); goto loop; }
	case LBR>>2: { advComileStub(77); goto loop; }
	case BNG>>2: { cursor = compileBng(cursor); goto loop; }
	case QMK>>2: { printMemStats(); goto loop; /*break;*/ }
	case DIG>>2: { cursor = consumeNumLit(cursor); goto loop; }
	case ALP>>2: { cursor = consumeAlpha(cursor); goto loop; }
	case DQO>>2: { cursor = consumeStringLit(cursor); goto loop; }
	case SQO>>2: { cursor = consumeCharLit(cursor); goto loop; }
	case RPA>>2: { if (*cursor == '{') {mc_setParams();cursor++;} else {io_printsn("Error: Right Paren alone.");} goto loop; }
	case RBR>>2: { io_prints("Invalid starting character, aborting\n"); break; }
	case BSL>>2: { while(*cursor++ != '\n'){} cursor++; goto loop; }
	case WSP>>2: { goto loop; }
	case NUL>>2: { executeOrContinue(1); io_prints("> "); break; }
	case BAD>>2: { io_prints("Bad input byte detected, aborting\n"); break; }
	case TYP>>2: { cursor = printInterpolatedString2(cursor); goto loop; }
}
	if (current != 0) { free(current); current = 0; }
	if (c.nextLines)
	{
		current = list_removeFirst(&c.nextLines);
		cursor = current->string;
		goto loop;
	}
	if (c.lockArmFith != 0) { c.lockArmFith = 0; }
	
	return;
}

/*e*/static u8*
consumeNumLit(u8 *cursor)/*i;*/
{
	u8 *newCursor;
	s32 val = s2i(cursor - 1, &newCursor);
	mc_integerLit(val);
	return newCursor;
}

/*e*/static u8*
compileMinus(u8 *cursor)/*i;*/
{
	if(class[*cursor]>>2==DIG>>2)
	{
		return consumeNumLit(cursor);
	} else {
		mc_stackSub();
	}
	return cursor;
}

/*e*/static u8*
compileAmp(u8 *cursor)/*i;*/
{
	if(*cursor == '~')
	{
		cursor++;
		mc_stackBitClear();
	} else {
		mc_stackAnd();
	}
	return cursor;
}

/*e*/static u8*
compileLth(u8 *cursor)/*i;*/
{
	if(*cursor == '{') {
		// less than comparator
		cursor++;
		compileCond(COND_BGE);
	} else if(*cursor == '=') {
		// less than or equals
		if(cursor[1] == '{')
		{
			cursor+=2;
			compileCond(COND_BGT);
		} else if(cursor[1] == '}') {
			cursor+=2;
			compileDoLoopEnd(COND_BLE);
		} else {
			invalidSequence();
		}
	} else if(*cursor == '}') {
		cursor++;
		compileDoLoopEnd(COND_BLT);
	} else {
		// left shift
		mc_stackLS();
	}
	return cursor;
}

/*e*/static u8*
compileGth(u8 *cursor)/*i;*/
{
	if(*cursor == '{') {
		// greater than comparator
		cursor++;
		compileCond(COND_BLE);
	} else if(*cursor == '=') {
		// greater than or equals
		if(cursor[1] == '{')
		{
			cursor+=2;
			compileCond(COND_BLT);
		} else if(cursor[1] == '}') {
			cursor+=2;
			compileDoLoopEnd(COND_BGE);
		} else {
			invalidSequence();
		}
	} else if(*cursor == '}') {
		cursor++;
		compileDoLoopEnd(COND_BGT);
	} else {
		// right shift
		mc_stackRS();
	}
	return cursor;
}

/*e*/static u8*
compileEqu(u8 *cursor)/*i;*/
{
	if (*cursor == '{')
	{
		// equals comparator
		cursor++;
		compileCond(COND_BNE);
	} else if(*cursor == '}') {
		cursor++;
		compileDoLoopEnd(COND_BEQ);
	} else {
		invalidSequence();
	}
	return cursor;
}

/*e*/static u8*
compileHas(u8 *cursor)/*i;*/
{
	if(*cursor == '=')
	{
		// indexed store
		cursor++;
		mc_stackStrIndex();
	} else {
		// indexed load
		mc_stackLdrIndex();
	}
	return cursor;
}

/*e*/static u8*
compileDol(u8 *cursor)/*i;*/
{
	if(*cursor == '=')
	{
		// pointer store
		cursor++;
		mc_stackStrTo();
	} else {
		// pointer load
		mc_stackLdrTo();
	}
	return cursor;
}

/*e*/static u8*
compileBng(u8 *cursor)/*i;*/
{
	if (*cursor == '{')
	{
		// equals comparator
		cursor++;
		compileCond(COND_BEQ);
	} else if(*cursor == '}') {
		cursor++;
		compileDoLoopEnd(COND_BNE);
	} else {
		tree_print(c.globals, 0);
	}
	return cursor;
}

/*e*/static void
compileCond(u32 cond)/*i;*/
{
	//~ popTos();
	mc_condition();
	if (c.blocks && c.blocks->next->blockType == BLOCK_WHILE)
	{
		Block *whileBlock = c.blocks->next;
		whileBlock->target2 = c.compileCursor;
		whileBlock->cond = cond;
		putMachineCode(0xBF00);
	} else if (c.blocks && c.blocks->next->blockType == BLOCK_CASE) {
		Block *newBlock = zalloc(sizeof(Block));
		newBlock->blockType = BLOCK_CASE_COND;
		newBlock->target = c.compileCursor;
		newBlock->cond = cond;
		putMachineCode(0xBF00);
		c.blocks = list_prepend(newBlock, c.blocks);
	} else {
		Block *newBlock = zalloc(sizeof(Block));
		newBlock->blockType = BLOCK_COND;
		newBlock->target = c.compileCursor;
		newBlock->cond = cond;
		putMachineCode(0xBF00);
		c.blocks = list_prepend(newBlock, c.blocks);
	}
}

/*e*/static u8*
compilePostfixPlu(u8 *cursor, u8* start, u32 wordLength)/*i;*/
{
	Tree *word = resolveWord(start, wordLength);
	if (word == 0) { return cursor; }
	if(cursor[1] == '=')
	{
		cursor+=2;
		switch (word->type)
		{
			case WORD_FUNCTION:
			case WORD_INLINE_FUNCTION1:
			case WORD_INLINE_FUNCTION2:
			io_prints("Error: cannot add to a function word.\n");
			break;
			case WORD_GLOBAL:
			mc_addEqualsGlobal(word->value);
			break;
			case WORD_CONSTANT:
			io_prints("Error: cannot add to a constant.\n");
			break;
			case WORD_LOCAL:
			mc_addEqualsLocal((u32)word->value);
			break;
		}
	}
	return cursor;
}

/*e*/static void
compileDoLoopEnd(u32 cond)/*i;*/
{
	mc_condition();
	if (c.blocks && c.blocks->next->blockType == BLOCK_DO)
	{
		Block *doBlock = list_removeFirst(&c.blocks);
		// output conditional jump
		putMachineCode(armCond(cond,doBlock->target- c.compileCursor-2));
		free(doBlock);
	} else {
		io_printsn("Error: not matched to do{.");
	}
}

/*e*/static void
executeOrContinue(u32 printStack)/*i;*/
{
	// if nothing has been compiled then return
	if (c.compileCursor == c.compileBase + 2) { return; }
	// if we are inside of a function definition then return
	if (c.blocks) { return; }
	if (printStack) {
		mc_printExprStack(); // compile the printing of expr stack
	}
	void *funcToCall = completeWord();
	long long result = armFithEnter(c.tos, c.returnStackBase, c.exprStack,
		funcToCall );
	c.tos = result;
	c.exprStack = (u32*)(u32)(result >> 32);
	c.compileCursor = c.compileBase + 2; // reset the cursor
}

/*e*/u32
fithPopTos(void)/*p;*/
{
	u32 tos = c.tos;
	c.tos = *c.exprStack;
	c.exprStack = c.exprStack + 1;
	return tos;
}

/*e*/void
fithPushValTos(u32 val)/*p;*/
{
	c.exprStack = c.exprStack - 1;
	*c.exprStack = c.tos;
	c.tos = val;
	return;
}

/*e*/
void
printFithStackElements(u32 tos, u32 *sp)/*p;*/
{	
	u32 *base = c.exprStackBase;
	if (base != sp)
	{
		base-=2;
		while (base >= sp) {
			io_prints("(");
			io_printi(*base--);
			io_prints(")");
		}
		io_prints("(");
		io_printi(tos);
		io_printsn(")");
	}
}

/*e*/static u8*
consumeAlpha(u8 *cursor)/*i;*/
{
	u8 *start = cursor - 1;
	u8 byte = *cursor;
	while (class[byte] & WORD_BODY)
	{
		cursor++;
		byte = *cursor;
	}
	// alpha parts of words cannot end with -, it is used as a postfix operator
	if (*(cursor - 1) == '-') { cursor--; }
	u32 wordLength = cursor - start;
	
	// check for built in words
	u8 *newCursor = builtInCompileWord(start, cursor, wordLength);
	if (newCursor) { cursor = newCursor; goto done; }
	
	byte = class[*cursor] >> 2;
	switch (byte)
{
	case PLU>>2: { cursor = compilePostfixPlu(cursor, start, wordLength); goto done; }
	//~ case AMP>>2: { cursor = compileAmp(cursor); break; }
	//~ case MIN>>2: { cursor = compileMin(start, cursor); break; }
	case SCO>>2: { cursor++; createVar(start, wordLength); goto done; }
	case COL>>2: { cursor++; createConstant(start, wordLength); goto done; }
	case ATS>>2: { cursor++; pushAddressOf(start, wordLength); goto done; }
	case LPA>>2: { cursor++; createWordFunction(start, wordLength); c.insideParams = 1; goto done; }
	//~ case LTH>>2: { cursor = compileLth(cursor); break; }// shift
	//~ case GTH>>2: { cursor = compileGth(cursor); break; } // shift
	case EQU>>2: { cursor++; assignVar(start, wordLength);goto done; }
	case LBL>>2: { cursor++; createWordFunction(start, wordLength); goto done; }
	default : break;
}
	// see if we are inside params
	if (c.insideParams)
	{
		createLocal(start, wordLength);
		goto done;
	}
	Tree *word = resolveWord(start, wordLength);
	if (word != 0)
	{
		u16 *code;
		switch (word->type)
		{
			case WORD_FUNCTION:
			callWord((u32)word->value);
			break;
			case WORD_INLINE_FUNCTION1:
			code = (u16*)((u32)word->value-1);
			putMachineCode(*code);
			break;
			case WORD_INLINE_FUNCTION2:
			code = (u16*)((u32)word->value-1);
			putMachineCode(*code++);
			putMachineCode(*code);
			break;
			case WORD_GLOBAL:
			mc_ldrGlobal(word->value);
			break;
			case WORD_CONSTANT:
			mc_integerLit((u32)word->value);
			break;
			case WORD_LOCAL:
			mc_ldrLocal((u32)word->value);
			break;
		}
	}
	
	done:
	return cursor;
}

/*e*/static Tree*
resolveWord(u8 *start, u32 wordLength)/*i;*/
{
	// check for locals
	Tree *word = tree_find(c.locals, start, wordLength);
	if (word != 0) { return word; }
	word = tree_find(c.globals, start, wordLength);
	if (word == 0) { io_prints("Error: word definition missing.\n"); }
	return word;
}

/*e*/static void
advComileStub(u32 index)/*i;*/
{
	io_prints("STUB!");io_printin(index);
}

/*e*/static void
createWordFunction(u8 *start, u32 length)/*i;*/
{
	if (c.blocks) { io_prints("Error: within a block.\n"); return; }
	Tree *word = tree_find(c.globals, start, length);
	if (word)
	{
		io_prints("Warning: redefinition of word.\n");
	} else {
		tree_add(&c.globals, start, length, 0);
		word = tree_find(c.globals, start, length);
	}
	word->type  = WORD_FUNCTION;
	word->value  = (void*)((u32)c.compileBase+1);
	Block *newBlock = zalloc(sizeof(Block));
	newBlock->blockType = BLOCK_WORD;
	newBlock->word = word;
	c.blocks = list_prepend(newBlock, c.blocks);
}

/*e*/static void
assignVar(u8 *start, u32 wordLength)/*i;*/
{
	// check for locals first
	Tree *local = tree_find(c.locals, start, wordLength);
	if (local)
	{
		if (local->type == WORD_LOCAL)
		{
			mc_strLocal((u32)local->value);
		} else {
			io_printsn("Error: cannot store to local constant.");
		}
	} else {
		// check global words
		Tree *word = tree_find(c.globals, start, wordLength);
		if (word)
		{
			if (word->type == WORD_GLOBAL)
			{
				mc_strGlobal(word->value);
			} else if (word->type == WORD_CONSTANT) {
				io_printsn("Error: cannot store to global constant.");
			} else {
				io_printsn("Error: Not a global variable.");
			}
		} else {
			io_printsn("Error: word definition missing.");
		}
	}
}

/*e*/static void
pushAddressOf(u8 *start, u32 wordLength)/*i;*/
{
	// check for locals first
	Tree *local = tree_find(c.locals, start, wordLength);
	if (local)
	{
		if (local->type == WORD_LOCAL)
		{
			io_printsn("Error: cannot take the address of local variable.");
		} else {
			io_printsn("Error: cannot take the address of local constant.");
		}
	} else {
		// check global words
		Tree *word = tree_find(c.globals, start, wordLength);
		if (word)
		{
			switch (word->type)
			{
				case WORD_FUNCTION:
				case WORD_INLINE_FUNCTION1:
				case WORD_INLINE_FUNCTION2:
				case WORD_GLOBAL:
				mc_integerLit((u32)word->value);
				break;
				case WORD_CONSTANT:
			io_printsn("Error: cannot take the address of global constant.");
				break;
			}
		} else {
			io_printsn("Error: word definition missing.");
		}
	}
}

/*e*/static u8*
compileRbl(u8 *cursor)/*i;*/
{
	if (cursor[0] == '{')
	{
		// handle else statement
		compileElse();
		return cursor + 1;
	}
	if(    (cursor[0] == 'e')
		&& (cursor[1] == 'l')
		&& (cursor[2] == 's')
		&& (cursor[3] == 'e')
		&& (cursor[4] == '{') )
	{
		// handle else statement
		compileElse();
		return cursor + 5;
	}
	endBlock();
	return cursor;
}

/*e*/static void
compileElse(void)/*i;*/
{
	Block *top = list_removeFirst(&c.blocks);
	if (top && top->blockType == BLOCK_COND)
	{
		Block *newBlock = zalloc(sizeof(Block));
		newBlock->blockType = BLOCK_ELSE;
		newBlock->target = c.compileCursor;
		c.blocks = list_prepend(newBlock, c.blocks);
		putMachineCode(0xBF00);
		*top->target = armCond(top->cond, c.compileCursor - top->target-2);
	} else {
		io_printsn("Error: Else not matched to condition.");
	}
	free(top);
}

/*e*/static void
compileWhile(void)/*i;*/
{
	Block *newBlock = zalloc(sizeof(Block));
	newBlock->blockType = BLOCK_WHILE;
	newBlock->target = c.compileCursor;
	c.blocks = list_prepend(newBlock, c.blocks);
}

/*e*/static void
compileDo(void)/*i;*/
{
	Block *newBlock = zalloc(sizeof(Block));
	newBlock->blockType = BLOCK_DO;
	newBlock->target = c.compileCursor;
	c.blocks = list_prepend(newBlock, c.blocks);
}

/*e*/static void
compileCase(void)/*i;*/
{
	Block *newBlock = zalloc(sizeof(Block));
	newBlock->blockType = BLOCK_CASE;
	c.blocks = list_prepend(newBlock, c.blocks);
}

/*e*/static void
compileReturn(void)/*i;*/
{
	Block *newBlock = zalloc(sizeof(Block));
	newBlock->blockType = BLOCK_CASE;
	newBlock->target = c.compileCursor;
	putMachineCode(0xBF00);
	c.retBlocks = list_prepend(newBlock, c.retBlocks);
}

/*e*/static void
compileOnce(void)/*i;*/
{
	Block *newBlock = zalloc(sizeof(Block));
	newBlock->blockType = BLOCK_ONCE;
	callWord((u32)fithOnce);
	newBlock->target = c.compileCursor;
	putMachineCode(0xBF00);
	c.blocks = list_prepend(newBlock, c.blocks);
}

/*e*/static void
endBlock(void)/*i;*/
{
	if (c.blocks == 0) { io_prints("Error: unmatched '}'.\n"); return; }
	Block *block = list_removeFirst(&c.blocks);
	u32 blockType = block->blockType;
	switch (blockType) {
	case BLOCK_WORD:
	{
		// button up word and save it off
		block->word->value = completeWord();
		u32 wordSize = ((u32)c.compileCursor - (u32)block->word->value) + 1;
		if (wordSize <= 4)
		{
			block->word->type = WORD_INLINE_FUNCTION1;
		} else if (wordSize <= 6) {
			block->word->type = WORD_INLINE_FUNCTION2;
		} else {
			block->word->type = WORD_FUNCTION;
		}
		io_prints(block->word->key);
		io_prints(": defined, # bytes ");
		io_printin(wordSize);
		// set up for next definition
		c.compileBase = c.compileCursor;
		mc_wordStart();
		break;
	}
	case BLOCK_COND:
	{
		// load address for jump offset and set it, easy
		*block->target = armCond(block->cond,c.compileCursor - block->target-2);
		break;
	}
	case BLOCK_ELSE:
	{
		*block->target = armBranch(c.compileCursor - block->target - 2);
		break;
	}
	case BLOCK_WHILE:
	{
		// output jump to start of while
		putMachineCode(armBranch(block->target - c.compileCursor - 2));
		// output jump to skip
		*block->target2 = armCond(block->cond,c.compileCursor-block->target2-2);
		break;
	}
	case BLOCK_CASE:
	{
		Block *caseJump = list_removeFirst(&block->caseList);
		while (caseJump)
		{
			*caseJump->target=armBranch(c.compileCursor - caseJump->target - 2);
			caseJump = list_removeFirst(&block->caseList);
		}
		break;
	}
	case BLOCK_CASE_COND:
	{
		u16 *fixMe = block->target;
		block->target = c.compileCursor;
		putMachineCode(0xBF00);
		*fixMe = armCond(block->cond,c.compileCursor-fixMe-2);
		Block *caseBlock = list_getFirst(c.blocks);
		caseBlock->caseList = list_prepend(block, caseBlock->caseList);
		// block has been repurposed do not free!
		return;
	}
	case BLOCK_ONCE:
	{
		*block->target = c.compileCursor - (block->target-2) - 2;
		break;
	}
	
	}
	free(block);
}

/*e*/static void*
completeWord(void)/*i;*/
{
	// fill in all return statements
	while (c.retBlocks)
	{
		Block *retBlock = list_removeFirst(&c.retBlocks);
		*retBlock->target = armBranch(c.compileCursor - retBlock->target - 2);
	}
	// output function ending
	u16 *start;
	if (c.localIndex == 1 && c.notLeaf == 0)
	{
		start = &c.compileBase[1];
		mc_wordEnd1Local(start); // compile the ending of a word
	} else if (c.localIndex > 1 && c.notLeaf == 0) {
		start = &c.compileBase[1];
		mc_wordEndMultiLocal(start); // compile the ending of a word
	} else if (c.localIndex == 0 && c.notLeaf == 1) {
		start = &c.compileBase[0];
		mc_wordEndNotLeafNoLocal(); // compile the ending of a word
	} else if (c.localIndex > 0 && c.notLeaf == 1) {
		start = &c.compileBase[0];
		mc_wordEnd(start+1); // compile the ending of a word
	} else { // (c.localIndex == 0 && c.notLeaf == 0)
		// overwrite ending
		start = &c.compileBase[2];
		mc_wordEndShort();
	}
	// fix up all branches to ending
	// output 4 byte constants
	mc_generateLargeConsts();
	// output all string constants
	mc_generateStringLits();
	// destroy all locals
	tree_free(c.locals); c.locals = 0;
	c.localIndex = 0;
	// reset state
	c.notLeaf = 0;
	return (void*)((u32)start+1);
}

// TODO add support for CREATE string ability
/*e*/static u8*
consumeStringLit(u8 *cursor)/*i;*/
{
	// move to start of string
	u8 *start = cursor;
	u8 *end = cursor;
	// use cursor to find the end
	again:
	while (*end != '\"'){ end++; }
	if (*(end-1) == '\\') { end++; goto again; }
	
	// push TOS and output holder code for string
	mc_pushTos();
	u32 stringLength = end - start;
	String *new = zalloc(stringLength + sizeof(String) - 3);
	new->length = stringLength;
	rom_func.memcpy(new->string, start, stringLength);
	new->target = c.compileCursor;
	putMachineCode(0xBF00);
	c.stringLits = list_append(new, c.stringLits);
	
	return end + 1;
}

/*e*/static u8*
consumeCharLit(u8 *cursor)/*i;*/
{
	u32 val = 0;
	if (*cursor != '\\'){
		val = *cursor++;
	} else {
		switch(cursor[1])
		{
			case '\"':
			val = '\"';
			break;
			case 'n':
			val = 0x0A;
			break;
			case 'r':
			val = 0x0D;
			break;
			case 't':
			val = 0x09;
			break;
			case '\\':
			val = 0x5C;
			break;
		}
		cursor += 2;
	}
	mc_integerLit(val);
	if (*cursor == '\'') { cursor++; }
	return cursor;
}

/*e*/static void
invalidSequence(void)/*i;*/
{
	io_printsn("INVALID SEQUENCE!");
}

/*e*/static void
createVar(u8 *start, u32 length)/*i;*/
{
	if (c.blocks)
	{
		// we are creating a local variable
		u32 localNum = createLocal(start, length);
		mc_strLocal(localNum);
	} else {
		// we are creating a global variable
		executeOrContinue(0); // prepare for a definition
		createGlobal(start, length);
	}
}

/*e*/static u32
createLocal(u8 *start, u32 length)/*i;*/
{
	if (c.localIndex >= 5){ io_printsn("Error: five Locals Max."); return 5; }
	u32 localNum = c.localIndex++;
	localNum = 7-localNum;
	Tree *word = tree_add(&c.locals, start, length, (void*)localNum);
	if (word)
	{
		io_printsn("Warning: redefinition of local that existed.");
	} else {
		word = tree_find(c.locals, start, length);
		word->value = (void*)localNum;
	}
	word->type = WORD_LOCAL;
	return localNum;
}

/*e*/static void
createGlobal(u8 *start, u32 length)/*i;*/
{
	u32 *globalAddr = mc_createGlobal();
	Tree *word = tree_add(&c.globals, start, length, globalAddr);
	if (word)
	{
		io_prints("Warning: redefinition of global.\n");
		word->value = globalAddr;
	} else {
		word = tree_find(c.globals, start, length);
	}
	word->type = WORD_GLOBAL;
	// initialize global
	mc_strGlobal(globalAddr);
}

/*e*/static void
createConstant(u8 *start, u32 length)/*i;*/
{
	Tree *word = 0;
	if (c.blocks)
	{
		// we are creating a local constant
		word = tree_add(&c.locals, start, length, 0);
		if (word)
		{
			io_printsn("Warning: redefinition of local constant.");
		} else {
			word = tree_find(c.locals, start, length);
		}
	} else {
		// we are creating a global constant
		word = tree_add(&c.globals, start, length, 0);
		if (word)
		{
			io_prints("Warning: redefinition of global constant.\n");
		} else {
			word = tree_find(c.globals, start, length);
		}
	}
	word->type = WORD_CONSTANT;
	// initialize global
	mc_strGlobal((u32*)&word->value);
}

/*e*/static u8*
printInterpolatedString1(u8 *start)/*i;*/
{
	// move to start of string
	u8 typeByte = 0xFD;
	u8 *end = start;
	if (*end == '%') { end+=1; start = end; goto again2; }
	// find start of interpolation
	again:
	while (*end != '\"' && *end != '%'){ end++; }
	if (*(end-1) == '\\') { end++; goto again; }
	// if no interpolation found just regular print
	if (*end == '\"') { start = consumeStringLit(start); callWord((u32)fithPrintsn); return start; }
	// check for type specifier
	
	if (*(end-1) == 'i') { *(end-1) = '\"'; }
	if (*(end-1) == 'h') { typeByte = 0xFE; *(end-1) = '\"'; }
	if (*(end-1) == 's') { typeByte = 0xFF; *(end-1) = '\"'; }
	// change ending to double quote
	*end++ = '\"';
	// consume and output the string clip
	consumeStringLit(start);
	callWord((u32)fithPrints);
	start = end;
	// re-write internal area
	again2:
	while (*end != '%'){ end++; }
	if (*(end-1) == '\\') { end++; goto again2; }
	if (*(end+1) == '%') { *end = ' '; end+=2; goto again2; }
	*end = typeByte;
	return start;
}

/*e*/static u8*
printInterpolatedString2(u8 *start)/*i;*/
{
	u8 typeByte = *(start-1);
	u8 *end = start;
	
	// print result
	switch (typeByte - 0xFD)
	{
		case 0:
		{
			if (*end == '\"') { callWord((u32)fithPrintin); return end + 1; }
			callWord((u32)fithPrinti);
			break;
		}
		case 1:
		{
			if (*end == '\"') { callWord((u32)fithPrinthn); return end + 1; }
			callWord((u32)fithPrinth);
			break;
		}
		case 2:
		{
			if (*end == '\"') { callWord((u32)fithPrintsn); return end + 1; }
			callWord((u32)fithPrints);
			break;
		}
	}
	
	return printInterpolatedString1(start);
}


// Section Built In Words

/*e*/static u8*
builtInCompileWord(u8 *start, u8 *cursor, u32 length)/*i;*/
{
	switch (length)
	{
		case 1:  return builtInWord1(start, cursor, length);
		case 2:  return builtInWord2(start, cursor, length);
		case 3:  return builtInWord3(start, cursor, length);
		case 4:  return builtInWord4(start, cursor, length);
		case 5:  return builtInWord5(start, cursor, length);
		case 6:  return builtInWord6(start, cursor, length);
		case 7:  return builtInWord7(start, cursor, length);
		default: return 0;
	}
}

/*e*/static u8*
builtInWord1(u8 *start, u8 *cursor, u32 length)/*i;*/
{
	if(    (start[0] == 'p') )
	{
		mc_printExprStack();
		return start + 1;
	}
	if(    (start[0] == 'c') )
	{
		callWord((u32)fithClearStack);
		return start + 1;
	}
	if(    (start[0] == '.')
		&& (start[1] == '"') )
	{
		return printInterpolatedString1(start + 2);
	}
	return 0;
}

/*e*/static u8*
builtInWord2(u8 *start, u8 *cursor, u32 length)/*i;*/
{
	// do{, start of do loop
	if(    (start[0] == 'd')
		&& (start[1] == 'o')
		&& (start[2] == '{') )
	{
		compileDo();
		return start + 3;
	}
	if(    (start[0] == 'o')
		&& (start[1] == 'r') )
	{
		mc_stackOr();
		return start + 2;
	}
	if(    (start[0] == 'p')
		&& (start[1] == 's') )
	{
		callWord((u32)fithPrints);
		return start + 2;
	}
	return 0;
}

/*e*/static u8*
builtInWord3(u8 *start, u8 *cursor, u32 length)/*i;*/
{
	if(    (start[0] == 'n')
		&& (start[1] == 'e')
		&& (start[2] == 'g') )
	{
		mc_negTos();
		return start + 3;
	}
	if(    (start[0] == 'a')
		&& (start[1] == 'n')
		&& (start[2] == 'd') )
	{
		mc_stackLogicAnd();
		return start + 3;
	}
	if(    (start[0] == 'd')
		&& (start[1] == 'u')
		&& (start[2] == 'p') )
	{
		mc_pushTos();
		return start + 3;
	}
	if(    (start[0] == 'a')
		&& (start[1] == 'b')
		&& (start[2] == 's') )
	{
		mc_stackAbs();
		return start + 3;
	}
	if(    (start[0] == 'n')
		&& (start[1] == 'i')
		&& (start[2] == 'p') )
	{
		mc_nip();
		return start + 3;
	}
	if(    (start[0] == 'p')
		&& (start[1] == 's')
		&& (start[2] == 'n') )
	{
		callWord((u32)fithPrintsn);
		return start + 3;
	}
	return 0;
}

/*e*/static u8*
builtInWord4(u8 *start, u8 *cursor, u32 length)/*i;*/
{
	// case{, start of case statement
	if(    (start[0] == 'c')
		&& (start[1] == 'a')
		&& (start[2] == 's')
		&& (start[3] == 'e')
		&& (start[4] == '{') )
	{
		compileCase();
		return start + 5;
	}
	if(    (start[0] == 'c')
		&& (start[1] == 'a')
		&& (start[2] == 'l')
		&& (start[3] == 'l') )
	{
		mc_call();
		return start + 4;
	}
	if(    (start[0] == 'd')
		&& (start[1] == 'r')
		&& (start[2] == 'o')
		&& (start[3] == 'p') )
	{
		mc_popTos();
		return start + 4;
	}
	if(    (start[0] == 'o')
		&& (start[1] == 'v')
		&& (start[2] == 'e')
		&& (start[3] == 'r') )
	{
		mc_over();
		return start + 4;
	}
	if(    (start[0] == 'p')
		&& (start[1] == 'i')
		&& (start[2] == 'c')
		&& (start[3] == 'k') )
	{
		mc_pick();
		return start + 4;
	}
	if(    (start[0] == 's')
		&& (start[1] == 'w')
		&& (start[2] == 'a')
		&& (start[3] == 'p') )
	{
		mc_swap();
		return start + 4;
	}
	if(    (start[0] == 'f')
		&& (start[1] == 'r')
		&& (start[2] == 'e')
		&& (start[3] == 'e') )
	{
		callWord((u32)fithFree);
		return start + 4;
	}
	if(    (start[0] == 'o')
		&& (start[1] == 'n')
		&& (start[2] == 'c')
		&& (start[3] == 'e')
		&& (start[4] == '{') )
	{
		compileOnce();
		return start + 5;
	}
	return 0;
}

/*e*/static u8*
builtInWord5(u8 *start, u8 *cursor, u32 length)/*i;*/
{
	// while, start of loop
	if(    (start[0] == 'w')
		&& (start[1] == 'h')
		&& (start[2] == 'i')
		&& (start[3] == 'l')
		&& (start[4] == 'e') )
	{
		compileWhile();
		return start + 5;
	}
	// leave, exit current enclosing switch or loop
	if(    (start[0] == 'l')
		&& (start[1] == 'e')
		&& (start[2] == 'a')
		&& (start[3] == 'v')
		&& (start[4] == 'e') )
	{
		advComileStub(2);
		return start + 5;
	}
	// again, start at the top of the current loop
	if(    (start[0] == 'a')
		&& (start[1] == 'g')
		&& (start[2] == 'a')
		&& (start[3] == 'i')
		&& (start[4] == 'n') )
	{
		advComileStub(3);
		return start + 5;
	}
	if(    (start[0] == 'a')
		&& (start[1] == 'l')
		&& (start[2] == 'l')
		&& (start[3] == 'o')
		&& (start[4] == 'c') )
	{
		callWord((u32)fithAlloc);
		return start + 5;
	}
	if(    (start[0] == 's')
		&& (start[1] == 'p')
		&& (start[2] == '-')
		&& (start[3] == 'o')
		&& (start[4] == 'n') )
	{
		c.stackCheck = 1;
		return start + 5;
	}
	return 0;
}

/*e*/static u8*
builtInWord6(u8 *start, u8 *cursor, u32 length)/*i;*/
{
	// while, start of loop
	if(    (start[0] == 'r')
		&& (start[1] == 'e')
		&& (start[2] == 't')
		&& (start[3] == 'u')
		&& (start[4] == 'r')
		&& (start[5] == 'n') )
	{
		compileReturn();
		return start + 6;
	}
	if(    (start[0] == 's')
		&& (start[1] == 'p')
		&& (start[2] == '-')
		&& (start[3] == 'o')
		&& (start[4] == 'f')
		&& (start[5] == 'f') )
	{
		c.stackCheck = 0;
		return start + 6;
	}
	return 0;
}

/*e*/static u8*
builtInWord7(u8 *start, u8 *cursor, u32 length)/*i;*/
{
	if(    (start[0] == 'r')
		&& (start[1] == 'e')
		&& (start[2] == 'a')
		&& (start[3] == 'l')
		&& (start[4] == 'l')
		&& (start[5] == 'o')
		&& (start[6] == 'c') )
	{
		callWord((u32)fithRealloc);
		return start + 7;
	}
	if(    (start[0] == 't')
		&& (start[1] == 'a')
		&& (start[2] == 'i')
		&& (start[3] == 'l')
		&& (start[4] == 'r')
		&& (start[5] == 'e')
		&& (start[6] == 'c') )
	{
		// output jump to start of function without rebuilding call stack
		putMachineCode(armBranch(&c.compileBase[2] - c.compileCursor - 2));
		return start + 7;
	}
	return 0;
}
