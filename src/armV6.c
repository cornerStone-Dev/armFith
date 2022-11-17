// armV6.c
#include "../localTypes.h"
#include "../inc/armV6_i.h"

#define SCRATCH 2
#define TOS 0
#define RET_SP 1
#define ARM_NOP 0xBF00

/*e*/u32
armSubImm(u32 dest, u32 val)/*p;*/
{
	u32 code = 0x3800;
	code += val + (dest << 8);
	return code;
}

/*e*/u32
armAddImm(u32 dest, u32 val)/*p;*/
{
	u32 code = 0x3000;
	code += val + (dest << 8);
	return code;
}

/*e*/u32
armSub3(u32 dest, u32 arg1, u32 arg2)/*p;*/
{
	u32 code = 0x1A00;
	code += dest + (arg1 << 3) + (arg2 << 6);
	return code;
}

/*e*/u32
armAdd3(u32 dest, u32 arg1, u32 arg2)/*p;*/
{
	u32 code = 0x1800;
	code += dest + (arg1 << 3) + (arg2 << 6);
	return code;
}

/*e*/static u32
armPush(u32 regBits)/*i;*/
{
	u32 code = 0xB400;
	code += regBits;
	return code;
}

/*e*/u32
armPop(u32 regBits)/*p;*/
{
	u32 code = 0xBC00;
	code += regBits;
	return code;
}

//~ static u32
//~ setLocalRegsBits(s32 numVars)
//~ {
	//~ u32 regBits = 0;
	//~ for (s32 x = 0; x < numVars; x++)
	//~ {
		//~ regBits <<= 1;
		//~ regBits++;
	//~ }
	//~ regBits <<= 4;
	//~ return regBits;
//~ }

//~ /*e*/u32
//~ armPushFuncStart(s32 numVars)/*p;*/
//~ {
	//~ u32 regBits = setLocalRegsBits(numVars);
	//~ regBits += (1<<8);
	//~ return armPush(regBits);
//~ }

//~ /*e*/u32
//~ armPopFuncEnd(s32 numVars)/*p;*/
//~ {
	//~ u32 regBits = setLocalRegsBits(numVars);
	//~ regBits += (1<<8);
	//~ return armPop(regBits);
//~ }

/*e*/u32
armBx(u32 reg)/*p;*/
{
	u32 code = 0x4700;
	code += reg << 3;
	return code;
}

static u32
armBlx(u32 reg)
{
	u32 code = 0x4780;
	code += reg << 3;
	return code;
}

/*e*/u32
armMovImm(u32 dest, u32 val)/*p;*/
{
	u32 code = 0x2000;
	code += val + (dest << 8);
	return code;
}

/*e*/static u32
armMov(u32 dest, u32 src)/*i;*/
{
	u32 code = 0x4600;
	code += ((dest>>3)<<7) + ((dest<<29)>>29) + (src << 3);
	return code;
}

/*e*/static u32
armMovs(u32 dest, u32 src)/*i;*/
{
	u32 code = 0x0000;
	code += dest + (src << 3);
	return code;
}

static u32
armAdr(u32 dest, u32 imm)
{
	u32 code = 0xA000;
	if (imm > 255)
	{
		io_printsn("Error: string is out of range.");
		imm = 1;
	}
	code += imm + (dest << 8);
	return code;
}

static u32
armLdrLit(u32 dest, u32 imm)
{
	u32 code = 0x4800;
	code += imm + (dest << 8);
	return code;
}

static u32
armLdmia(u32 src, u32 regBits)
{
	u32 code = 0xC800;
	code += regBits + (src << 8);
	return code;
}

static u32
armStmia(u32 src, u32 regBits)
{
	u32 code = 0xC000;
	code += regBits + (src << 8);
	return code;
}

static u32
armMul(u32 dest, u32 arg1)
{
	u32 code = 0x4340;
	code += dest + (arg1 << 3);
	return code;
}

static u32
armOr(u32 dest, u32 arg1)
{
	u32 code = 0x4300;
	code += dest + (arg1 << 3);
	return code;
}

static u32
armXor(u32 dest, u32 arg1)
{
	u32 code = 0x4040;
	code += dest + (arg1 << 3);
	return code;
}

static u32
armNot(u32 dest, u32 arg1)
{
	u32 code = 0x43C0;
	code += dest + (arg1 << 3);
	return code;
}

static u32
armAnd(u32 dest, u32 arg1)
{
	u32 code = 0x4000;
	code += dest + (arg1 << 3);
	return code;
}

static u32
armBic(u32 dest, u32 arg1)
{
	u32 code = 0x4380;
	code += dest + (arg1 << 3);
	return code;
}

static u32
armLslsImm(u32 dest, u32 src, u32 val)
{
	u32 code = 0x0000;
	code += dest + (src << 3) + ((val&0X1F) << 6);
	return code;
}

static u32
armLsls(u32 dest, u32 arg1)
{
	u32 code = 0x4080;
	code += dest + (arg1 << 3);
	return code;
}

static u32
armLsrsImm(u32 dest, u32 src, u32 val)
{
	u32 code = 0x0800;
	code += dest + (src << 3) + ((val&0X1F) << 6);
	return code;
}

static u32
armLsrs(u32 dest, u32 arg1)
{
	u32 code = 0x40C0;
	code += dest + (arg1 << 3);
	return code;
}

static u32
armAsrsImm(u32 dest, u32 src, u32 val)
{
	u32 code = 0x1000;
	code += dest + (src << 3) + ((val&0x1F) << 6);
	return code;
}

static u32
armCmp(u32 left, u32 right)
{
	u32 code = 0x4280;
	code += left + (right << 3);
	return code;
}

static u32
armCmpImm(u32 left, u32 val)
{
	u32 code = 0x2800;
	code += val + (left << 8);
	return code;
}

static u32
armLdrOffset(u32 dest, u32 src, u32 offset)
{
	u32 code = 0x6800;
	code += dest + (src << 3) + (offset << 6);
	return code;
}

static u32
armLdrIndex(u32 dest, u32 src, u32 index)
{
	u32 code = 0x5800;
	code += dest + (src << 3) + (index << 6);
	return code;
}

static u32
armLdrByteOffset(u32 dest, u32 src, u32 offset)
{
	u32 code = 0x7800;
	code += dest + (src << 3) + (offset << 6);
	return code;
}

static u32
armLdrByteIndex(u32 dest, u32 src, u32 index)
{
	u32 code = 0x5C00;
	code += dest + (src << 3) + (index << 6);
	return code;
}

static u32
armLdrSpOffset(u32 dest, u32 offset)
{
	u32 code = 0x9800;
	code += offset + (dest << 8);
	return code;
}

static u32
armStrOffset(u32 src, u32 dest, u32 offset)
{
	u32 code = 0x6000;
	code += src + (dest << 3) + (offset << 6);
	return code;
}

static u32
armStrIndex(u32 src, u32 dest, u32 index)
{
	u32 code = 0x5000;
	code += src + (dest << 3) + (index << 6);
	return code;
}

static u32
armStrByteOffset(u32 src, u32 dest, u32 offset)
{
	u32 code = 0x7000;
	code += src + (dest << 3) + (offset << 6);
	return code;
}

static u32
armStrByteIndex(u32 src, u32 dest, u32 index)
{
	u32 code = 0x5400;
	code += src + (dest << 3) + (index << 6);
	return code;
}

/*e*/u32
armCond(u32 cond, s32 imm)/*p;*/
{
	u32 code = 0xD000;
	if (imm < -128 || imm > 127)
	{
		io_printsn("Error: conditional branch out of range.");
		imm = -1;
	}
	u32 encode = imm;
	code += ((encode<<24)>>24) + (cond << 8);
	return code;
}

/*e*/ u32
armBranch(s32 imm)/*p;*/
{
	u32 code = 0xE000;
	if (imm < -1024 || imm > 1023)
	{
		io_printsn("Error: branch out of range.");
		imm = -1;
	}
	u32 encode = imm;
	code += (encode<<21)>>21;
	return code;
}

static u32
armNeg(u32 dest, u32 arg1)
{
	u32 code = 0x4240;
	code += dest + (arg1 << 3);
	return code;
}

static u32
armSbcs(u32 dest, u32 arg1)
{
	u32 code = 0x4180;
	code += dest + (arg1 << 3);
	return code;
}


/*e*/void
putMachineCode(u32 instruction)/*p;*/
{
	*c.compileCursor++ = instruction;
}

/*e*/void
mc_callRelative(u32 target, u32 currentAddr)/*p;*/
{
	u16 *outputCursor = (u16*)currentAddr;
	u32 currentPC = currentAddr + 4;
	u32 jump = (target - currentPC) >> 1;
	u32 imm11 = jump << 21 >> 21;
	u32 imm10 = jump << 11 >> 22;
	u32 i2    = jump << 10 >> 31;
	u32 i1    = jump << 9 >> 31;
	u32 S     = jump << 8 >> 31;
	u32 j2    = (i2^1)^S;
	u32 j1    = (i1^1)^S;
	u32 code = 0xF000;
	code += (S<<10) + imm10;
	*outputCursor++ = code;
	code = 0xD000;
	code += (j2<<11) + (j1<<13) + imm11;
	*outputCursor = code;
}

/*e*/void
callWord(u32 target)/*p;*/
{
	c.notLeaf = 1;
	u32 currentAddr = (u32)c.compileCursor;
	mc_callRelative(target, currentAddr);
	c.compileCursor += 2;
}

/*e*/void
mc_pushTos(void)/*p;*/
{
	putMachineCode(armPush(1<<TOS));
}

/*e*/static void
mc_pushScratch(void)/*i;*/
{
	putMachineCode(armPush(1<<SCRATCH));
}

/*e*/static void
mc_popScratch(void)/*i;*/
{
	if (c.stackCheck) { callWord((u32)checkedPopStack); }
	putMachineCode(armPop(1<<SCRATCH));
}

/*e*/void
mc_popTos(void)/*p;*/
{
	if (c.stackCheck) { callWord((u32)checkedPopStack); }
	putMachineCode(armPop(1<<TOS));
}

static void
mc_smallIntLit(s32 value)
{
	putMachineCode(armMovImm(TOS, value));
}

static void
mc_largeIntLit(s32 value)
{
	LargeConst *new = zalloc(sizeof(LargeConst));
	new->target = c.compileCursor;
	new->value = value;
	c.largeIntConsts = list_append(new, c.largeIntConsts);
	putMachineCode(0x4800);
}

/*e*/void
mc_integerLit(s32 value)/*p;*/
{
	mc_pushTos();
	if (value >=0 && value <=255)
	{
		mc_smallIntLit(value);
	} else {
		mc_largeIntLit(value);
	}
}

/*e*/void
mc_wordStart(void)/*p;*/
{
	putMachineCode(armMov(SCRATCH, 14));
	putMachineCode(armStmia(RET_SP, (1<<SCRATCH))); // fill in later with more registers
}

/*e*/void
mc_wordEnd(u16 *fixMe)/*p;*/
{
	u32 regBits = setLocalRegsBits(c.localIndex);
	*fixMe = armStmia(RET_SP, regBits + (1<<SCRATCH));
	putMachineCode(armSubImm(RET_SP, (c.localIndex+1)<<2));
	putMachineCode(armLdmia(RET_SP, regBits + (1<<SCRATCH)));
	putMachineCode(armSubImm(RET_SP, (c.localIndex+1)<<2));
	putMachineCode(armBx(SCRATCH));
}

/*e*/void
mc_wordEndMultiLocal(u16 *fixMe)/*p;*/
{
	u32 regBits = setLocalRegsBits(c.localIndex);
	*fixMe = armStmia(RET_SP, regBits);
	putMachineCode(armSubImm(RET_SP, (c.localIndex)<<2));
	putMachineCode(armLdmia(RET_SP, regBits));
	putMachineCode(armSubImm(RET_SP, (c.localIndex)<<2));
	putMachineCode(armBx(14));
}

/*e*/void
mc_wordEnd1Local(u16 *fixMe)/*p;*/
{
	*fixMe = armStmia(RET_SP, (1<<7));
	putMachineCode(armSubImm(RET_SP, 4));
	putMachineCode(armLdrOffset(7, RET_SP, 0));
	putMachineCode(armBx(14));
}

/*e*/void
mc_wordEndNotLeafNoLocal(void)/*p;*/
{
	putMachineCode(armSubImm(RET_SP, 4));
	putMachineCode(armLdrOffset(SCRATCH, RET_SP, 0));
	putMachineCode(armBx(SCRATCH));
}

/*e*/void
mc_wordEndShort()/*p;*/
{
	putMachineCode(armBx(14));
}

/*e*/void
mc_printExprStack(void)/*p;*/
{
	callWord((u32)printFithStack);
}

/*e*/void
mc_stackAdd(void)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>8) == 32)
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		u32 val = (prevCode<<24)>>24;
		// TODO can optimize val <= 7 and local to add with load
		putMachineCode(armAddImm(TOS, val));
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		prevCode = *(c.compileCursor-1);
		if ( ((prevCode>>6) == 0x00) )
		{
			// we just pushed a local, re-write
			c.compileCursor -= 1;
			u32 src2 = prevCode>>3;
			putMachineCode(armAdd3(TOS,src2,src));
			return;
		}
		putMachineCode(armAdd3(TOS,TOS,src));
		return;
	}
	mc_popScratch();
	putMachineCode(armAdd3(TOS,TOS,SCRATCH));
}

/*e*/void
mc_stackSub(void)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>8) == 32)
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		u32 val = (prevCode<<24)>>24;
		// TODO can optimize val <= 7 and local to add with load
		putMachineCode(armSubImm(TOS, val));
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		prevCode = *(c.compileCursor-1);
		if ( ((prevCode>>6) == 0x00) )
		{
			// we just pushed a local, re-write
			c.compileCursor -= 1;
			u32 src2 = prevCode>>3;
			putMachineCode(armSub3(TOS,src2,src));
			return;
		}
		putMachineCode(armSub3(TOS,TOS,src));
		return;
	}
	mc_popScratch();
	putMachineCode(armSub3(TOS,SCRATCH,TOS));
}

// TODO do re-write of powers of 2
/*e*/void
mc_stackMul(void)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>8) == 32)
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		u32 val = (prevCode<<24)>>24;
		putMachineCode(armMovImm(SCRATCH, val));
		putMachineCode(armMul(TOS, SCRATCH));
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		putMachineCode(armMul(TOS,src));
		return;
	}
	mc_popScratch();
	putMachineCode(armMul(TOS, SCRATCH));
}

/*e*/void
mc_stackOr(void)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>8) == 32)
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		u32 val = (prevCode<<24)>>24;
		putMachineCode(armMovImm(SCRATCH, val));
		putMachineCode(armOr(TOS, SCRATCH));
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		putMachineCode(armOr(TOS,src));
		return;
	}
	mc_popScratch();
	putMachineCode(armOr(TOS, SCRATCH));
}

/*e*/void
mc_stackXor(void)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>8) == 32)
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		u32 val = (prevCode<<24)>>24;
		putMachineCode(armMovImm(SCRATCH, val));
		putMachineCode(armXor(TOS, SCRATCH));
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		putMachineCode(armXor(TOS,src));
		return;
	}
	mc_popScratch();
	putMachineCode(armXor(TOS, SCRATCH));
}

/*e*/void
mc_stackAnd(void)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>8) == 32)
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		u32 val = (prevCode<<24)>>24;
		putMachineCode(armMovImm(SCRATCH, val));
		putMachineCode(armAnd(TOS, SCRATCH));
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		putMachineCode(armAnd(TOS,src));
		return;
	}
	mc_popScratch();
	putMachineCode(armAnd(TOS, SCRATCH));
}

/*e*/void
mc_stackBitClear(void)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>8) == 32)
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		u32 val = (prevCode<<24)>>24;
		putMachineCode(armMovImm(SCRATCH, val));
		putMachineCode(armBic(TOS, SCRATCH));
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		putMachineCode(armBic(TOS,src));
		return;
	}
	putMachineCode(armMovs(SCRATCH, TOS));
	mc_popTos();
	putMachineCode(armBic(TOS, SCRATCH));
}

/*e*/void
mc_stackLS(void)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>8) == 32)
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		u32 val = (prevCode<<24)>>24;
		prevCode = *(c.compileCursor-1);
		if ( ((prevCode>>6) == 0x00) )
		{
			// we just pushed a local, re-write
			c.compileCursor -= 1;
			u32 src = prevCode>>3;
			putMachineCode(armLslsImm(TOS, src, val));
			return;
		}
		putMachineCode(armLslsImm(TOS, TOS, val));
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		putMachineCode(armLsls(TOS,src));
		return;
	}
	putMachineCode(armMovs(SCRATCH, TOS));
	mc_popTos();
	putMachineCode(armLsls(TOS,SCRATCH));
}

/*e*/void
mc_stackRS(void)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>8) == 32)
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		u32 val = (prevCode<<24)>>24;
		prevCode = *(c.compileCursor-1);
		if ( ((prevCode>>6) == 0x00) )
		{
			// we just pushed a local, re-write
			c.compileCursor -= 1;
			u32 src = prevCode>>3;
			putMachineCode(armLsrsImm(TOS, src, val));
			return;
		}
		putMachineCode(armLsrsImm(TOS, TOS, val));
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		putMachineCode(armLsrs(TOS,src));
		return;
	}
	putMachineCode(armMovs(SCRATCH, TOS));
	mc_popTos();
	putMachineCode(armLsrs(TOS,SCRATCH));
}

/*e*/void
mc_stackNot(void)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 1;
		u32 src = prevCode>>3;
		putMachineCode(armNot(TOS,src));
		return;
	}
	putMachineCode(armNot(TOS, TOS));
}

/*e*/void
mc_negTos(void)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 1;
		u32 src = prevCode>>3;
		putMachineCode(armNeg(TOS,src));
		return;
	}
	putMachineCode(armNeg(TOS, TOS));
}

/*e*/void
mc_stackLogicAnd(void)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	u32 val = (prevCode<<24)>>24;
	if ( (prevCode>>8) == 32 )
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		if (val > 0)
		{
			putMachineCode(armMovImm(SCRATCH, 1));
			putMachineCode(armNeg(SCRATCH, SCRATCH));
			putMachineCode(armAnd(TOS,SCRATCH));
		} else {
			putMachineCode(armMovImm(SCRATCH, 0));
			putMachineCode(armAnd(TOS,SCRATCH));
		}
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		putMachineCode(armNeg(TOS, TOS));
		putMachineCode(armSbcs(TOS, TOS));
		putMachineCode(armAnd(TOS,src));
		return;
	}
	//~ popScratch();
	//~ putMachineCode(armNeg(TOS, TOS));
	//~ putMachineCode(armSbcs(TOS, TOS));
	//~ putMachineCode(armAnd(TOS, SCRATCH));
	callWord((u32)fith_logicalAnd);
}

// TODO optimize adding registers together
/*e*/void
mc_stackLdrTo(void)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	u32 val = (prevCode<<24)>>24;
	if ( (prevCode>>11) == 6 && val <= 124)
	{
		// we just added a small constant, re-write
		c.compileCursor -= 1;
		prevCode = *(c.compileCursor-1);
		if ( ((prevCode>>6) == 0x00) )
		{
			// we just pushed a local, re-write
			c.compileCursor -= 1;
			u32 src = prevCode>>3;
			putMachineCode(armLdrOffset(TOS,src,val>>2));
			return;
		}
		putMachineCode(armLdrOffset(TOS,TOS,val>>2));
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 1;
		u32 src = prevCode>>3;
		putMachineCode(armLdrOffset(TOS,src,0));
		return;
	}
	putMachineCode(armLdrOffset(TOS,TOS,0));
}

/*e*/void
mc_stackStrTo(void)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	u32 val = (prevCode<<24)>>24;
	if ( (prevCode>>11) == 6 && val <= 124)
	{
		// we just added a small constant, re-write
		c.compileCursor -= 1;
		prevCode = *(c.compileCursor-1);
		if ( ((prevCode>>6) == 0x00) )
		{
			// we just pushed a local, re-write
			c.compileCursor -= 2;
			u32 dst = prevCode>>3;
			prevCode = *(c.compileCursor-1);
			if ( ((prevCode>>6) == 0x00) )
			{
				c.compileCursor -= 2;
				u32 data = prevCode>>3;
				putMachineCode(armStrOffset(data, dst, val>>2));
				return; // data ptr 4 + $= 
			}
			putMachineCode(armStrOffset(TOS,dst,val>>2));
			mc_popTos();
			return; // ptr 4 + $= 
		}
		mc_popScratch();
		putMachineCode(armStrOffset(SCRATCH,TOS,val>>2));
		mc_popTos();
		return; // 4 + $= 
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 dst = prevCode>>3;
		prevCode = *(c.compileCursor-1);
		if ( ((prevCode>>6) == 0x00) )
		{
			c.compileCursor -= 2;
			u32 data = prevCode>>3;
			putMachineCode(armStrOffset(data, dst, 0));
			return; // data ptr $= 
		}
		putMachineCode(armStrOffset(TOS,dst,0));
		mc_popTos();
		return; // ptr $= 
	}
	mc_popScratch();
	putMachineCode(armStrOffset(SCRATCH,TOS,0));
	mc_popTos(); // $=
}

/*e*/void
mc_stackLdrByteTo(void)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	u32 val = (prevCode<<24)>>24;
	if ( (prevCode>>11) == 6 && val <= 31)
	{
		// we just added a small constant, re-write
		c.compileCursor -= 1;
		prevCode = *(c.compileCursor-1);
		if ( ((prevCode>>6) == 0x00) )
		{
			// we just pushed a local, re-write
			c.compileCursor -= 1;
			u32 src = prevCode>>3;
			putMachineCode(armLdrByteOffset(TOS,src,val));
			return;
		}
		putMachineCode(armLdrByteOffset(TOS,TOS,val));
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 1;
		u32 src = prevCode>>3;
		putMachineCode(armLdrByteOffset(TOS,src,0));
		return;
	}
	putMachineCode(armLdrByteOffset(TOS,TOS,0));
}

/*e*/void
mc_stackStrByteTo(void)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	u32 val = (prevCode<<24)>>24;
	if ( (prevCode>>11) == 6 && val <= 31)
	{
		// we just added a small constant, re-write
		c.compileCursor -= 1;
		prevCode = *(c.compileCursor-1);
		if ( ((prevCode>>6) == 0x00) )
		{
			// we just pushed a local, re-write
			c.compileCursor -= 2;
			u32 dst = prevCode>>3;
			prevCode = *(c.compileCursor-1);
			if ( ((prevCode>>6) == 0x00) )
			{
				c.compileCursor -= 2;
				u32 data = prevCode>>3;
				putMachineCode(armStrByteOffset(data, dst, val));
				return; // data ptr 4 + $= 
			}
			putMachineCode(armStrByteOffset(TOS,dst,val));
			mc_popTos();
			return; // ptr 4 + $= 
		}
		mc_popScratch();
		putMachineCode(armStrByteOffset(SCRATCH,TOS,val));
		mc_popTos();
		return; // 4 + $= 
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 dst = prevCode>>3;
		prevCode = *(c.compileCursor-1);
		if ( ((prevCode>>6) == 0x00) )
		{
			c.compileCursor -= 2;
			u32 data = prevCode>>3;
			putMachineCode(armStrByteOffset(data, dst, 0));
			return; // data ptr $= 
		}
		putMachineCode(armStrByteOffset(TOS,dst,0));
		mc_popTos();
		return; // ptr $= 
	}
	mc_popScratch();
	putMachineCode(armStrByteOffset(SCRATCH,TOS,0));
	mc_popTos(); // $=
}

/*e*/void
mc_stackDiv(void)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>8) == 32)
	{
		// we just pushed a small constant, maybe re-write
		u32 val = (prevCode<<24)>>24;
		val >>= 1;
		if ((val) && ((val & (val - 1)) == 0) )
		{
			// power of two
			u32 i = 1;
			while ( (val&1) == 0 )
			{
				i++;
				val >>= 1;
			}
			c.compileCursor -= 2;
			putMachineCode(armAsrsImm(0, 0, i));
			return;
		}
	}
	if ( (prevCode>>11) == 9)
	{
		// we just pushed a large constant, maybe re-write
		u32 val = c.largeIntConsts->value;
		val >>= 8;
		if ((val) && ((val & (val - 1)) == 0) )
		{
			// power of two, do a re-write
			c.largeIntConsts->target = 0;
			u32 i = 8;
			while ( (val&1) == 0 )
			{
				i++;
				val >>= 1;
			}
			c.compileCursor -= 2;
			putMachineCode(armAsrsImm(0, 0, i));
			return;
		}
	}
	callWord((u32)fithDiv);
}

/*e*/void
mc_stackMod(void)/*p;*/
{
	callWord((u32)fithMod);
}

/*e*/void
mc_stackAbs(void)/*p;*/
{
	putMachineCode(armAsrsImm(2,0,31));
	putMachineCode(armAdd3(0,0,2));
	putMachineCode(armXor(0,2));
}

/*e*/void
mc_over(void)/*p;*/
{
	mc_pushTos();
	putMachineCode(armLdrSpOffset(TOS, 1));
}

/*e*/void
mc_pick(void)/*p;*/
{
	mc_pushTos();
	putMachineCode(armLdrSpOffset(TOS, 2));
}

/*e*/void
mc_nip(void)/*p;*/
{
	mc_popScratch();
}

/*e*/void
mc_swap(void)/*p;*/
{
	putMachineCode(armMovs(SCRATCH, TOS));
	mc_popTos();
	mc_pushScratch();
}

/*e*/void
mc_condition(void)/*p;*/
{
	// compare top two items on the stack and consume them
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>8) == 32)
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		u32 val = (prevCode<<24)>>24;
		prevCode = *(c.compileCursor-1);
		if ( ((prevCode>>6) == 0x00) )
		{
			// we just pushed a local, re-write
			c.compileCursor -= 2;
			u32 src = prevCode>>3;
			putMachineCode(armCmpImm(src, val));
			return;
		}
		putMachineCode(armCmpImm(TOS, val));
		mc_popTos();
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		prevCode = *(c.compileCursor-1);
		if ( ((prevCode>>6) == 0x00) )
		{
			// we just pushed a local, re-write
			c.compileCursor -= 2;
			u32 src2 = prevCode>>3;
			putMachineCode(armCmp(src2, src));
			return;
		}
		putMachineCode(armCmp(TOS,src));
		mc_popTos();
		return;
	}
	mc_popScratch();
	putMachineCode(armCmp(SCRATCH,TOS));
	mc_popTos();
}

/*e*/void
mc_stackLdrIndex(void)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	u32 val = (prevCode<<24)>>24;
	if ( (prevCode>>8) == 32 && val <= 31) // 3 #
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		prevCode = *(c.compileCursor-1);
		if ( ((prevCode>>6) == 0x00) ) // array 3 #
		{
			// we just pushed a local, re-write
			c.compileCursor -= 1;
			u32 addr = prevCode>>3;
			putMachineCode(armLdrOffset(TOS, addr, val));
			return;
		}
		putMachineCode(armLdrOffset(TOS, TOS, val));
		return;
	}
	if ( (prevCode>>8) == 32 && val <= 63) // 44 #
	{
		c.compileCursor -= 2;
		prevCode = *(c.compileCursor-1);
		if ( ((prevCode>>6) == 0x00) ) // array 44 #
		{
			// we just pushed a local, re-write
			c.compileCursor -= 1;
			u32 addr = prevCode>>3;
			putMachineCode(armMovImm(SCRATCH, val<<2));
			putMachineCode(armLdrOffset(TOS, addr, SCRATCH));
			return;
		}
		putMachineCode(armMovImm(SCRATCH, val<<2));
		putMachineCode(armLdrIndex(TOS,TOS,SCRATCH));
		return;
	}
	if ( ((prevCode>>6) == 0x00) ) // index #
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		prevCode = *(c.compileCursor-1);
		if ( ((prevCode>>6) == 0x00) ) // array index #
		{
			c.compileCursor -= 1;
			u32 addr = prevCode>>3;
			putMachineCode(armLslsImm(SCRATCH, src, 2));
			putMachineCode(armLdrOffset(TOS, addr, SCRATCH));
			return;
		}
		putMachineCode(armLslsImm(SCRATCH, src, 2));
		putMachineCode(armLdrIndex(TOS,TOS,SCRATCH));
		return;
	}
	putMachineCode(armLslsImm(TOS, TOS, 2)); // #
	mc_popScratch();
	putMachineCode(armLdrIndex(TOS,SCRATCH,TOS));
}

/*e*/void
mc_stackStrIndex(void)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	u32 val = (prevCode<<24)>>24;
	if ( (prevCode>>8) == 32 && val <= 31)
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		prevCode = *(c.compileCursor-1);
		if ( ((prevCode>>6) == 0x00) )
		{
			c.compileCursor -= 2;
			u32 addr = prevCode>>3;
			prevCode = *(c.compileCursor-1);
			if ( ((prevCode>>6) == 0x00) )
			{
				c.compileCursor -= 2;
				u32 data = prevCode>>3;
				putMachineCode(armStrOffset(data, addr, val));
				return; // data addr 4 #=
			}
			putMachineCode(armStrOffset(TOS, addr, val));
			mc_popTos();
			return; // addr 4 #=
		}
		mc_popScratch();
		putMachineCode(armStrOffset(SCRATCH, TOS, val));
		mc_popTos();
		return; // 4 #=
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		prevCode = *(c.compileCursor-1);
		if ( ((prevCode>>6) == 0x00) )
		{
			c.compileCursor -= 2;
			u32 addr = prevCode>>3;
			prevCode = *(c.compileCursor-1);
			if ( ((prevCode>>6) == 0x00) )
			{
				c.compileCursor -= 2;
				u32 data = prevCode>>3;
				putMachineCode(armLslsImm(SCRATCH, src, 2));
				putMachineCode(armStrIndex(data, addr, SCRATCH));
				return; // data addr index #=
			}
			putMachineCode(armLslsImm(SCRATCH, src, 2));
			putMachineCode(armStrIndex(TOS, addr, SCRATCH));
			mc_popTos();
			return;  // addr index #=
		}
		putMachineCode(armLslsImm(SCRATCH, src, 2));
		putMachineCode(armAdd3(TOS,TOS,SCRATCH));
		mc_popScratch();
		putMachineCode(armStrOffset(SCRATCH,TOS,0));
		mc_popTos();
		return; // index #=
	}
	// TODO make this a function call for code seuqences > 3
	putMachineCode(armLslsImm(TOS, TOS, 2));
	mc_popScratch();
	putMachineCode(armAdd3(TOS,TOS,SCRATCH));
	mc_popScratch();
	putMachineCode(armStrOffset(SCRATCH,TOS,0));
	mc_popTos(); // #=
}

/*e*/void
mc_generateLargeConsts(void)/*p;*/
{
	if (c.largeIntConsts == 0) { return; }
	// align cursor to 4 bytes
	if ((u32)c.compileCursor & 2) { putMachineCode(ARM_NOP); }
	u32 *constantsStart = (u32*)c.compileCursor;
	u32 *constantsCursor = constantsStart;
	*constantsCursor = 0;
	// process constants
	do {
		LargeConst *todo = list_removeFirst(&c.largeIntConsts);
		u16 *cursor = todo->target;
		if (cursor == 0) { goto skip; }
		// check if constant already generated
		u32 *walk = constantsStart;
		while (walk != constantsCursor) {
			if (*walk == todo->value) { break; }
			walk++;
		}
		// if not generate new constant and add zero sentinal
		if (walk == constantsCursor)
		{
			*constantsCursor++ = todo->value;
			*constantsCursor = 0;
		}
		u32 alignPC = (((u32)cursor + 4) >> 2) << 2;
		if (todo->putInScratch == 0) {
			*cursor = armLdrLit(TOS, ((u32)walk - alignPC) >>2);
		} else {
			*cursor = armLdrLit(SCRATCH, ((u32)walk - alignPC) >>2);
		}
		skip:
		free(todo);
	} while (c.largeIntConsts);
	c.compileCursor = (u16*)constantsCursor;
}

/*e*/void
mc_generateStringLits(void)/*p;*/
{
	if (c.stringLits == 0) { return; }
	// align cursor to 4 bytes
	if ((u32)c.compileCursor & 2) { putMachineCode(ARM_NOP); }
	u8 *constantsStart = (u8*)c.compileCursor;
	u8 *constantsCursor = constantsStart;
	// process constants
	do {
		String *todo = list_removeFirst(&c.stringLits);
		if (todo->target == 0) { goto skip; }
		// generate new string lit and add zero 
		u8 *cursor = todo->string;
		u8 *end = cursor + todo->length;
		while (cursor < end)
		{
			if (*cursor != '\\'){
				*constantsCursor++ = *cursor++;
			} else {
				switch(cursor[1])
				{
					case '\"':
					*constantsCursor++ = '\"';
					break;
					case 'n':
					*constantsCursor++ = 0x0A;
					break;
					case 'r':
					*constantsCursor++ = 0x0D;
					break;
					case 't':
					*constantsCursor++ = 0x09;
					break;
					case '\\':
					*constantsCursor++ = 0x5C;
					break;
				}
				cursor += 2;
			}
		}
		*constantsCursor++ = 0;
		// output relative address calculation
		u32 alignPC = (((u32)todo->target + 4) >> 2) << 2;
		*todo->target = armAdr(TOS, ((u32)constantsStart - alignPC) >>2);
		// set up new pointers, round up to next 4 bytes
		constantsStart = (u8*)(((u32)constantsCursor + 3) >> 2 << 2);
		constantsCursor = constantsStart;
		skip:
		free(todo);
	} while (c.stringLits);
	c.compileCursor = (u16*)constantsStart;
}

/*e*/void
mc_strGlobal(u32 *globalAddr)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		// load address
		mc_largeIntLit((u32)globalAddr);
		// put it into scratch instead of TOS
		c.largeIntConsts->putInScratch = 1;
		putMachineCode(armStrOffset(src, SCRATCH, 0));
		return;
	}
	// load address
	mc_largeIntLit((u32)globalAddr);
	// put it into scratch instead of TOS
	c.largeIntConsts->putInScratch = 1;
	putMachineCode(armStrOffset(TOS, SCRATCH, 0));
	mc_popTos();
}

/*e*/void
mc_ldrGlobal(u32 *globalAddr)/*p;*/
{
	mc_pushTos();
	// load address
	mc_largeIntLit((u32)globalAddr);
	// put it into scratch instead of TOS
	c.largeIntConsts->putInScratch = 1;
	putMachineCode(armLdrOffset(TOS, SCRATCH, 0));
}

/*e*/void
mc_addEqualsGlobal(u32 *globalAddr)/*p;*/
{
	// load address
	mc_largeIntLit((u32)globalAddr);
	// put it into scratch instead of TOS
	c.largeIntConsts->putInScratch = 1;
	// do the rest in here
	callWord((u32)fithAddEqualsGlobal);
}

/*e*/void
mc_subEqualsGlobal(u32 *globalAddr)/*p;*/
{
	// load address
	mc_largeIntLit((u32)globalAddr);
	// put it into scratch instead of TOS
	c.largeIntConsts->putInScratch = 1;
	// do the rest in here
	callWord((u32)fithSubEqualsGlobal);
}

/*e*/void
mc_lshEqualsGlobal(u32 *globalAddr)/*p;*/
{
	// load address
	mc_largeIntLit((u32)globalAddr);
	// put it into scratch instead of TOS
	c.largeIntConsts->putInScratch = 1;
	// do the rest in here
	callWord((u32)fithLslsEqualsGlobal);
}

/*e*/void
mc_rshEqualsGlobal(u32 *globalAddr)/*p;*/
{
	// load address
	mc_largeIntLit((u32)globalAddr);
	// put it into scratch instead of TOS
	c.largeIntConsts->putInScratch = 1;
	// do the rest in here
	callWord((u32)fithLsrsEqualsGlobal);
}

/*e*/void
mc_andEqualsGlobal(u32 *globalAddr)/*p;*/
{
	// load address
	mc_largeIntLit((u32)globalAddr);
	// put it into scratch instead of TOS
	c.largeIntConsts->putInScratch = 1;
	// do the rest in here
	callWord((u32)fithAndEqualsGlobal);
}

/*e*/void
mc_bicEqualsGlobal(u32 *globalAddr)/*p;*/
{
	// load address
	mc_largeIntLit((u32)globalAddr);
	// put it into scratch instead of TOS
	c.largeIntConsts->putInScratch = 1;
	// do the rest in here
	callWord((u32)fithBicEqualsGlobal);
}

/*e*/void
mc_xorEqualsGlobal(u32 *globalAddr)/*p;*/
{
	// load address
	mc_largeIntLit((u32)globalAddr);
	// put it into scratch instead of TOS
	c.largeIntConsts->putInScratch = 1;
	// do the rest in here
	callWord((u32)fithXorEqualsGlobal);
}

/*e*/void
mc_orrEqualsGlobal(u32 *globalAddr)/*p;*/
{
	// load address
	mc_largeIntLit((u32)globalAddr);
	// put it into scratch instead of TOS
	c.largeIntConsts->putInScratch = 1;
	// do the rest in here
	callWord((u32)fithOrrEqualsGlobal);
}

/*e*/void
mc_mulEqualsGlobal(u32 *globalAddr)/*p;*/
{
	// load address
	mc_largeIntLit((u32)globalAddr);
	// put it into scratch instead of TOS
	c.largeIntConsts->putInScratch = 1;
	// do the rest in here
	callWord((u32)fithMulEqualsGlobal);
}

/*e*/void
mc_modEqualsGlobal(u32 *globalAddr)/*p;*/
{
	// load global
	mc_ldrGlobal(globalAddr);
	// swap operators
	mc_swap();
	// do the mod operation
	mc_stackMod();
	// store global
	mc_strGlobal(globalAddr);
}

/*e*/void
mc_divEqualsGlobal(u32 *globalAddr)/*p;*/
{
	// load global
	mc_ldrGlobal(globalAddr);
	// swap operators
	mc_swap();
	// do the mod operation
	mc_stackDiv();
	// store global
	mc_strGlobal(globalAddr);
}


/*e*/u32*
mc_createGlobal(void)/*p;*/
{
	if ((u32)c.compileBase & 2) { c.compileBase++; }
	u32 *globalAddr = (u32*)c.compileBase;
	c.compileBase = c.compileBase + 2;
	c.compileCursor = c.compileBase;
	mc_wordStart();
	return globalAddr;
}

/*e*/void
mc_strLocal(u32 localNum)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>8) == 32)
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		u32 val = (prevCode<<24)>>24;
		putMachineCode(armMovImm(localNum, val));
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		putMachineCode(armMov(localNum,src));
		return;
	}
	// move TOS into local
	putMachineCode(armMovs(localNum, TOS));
	mc_popTos();
}

/*e*/void
mc_ldrLocal(u32 localNum)/*p;*/
{
	mc_pushTos();
	putMachineCode(armMovs(TOS, localNum));
}

/*e*/void
mc_addEqualsLocal(u32 localNum)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>8) == 32)
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		u32 val = (prevCode<<24)>>24;
		putMachineCode(armAddImm(localNum, val));
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		putMachineCode(armAdd3(localNum,localNum,src));
		return;
	}
	putMachineCode(armAdd3(localNum,localNum,TOS));
	mc_popTos();
}

/*e*/void
mc_subEqualsLocal(u32 localNum)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>8) == 32)
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		u32 val = (prevCode<<24)>>24;
		putMachineCode(armSubImm(localNum, val));
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		putMachineCode(armSub3(localNum,localNum,src));
		return;
	}
	putMachineCode(armSub3(localNum,localNum,TOS));
	mc_popTos();
}

/*e*/void
mc_lshEqualsLocal(u32 localNum)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>8) == 32)
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		u32 val = (prevCode<<24)>>24;
		putMachineCode(armLslsImm(localNum, localNum, val));
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		putMachineCode(armLsls(localNum,src));
		return;
	}
	putMachineCode(armLsls(localNum, TOS));
	mc_popTos();
}

/*e*/void
mc_rshEqualsLocal(u32 localNum)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>8) == 32)
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		u32 val = (prevCode<<24)>>24;
		putMachineCode(armLsrsImm(localNum, localNum, val));
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		putMachineCode(armLsrs(localNum,src));
		return;
	}
	putMachineCode(armLsrs(localNum, TOS));
	mc_popTos();
}

/*e*/void
mc_andEqualsLocal(u32 localNum)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>8) == 32)
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		u32 val = (prevCode<<24)>>24;
		putMachineCode(armMovImm(SCRATCH, val));
		putMachineCode(armAnd(localNum, SCRATCH));
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		putMachineCode(armAnd(localNum,src));
		return;
	}
	putMachineCode(armAnd(localNum,TOS));
	mc_popTos();
}

/*e*/void
mc_bicEqualsLocal(u32 localNum)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>8) == 32)
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		u32 val = (prevCode<<24)>>24;
		putMachineCode(armMovImm(SCRATCH, val));
		putMachineCode(armBic(localNum, SCRATCH));
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		putMachineCode(armBic(localNum,src));
		return;
	}
	putMachineCode(armBic(localNum,TOS));
	mc_popTos();
}

/*e*/void
mc_xorEqualsLocal(u32 localNum)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>8) == 32)
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		u32 val = (prevCode<<24)>>24;
		putMachineCode(armMovImm(SCRATCH, val));
		putMachineCode(armXor(localNum, SCRATCH));
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		putMachineCode(armXor(localNum,src));
		return;
	}
	putMachineCode(armXor(localNum,TOS));
	mc_popTos();
}

/*e*/void
mc_orrEqualsLocal(u32 localNum)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>8) == 32)
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		u32 val = (prevCode<<24)>>24;
		putMachineCode(armMovImm(SCRATCH, val));
		putMachineCode(armOr(localNum, SCRATCH));
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		putMachineCode(armOr(localNum,src));
		return;
	}
	putMachineCode(armOr(localNum,TOS));
	mc_popTos();
}

/*e*/void
mc_mulEqualsLocal(u32 localNum)/*p;*/
{
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>8) == 32)
	{
		// we just pushed a small constant, re-write
		c.compileCursor -= 2;
		u32 val = (prevCode<<24)>>24;
		putMachineCode(armMovImm(SCRATCH, val));
		putMachineCode(armMul(localNum, SCRATCH));
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		putMachineCode(armMul(localNum,src));
		return;
	}
	putMachineCode(armMul(localNum,TOS));
	mc_popTos();
}

/*e*/void
mc_modEqualsLocal(u32 localNum)/*p;*/
{
	// load local
	mc_ldrLocal(localNum);
	// swap operators
	mc_swap();
	// do the mod operation
	mc_stackMod();
	// store local
	mc_strLocal(localNum);
}

/*e*/void
mc_divEqualsLocal(u32 localNum)/*p;*/
{
	// load local
	mc_ldrLocal(localNum);
	// swap operators
	mc_swap();
	// do the mod operation
	mc_stackDiv();
	// store local
	mc_strLocal(localNum);
}

/*e*/static u32
setLocalRegsBits(s32 numVars)/*i;*/
{
	u32 regBits = 0;
	for (s32 x = 0; x < numVars; x++)
	{
		regBits <<= 1;
		regBits++;
	}
	regBits <<= 8 - numVars;
	return regBits;
}

/*e*/void
mc_setParams(void)/*p;*/
{
	if (!c.insideParams) { io_prints("Error: not inside params.\n"); return; }
	if (c.localIndex > 1)
	{
		u32 regBits = setLocalRegsBits(c.localIndex - 1);
		putMachineCode(armPop(regBits));
	}
	putMachineCode(armMovs(8-c.localIndex, TOS));
	mc_popTos();
	c.insideParams = 0;
}

/*e*/void
mc_call(void)/*p;*/
{
	c.notLeaf = 1;
	u32 prevCode = *(c.compileCursor-1);
	if ( (prevCode>>11) == 9)
	{
		// we just pushed a large constant, re=write
		c.compileCursor -= 2;
		c.largeIntConsts->target = 0;
		callWord(c.largeIntConsts->value);
		return;
	}
	if ( ((prevCode>>6) == 0x00) )
	{
		// we just pushed a local, re-write
		c.compileCursor -= 2;
		u32 src = prevCode>>3;
		putMachineCode(armBlx(src));
		return;
	}
	putMachineCode(armMovs(SCRATCH, TOS));
	mc_popTos();
	putMachineCode(armBlx(SCRATCH));
}

/*e*/void
mc_newCoroutine(u16 *cursor)/*p;*/
{
	// output relative address calculation
	u32 alignPC = (((u32)cursor + 4) >> 2) << 2;
	*cursor = armAdr(SCRATCH, ((u32)(cursor+4) - alignPC) >>2);
	cursor++;
	*cursor = armPush((1<<1)+(1<<3)+(1<<4)+(1<<5)+(1<<6)+(1<<7)+(1<<8));
	cursor++;
	mc_callRelative((u32)co_call, (u32)cursor);
}

/*e*/void
checkedPopTosPrint(void)/*p;*/
{
	io_printsn("Stack underflow.");
}
