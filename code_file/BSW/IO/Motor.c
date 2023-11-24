#include <gpt12.h>
#include <Ifx_reg.h>
#include <Ifx_Types.h>
#include <IfxGpt12.h>
#include <IfxPort.h>
#include "Motor.h"
#include "Bsp.h"
#include "isr_priority.h"

#define DIR_A       &MODULE_P10,1
#define PWM_A       &MODULE_P02,1
#define BREAK_A     &MODULE_P02,7

#define DIR_B       &MODULE_P10,2
#define PWM_B       &MODULE_P10,3
#define BREAK_B     &MODULE_P02,6

#define ISR_PROVIDER_GPT12_TIMER    IfxSrc_Tos_cpu0

void Init_DCMotors()
{
	/* Init CH-A (Left Motor) */
    IfxPort_setPinModeOutput(DIR_A, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);    /* DIR-A 출력 핀 설정 */
    IfxPort_setPinModeOutput(PWM_A, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);    /* PWM-A 출력 핀 설정 */
    IfxPort_setPinModeOutput(BREAK_A, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);  /* BRAKE-A 출력 핀 설정 */
    IfxPort_setPinHigh(DIR_A);      /* 모터 회전 방향 (1: 앞, 0: 뒤) */
    IfxPort_setPinHigh(BREAK_A);    /* 모터 정지 (1: 정지, 0: PWM-A에 따라 동작) */
    IfxPort_setPinLow(PWM_A);      /* 100% PWM duty  */

	/* Init CH-B (Right Motor) */
    IfxPort_setPinModeOutput(DIR_B, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);    /* DIR-B 출력 핀 설정 */
    IfxPort_setPinModeOutput(PWM_B, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);    /* PWM-B 출력 핀 설정 */
    IfxPort_setPinModeOutput(BREAK_B, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);  /* BRAKE-B 출력 핀 설정 */
    IfxPort_setPinHigh(DIR_B);      /* 모터 회전 방향 (1: 앞, 0: 뒤) */
    IfxPort_setPinHigh(BREAK_B);    /* 모터 정지 (1: 정지, 0: PWM-B에 따라 동작) */
    IfxPort_setPinLow(PWM_B);      /* 100% PWM duty  */

    init_gpt2();
}

/* 1: 정방향, 2: 역방향 */
void movChA(int dir)
{
	if(dir)
	{
		IfxPort_setPinHigh(DIR_A); /* 모터 회전 방향 (1: 앞, 0: 뒤) */
	}
	else {
		IfxPort_setPinLow(DIR_A); /* 모터 회전 방향 (1: 앞, 0: 뒤) */
	}
	IfxPort_setPinLow(BREAK_A); /* 모터 정지 (1: 정지, 0: PWM-A에 따라 동작) */
	IfxPort_setPinHigh(PWM_A); /* 100% PWM duty  */
}

/* 1: 정방향, 2: 역방향 */
void movChB(int dir)
{
	if(dir)
	{
		IfxPort_setPinHigh(DIR_B); /* 모터 회전 방향 (1: 앞, 0: 뒤) */
	}
	else {
		IfxPort_setPinLow(DIR_B); /* 모터 회전 방향 (1: 앞, 0: 뒤) */
	}
	IfxPort_setPinLow(BREAK_B); /* 모터 정지 (1: 정지, 0: PWM-B에 따라 동작) */
	IfxPort_setPinHigh(PWM_B); /* 100% PWM duty  */
}

void stopChA(void)
{
	IfxPort_setPinHigh(BREAK_A); /* 모터 정지 (1: 정지, 0: PWM-A에 따라 동작) */
}

void stopChB(void)
{
	IfxPort_setPinHigh(BREAK_B); /* 모터 정지 (1: 정지, 0: PWM-B에 따라 동작) */
}

void goChA(void)
{
    IfxPort_setPinLow(BREAK_A); /* 모터 정지 (1: 정지, 0: PWM-A에 따라 동작) */
}

void goChB(void)
{
    IfxPort_setPinLow(BREAK_B); /* 모터 정지 (1: 정지, 0: PWM-B에 따라 동작) */
}

/* 1: 정방향, 0: 역방향 */
void movChA_PWM(int duty, int dir)
{
	setLeftMotorDuty(duty);  //
	if (dir) {
		IfxPort_setPinHigh(DIR_A); /* 모터 회전 방향 (1: 앞, 0: 뒤) */
	} else 	{
		IfxPort_setPinLow(DIR_A); /* 모터 회전 방향 (1: 앞, 0: 뒤) */
	}
	IfxPort_setPinLow(BREAK_A); /* 모터 정지 (1: 정지, 0: PWM-A에 따라 동작) */
}

/* 1: 정방향, 0: 역방향 */
void movChB_PWM(int duty, int dir)
{
	setRightMotorDuty(duty);  //
	if (dir) {
		IfxPort_setPinHigh(DIR_B); /* 모터 회전 방향 (1: 앞, 0: 뒤) */
	} else 	{
		IfxPort_setPinLow(DIR_B); /* 모터 회전 방향 (1: 앞, 0: 뒤) */
	}
	IfxPort_setPinLow(BREAK_B); /* 모터 정지 (1: 정지, 0: PWM-B에 따라 동작) */
}
