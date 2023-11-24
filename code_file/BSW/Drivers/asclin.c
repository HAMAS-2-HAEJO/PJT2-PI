#include "IfxAsclin_Asc.h"
#include "IfxCpu_Irq.h"
#include <stdio.h>
#include "asclin.h"
#include "IfxStdIf_DPipe.h"
#include "isr_priority.h"

#define ASC_TX_BUFFER_SIZE          256                                     /* Define the TX buffer size in byte    */
#define ASC_RX_BUFFER_SIZE          256                                     /* Define the RX buffer size in byte    */
#define ASC_BAUDRATE                115200                                  /* Define the UART baud rate            */

#define TOF_BAUDRATE                921600                                  /* Define the UART baud rate            */

#define BLUETOOTH_BAUDRATE          9600                                  /* Define the UART baud rate            */

/* Declaration of the ASC handle */
static IfxAsclin_Asc g_ascHandle0;
static IfxAsclin_Asc g_ascHandle1;
static IfxAsclin_Asc g_ascHandle3;

static IfxStdIf_DPipe  g_ascStandardInterface;                                     /* Standard interface object            */

/* The transfer buffers allocate memory for the data itself and for FIFO runtime variables.
 * 8 more bytes have to be added to ensure a proper circular buffer handling independent from
 * the address to which the buffers have been located.
 */
uint8 g_uartTxBuffer[ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
uint8 g_uartRxBuffer[ASC_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];

uint8 g_uartTxBuffer_0[ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
uint8 g_uartRxBuffer_0[ASC_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
uint8 g_uartTxBuffer_1[ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
uint8 g_uartRxBuffer_1[ASC_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];

/* Adding of the interrupt service routines */
IFX_INTERRUPT(asclin3TxISR, 0, ISR_PRIORITY_ASCLIN_TX);
void asclin3TxISR(void)
{
    IfxAsclin_Asc_isrTransmit(&g_ascHandle3);
}

IFX_INTERRUPT(asclin3RxISR, 0, ISR_PRIORITY_ASCLIN_RX);
void asclin3RxISR(void)
{
    IfxAsclin_Asc_isrReceive(&g_ascHandle3);
}

IFX_INTERRUPT(asclin3ErrISR, 0, ISR_PRIORITY_ASCLIN_ER);
void asclin3ErrISR(void)
{
    while(1);
}

/* This function initializes the ASCLIN UART module */
void _init_uart3(void)
{
    IfxAsclin_Asc_Config ascConf;

    /* Set default configurations */
    IfxAsclin_Asc_initModuleConfig(&ascConf, &MODULE_ASCLIN3); /* Initialize the structure with default values      */

    /* Set the desired baud rate */
    ascConf.baudrate.baudrate = ASC_BAUDRATE;                                   /* Set the baud rate in bit/s       */
    ascConf.baudrate.oversampling = IfxAsclin_OversamplingFactor_16;            /* Set the oversampling factor      */

    /* Configure the sampling mode */
    ascConf.bitTiming.medianFilter = IfxAsclin_SamplesPerBit_three;             /* Set the number of samples per bit*/
    ascConf.bitTiming.samplePointPosition = IfxAsclin_SamplePointPosition_8;    /* Set the first sample position    */

    /* ISR priorities and interrupt target */
    ascConf.interrupt.txPriority = ISR_PRIORITY_ASCLIN_TX;  /* Set the interrupt priority for TX events             */
    ascConf.interrupt.rxPriority = ISR_PRIORITY_ASCLIN_RX;  /* Set the interrupt priority for RX events             */
    ascConf.interrupt.erPriority = ISR_PRIORITY_ASCLIN_ER;  /* Set the interrupt priority for Error events          */
    ascConf.interrupt.typeOfService = IfxSrc_Tos_cpu0;

    /* Pin configuration */
    const IfxAsclin_Asc_Pins pins = {
            .cts        = NULL_PTR,                         /* CTS pin not used                                     */
            .ctsMode    = IfxPort_InputMode_pullUp,
            .rx         = &IfxAsclin3_RXD_P32_2_IN ,        /* Select the pin for RX connected to the USB port      */
            .rxMode     = IfxPort_InputMode_pullUp,         /* RX pin                                               */
            .rts        = NULL_PTR,                         /* RTS pin not used                                     */
            .rtsMode    = IfxPort_OutputMode_pushPull,
            .tx         = &IfxAsclin3_TX_P15_7_OUT,         /* Select the pin for TX connected to the USB port      */
            .txMode     = IfxPort_OutputMode_pushPull,      /* TX pin                                               */
            .pinDriver  = IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    ascConf.pins = &pins;

    /* FIFO buffers configuration */
    ascConf.txBuffer = g_uartTxBuffer;                      /* Set the transmission buffer                          */
    ascConf.txBufferSize = ASC_TX_BUFFER_SIZE;              /* Set the transmission buffer size                     */
    ascConf.rxBuffer = g_uartRxBuffer;                      /* Set the receiving buffer                             */
    ascConf.rxBufferSize = ASC_RX_BUFFER_SIZE;              /* Set the receiving buffer size                        */

    /* Init ASCLIN module */
    IfxAsclin_Asc_initModule(&g_ascHandle3, &ascConf);          /* Initialize the module with the given configuration   */

    /* Initialize the Standard Interface */
    IfxAsclin_Asc_stdIfDPipeInit(&g_ascStandardInterface, &g_ascHandle3);

    /* Initialize the Console */
    Ifx_Console_init(&g_ascStandardInterface);
}

/* Send character CHR via the serial line */
void _out_uart3(const unsigned char chr)
{
 //   while(IfxAsclin_Asc_canWriteCount(&g_ascHandle3, 1, TIME_INFINITE) != TRUE);
    IfxAsclin_Asc_blockingWrite(&g_ascHandle3, chr);
}

/* Receive (and wait for) a character from the serial line */
unsigned char _in_uart3(void)
{
    return IfxAsclin_Asc_blockingRead(&g_ascHandle3);
}

int _poll_uart3(unsigned char *chr)
{
    unsigned char ch;
    Ifx_SizeT count = 1;
    int res = 0;

    res = IfxAsclin_Asc_read(&g_ascHandle3, &ch, &count, 5);
    if(res == TRUE)
    {
        *chr = ch;
    }

    return res;
}

IFX_INTERRUPT(asclin1TxISR, 0, ISR_PRIORITY_ASCLIN_TOF_TX);
void asclin1TxISR(void)
{
    IfxAsclin_Asc_isrTransmit(&g_ascHandle1);
}

IFX_INTERRUPT(asclin1ErrISR, 0, ISR_PRIORITY_ASCLIN_TOF_ER);
void asclin1ErrISR(void)
{
    while(1);
}

/* This function initializes the ASCLIN UART module */
void _init_uart1(void)
{
    IfxAsclin_Asc_Config ascConf;

    /* Set default configurations */
    IfxAsclin_Asc_initModuleConfig(&ascConf, &MODULE_ASCLIN1); /* Initialize the structure with default values      */

    /* Set the desired baud rate */
    ascConf.baudrate.baudrate = TOF_BAUDRATE;                                   /* Set the baud rate in bit/s       */
    //ascConf.baudrate.prescaler = 1;
    ascConf.baudrate.oversampling = IfxAsclin_OversamplingFactor_16;            /* Set the oversampling factor      */

    /* Configure the sampling mode */
    ascConf.bitTiming.medianFilter = IfxAsclin_SamplesPerBit_three;             /* Set the number of samples per bit*/
    ascConf.bitTiming.samplePointPosition = IfxAsclin_SamplePointPosition_8;    /* Set the first sample position    */

    /* ISR priorities and interrupt target */
    ascConf.interrupt.txPriority = ISR_PRIORITY_ASCLIN_TOF_TX;  /* Set the interrupt priority for TX events             */
    ascConf.interrupt.rxPriority = ISR_PRIORITY_ASCLIN_TOF_RX;  /* Set the interrupt priority for RX events             */
    ascConf.interrupt.erPriority = ISR_PRIORITY_ASCLIN_TOF_ER;  /* Set the interrupt priority for Error events          */
    ascConf.interrupt.typeOfService = IfxSrc_Tos_cpu0;

    /* Pin configuration */
    const IfxAsclin_Asc_Pins pins = {
            .cts        = NULL_PTR,                         /* CTS pin not used                                     */
            .ctsMode    = IfxPort_InputMode_pullUp,
            .rx         = &IfxAsclin1_RXA_P15_1_IN ,        /* Select the pin for RX connected to the USB port      */
            .rxMode     = IfxPort_InputMode_pullUp,         /* RX pin                                               */
            .rts        = NULL_PTR,                         /* RTS pin not used                                     */
            .rtsMode    = IfxPort_OutputMode_pushPull,
            .tx         = &IfxAsclin1_TX_P15_0_OUT,         /* Select the pin for TX connected to the USB port      */
            .txMode     = IfxPort_OutputMode_pushPull,      /* TX pin                                               */
            .pinDriver  = IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    ascConf.pins = &pins;

    /* FIFO buffers configuration */
    ascConf.txBuffer = g_uartTxBuffer_1;                      /* Set the transmission buffer                          */
    ascConf.txBufferSize = ASC_TX_BUFFER_SIZE;              /* Set the transmission buffer size                     */
    ascConf.rxBuffer = g_uartRxBuffer_1;                      /* Set the receiving buffer                             */
    ascConf.rxBufferSize = ASC_RX_BUFFER_SIZE;              /* Set the receiving buffer size                        */

    /* Init ASCLIN module */
    IfxAsclin_Asc_initModule(&g_ascHandle1, &ascConf);          /* Initialize the module with the given configuration   */
}

/* Send character CHR via the serial line */
void _out_uart1(const unsigned char chr)
{
 //   while(IfxAsclin_Asc_canWriteCount(&g_ascHandle3, 1, TIME_INFINITE) != TRUE);
    IfxAsclin_Asc_blockingWrite(&g_ascHandle1, chr);
}

/* Receive (and wait for) a character from the serial line */
unsigned char _in_uart1(void)
{
    unsigned char ch;

    /* wait for a new character */
    while (_poll_uart1(&ch) == 0);

    return ch;
}

int _poll_uart1(unsigned char *chr)
{
    unsigned char ch;
    Ifx_SizeT count = 0;
    int res = 0;

    count = IfxAsclin_getRxFifoFillLevel(g_ascHandle1.asclin);
    if(count >= 1)
    {
        IfxAsclin_read8(g_ascHandle1.asclin, &ch, 1);
        *chr = ch;
        res = TRUE;
    }
    else
        res = FALSE;
    return res;
}

IFX_INTERRUPT(asclin0TxISR, 0, ISR_PRIORITY_ASCLIN_BLUETOOTH_TX);
void asclin0TxISR(void)
{
    IfxAsclin_Asc_isrTransmit(&g_ascHandle0);
}

IFX_INTERRUPT(asclin0RxISR, 0, ISR_PRIORITY_ASCLIN_BLUETOOTH_RX);
void asclin0RxISR(void)
{
    IfxAsclin_Asc_isrReceive(&g_ascHandle0);
}

IFX_INTERRUPT(asclin0ErrISR, 0, ISR_PRIORITY_ASCLIN_BLUETOOTH_ER);
void asclin0ErrISR(void)
{
    while(1);
}

/* This function initializes the ASCLIN UART module */
void _init_uart0(void)
{
    IfxAsclin_Asc_Config ascConf;

    /* Set default configurations */
    IfxAsclin_Asc_initModuleConfig(&ascConf, &MODULE_ASCLIN0); /* Initialize the structure with default values      */

    /* Set the desired baud rate */
    ascConf.baudrate.baudrate = BLUETOOTH_BAUDRATE;                                   /* Set the baud rate in bit/s       */
    ascConf.baudrate.oversampling = IfxAsclin_OversamplingFactor_16;            /* Set the oversampling factor      */

    /* Configure the sampling mode */
    ascConf.bitTiming.medianFilter = IfxAsclin_SamplesPerBit_three;             /* Set the number of samples per bit*/
    ascConf.bitTiming.samplePointPosition = IfxAsclin_SamplePointPosition_8;    /* Set the first sample position    */

    /* ISR priorities and interrupt target */
    ascConf.interrupt.txPriority = ISR_PRIORITY_ASCLIN_BLUETOOTH_TX;  /* Set the interrupt priority for TX events             */
    ascConf.interrupt.rxPriority = ISR_PRIORITY_ASCLIN_BLUETOOTH_RX;  /* Set the interrupt priority for RX events             */
    ascConf.interrupt.erPriority = ISR_PRIORITY_ASCLIN_BLUETOOTH_ER;  /* Set the interrupt priority for Error events          */
    ascConf.interrupt.typeOfService = IfxSrc_Tos_cpu0;

    /* Pin configuration */
    const IfxAsclin_Asc_Pins pins = {
            .cts        = NULL_PTR,                         /* CTS pin not used                                     */
            .ctsMode    = IfxPort_InputMode_pullUp,
            .rx         = &IfxAsclin0_RXA_P14_1_IN ,        /* Select the pin for RX connected to the USB port      */
            .rxMode     = IfxPort_InputMode_pullUp,         /* RX pin                                               */
            .rts        = NULL_PTR,                         /* RTS pin not used                                     */
            .rtsMode    = IfxPort_OutputMode_pushPull,
            .tx         = &IfxAsclin0_TX_P14_0_OUT,         /* Select the pin for TX connected to the USB port      */
            .txMode     = IfxPort_OutputMode_pushPull,      /* TX pin                                               */
            .pinDriver  = IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    ascConf.pins = &pins;

    /* FIFO buffers configuration */
    ascConf.txBuffer = g_uartTxBuffer_0;                      /* Set the transmission buffer                          */
    ascConf.txBufferSize = ASC_TX_BUFFER_SIZE;              /* Set the transmission buffer size                     */
    ascConf.rxBuffer = g_uartRxBuffer_0;                      /* Set the receiving buffer                             */
    ascConf.rxBufferSize = ASC_RX_BUFFER_SIZE;              /* Set the receiving buffer size                        */

    /* Init ASCLIN module */
    IfxAsclin_Asc_initModule(&g_ascHandle0, &ascConf);          /* Initialize the module with the given configuration   */
}

/* Send character CHR via the serial line */
void _out_uart0(const unsigned char chr)
{
 //   while(IfxAsclin_Asc_canWriteCount(&g_ascHandle3, 1, TIME_INFINITE) != TRUE);
    IfxAsclin_Asc_blockingWrite(&g_ascHandle0, chr);
}

/* Receive (and wait for) a character from the serial line */
unsigned char _in_uart0(void)
{
    return IfxAsclin_Asc_blockingRead(&g_ascHandle0);
}

int _poll_uart0(unsigned char *chr)
{
    unsigned char ch;
    Ifx_SizeT count = 1;
    int res = 0;

    res = IfxAsclin_Asc_read(&g_ascHandle0, &ch, &count, TIME_INFINITE);
    if(res == TRUE)
    {
        *chr = ch;
    }

    return res;
}

int _nonBlock_poll_uart0(unsigned char *chr)
{
    unsigned char ch;
    Ifx_SizeT count = 1;
    int res = 0;

    res = IfxAsclin_Asc_read(&g_ascHandle0, &ch, &count, 10);
    if (res == TRUE)
    {
        *chr = ch;
    }

    return res;
}
