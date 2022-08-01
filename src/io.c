// io.c
#include "../localTypes.h"

static u8   uart0Buffer[256];
static u32  uart0BuffStartIndex;
static u32  uart0BuffIndex;
ROMFunctions rom_func;

/*e*/
s32
s2i(u8 *b, u8 **e)/*p;*/
{
	s32 result     = 0;
	s32 isNegative = 1;
	if (*b == '-')
	{
		b++;
		isNegative = -1;
	}
	
	if (*b == '0' && *(b+1) == 'x')
	{
		// process hex numbers
		b += 2;
		tryAnotherByte:
		if ( (*b >= '0') && (*b <= '9') )
		{
			result = (result * 16) + (*b - '0');
			b++;
			goto tryAnotherByte;
		} else if ( (*b >= 'A') && (*b <= 'F') ) {
			result = (result * 16) + (*b - ('A' - 10));
			b++;
			goto tryAnotherByte;
		} else {
			goto end;
		}
	}
	
	while( (*b >= '0') && (*b <= '9') )
	{
		result = (result * 10) + (*b - '0');
		b++;
	}
	
	end:
	result = isNegative * result;
	if (e) { *e = b; }
	
	return result;
}

/*e*/
u8*
i2s(s32 in, u8 *out)/*p;*/
{
	u8 number[16];
	s32 remainder = 0;
	s32 index = 0;
	s32 isNegative = 0;
	if (in >> 31)
	{
		isNegative = 1;
		in = -in;
	}
	do {
		remainder = asmMod(10, in);
		in        = asmGetDiv();
		number[index++] = remainder + '0';
	} while (in != 0);
	index--;
	// number is now consumed as a string
	if (isNegative)
	{
		*out++ = '-';
	}
	do {
		*out++ = number[index--];
	} while (index >= 0);
	*out = 0;
	return out;
}

/*e*/
u8*
i2sh(s32 in, u8 *out)/*p;*/
{
	// generate number directly in output
	s32 byte;
	for (s32 x = 0; x < 8; x++)
	{
		byte = (in>>((7-x)*4))&0x0F;
		byte += '0';
		if (byte > '9')
		{
			byte += 7;
		}
		out[x] = byte;
	}
	out += 8;
	*out = 0;
	return out;
}

static void txByte(u32 byte)
{
	Uart0MemMap *uart = (void*)UART0_BASE;
	//~ printAgain:
	// print buffer is full, wait for space to open in tx fifo
	while ((uart->flags&(1<<5))!=0) { }
	uart->data = byte;
	// deal with /r/n sequence
	//~ if (byte == '\n') { byte = '\r'; goto printAgain; }
}

/*e*/
void io_txByte(u32 byte)/*p;*/
{
	asm("CPSID i");
	os_takeSpinLock(LOCK_UART0_OUT);
	txByte(byte);
	os_giveSpinLock(LOCK_UART0_OUT);
	asm("CPSIE i");
}


/*e*/
void io_prints(u8 *string)/*p;*/
{
	asm("CPSID i");
	os_takeSpinLock(LOCK_UART0_OUT);
	u32 byte = *string++;
	if (byte != 0)
	{
		do {
			txByte(byte);
			byte = *string++;
		} while (byte != 0);
	}
	os_giveSpinLock(LOCK_UART0_OUT);
	asm("CPSIE i");
}

/*e*/
void io_printsn(u8 *string)/*p;*/
{
	asm("CPSID i");
	os_takeSpinLock(LOCK_UART0_OUT);
	u32 byte = *string++;
	if (byte != 0)
	{
		do {
			txByte(byte);
			byte = *string++;
		} while (byte != 0);
	}
	txByte('\n');
	os_giveSpinLock(LOCK_UART0_OUT);
	asm("CPSIE i");
}

/*e*/
void io_printsl(u8 *string, u32 len)/*p;*/
{
	asm("CPSID i");
	os_takeSpinLock(LOCK_UART0_OUT);
	for (u32 i = 0; i < len; i++)
	{
		txByte(string[i]);
	}
	os_giveSpinLock(LOCK_UART0_OUT);
	asm("CPSIE i");
}

/*e*/
void io_printsln(u8 *string, u32 len)/*p;*/
{
	asm("CPSID i");
	os_takeSpinLock(LOCK_UART0_OUT);
	for (u32 i = 0; i < len; i++)
	{
		txByte(string[i]);
	}
	txByte('\n');
	os_giveSpinLock(LOCK_UART0_OUT);
	asm("CPSIE i");
}

/*e*/
void io_printi(s32 in)/*p;*/
{
	u8 number[16];
	i2s(in, number);
	io_prints(number);
}

/*e*/
void io_printh(s32 in)/*p;*/
{
	u8 number[16];
	i2sh(in, number);
	io_prints(number);
}

/*e*/
void io_printin(s32 in)/*p;*/
{
	u8 number[16];
	i2s(in, number);
	io_printsn(number);
}

/*e*/
void io_printhn(s32 in)/*p;*/
{
	u8 number[16];
	i2sh(in, number);
	io_printsn(number);
}

/*e*/
s32 io_programFlash(void *data, u32 size, u32 targetBlockNum)/*p;*/
{
	// reserve the first 67 blocks for RAM mirror
	//~ if (targetBlockNum < 67) { return -1; }
	// round up size to 256
	
	size = (size + 255) / 256 * 256;
	u32 blockAddr = targetBlockNum * 4096;
	u32 blockSize = (size + 4095) / 4096 * 4096;
	asm("CPSID i");
	os_takeSpinLock(LOCK_FLASH);
	rom_func._connect_internal_flash();
	rom_func._flash_exit_xip();
	rom_func._flash_range_erase(blockAddr, blockSize, 4096, 0x20);
	rom_func.flash_range_program(blockAddr, data, size);
	rom_func._flash_flush_cache();
	xipSetup();
	os_giveSpinLock(LOCK_FLASH);
	asm("CPSIE i");
	return 0;
}

#define SIO_GPIO_OUT_XOR (SIO_BASE + 0x1C) 

/*e*/
void io_ledToggle(void)/*p;*/
{
	u32 *gpioXor = (void*)SIO_GPIO_OUT_XOR;
	*gpioXor = (1<<25);
}

static void bufferAndSend(u32 data)
{
	uart0Buffer[uart0BuffIndex++] = data;
	if (data == 0x0D) // finished line
	{
		// add new line and null terminate
		uart0Buffer[uart0BuffIndex++] = '\n';
		uart0Buffer[uart0BuffIndex++] = 0;
		u32 startOfLine = (u32)&uart0Buffer[uart0BuffStartIndex];
		if (uart0BuffIndex > 128)
		{
			uart0BuffStartIndex = 0;
			uart0BuffIndex = 0;
		} else {
			uart0BuffStartIndex = uart0BuffIndex;
		}
		u32 dataToSend = ((u32)armFith << 16 >> 16);
		dataToSend += startOfLine << 16;
		helper_sendMsg1(dataToSend);
		asm("sev");
	}
}

void uart0SingleChar(void *arg)
{
	Uart0MemMap *uart = arg;
	do {
		//~ (*uartHandler)(uart->data);
		bufferAndSend(uart->data);
	} while ( (uart->flags & (1<<4)) == 0);
	// we have finished draining the fifo from input. Enable rx interrupts.
	uart->intMaskSet |= (1<<4)|(1<<6);
}

/*e*/
void isr_Uart0(void)/*p;*/
{
	Uart0MemMap *uart = (void*)UART0_BASE;
	//~ io_printhn(uart->rawIntStatus);
	// clear the interrupts
	uart->intClear = 0x7FF;
	// turn off rx because we do NOT want to trigger again until finished
	uart->intMaskSet = 0;
	uart0SingleChar(uart);
}

typedef void *(*rom_table_lookup_fn)(u16 *table, u32 code);

static void*
rom_func_lookup(u32 code)
{
	rom_table_lookup_fn *rom_table_lookup = (rom_table_lookup_fn*)0x18;
	u16 *func_table = (u16 *)0x14;
	return (*rom_table_lookup)((u16 *)(u32)(*func_table), code);
}

//~ static void*
//~ rom_data_lookup(u32 code)
//~ {
	//~ rom_table_lookup_fn *rom_table_lookup = (rom_table_lookup_fn*)0x18;
	//~ u16 *data_table = (u16 *)0x16;
	//~ return (*rom_table_lookup)((u16 *)(u32)(*data_table), code);
//~ }

static u32 rom_table_code(u8 c1, u8 c2)
{
	return (c2 << 8) | c1;
}

static void
loadRomFuncAddrs(void)
{
	// grab all function addresses
	rom_func._connect_internal_flash = rom_func_lookup(rom_table_code('I','F'));
	rom_func._flash_exit_xip = rom_func_lookup(rom_table_code('E','X'));
	rom_func._flash_range_erase = rom_func_lookup(rom_table_code('R','E'));
	rom_func.flash_range_program = rom_func_lookup(rom_table_code('R','P'));
	rom_func._flash_flush_cache = rom_func_lookup(rom_table_code('F','C'));
	rom_func.memcpy = rom_func_lookup(rom_table_code('M','C'));
	rom_func.memset = rom_func_lookup(rom_table_code('M','S'));
}

/*e*/
void picoInit(void)/*p;*/
{
	// clear error flags in FIFO
	u32 *fifoStatus = (void*)SIO_FIFO_ST;
	*fifoStatus = 0x0C;
	// disable all interrupts
	u32 *intDisable = (void*)PPB_INTERRUPT_DISABLE;
	*intDisable = 0xFFFFFFFF;
	// clear all pending interrupts
	u32 *intPend = (void*)PPB_INTERRUPT_CLEAR_PEND;
	*intPend = 0xFFFFFFFF;
	// enable NVIC interrupts
	u32 *intEnable = (void*)PPB_INTERRUPT_ENABLE;
	*intEnable = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<15)|(1<<20)|(1<<26)|(1<<27)|(1<<28);
	// set interrupt priorities
	u32 *intPriority = (void*)PPB_NVIC_IPR6;
	*intPriority++ = (1<<22)|(2<<30);
	*intPriority = (3<<6);
	// disable deep sleep and disable "wake up on every possible event"
	u32 *sysCtrl = (void*)PPB_SYS_CNTRL;
	*sysCtrl = 0;
	// set sysTick to lowest priority and PendSV
	intPriority = (void*)PPB_SYS_SHPR2;
	*intPriority = (3<<30)|(3<<22);
	intPriority--; *intPriority = (3<<30); // SVC is also lowest priority
	//~ enableWatchDogTick();
	//~ timerInit();
	loadRomFuncAddrs();
	
	
	// set up flash
	rom_func._connect_internal_flash();
	rom_func._flash_exit_xip();
	rom_func._flash_flush_cache();
	xipSetup();
	// we can now read flash addresses
	//~ treeTest();
}
