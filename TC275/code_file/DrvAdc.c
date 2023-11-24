/*----------------------------------------------------------------*/
/*                        Include Header File                          */
/*----------------------------------------------------------------*/
#include "DrvAdc.h"
#include "IfxVadc.h"
#include "IfxVadc_Adc.h"

/*----------------------------------------------------------------*/
/*                        Define                                        */
/*----------------------------------------------------------------*/


/*----------------------------------------------------------------*/
/*                        Typedefs                                    */
/*----------------------------------------------------------------*/
typedef struct
{
    IfxVadc_Adc vadc; /* VADC handle */
    IfxVadc_Adc_Group adcGroup;
} App_VadcAutoScan;


/*----------------------------------------------------------------*/
/*                        Static Function Prototype                  */
/*----------------------------------------------------------------*/
static void DrvAdc_Group0Init(void);
static void DrvAdc_Group0ChannelInit(uint8 param_ChNum);

/*----------------------------------------------------------------*/
/*                        Variables                                    */
/*----------------------------------------------------------------*/
App_VadcAutoScan g_VadcAutoScan;

IfxVadc_Adc_Channel adc0Channel[ADC_GROUP0_MAX];

SensorAdcRaw stSensorAdcRaw; // ADC Raw 값 받을 변수


/*----------------------------------------------------------------*/
/*                        Functions                                    */
/*----------------------------------------------------------------*/

/*---------------------Interrupt Define--------------------------*/



/*---------------------Test Code--------------------------*/
void DrvAdc_GetAdcRawGroup0(void)   //ADC 센싱 값을 처음 받는 부분
{

    Ifx_VADC_RES conversionResult;    // VADC 레지스터 값을 받을 변수 conversionReult를 Ifx_VADC_RES 구조체로 선언한다.

    /*Get Data*/
    conversionResult = IfxVadc_Adc_getResult(&adc0Channel[ADC_GROUP0_CH1]);
    stSensorAdcRaw.UlSSense1_Raw = conversionResult.B.RESULT;
    conversionResult = IfxVadc_Adc_getResult(&adc0Channel[ADC_GROUP0_CH2]);
    stSensorAdcRaw.UlSSense2_Raw = conversionResult.B.RESULT;
    conversionResult = IfxVadc_Adc_getResult(&adc0Channel[ADC_GROUP0_CH3]);
    stSensorAdcRaw.UlSSense3_Raw = conversionResult.B.RESULT;

    /*Start Autoscan */
    IfxVadc_Adc_startScan(&g_VadcAutoScan.adcGroup);
}


/*---------------------Init Function--------------------------*/
void DrvAdcInit(void)
{
    DrvAdc_Group0Init();
}

static void DrvAdc_Group0Init(void)
{
    /* VADC Configuration */

    /* create configuration */
    IfxVadc_Adc_Config adcConfig;
    IfxVadc_Adc_initModuleConfig(&adcConfig, &MODULE_VADC);

    /* initialize module */
    IfxVadc_Adc_initModule(&g_VadcAutoScan.vadc, &adcConfig);

    /* create group config */
    IfxVadc_Adc_GroupConfig adcGroupConfig;
    IfxVadc_Adc_initGroupConfig(&adcGroupConfig, &g_VadcAutoScan.vadc);

    /* with group 0 */
    adcGroupConfig.groupId = IfxVadc_GroupId_0;
    adcGroupConfig.master  = adcGroupConfig.groupId;

    /* enable scan source */
    adcGroupConfig.arbiter.requestSlotScanEnabled = TRUE;

    /* enable auto scan */
    adcGroupConfig.scanRequest.autoscanEnabled = TRUE;

    /* enable all gates in "always" mode (no edge detection) */
    adcGroupConfig.scanRequest.triggerConfig.gatingMode = 1;

    /* initialize the group */
    /*IfxVadc_Adc_Group adcGroup;*/    //declared globally
    IfxVadc_Adc_initGroup(&g_VadcAutoScan.adcGroup, &adcGroupConfig);

    /*ADC Channel Init*/
    DrvAdc_Group0ChannelInit(ADC_GROUP0_CH1);
    DrvAdc_Group0ChannelInit(ADC_GROUP0_CH2);
    DrvAdc_Group0ChannelInit(ADC_GROUP0_CH3);

    /* start autoscan */
    IfxVadc_Adc_startScan(&g_VadcAutoScan.adcGroup);
}

static void DrvAdc_Group0ChannelInit(uint8 param_ChNum)
{
    IfxVadc_Adc_ChannelConfig adcChannelConfigInfo;
    uint32 ulTemp = ((uint32)1u << param_ChNum);
    
    IfxVadc_Adc_initChannelConfig(&adcChannelConfigInfo, &g_VadcAutoScan.adcGroup);

    adcChannelConfigInfo.channelId      = (IfxVadc_ChannelId)(param_ChNum);
    adcChannelConfigInfo.resultRegister = (IfxVadc_ChannelResult)(param_ChNum); 
    
    /* initialize the channel */
    IfxVadc_Adc_initChannel(&adc0Channel[param_ChNum], &adcChannelConfigInfo);

    /* add to scan */
    IfxVadc_Adc_setScan(&g_VadcAutoScan.adcGroup, ulTemp, ulTemp);
}

#if 0
static void DrvAdc1Init(void)
{
    uint32    chnIx;
    IfxVadc_Adc_ChannelConfig adcChannelConfig[2];     /* create channel config */

    /* VADC Configuration */

    /* create configuration */
    IfxVadc_Adc_Config adcConfig;
    IfxVadc_Adc_initModuleConfig(&adcConfig, &MODULE_VADC);

    /* initialize module */
    IfxVadc_Adc_initModule(&g_VadcBackgroundScan.vadc, &adcConfig);

    /* create group config */
    IfxVadc_Adc_GroupConfig adcGroupConfig;
    IfxVadc_Adc_initGroupConfig(&adcGroupConfig, &g_VadcBackgroundScan.vadc);

    /* with group 1 */
    adcGroupConfig.groupId = IfxVadc_GroupId_1;
    adcGroupConfig.master  = adcGroupConfig.groupId;

    /* enable background scan source */
    adcGroupConfig.arbiter.requestSlotBackgroundScanEnabled = TRUE;

    /* enable background auto scan */
    adcGroupConfig.backgroundScanRequest.autoBackgroundScanEnabled = TRUE;

    /* enable all gates in "always" mode (no edge detection) */
    adcGroupConfig.backgroundScanRequest.triggerConfig.gatingMode = IfxVadc_GatingMode_always;

    /* initialize the group */
    IfxVadc_Adc_initGroup(&g_VadcBackgroundScan.adcGroup, &adcGroupConfig);

   for (chnIx = 0; chnIx < 2; ++chnIx)
    {
        IfxVadc_Adc_initChannelConfig(&adcChannelConfig[chnIx], &g_VadcBackgroundScan.adcGroup);

        adcChannelConfig[chnIx].channelId         = (IfxVadc_ChannelId)(chnIx + 3);
        adcChannelConfig[chnIx].resultRegister    = (IfxVadc_ChannelResult)(3 + chnIx); // use register #5 and 6 for results
        adcChannelConfig[chnIx].backgroundChannel = TRUE;

        /* initialize the channel */
        IfxVadc_Adc_initChannel(&adc1Channel[chnIx], &adcChannelConfig[chnIx]);

        /* add to background scan */
        unsigned channels = (1 << adcChannelConfig[chnIx].channelId);
        unsigned mask     = channels;
        IfxVadc_Adc_setBackgroundScan(&g_VadcBackgroundScan.vadc, &g_VadcBackgroundScan.adcGroup, channels, mask);
    }

    /* start scan */
    IfxVadc_Adc_startBackgroundScan(&g_VadcBackgroundScan.vadc);
}

void VadcBackgroundScanDemo_run(void)
{
    uint32    chnIx;

    /* check results */
    for (chnIx = 0; chnIx < 2; ++chnIx)
    {
        /* wait for valid result */
        Ifx_VADC_RES conversionResult;

        do
        {
            conversionResult = IfxVadc_Adc_getResult(&adc1Channel[chnIx]);
        } while (!conversionResult.B.VF);

         g_Vadc1Result[chnIx] = conversionResult.B.RESULT;
    }
}

#endif
