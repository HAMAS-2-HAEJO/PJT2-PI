#include <gpt12.h>
#include <Ifx_reg.h>
#include <IfxPort.h>
#include <IfxGpt12.h>
#include "Buzzer.h"
#include "asclin.h"
#include "isr_priority.h"

#define Buzzer                      &MODULE_P02,3

#define ISR_PROVIDER_GPT12_TIMER    IfxSrc_Tos_cpu0
#define GPT1_BLOCK_PRESCALER        32      /* GPT1 block prescaler value                 */
#define TIMER_T3_INPUT_PRESCALER    32      /* Timer input prescaler value                */
#define GPT120_MODULE_FREQUENCY     100000000

int beepCnt = 0;
int beepOnOff = 100;

IFX_INTERRUPT(IsrGpt120T3Handler_Beep, 0, ISR_PRIORITY_GPT1T3_TIMER);
void IsrGpt120T3Handler_Beep()
{
	if ((beepCnt < beepOnOff) || (beepOnOff == 1)) {
		IfxPort_togglePin(Buzzer);
	} else if (beepCnt < beepOnOff * 2) {
        IfxPort_setPinLow(Buzzer);
	} else {
		beepCnt = 0;
	}
	beepCnt++;
}

void Init_Buzzer()
{
    IfxPort_setPinModeOutput(Buzzer, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general); 

	init_gpt1();

	runGpt12_T3();
}

void setBeepCycle(int cycle)
{
	beepOnOff = cycle;
}

void Beep(unsigned int hz)
{
	volatile int loop = 1000000 / hz / 2; /* 주파수에 따른 us 계산 */
	for (volatile int i = 0; i < loop; i++) /* loop * 1us 동안 delay */
		for (volatile int j = 0; j < 1; j++)
			for (volatile int k = 0; k < 1; k++)
			    __nop();
}

