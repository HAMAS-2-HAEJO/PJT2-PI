/***********************************************************************/
/*Include*/
/***********************************************************************/
#include "AppScheduling.h"
#include "Driver_Stm.h"
#include "GtmTomPwmHlDemo.h"
#include "Blinky_LED.h"
#include "MidAdc.h"
#include "IfxPort.h"
#include "IfxPort_PinMap.h"
#include "math.h"
#include <asclin.h>
#include "Motor.h"
#include "Drivers/asclin.h"
#include "IO/ToF.h"
#include <stdio.h>
#include "my_stdio.h"
/***********************************************************************/
/*Define*/
/***********************************************************************/

/***********************************************************************/
/*Typedef*/
/***********************************************************************/
typedef struct
{
    uint32 u32nuCnt1ms;
    uint32 u32nuCnt10ms;
    uint32 u32nuCnt100ms;
    uint32 u32nuCnt1000ms;
} TestCnt;
/***********************************************************************/
/*Static Function Prototype*/
/***********************************************************************/
static void AppNoTask (void);
static void AppTask1ms (void);
static void AppTask10ms (void);
static void AppTask100ms (void);
float32 LPF (float32 y_old, float32 x, float32 Ts, float32 band);
/***********************************************************************/
/*Variable*/
/***********************************************************************/
uint32 ULSraw;
TestCnt stTestCnt;
boolean ENCA;
boolean ENCB;
boolean ENCA_old;
boolean ENCB_old;
uint32 trig_A;
uint32 trig_B;
boolean intr_A;
boolean intr_B;
int duty;
int dir = 1;
float32 Vin;
int S;
int S_old;
int PosCnt = 0;
int PosCntd = 0;
float32 Direction;
float32 Pos_rad;
float32 ome_d;
float32 Pos_rad_d;
int Pos_deg;
float32 theta;
float32 theta_old;
float32 theta_d_old;
float32 w = 0;
float32 Wd;
float32 w_old = 0;
float32 error_w = 0;
uint32 W_RPM;
float32 w_ref;
uint32 ACnt;
float32 error_w_int_old;
float32 error_w_int;
float32 du_w;
float32 kp = 0.3;
float32 ki = 0.9;
float32 t;
float32 per;
float32 per_old;
float32 W_st;
float32 V_st;

int tof_distance;
float32 L_des = 20; //유지 거리
float32 L_Error; //현재거리 - 유지거리
float32 tau, tau_old;
float32 Wconst = 50;
float32 L_Error_int;
float32 L_Error_int_old;
float32 L_kp = 4;
float32 L_ki = 3.9;
float32 Vref = 50;

/***********************************************************************/
/*Function*/
/***********************************************************************/
static void AppNoTask (void)
{
    ENCA = IfxPort_getPinState(&MODULE_P02, 1); // Encoder A signal state
    ENCB = IfxPort_getPinState(&MODULE_P02, 0); // Encoder B signal state
    if (ENCA == FALSE && ENCB == FALSE)
    {
        S = 0;
    }
    else if (ENCA == FALSE && ENCB == TRUE)
    {
        S = 1;
    }
    else if (ENCA == TRUE && ENCB == TRUE)
    {
        S = 2;
    }
    else if (ENCA == TRUE && ENCB == FALSE)
    {
        S = 3;
    }

    if (S - S_old == 1 || S - S_old == -3)
    {
        PosCnt = PosCntd - 1;
        Direction = 1;
    }
    else if (S - S_old == -1 || S - S_old == 3)
    {
        PosCnt = PosCntd + 1;
        Direction = -1;
    }
    S_old = S;

    Pos_rad = PosCnt * 2 * 3.14159265358979323 / 48;   //   ڴ         ,      ̿      ġ
    Pos_deg = (int) (PosCnt * 360 / 48);
    PosCntd = PosCnt;
    ENCA_old = ENCA;
    ENCB_old = ENCB;
    theta = Pos_rad;
}

static void AppTask1ms (void)
{
    ACnt++;
    Wd = 5;
    float32 Ts = 0.001;
    DrvAdc_GetAdcRawGroup0();  // ADC  ޱ
    SensorAdcRaw *pstSensorAdcRaw = MidAdc_GetAdcGroup0SenseRaw(); //
    ULSraw = pstSensorAdcRaw->UlSSense1_Raw;       //ADC value 0~5V 0~4095
    t = ACnt * Ts;
    w_ref = (Vref/10) * 3.14 * 2.0f;
    w = (theta - theta_old) / Ts;
    if (w < 0)
        w = -(w);
    w = LPF(w_old, w, Ts, 500);
    w_old = w;
    W_RPM = (uint32) (60 * w / (2 * 3.141592));
    theta_old = theta;

    error_w = w_ref - w;
    error_w_int = error_w_int_old + (error_w) * Ts;
    error_w_int_old = error_w_int;

    if (error_w_int > 10)
    {
        error_w_int = 10;
    }

    Vin = (kp * error_w + ki * error_w_int);

    if (Vin > 11)
    {
        Vin = 11;
    }
    else if (Vin < 0)
    {
        Vin = 0;
    }

    int value = (Vin / 12) * 100;
    duty = value;

    movChB_PWM(duty, dir);
}

static void AppTask10ms (void)
{
    tof_distance = getTofDistance();
    tof_distance /= 10;

    /*if (tof_distance > 0)
     {
     my_printf("%d\n", tof_distance);
     }*/

    float32 Ts = 0.01;
    L_Error = tof_distance - L_des;

    if (L_Error > 0)
    {
        tau = 0;
        if (tau_old != tau)
        {
            L_Error_int_old = 0;
        }
    }
    else
    {
        tau = 1;
        if (tau_old != tau)
        {
            L_Error_int_old = 0;
        }
    }
    tau_old = tau;

    L_Error_int = L_Error_int_old + (L_Error) * Ts;
    if(L_Error_int > 20)
    {
        L_Error_int = 20;
    }
    L_Error_int_old = L_Error_int;

    float32 L_Wd = tau * ((L_Error * L_kp) + (L_Error_int * L_ki));
    my_printf("%f\n", L_Wd);
    Vref = Wconst + L_Wd;
}

static void AppTask100ms (void)
{

}

static void AppTask1000ms (void)
{

}

float32 LPF (float32 y_old, float32 x, float32 Ts, float32 band)
{
    double A1 = Ts / (Ts + 1 / band);
    float32 y = y_old + A1 * (x - y_old);

    return y;
}

void AppScheduling (void)
{
    AppNoTask();
//    printf("appsch\n");
    if (stSchedulingInfo.u8nuScheduling1msFlag == 1u)
    {
        stSchedulingInfo.u8nuScheduling1msFlag = 0u;
//        printf("appsch1m\n");
        stTestCnt.u32nuCnt1ms++;
        AppTask1ms();

        if (stSchedulingInfo.u8nuScheduling10msFlag == 1u)
        {
//            printf("appsch10m\n");
            stSchedulingInfo.u8nuScheduling10msFlag = 0u;
            stTestCnt.u32nuCnt10ms++;
            AppTask10ms();
        }

        if (stSchedulingInfo.u8nuScheduling100msFlag == 1u)
        {
//            printf("appsch100m\n");
            stSchedulingInfo.u8nuScheduling100msFlag = 0u;
            stTestCnt.u32nuCnt100ms++;
            AppTask100ms();
        }
        if (stSchedulingInfo.u8nuScheduling1000msFlag == 1u)
        {
//            printf("appsch1000m\n");
            stSchedulingInfo.u8nuScheduling1000msFlag = 0u;
            stTestCnt.u32nuCnt1000ms++;
            AppTask1000ms();
        }
    }
}
