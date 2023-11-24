/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "GtmTomPwmHlDemo.h"
#include "ConfigurationIsr.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/

App_GtmTomPwmHl g_GtmTomPwmHl; /**< \brief Demo information */
uint32 PWMCnt;
/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

IFX_INTERRUPT(ISR_Timer, 0, ISR_PRIORITY_TIMER);

void ISR_Timer(void)
{
   IfxCpu_enableInterrupts();
   IfxGtm_Tom_Timer_acknowledgeTimerIrq(&g_GtmTomPwmHl.drivers.timer);
   g_GtmTomPwmHl.isrCounter.counter++;

}


void GtmTomPwmHl_initTimer(void)
{
    {
        IfxGtm_Tom_Timer_Config timerConfig;
        IfxGtm_Tom_PwmHl_Config pwmHlConfig;
        IfxGtm_Tom_Timer_initConfig(&timerConfig, &MODULE_GTM);
        IfxGtm_Tom_PwmHl_initConfig(&pwmHlConfig);

        timerConfig.base.frequency                  = 3000;
        timerConfig.base.isrPriority                = ISR_PRIORITY(INTERRUPT_TIMER);
        timerConfig.base.isrProvider                = ISR_PROVIDER(INTERRUPT_TIMER);
        timerConfig.base.minResolution              = (1.0 / timerConfig.base.frequency) / 1000;
        timerConfig.base.trigger.enabled            = FALSE;
        timerConfig.clock                           = IfxGtm_Tom_Ch_ClkSrc_cmuFxclk0;
        timerConfig.base.countDir                   = IfxStdIf_Timer_CountDir_upAndDown;

        timerConfig.tom                             = IfxGtm_Tom_0;
        timerConfig.timerChannel                    = IfxGtm_Tom_Ch_0;
        timerConfig.triggerOut                      = &IfxGtm_TOM0_0_TOUT77_P15_6_OUT;

        timerConfig.base.trigger.outputEnabled      = TRUE;
        timerConfig.base.trigger.enabled            = TRUE;
        timerConfig.base.trigger.triggerPoint       = 500;
        timerConfig.base.trigger.risingEdgeAtPeriod = TRUE;

        IfxGtm_Tom_Timer_init(&g_GtmTomPwmHl.drivers.timer, &timerConfig);

        IfxGtm_Tom_ToutMapP ccx[2], coutx[2];
        coutx[0] = &IfxGtm_TOM0_3_TOUT105_P10_3_OUT;
        ccx[0]   = &IfxGtm_TOM0_4_TOUT22_P33_0_OUT;
        coutx[1] = &IfxGtm_TOM0_2_TOUT107_P10_5_OUT;
        ccx[1]   = &IfxGtm_TOM0_5_TOUT23_P33_1_OUT;

        pwmHlConfig.timer                 = &g_GtmTomPwmHl.drivers.timer;
        pwmHlConfig.tom                   = timerConfig.tom;
        pwmHlConfig.base.deadtime         = 2e-6;
        pwmHlConfig.base.minPulse         = 1e-6;
        pwmHlConfig.base.channelCount     = 2;
        pwmHlConfig.base.emergencyEnabled = FALSE;
        pwmHlConfig.base.outputMode       = IfxPort_OutputMode_none;
        pwmHlConfig.base.outputDriver     = IfxPort_PadDriver_cmosAutomotiveSpeed1;
        pwmHlConfig.base.ccxActiveState   = Ifx_ActiveState_high;
        pwmHlConfig.base.coutxActiveState = Ifx_ActiveState_high;
        pwmHlConfig.ccx                   = ccx;
        pwmHlConfig.coutx                 = coutx;

        IfxGtm_Tom_PwmHl_init(&g_GtmTomPwmHl.drivers.pwm, &pwmHlConfig);

        IfxGtm_Tom_Timer_run(&g_GtmTomPwmHl.drivers.timer);
    }
}


/** \brief Demo init API
 *
 * This function is called from main during initialization phase
 */
void GtmTomPwmHl_init(void)
{
    /* disable interrupts */
    boolean  interruptState = IfxCpu_disableInterrupts();
    /** - GTM clocks */
    Ifx_GTM *gtm = &MODULE_GTM;
    g_GtmTomPwmHl.info.gtmFreq = IfxGtm_Cmu_getModuleFrequency(gtm);
    IfxGtm_enable(gtm);

    /* Set the global clock frequencies */
    IfxGtm_Cmu_setGclkFrequency(&MODULE_GTM, g_GtmTomPwmHl.info.gtmFreq);
    g_GtmTomPwmHl.info.gtmGclkFreq = IfxGtm_Cmu_getGclkFrequency(gtm);

    IfxGtm_Cmu_setClkFrequency(&MODULE_GTM, IfxGtm_Cmu_Clk_0, g_GtmTomPwmHl.info.gtmGclkFreq);
    g_GtmTomPwmHl.info.gtmCmuClk0Freq = IfxGtm_Cmu_getClkFrequency(gtm, IfxGtm_Cmu_Clk_0, TRUE);

    /** - Initialise the GTM part */
    GtmTomPwmHl_initTimer();
    g_GtmTomPwmHl.info.timerValue =  IfxGtm_Tom_Timer_getPeriod(&g_GtmTomPwmHl.drivers.timer);
    g_GtmTomPwmHl.tOn[0] = 0;
    g_GtmTomPwmHl.tOn[1] = 0;
    /* enable interrupts again */
    IfxCpu_restoreInterrupts(interruptState);

    IfxGtm_Cmu_enableClocks(gtm, IFXGTM_CMU_CLKEN_FXCLK | IFXGTM_CMU_CLKEN_CLK0);
}


/** \brief run API
 *
 * This function is called from main, background loop
 */



void GtmTomPwmHl_run(void)
{

    PWMCnt++;
    IfxGtm_Tom_PwmHl *pwmHl = &g_GtmTomPwmHl.drivers.pwm;
    IfxGtm_Tom_Timer *timer = &g_GtmTomPwmHl.drivers.timer;
    g_GtmTomPwmHl.drivers.timer.base.countDir= IfxStdIf_Timer_CountDir_upAndDown;
    IfxGtm_Tom_Timer_getPeriod(timer);
    Ifx_TimerValue DUTY[2];

    DUTY[0]=(uint32)(g_GtmTomPwmHl.tOn[0]*IfxGtm_Tom_Timer_getPeriod(timer));
    DUTY[1]=(uint32)(g_GtmTomPwmHl.tOn[1]*IfxGtm_Tom_Timer_getPeriod(timer));

    IfxGtm_Tom_PwmHl_setMode(pwmHl, Ifx_Pwm_Mode_centerAligned);
    IfxGtm_Tom_Timer_disableUpdate(timer);
    IfxGtm_Tom_PwmHl_setOnTime(pwmHl,DUTY);
    IfxGtm_Tom_Timer_applyUpdate(timer);
}
