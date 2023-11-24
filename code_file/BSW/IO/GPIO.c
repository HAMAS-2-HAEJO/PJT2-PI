#include <IfxPort.h>
#include "GPIO.h"
#include "Bsp.h"

#define Switch1      &MODULE_P02,0
#define LED_BLUE     &MODULE_P10,2
#define Switch2      &MODULE_P02,1
#define LED_RED      &MODULE_P10,1

void Init_GPIO()
 {
	/* Set P10.2(LED1) as push-pull output */
    IfxPort_setPinModeOutput(LED_BLUE, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);

	/* Set P10.1(LED2) as push-pull output */
    IfxPort_setPinModeOutput(LED_RED, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);

	/* Set P2.0(SW1) as input pull-up */
    IfxPort_setPinModeInput(Switch1, IfxPort_InputMode_pullUp);

	/* Set P2.1(SW2) as input pull-up */
    IfxPort_setPinModeInput(Switch2, IfxPort_InputMode_pullUp);
}

void setLED1(int onoff)	// on if true, off if false
{
	if(onoff)
	{
        IfxPort_setPinHigh(LED_BLUE);
	}
	else
	{
        IfxPort_setPinLow(LED_BLUE);
	}
}

void setLED2(int onoff)
{
	if(onoff)
	{
        IfxPort_setPinHigh(LED_RED);
	}
	else
	{
        IfxPort_setPinLow(LED_RED);
	}
}

int getSW1(void)
{
    if (IfxPort_getPinState(Switch1))
        return 1;
    else
        return 0;
}

int getSW2(void)
{
    if (IfxPort_getPinState(Switch2))
        return 1;
    else
        return 0;
}
