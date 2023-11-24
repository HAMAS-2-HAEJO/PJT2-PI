#include <Ifx_reg.h>
#include <IfxGpt12.h>
#include <IO/Ultrasonic.h>
#include "IfxPort.h"
#include "Bsp.h"
#include "gpt12.h"

#define REAR_TRIG        &MODULE_P00,0
#define REAR_ECHO        &MODULE_P00,1
#define LEFT_TRIG        &MODULE_P00,6
#define LEFT_ECHO        &MODULE_P00,7
#define RIGHT_TRIG       &MODULE_P00,3
#define RIGHT_ECHO       &MODULE_P00,4

void Init_Ultrasonics()
{
	/* Init Rear Ultrasonic Pin */
    IfxPort_setPinModeOutput(REAR_TRIG, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
	IfxPort_setPinModeInput(REAR_ECHO, IfxPort_InputMode_pullDown);
    IfxPort_setPinModeOutput(LEFT_TRIG, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeInput(LEFT_ECHO, IfxPort_InputMode_pullDown);
    IfxPort_setPinModeOutput(RIGHT_TRIG, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeInput(RIGHT_ECHO, IfxPort_InputMode_pullDown);

	init_gpt1();
}

float ReadRearUltrasonic_noFilt()
{
	volatile int j=0;
	unsigned int timer_end;
	float rear_duration;
	float distance;

	/* Send Trigger Pulse */
    IfxPort_setPinHigh(REAR_TRIG); // Rear TRIG_HIGH
	for(j=0; j<1000; j++) continue;  //waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 1)); // -> 1ms delay
    IfxPort_setPinLow(REAR_TRIG); // Rear TRIG_LOW

	/* Calculate Distance */
	IfxGpt12_T4_setTimerValue(&MODULE_GPT120, 0);
	while (IfxPort_getPinState(REAR_ECHO) == 0); // wait for Rear ECHO_HIGH
	IfxGpt12_T4_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
	while (IfxPort_getPinState(REAR_ECHO) == 1); // wait for Rear ECHO_LOW
	IfxGpt12_T4_run(&MODULE_GPT120, IfxGpt12_TimerRun_stop);

	timer_end = IfxGpt12_T4_getTimerValue(&MODULE_GPT120);
	rear_duration = (timer_end - 0) * 10.24;

	distance = 0.0343 * rear_duration / 2.0; // cm/us
	return distance;
}

float ReadRearUltrasonic_Filt()
{
	float distance_nofilt;
	static float rear_avg_filt_buf[FILT_SIZE] = {0,};
	static int rear_old_index = 0;
	float distance_filt;
	static int rear_sensorRxCnt = 0;

	distance_nofilt = ReadRearUltrasonic_noFilt();

	++rear_old_index;
	rear_old_index %= FILT_SIZE;  // Buffer Size = 5
	rear_avg_filt_buf[rear_old_index] = distance_nofilt;
	rear_sensorRxCnt++;

	/* Calculate Moving Average Filter */
	if (rear_sensorRxCnt >= FILT_SIZE) {
		float sum = 0;
		for (int i = 0; i < FILT_SIZE; i++) { sum += rear_avg_filt_buf[i]; }
		distance_filt = sum / FILT_SIZE;
	}
	else
		distance_filt = distance_nofilt;

	return distance_filt;
}

float ReadLeftUltrasonic_noFilt()
{
    volatile int j=0;
    unsigned int timer_end;
    float left_duration;
    float distance;

    /* Send Trigger Pulse */
    IfxPort_setPinHigh(LEFT_TRIG); // Rear TRIG_HIGH
    for(j=0; j<1000; j++) continue;  //waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 1)); // -> 1ms delay
    IfxPort_setPinLow(LEFT_TRIG); // Rear TRIG_LOW

    /* Calculate Distance */
    IfxGpt12_T4_setTimerValue(&MODULE_GPT120, 0);
    while (IfxPort_getPinState(LEFT_ECHO) == 0); // wait for Rear ECHO_HIGH
    IfxGpt12_T4_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
    while (IfxPort_getPinState(LEFT_ECHO) == 1); // wait for Rear ECHO_LOW
    IfxGpt12_T4_run(&MODULE_GPT120, IfxGpt12_TimerRun_stop);

    timer_end = IfxGpt12_T4_getTimerValue(&MODULE_GPT120);
    left_duration = (timer_end - 0) * 10.24;

    distance = 0.0343 * left_duration / 2.0; // cm/us
    return distance;
}

float ReadLeftUltrasonic_Filt()
{
    float distance_nofilt;
    static float left_avg_filt_buf[FILT_SIZE] = {0,};
    static int left_old_index = 0;
    float distance_filt;
    static int left_sensorRxCnt = 0;

    distance_nofilt = ReadLeftUltrasonic_noFilt();

    ++left_old_index;
    left_old_index %= FILT_SIZE;  // Buffer Size = 5
    left_avg_filt_buf[left_old_index] = distance_nofilt;
    left_sensorRxCnt++;

    /* Calculate Moving Average Filter */
    if (left_sensorRxCnt >= FILT_SIZE) {
        float sum = 0;
        for (int i = 0; i < FILT_SIZE; i++) { sum += left_avg_filt_buf[i]; }
        distance_filt = sum / FILT_SIZE;
    }
    else
        distance_filt = distance_nofilt;

    return distance_filt;
}

float ReadRightUltrasonic_noFilt()
{
    volatile int j=0;
    unsigned int timer_end;
    float right_duration;
    float distance;

    /* Send Trigger Pulse */
    IfxPort_setPinHigh(REAR_TRIG); // Rear TRIG_HIGH
    for(j=0; j<1000; j++) continue;  //waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 1)); // -> 1ms delay
    IfxPort_setPinLow(REAR_TRIG); // Rear TRIG_LOW

    /* Calculate Distance */
    IfxGpt12_T4_setTimerValue(&MODULE_GPT120, 0);
    while (IfxPort_getPinState(REAR_ECHO) == 0); // wait for Rear ECHO_HIGH
    IfxGpt12_T4_run(&MODULE_GPT120, IfxGpt12_TimerRun_start);
    while (IfxPort_getPinState(REAR_ECHO) == 1); // wait for Rear ECHO_LOW
    IfxGpt12_T4_run(&MODULE_GPT120, IfxGpt12_TimerRun_stop);

    timer_end = IfxGpt12_T4_getTimerValue(&MODULE_GPT120);
    right_duration = (timer_end - 0) * 10.24;

    distance = 0.0343 * right_duration / 2.0; // cm/us
    return distance;
}

float ReadRightUltrasonic_Filt()
{
    float distance_nofilt;
    static float right_avg_filt_buf[FILT_SIZE] = {0,};
    static int right_old_index = 0;
    float distance_filt;
    static int right_sensorRxCnt = 0;

    distance_nofilt = ReadRightUltrasonic_noFilt();

    ++right_old_index;
    right_old_index %= FILT_SIZE;  // Buffer Size = 5
    right_avg_filt_buf[right_old_index] = distance_nofilt;
    right_sensorRxCnt++;

    /* Calculate Moving Average Filter */
    if (right_sensorRxCnt >= FILT_SIZE) {
        float sum = 0;
        for (int i = 0; i < FILT_SIZE; i++) { sum += right_avg_filt_buf[i]; }
        distance_filt = sum / FILT_SIZE;
    }
    else
        distance_filt = distance_nofilt;

    return distance_filt;
}
