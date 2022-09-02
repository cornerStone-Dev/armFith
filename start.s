
.cpu cortex-m0plus
.thumb
.syntax unified

;@ Section Constants
ATOMIC_XOR         = 0x1000
ATOMIC_SET         = 0x2000
ATOMIC_CLR         = 0x3000
PBB_BASE           = 0xE0000000
SYST_CSR           = PBB_BASE + 0xE010
SYST_RVR           = 0x04
SYST_CVR           = 0x08
SYST_CALIB         = 0x0C
EXTERNAL_INTS_E      = PBB_BASE + 0xE180
EXTERNAL_INTS      = PBB_BASE + 0xE280
ICSR_REG           = PBB_BASE + 0xED04
VTOR               = PBB_BASE + 0xED08
XOSC_BASE          = 0x40024000
XOSC_CTRL_RW       = XOSC_BASE + 0x00
XOSC_CTRL_SET      = XOSC_CTRL_RW + 0x2000
XOSC_STATUS        = XOSC_BASE + 0x04
XOSC_STARTUP       = XOSC_BASE + 0x0C
XOSC_CTRL_RW_OFF       =  0x00
XOSC_STATUS_OFF        =  0x04
XOSC_STARTUP_OFF       =  0x0C
CLOCKS_BASE        = 0x40008000
CLK_REF_CTRL       = CLOCKS_BASE + 0x30
CLK_REF_SELECTED   = CLOCKS_BASE + 0x38
CLK_SYS_CTRL       = CLOCKS_BASE + 0x3C
CLK_SYS_SELECTED   = CLOCKS_BASE + 0x44
CLK_PERI_CTRL      = CLOCKS_BASE + 0x48
CLK_SYS_RESUS_CTRL = CLOCKS_BASE + 0x78
CLK_REF_CTRL_OFF       = 0x30
CLK_REF_SELECTED_OFF   = 0x38
CLK_SYS_CTRL_OFF      = 0x3C
CLK_SYS_SELECTED_OFF   = 0x44
CLK_PERI_CTRL_OFF      = 0x48
CLK_SYS_RESUS_CTRL_OFF = 0x78
PSM_BASE           = 0x40010000
PSM_WDSEL          = PSM_BASE + 0x08
SYSCFG_BASE        = 0x40004000
PROC_0_NMI         = SYSCFG_BASE + 0x00

SIO_BASE               = 0xD0000000
SIO_GPIO_OUT_CLR       = SIO_BASE + 0x18
SIO_GPIO_OUT_XOR       = SIO_BASE + 0x1C 
SIO_GPIO_OE_SET        = SIO_BASE + 0x24
SIO_GPIO_OE_CLR        = SIO_BASE + 0x28
SIO_FIFO_ST            = 0x050
SIO_FIFO_WRITE         = 0x054
SIO_FIFO_READ          = 0x058
SIO_SIGNED_DIVIDEND    = 0x068
SIO_SIGNED_DIVISOR     = 0x06C
SIO_QUOTIENT           = 0x070
SIO_REMAINDER          = 0x074
SIO_DIV_CSR            = 0x078
SIO_SPINLOCK_0         = SIO_BASE + 0x16C

PPB_BASE               = 0xE0000000
PPB_INTERRUPT_PEND     = PPB_BASE + 0xE280


IO_BANK0_BASE          = 0x40014000
IO_GPIO00_CTRL         = IO_BANK0_BASE + 0x004
IO_GPIO01_CTRL         = IO_BANK0_BASE + 0x00C
IO_GPIO12_CTRL         = IO_BANK0_BASE + 0x064
IO_GPIO13_CTRL         = IO_BANK0_BASE + 0x06C


IO_GPIO25_CTRL_RW      = IO_BANK0_BASE + 0x0CC

RESETS_RESET_CLR       = 0x4000C000 + 0x3000
RESETS_RESET_DONE_RW   = 0x4000C000 + 0x8  

WATCHDOG_BASE      = 0x40058000
WATCHDOG_CNTRL     = WATCHDOG_BASE

PLL_SYS_BASE       = 0x40028000
PLL_SYS_CTRL       = PLL_SYS_BASE + 0x00
PLL_SYS_POWER      = PLL_SYS_BASE + 0x04
PLL_SYS_FBDIV      = PLL_SYS_BASE + 0x08
PLL_SYS_PRIM       = PLL_SYS_BASE + 0x0C

UART0_BASE         = 0x40034000
UART0_DR           = 0x000
UART0_FR           = 0x018
UART0_IBRD         = 0x024
UART0_FBRD         = 0x028
UART0_LCR          = 0x02C
UART0_CR           = 0x030
UART0_IRMASK       = 0x038
UART0_IRMASKSTATUS = 0x040
UART0_IRCLEAR      = 0x044
UART0_DMA_CR       = 0x048

DMA_BASE           = 0x50000000
DMA0_READ          = 0x000
DMA0_WRITE         = 0x004
DMA0_TRAN_CNT      = 0x008
DMA0_CTRL          = 0x00C
DMA1_READ          = 0x054
DMA1_WRITE         = 0x058
DMA1_TRAN_CNT      = 0x05C
DMA1_CTRL          = 0x050

DMA_2_BASE         = 0x50000090
DMA2_CTRL          = 0x0
DMA2_READ          = 0x4
DMA2_WRITE         = 0x8
DMA2_TRAN_CNT      = 0xc
DMA3_CTRL          = 0x40
DMA3_READ          = 0x44
DMA3_WRITE         = 0x48
DMA3_TRAN_CNT      = 0x4c
      
DELAY_COUNT = 0x00100000

FIFO_BUFF_START  = 0x20040000
FIFO_WRITER_ADDR = 0x20040100

END_OF_RAM              = 0x20042000
CORE0_FITH_RETURN_STACK = 0x20041C20
CORE1_FITH_EXPR_STACK   = 0x20041000
CORE1_FITH_RETURN_STACK = 0x20040C00
SIZE_OF_RAM_BUILD = (__bss_start__-0x20000000)

PICO_FLASH_SPI_CLKDIV =  4

CMD_READ =  0x03

// Value is number of address bits divided by 4
ADDR_L =  6
SSI_CTRLR0_SPI_FRF_VALUE_STD =  0x0
SSI_CTRLR0_SPI_FRF_LSB  =      21
SSI_SPI_CTRLR0_XIP_CMD_LSB = 24
SSI_SPI_CTRLR0_ADDR_L_LSB = 2
SSI_SPI_CTRLR0_INST_L_LSB = 8
SSI_SPI_CTRLR0_TRANS_TYPE_VALUE_1C1A = 0
SSI_SPI_CTRLR0_TRANS_TYPE_LSB = 0
SSI_CTRLR0_DFS_32_LSB = 16
SSI_CTRLR0_TMOD_VALUE_EEPROM_READ = 3
SSI_CTRLR0_TMOD_LSB = 8
CTRLR0_XIP =  (SSI_CTRLR0_SPI_FRF_VALUE_STD << SSI_CTRLR0_SPI_FRF_LSB) + (31 << SSI_CTRLR0_DFS_32_LSB) + (SSI_CTRLR0_TMOD_VALUE_EEPROM_READ  << SSI_CTRLR0_TMOD_LSB)

SPI_CTRLR0_XIP = (CMD_READ << SSI_SPI_CTRLR0_XIP_CMD_LSB) + (ADDR_L << SSI_SPI_CTRLR0_ADDR_L_LSB) + (2 << SSI_SPI_CTRLR0_INST_L_LSB) + (SSI_SPI_CTRLR0_TRANS_TYPE_VALUE_1C1A << SSI_SPI_CTRLR0_TRANS_TYPE_LSB)


;@ Section Macros

.macro NEXT
	ldrh r1, [r7, r7]
	add  r1, r8
	bx   r1
.endm

;@ Section Vector Table
.global vector_table
vector_table:
	b reset
	.balign 4
	.word reset ;@ has to be offset 4
	.word REBOOT ;@purgatory  ;@ 2 NMI
	.word whoisme ;@purgatory  ;@ 3 HardFault

	.word SIZE_OF_RAM_BUILD ;@ 4 Reserved
	.word flashEntry   ;@ 5 Reserved
	.word 0  ;@ 6 Reserved
	.word REBOOT  ;@ 7 Reserved
	
	.word REBOOT  ;@ 8 Reserved
	.word REBOOT  ;@ 9 Reserved
	.word REBOOT  ;@ 10 Reserved
	.word REBOOT  ;@ 11 SVCall
	
	.word REBOOT  ;@ 12 Reserved
	.word REBOOT  ;@ 13 Reserved
	.word REBOOT  ;@ 14 PendSV isrPendSvCall
	.word REBOOT  ;@ 15 SysTick
	
	.word REBOOT   ;@ 16 external interrupt 0
	.word REBOOT
	.word REBOOT
	.word REBOOT
	
	.word REBOOT   ;@ 4
	.word REBOOT
	.word REBOOT
	.word REBOOT
	
	.word REBOOT   ;@ 8
	.word REBOOT
	.word REBOOT
	.word REBOOT
	
	.word REBOOT   ;@ 12
	.word REBOOT
	.word REBOOT
	.word fifoEnqueue
	
	.word fifoEnqueue   ;@ 16
	.word REBOOT
	.word REBOOT
	.word REBOOT
	
	.word isr_Uart0   ;@ 20
	.word REBOOT
	.word REBOOT
	.word REBOOT
	
	.word REBOOT   ;@ 24
	.word REBOOT
	.word REBOOT;@runTasksP0   ;@ 26, first software defined interrupt
	.word REBOOT;@runTasksP1
	
	.word REBOOT;@runTasksP2   ;@ 28
	.word REBOOT
	.word REBOOT
	.word REBOOT

.balign 2
.code 16
.thumb_func
.global setZeroWait
.type setZeroWait, %function
setZeroWait:
	ldr  r2,=DMA_2_BASE ;@ base reg
1:
	ldr  r3,[r2, #DMA2_CTRL]
	lsls r3, 7
	bmi  1b
	bx lr

.balign 4
.global boot2Entry
;@~ .thumb_func
;@~ .type boot2Entry, %function
boot2Entry:
	bl   clocksSetup ;@ set up clocks
	bl   xipSetup ;@ set up xip to do flash reads
	;@ r0 = 0, r1 = 1 rest is garbage
	
	lsls r6,r1,#29 ;@ RAM addr
	ldr  r5, =0x10000000 + 4096;@ flash addr
	
	ldr  r1, [r5, #16] ;@ size of code
	;@ r0=0, r1=size of code;r5=flash base;r6=RAM base; 
1:
	ldr  r4, [r5, r0] ;@ load from flash
	str  r4, [r6, r0] ;@ store to ram
	adds r0, 4
	cmp  r0, r1
	bne  1b
	ldr  r4, [r6, #20] ;@ load flash entry vector
	blx  r4

.global clocksSetup
.thumb_func
.type clocksSetup, %function
clocksSetup:
    ldr r2,=XOSC_BASE
	movs r1, 47
	str r1,[r2, #XOSC_STARTUP_OFF] ;@ set timeout, from manual
	ldr r1,=0xFABAA0
	str r1,[r2, #XOSC_CTRL_RW_OFF] ;@ set enable and speed range

1:
	ldr r1,[r2, #XOSC_STATUS_OFF] ;@ read status to see if it is ready
	cmp r1, #0
	bge 1b

	ldr  r2,=CLOCKS_BASE
	movs r1, 0
	str  r1,[r2, #CLK_SYS_RESUS_CTRL_OFF] ;@ disable resus mis-feature
	movs r1, 2
	str  r1,[r2, #CLK_REF_CTRL_OFF] ;@ move reference clock to crystal
	movs r3, 4
1:
	ldr r1,[r2, #CLK_REF_SELECTED_OFF] ;@ read status to see if it is ready
	tst r1, r3
	beq 1b
	
	;@ bring up PLL
	movs r3, 1
	lsls r3,r3,#12
	ldr r0, =RESETS_RESET_CLR
	str r3, [r0]
	ldr r0, =RESETS_RESET_DONE_RW ;@ read status to see if it is ready
1:
	ldr r1,[r0]
	tst r1, r3
	beq 1b
	
	ldr  r2,=PLL_SYS_BASE ;@ base reg 
	movs r1, 40
	str  r1,[r2, #PLL_SYS_FBDIV - PLL_SYS_BASE] ;@ set up multiplier
	
	ldr r0,=PLL_SYS_POWER + ATOMIC_CLR ;@ turn on power
	movs r1, 0x21
	str r1,[r0]
	
	movs r3, 1
	lsls r3,r3,#31
1:
	ldr r1,[r2] ;@ wait for resonance cascade
	tst r1, r3
	beq 1b
	
	;@~ ldr r1,=(((4<<16)|(1<<12))>>12)
	movs r1, 0x41
	lsls r1, 12
	str r1,[r2, #PLL_SYS_PRIM - PLL_SYS_BASE] ;@ set post dividers
	
	;@ turn on post dividers
	movs r1, 0x08
	str r1,[r0]
	;@ PLL_SYS is now at 120 mhz, pico max is 133, this is 90% of that
	;@ so nice margin of safety
	
	ldr r2,=CLOCKS_BASE
	movs r1, 1
	str r1,[r2, #CLK_SYS_CTRL_OFF] ;@ set sys clock to PLL_SYS
	movs r3,2
1:
	ldr r1,[r2, #CLK_REF_SELECTED_OFF] ;@ read status to see if it is ready
	tst r1, r3
	bne 1b
	
	movs r1, 0x88
	lsls r1, 4
	str  r1,[r2, #CLK_PERI_CTRL_OFF] ;@ set peripheral clock to the ref clock and enable
	;@ we are done
	bx   lr

.global xipSetup
.thumb_func
.type xipSetup, %function
xipSetup: ;@ r0-r3 are garbage
	;@ try to set up xip
	movs  r3, 0x18                // Use as base address where possible
	lsls r3, 24

    // Disable SSI to allow further config
    movs r0, #0
    str  r0, [r3, #0x08]
    
    // NDF=0 (single 32b read)
    str  r0, [r3, #0x04]

    // Set baud rate
    movs r1, #4
    str  r1, [r3, #0x14]

    ldr  r1, =(CTRLR0_XIP)
    str  r1, [r3, #0x00]

    ldr  r1, =(SPI_CTRLR0_XIP)
    adds r3, #244
    str  r1, [r3]

    // Re-enable SSI
    subs r3, #244
    movs r1, #1
    str  r1, [r3, #0x08]
	
	bx   lr

.global dmaSetup
.thumb_func
.type dmaSetup, %function
dmaSetup:
;@ get DMA out of reset
	movs r3, 4 
	ldr r0, =RESETS_RESET_CLR
	str r3, [r0]
	ldr r0, =RESETS_RESET_DONE_RW ;@ read status to see if it is ready
1:
	ldr r1,[r0]
	tst r1, r3
	beq 1b
	
	ldr  r2,=DMA_2_BASE ;@ base reg
	ldr  r1, =(0x3F<<15)|(1<<21)|(2<<11)|(1<<5)|(2<<2)|(1<<0)
	str  r1,[r2, #DMA2_CTRL]
	adr  r1, ZERO_CONSTANT_LOCATION
	str  r1,[r2, #DMA2_READ] ;@ set as DMA read
	
	bx   lr

.balign 2
.code 16
.thumb_func
.global setZero
.type setZero, %function
setZero: ;@ r0 = dst r1 = size
	ldr  r2,=DMA_2_BASE ;@ base reg
	str  r0,[r2, #DMA2_WRITE]
	lsrs r1, 2
	str  r1,[r2, #DMA2_TRAN_CNT]
	bx lr

.balign 4
ZERO_CONSTANT_LOCATION:
.word 0
.balign 4
.ltorg

.global reset
.balign 2
.code 16
.thumb_func
.type reset, %function
reset:
	;@ config clocks
	bl clocksSetup
.global flashEntry
.balign 2
.code 16
.thumb_func
.type flashEntry, %function
flashEntry:
	;@ set up DMA to clear RAM
	bl   dmaSetup
	ldr  r0, = __bss_start__
	ldr  r1, = __bss_end__  ;@END_OF_RAM
	subs r1, r0
	bl   setZero
	;@ configure vector table
	ldr  r1, =VTOR
	ldr  r0, =vector_table
	str  r0,[r1]
	;@ set stack
	ldr  r0,=END_OF_RAM  ;@INITIAL_STACK
	msr  MSP, r0
	;@~ subs r0, 252
	;@~ mov  r8, r0 ;@ INITIAL_PROCESS_START
	;@~ mov  r9, r0 ;@ COPY INTO R9
	movs r2, 1
	bl resetIOBank
	bl configUART
	
	bl setZeroWait ;@ until there is enough time to rip through both stacks
	bl   memSysInit
	bl   helper_unlock
	bl   picoInit
	bl   armFithInit
	;@~ bl   createFirstProcess
	ldr  r1,=CORE0_FITH_RETURN_STACK  ;@INITIAL_STACK
1:  wfe
	b    1b
	
	b REBOOT

.balign 2
.code 16
.thumb_func
.global REBOOT
.type REBOOT, %function
REBOOT:
	;@~ ldr r0,=PSM_WDSEL ;@ ENABLE MASS RESET
	;@~ ldr r1,=0x1FFFC
	;@~ str r1,[r0]
	ldr  r0,=WATCHDOG_CNTRL ;@ reboot
	movs r1, 1
	lsls r1, 31
	str r1,[r0]
	b purgatory

.balign 2
.code 16
.thumb_func
.type whoisme, %function
whoisme:
	;@~ mrs r0, IPSR
	push {r4,r5,r6,r7}
	mov  r4, sp
	movs r0, '\n'
	bl print1Byte
	movs r0, '\n'
	bl print1Byte
	movs r0, '\n'
	bl print1Byte
	movs r0, r4
	bl printWord
	movs r0, '\n'
	bl print1Byte
	ldr  r5, =40
1:	ldr  r0, [r4]
	bl printWord
	movs r0, '\n'
	bl print1Byte
	adds r4, 4
	subs r5, 1
	bne  1b
	;@~ ldr r0, [sp, #0x00]
	;@~ bl printWord
	;@~ movs r0, '\n'
	;@~ bl print1Byte
	b purgatory

.code 16
.thumb_func
.type purgatory, %function
purgatory:
	b purgatory

.balign 2
.code 16
.thumb_func
.type fifoEnqueue, %function
fifoEnqueue:
	push {lr}
	ldr  r3, =SIO_BASE
;@~ 1:
	ldr  r0, [r3, #SIO_FIFO_READ] ;@ read the fifo
	;@~ bl   queueProcessSignal
	;@~ ldr  r3, =SIO_BASE
	;@~ ldr  r0, [r3, #SIO_FIFO_ST] ;@ read fifo status
	;@~ lsrs r0, 1
	;@~ bcs  1b ;@ drain fifo
	pop  {pc}

.balign 2
.code 16
.thumb_func
.type resetIOBank, %function
resetIOBank:
	lsls r3,r2,#5
	lsls r1,r2,#10
	adds r3, r1
	lsls r1,r2,#11
	adds r3, r1
	lsls r1,r2,#21
	adds r3, r1
	ldr  r0, =RESETS_RESET_CLR
	str  r3, [r0]
	ldr  r0, =RESETS_RESET_DONE_RW
	1:
	ldr  r1,[r0]
	tst  r1, r3
	beq  1b
	lsls r3,r2,25
	ldr  r0, =SIO_GPIO_OE_CLR
	str  r3, [r0]
	ldr  r0, =SIO_GPIO_OUT_CLR
	str  r3, [r0]
	ldr  r0, =SIO_GPIO_OE_SET
	str  r3, [r0]
	
	movs r1, 5  ;@ GPIO control
	;@~ movs r1, 7 ;@ PIO 1 control
	ldr  r0, =IO_GPIO25_CTRL_RW
	str  r1, [r0]
	;@ ldr  r0, =SIO_GPIO_OE_SET
	;@ lsls r1,r2,20
	;@ adds r3, r1
	;@ lsls r1,r2,21
	;@ adds r3, r1
	;@ lsls r1,r2,22
	;@ adds r3, r1
	;@ str  r3, [r0]
	bx   lr
	
.balign 2
.code 16
.thumb_func
.type configUART, %function
configUART:
	;@ Section UART 
	;@bring up UART
	lsls r3,r2,#22
	ldr r0, =RESETS_RESET_CLR
	str r3, [r0]
	ldr r0, =RESETS_RESET_DONE_RW ;@ read status to see if it is ready
1:
	ldr r1,[r0]
	tst r1, r3
	beq 1b
	
	ldr r4,=UART0_BASE ;@ base reg
	ldr r1,=6
	str r1,[r4, #UART0_IBRD] ;@ set up baud
	
	ldr r1,=33
	str r1,[r4, #UART0_FBRD] ;@ set up fractional baud
	
	ldr r1,=0x70
	str r1,[r4, #UART0_LCR] ;@ set up fractional baud
	
	ldr r1,=(1<<9)|(1<<8)|(1<<0)
	str r1,[r4, #UART0_CR] ;@ enable UART, TX and RX
	
	;@~ ldr r1,=(1<<1)
	;@~ str r1,[r4, #UART0_DMA_CR] ;@ enable DMA on RX and tx (1<<0)
	
	ldr r1,=(1<<6)|(1<<4)|(1<<5) ;@
	str r1,[r4, #UART0_IRMASK]
	
	;@~ ldr r0,=IO_GPIO00_CTRL ;@ set gpio 0 to UART 0 TX
	;@~ ldr r1,=2
	;@~ str r1,[r0]
	
	;@~ ldr r0,=IO_GPIO01_CTRL ;@set gpio 1 to UART 0 RX
	;@~ ldr r1,=2
	;@~ str r1,[r0]
	
	ldr r0,=IO_GPIO12_CTRL ;@ set gpio 0 to UART 0 TX
	ldr r1,=2
	str r1,[r0]
	
	ldr r0,=IO_GPIO13_CTRL ;@set gpio 1 to UART 0 RX
	ldr r1,=2
	str r1,[r0]
	
	;@ get DMA out of reset
	;@~ lsls r3,r2,#2
	;@~ ldr r0, =RESETS_RESET_CLR
	;@~ str r3, [r0]
	;@~ ldr r0, =RESETS_RESET_DONE_RW ;@ read status to see if it is ready
;@~ 1:
	;@~ ldr r1,[r0]
	;@~ tst r1, r3
	;@~ beq 1b
	
	;@~ movs r3, r4
	
	ldr r4,=DMA_BASE ;@ base reg
	ldr r1, =(0x3F<<15)|(1<<21)|(1<<11)|(1<<5)|(1<<4)|(2<<2)|(1<<0)
	str r1,[r4, #DMA1_CTRL]
	
	bx lr

.balign 2
.code 16
.thumb_func
.global dmaWordForwardCopy
.type dmaWordForwardCopy, %function
dmaWordForwardCopy: ;@ r0 = src r1 = dst r2 = size
	push {r4,lr}
	ldr  r4,=DMA_BASE ;@ base reg
1:
	ldr  r3,[r4, #DMA1_CTRL]
	lsls r3, 7
	bmi  1b
	str  r0,[r4, #DMA1_READ]
	str  r1,[r4, #DMA1_WRITE]
	lsrs r2, 2
	str  r2,[r4, #DMA1_TRAN_CNT]
	pop  {r4,pc}

.balign 2
.code 16
.thumb_func
.global readSysTimerVal
.type readSysTimerVal, %function
readSysTimerVal:
	ldr  r1, =SYST_CSR
	ldr  r1, [r1, #SYST_CVR]
	subs r0, r1, r0
	bx lr

.balign 2
.code 16
.thumb_func
.global startSysTimer
.type startSysTimer, %function
startSysTimer:
	ldr  r1, =SYST_CSR
	ldr  r0, =0xFFFFFF
	str  r0, [r1, #SYST_RVR]
	movs r0, 0
	str  r0, [r1, #SYST_CVR]
	movs r0, 5
	str  r0, [r1, #0]
	bx lr

.balign 2
.code 16
.thumb_func
.global endSysTimer
.type endSysTimer, %function
endSysTimer:
	ldr  r1, =SYST_CSR
	ldr  r2, [r1, #SYST_CVR]
	ldr  r0, =0xFFFFFF
	subs r0, r0, r2
	movs r2, 0
	str  r2, [r1, #0]
	bx lr

.balign 2
.code 16
.thumb_func
.global printWord
.type printWord, %function
printWord: ;@ r0 = data to print
	push {r4,r5,r6,lr}
	;@~ ldr  r1, =SIO_SPINLOCK_0
;@~ 1:	ldr  r2, [r1]
	;@~ cmp  r2, #0
	;@~ beq  1b
	ldr r2,=0x0F
	ldr r3,=UART0_BASE ;@ get address of UART
	movs r4, r0
	movs r5, 28
	movs r6, #(1<<5)
1:
	ldr   r0,[r3, #UART0_FR]
	tst   r0, r6
	bne   1b
	movs  r0, r4
	lsrs  r0, r5
	ands  r0, r0, r2
	adds  r0, 48
	cmp   r0, 57
	ble   2f
	adds  r0, 7
2:
	strb  r0,[r3, #UART0_DR] ;@ write data out the serial port
	subs  r5, 4
	bge   1b
	;@~ movs r0, '\n'
	;@~ bl print1Byte
	;@~ movs r0, '\n'
	;@~ bl print1Byte
	;@~ movs r0, '\n'
	;@~ bl print1Byte
	;@~ ldr  r1, =SIO_SPINLOCK_0
	;@~ str  r0, [r1]
	pop {r4,r5,r6,pc}

.balign 2
.code 16
.thumb_func
.type print1Byte, %function
print1Byte: ;@ r0 = data to print
	ldr r1,=UART0_BASE ;@ get address of UART
1:
	ldr r2,[r1, #UART0_FR]
	lsls r2, 26 
	cmp r2, #0
	blt 1b
	strb r0,[r1] ;@ write data out the serial port
	bx lr


.balign 2
.code 16
.thumb_func
.global os_takeSpinLock
.type os_takeSpinLock, %function
os_takeSpinLock: ;@ r0 = lock to take
	lsls r0, 2
	ldr  r3, =SIO_SPINLOCK_0
1:	ldr  r2, [r3, r0]
	cmp  r2, #0
	beq  1b
	bx   lr
	
.balign 2
.code 16
.thumb_func
.global os_giveSpinLock
.type os_giveSpinLock, %function
os_giveSpinLock: ;@ r0 = lock to give
	lsls r0, 2
	ldr  r3, =SIO_SPINLOCK_0
	str  r0, [r3, r0]
	bx   lr

.balign 2
.code 16
.thumb_func
.global core1ServerSetup
.type core1ServerSetup, %function
;@ see tFith.c
;@ we set up this core to run fith natively, r1, r3-r7 are preserved
;@ r0 is TOS and r2 is scratch. In this context r3-r7 can be used
core1ServerSetup:
	bl   allocStack
	movs r1, r0
	movs r2, 1
	lsls r2, 9
	adds r2, r1, r2
	mov  sp, r2 ;@ could be done every iteration?
.thumb_func
.global core1Server
.type core1Server, %function
core1Server: ;@ r0 = lock to give
	ldr   r5, =SIO_BASE
	movs  r6, r1
	movs  r7, r2
1:
	ldr   r2, [r5, #SIO_FIFO_ST] ;@ read fifo status
	lsrs  r2, 1
	bcc   2f ;@ if fifo has data process it
	ldr   r2, [r5, #SIO_FIFO_READ] ;@ read the fifo
	ldr   r0, [r2, #4] ;@ load argument
	ldr   r2, [r2, #0] ;@ load function
	blx   r2 ;@ call function
	movs  r1, r6
	mov   sp, r7
	b     1b
2:
	wfe
	b     1b

.balign 2
.code 16
.thumb_func
.global asmDiv
.type asmDiv, %function
asmDiv: ;@ r0 = DIVISOR r1 = DIVIDEND
	ldr  r2, = SIO_BASE
	str  r1, [r2, #SIO_SIGNED_DIVIDEND]
	str  r0, [r2, #SIO_SIGNED_DIVISOR] ;@ now takes 8 cycles to finish
	b    1f
1:  b    1f
1:  b    1f
1:  b    1f
1:
	ldr  r0, [r2, #SIO_QUOTIENT]
	bx   lr

.balign 2
.code 16
.thumb_func
.global asmMod
.type asmMod, %function
asmMod: ;@ r0 = DIVISOR r1 = DIVIDEND
	ldr  r2, = SIO_BASE
	str  r1, [r2, #SIO_SIGNED_DIVIDEND]
	str  r0, [r2, #SIO_SIGNED_DIVISOR] ;@ now takes 8 cycles to finish
	b    1f
1:  b    1f
1:  b    1f
1:  b    1f
1:
	ldr  r0, [r2, #SIO_REMAINDER]
	ldr  r1, [r2, #SIO_QUOTIENT]
	bx   lr

.balign 2
.code 16
.thumb_func
.global asmGetDiv
.type asmGetDiv, %function
asmGetDiv: ;@ call right after asmMod
	movs r0, r1
	bx   lr

.balign 2
.code 16
.thumb_func
.global fithDiv
.type fithDiv, %function
fithDiv: ;@ r0 = TOS r1 = Return SP r2 = SCRATCH
	ldr  r2, = SIO_BASE
	str  r0, [r2, #SIO_SIGNED_DIVISOR]
	pop  {r0}
	str  r0, [r2, #SIO_SIGNED_DIVIDEND] ;@ now takes 8 cycles to finish
	b    1f
1:  b    1f
1:  b    1f
1:  b    1f
1:
	ldr  r0, [r2, #SIO_QUOTIENT]
	bx   lr

.balign 2
.code 16
.thumb_func
.global fithMod
.type fithMod, %function
fithMod: ;@ r0 = TOS r1 = Return SP r2 = SCRATCH
	ldr  r2, = SIO_BASE
	str  r0, [r2, #SIO_SIGNED_DIVISOR]
	pop  {r0}
	str  r0, [r2, #SIO_SIGNED_DIVIDEND] ;@ now takes 8 cycles to finish
	b    1f
1:  b    1f
1:  b    1f
1:  b    1f
1:
	ldr  r0, [r2, #SIO_REMAINDER]
	bx   lr

.balign 4
.ltorg

.balign 2
.code 16
.thumb_func
.global st_len
.type st_len, %function
st_len: ;@ r0 has pointer to start of string, check 4 byte alignment
	movs r1, r0
	movs r0, 0
	movs r2, 3
	tst  r2, r1
	bne  stringLenByte
	movs r2, 0xFF
5:
	ldm  r1!, {r3}
	tst  r3, r2
	beq  1f
	lsrs r3, 8
	tst  r3, r2
	beq  2f
	lsrs r3, 8
	tst  r3, r2
	beq  3f
	lsrs r3, 8
	tst  r3, r2
	beq  4f
	adds r0, 4
	b    5b
4:
	adds r0, 3
	bx   lr
3:
	adds r0, 1
2:
	adds r0, 1
1:
	bx   lr

1:
	adds r0, 1
stringLenByte:
	ldrb r2, [r1, r0]
	cmp  r2, 0
	bne  1b
	bx   lr

;@ ARM implementations for the compiler
.global __gnu_thumb1_case_uqi
.thumb_func
__gnu_thumb1_case_uqi:
	mov     r12, r1
	mov     r1, lr
	lsrs    r1, r1, #1
	lsls    r1, r1, #1
	ldrb    r1, [r1, r0]
	lsls    r1, r1, #1
	add     lr, lr, r1
	mov     r1, r12
	bx      lr

.global __gnu_thumb1_case_sqi
.thumb_func
__gnu_thumb1_case_sqi:
	mov     r12, r1
	mov     r1, lr
	lsrs    r1, r1, #1
	lsls    r1, r1, #1
	ldrsb   r1, [r1, r0]
	lsls    r1, r1, #1
	add     lr, lr, r1
	mov     r1, r12
	bx      lr

.global __gnu_thumb1_case_uhi
.thumb_func
__gnu_thumb1_case_uhi:
	push    {r0, r1}
	mov     r1, lr
	lsrs    r1, r1, #1
	lsls    r0, r0, #1
	lsls    r1, r1, #1
	ldrh    r1, [r1, r0]
	lsls    r1, r1, #1
	add     lr, lr, r1
	pop     {r0, r1}
	bx      lr

.global __gnu_thumb1_case_shi
.thumb_func
__gnu_thumb1_case_shi:
	push    {r0, r1}
	mov     r1, lr
	lsrs    r1, r1, #1
	lsls    r0, r0, #1
	lsls    r1, r1, #1
	ldrsh   r1, [r1, r0]
	lsls    r1, r1, #1
	add     lr, lr, r1
	pop     {r0, r1}
	bx      lr

.global __gnu_thumb1_case_si
.thumb_func
__gnu_thumb1_case_si:
	push	{r0, r1}
	mov	r1, lr
	adds.n	r1, r1, #2
	lsrs	r1, r1, #2
	lsls	r0, r0, #2
	lsls	r1, r1, #2
	ldr	r0, [r1, r0]
	adds	r0, r0, r1
	mov	lr, r0
	pop	{r0, r1}
	mov	pc, lr
	
.balign 2
.code 16
.thumb_func
.global printFithStack
.type printFithStack, %function
printFithStack: ;@ r0 = TOS r1 = Return SP r2 = SCRATCH SP = EXPR_SP
	push {r0, r1, r3, lr}
	add  r1, sp, #16
	bl   printFithStackElements
	pop  {r0, r1, r3, pc}

.balign 2
.code 16
.thumb_func
.global armFithEnter
.type armFithEnter, %function
armFithEnter: ;@ r0 = TOS r1 = Return SP r2 = Expr SP r3 = target
	push {r4, lr}
	mov  r4, sp ;@ save off C stack pointer
	mov  sp, r2 ;@ overwrite sp with armFith stack pointer
	blx  r3 ;@ jump to target armFith function
	mov  r1, sp ;@ prepare to return armFith stack pointer
	mov  sp, r4 ;@ restore C stack pointer
	pop  {r4, pc}

.balign 2
.code 16
.thumb_func
.global fith_logicalAnd
.type fith_logicalAnd, %function
fith_logicalAnd:
	pop  {r2}
	rsbs r0, r0, 0
	sbcs r0, r0
	ands r0, r2
	bx   lr

.balign 2
.code 16
.thumb_func
.global fithFree
.type fithFree, %function
fithFree:
	pop  {r2}
	push {r1, r2, r3, lr}
	bl   free
	ldr	r0, [sp, #4]
	pop  {r1, r2, r3, pc}

.balign 2
.code 16
.thumb_func
.global fithAlloc
.type fithAlloc, %function
fithAlloc:
	push {r1, r3, lr}
	bl   zalloc
	pop  {r1, r3, pc}

.balign 2
.code 16
.thumb_func
.global fithRealloc
.type fithRealloc, %function
fithRealloc:
	pop  {r2}
	push {r1, r3, lr}
	movs r1, r0
	movs r0, r2
	bl   realloc
	pop  {r1, r3, pc}

.balign 2
.code 16
.thumb_func
.global fithPrintsn
.type fithPrintsn, %function
fithPrintsn:
	pop  {r2}
	push {r1, r2, r3, lr}
	bl   io_printsn
	ldr	r0, [sp, #4]
	pop  {r1, r2, r3, pc}

.balign 2
.code 16
.thumb_func
.global fithPrints
.type fithPrints, %function
fithPrints:
	pop  {r2}
	push {r1, r2, r3, lr}
	bl   io_prints
	ldr	r0, [sp, #4]
	pop  {r1, r2, r3, pc}

.balign 2
.code 16
.thumb_func
.global fithPrinti
.type fithPrinti, %function
fithPrinti:
	pop  {r2}
	push {r1, r2, r3, lr}
	bl   io_printi
	ldr	r0, [sp, #4]
	pop  {r1, r2, r3, pc}

.balign 2
.code 16
.thumb_func
.global fithPrintin
.type fithPrintin, %function
fithPrintin:
	pop  {r2}
	push {r1, r2, r3, lr}
	bl   io_printin
	ldr	r0, [sp, #4]
	pop  {r1, r2, r3, pc}

.balign 2
.code 16
.thumb_func
.global fithPrinth
.type fithPrinth, %function
fithPrinth:
	pop  {r2}
	push {r1, r2, r3, lr}
	bl   io_printh
	ldr	r0, [sp, #4]
	pop  {r1, r2, r3, pc}

.balign 2
.code 16
.thumb_func
.global fithPrinthn
.type fithPrinthn, %function
fithPrinthn:
	pop  {r2}
	push {r1, r2, r3, lr}
	bl   io_printhn
	ldr	r0, [sp, #4]
	pop  {r1, r2, r3, pc}

.balign 2
.code 16
.thumb_func
.global fithOnce
.type fithOnce, %function
fithOnce: ;@ preserve r0, r1, r3
	push {r0, r1}
	movs r0, 0xE0
	lsls r0, r0, #8
	mov  r2, lr
	subs r2, 1
	ldrh r1, [r2]
	adds r0, r1
	subs r2, 4
	strh r0, [r2]
	adds r2, 7
	pop  {r0, r1}
	bx   r2

.balign 2
.code 16
.thumb_func
.global fithClearStack
.type fithClearStack, %function
fithClearStack:
	mov   r2, sp
	adds  r2, 248
	adds  r2, 248
	lsrs  r2, 9
	lsls  r2, 9
	mov   sp, r2
	bx    lr

.balign 2
.code 16
.thumb_func
.global co_yieldWrapper
.type co_yieldWrapper, %function
co_yieldWrapper: ;@ r0 = arg, r1 = ToCoroutine
	push {r1}
	;@~ push {r0, r1, r2, r3}
	;@~ movs  r0, r1
	;@~ bl    printWord
	;@~ pop  {r0, r1, r2, r3}

.balign 2
.code 16
.thumb_func
.global co_yield
.type co_yield, %function
co_yield: ;@ r0 = arg, pop into r2 for ToCoroutine
	pop  {r2}
	push {r1, r3, r4, r5, r6, r7, lr}
	mov   r8, sp
	mov   sp, r2
	pop  {r1, r3, r4, r5, r6, r7, pc}

.balign 2
.code 16
.thumb_func
.global co_getFromFith
.type co_getFromFith, %function
co_getFromFith:
	push {r0}

.balign 2
.code 16
.thumb_func
.global co_getFrom
.type co_getFrom, %function
co_getFrom:
	mov   r0, r8
	bx    lr

.balign 2
.code 16
.thumb_func
.global printSP
.type printSP, %function
printSP:
	push {lr}
	mov  r0, sp
	bl printWord
	movs r0, '\n'
	bl print1Byte
	pop  {pc}

.balign 2
.code 16
.thumb_func
.global checkedPopStack
.type checkedPopStack, %function
checkedPopStack:
	push {r0, r1, r2, r3, lr}
	mov   r0, sp
	adds  r0, 20
	lsrs  r0, 9
	lsrs  r2, r1, 9
	cmp   r0, r2
	beq   1f
	bl    checkedPopTosPrint ;@ print warning
	ldr   r0, [sp, #16]      ;@ load return address
	adds  r0, 2              ;@ skip pop_tos instruction
	str   r0, [sp, #16]      ;@ replace return address
1:
	pop  {r0, r1, r2, r3, pc}

.balign 2
.code 16
.thumb_func
.global fithAddEqualsGlobal
.type fithAddEqualsGlobal, %function
fithAddEqualsGlobal: ;@ r0 = value to add r2 = address of global
	push {r1}
	ldr   r1, [r2]
	adds  r0, r1
	str   r0, [r2]
	pop  {r1}
	pop  {r0}
	bx    lr

.balign 2
.code 16
.thumb_func
.global fithSubEqualsGlobal
.type fithSubEqualsGlobal, %function
fithSubEqualsGlobal: ;@ r0 = value to add r2 = address of global
	push {r1}
	ldr   r1, [r2]
	subs  r0, r1, r0
	str   r0, [r2]
	pop  {r1}
	pop  {r0}
	bx    lr

.balign 2
.code 16
.thumb_func
.global fithMulEqualsGlobal
.type fithMulEqualsGlobal, %function
fithMulEqualsGlobal: ;@ r0 = value to add r2 = address of global
	push {r1}
	ldr   r1, [r2]
	muls  r0, r1
	str   r0, [r2]
	pop  {r1}
	pop  {r0}
	bx    lr

.balign 2
.code 16
.thumb_func
.global fithOrrEqualsGlobal
.type fithOrrEqualsGlobal, %function
fithOrrEqualsGlobal: ;@ r0 = value to add r2 = address of global
	push {r1}
	ldr   r1, [r2]
	orrs  r0, r1
	str   r0, [r2]
	pop  {r1}
	pop  {r0}
	bx    lr

.balign 2
.code 16
.thumb_func
.global fithAndEqualsGlobal
.type fithAndEqualsGlobal, %function
fithAndEqualsGlobal: ;@ r0 = value to add r2 = address of global
	push {r1}
	ldr   r1, [r2]
	ands  r0, r1
	str   r0, [r2]
	pop  {r1}
	pop  {r0}
	bx    lr

.balign 2
.code 16
.thumb_func
.global fithBicEqualsGlobal
.type fithBicEqualsGlobal, %function
fithBicEqualsGlobal: ;@ r0 = value to add r2 = address of global
	push {r1}
	ldr   r1, [r2]
	bics  r1, r0
	str   r1, [r2]
	pop  {r1}
	pop  {r0}
	bx    lr

.balign 2
.code 16
.thumb_func
.global fithXorEqualsGlobal
.type fithXorEqualsGlobal, %function
fithXorEqualsGlobal: ;@ r0 = value to add r2 = address of global
	push {r1}
	ldr   r1, [r2]
	eors  r1, r0
	str   r1, [r2]
	pop  {r1}
	pop  {r0}
	bx    lr

.balign 2
.code 16
.thumb_func
.global fithLslsEqualsGlobal
.type fithLslsEqualsGlobal, %function
fithLslsEqualsGlobal: ;@ r0 = value to add r2 = address of global
	push {r1}
	ldr   r1, [r2]
	lsls  r1, r0
	str   r1, [r2]
	pop  {r1}
	pop  {r0}
	bx    lr

.balign 2
.code 16
.thumb_func
.global fithLsrsEqualsGlobal
.type fithLsrsEqualsGlobal, %function
fithLsrsEqualsGlobal: ;@ r0 = value to add r2 = address of global
	push {r1}
	ldr   r1, [r2]
	lsrs  r1, r0
	str   r1, [r2]
	pop  {r1}
	pop  {r0}
	bx    lr

.balign 2
.code 16
.thumb_func
.global fithCommaU8
.type fithCommaU8, %function
fithCommaU8: ;@ r0 = value to store r2 = address location
	pop  {r2}
	strb  r0, [r2]
	adds  r0, r2, 1
	bx    lr

.balign 2
.code 16
.thumb_func
.global fithCommaU16
.type fithCommaU16, %function
fithCommaU16: ;@ r0 = value to store r2 = address location
	pop  {r2}
	adds  r2, 1
	lsrs  r2, 1
	lsls  r2, 1
	strh  r0, [r2]
	adds  r0, r2, 2
	bx    lr

.balign 2
.code 16
.thumb_func
.global fithCommaS32
.type fithCommaS32, %function
fithCommaS32: ;@ r0 = value to store r2 = address location
	pop  {r2}
	adds  r2, 3
	lsrs  r2, 2
	lsls  r2, 2
	str   r0, [r2]
	adds  r0, r2, 4
	bx    lr
