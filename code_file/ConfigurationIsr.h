
#ifndef CONFIGURATIONISR_H
#define CONFIGURATIONISR_H

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/** \brief Build the ISR configuration object
 * \param no interrupt priority
 * \param cpu assign CPU number
 */
#define ISR_ASSIGN(no, cpu)  ((no << 8) + cpu)
/** \brief extract the priority out of the ISR object */
#define ISR_PRIORITY(no_cpu) (no_cpu >> 8)
/** \brief extract the service provider  out of the ISR object */
#define ISR_PROVIDER(no_cpu) (no_cpu % 8)

/**
 * \name Interrupt priority configuration.
 * The interrupt priority range is [1,255]
 * \{ */

#define ISR_PRIORITY_TIMER          200 /**< \brief Define the 1ms timer interrupt priority.  */
/** \} */
/**
 * \name Interrupt service provider configuration.
 * \{ */

#define ISR_PROVIDER_TIMER          IfxSrc_Tos_cpu0 /**< \brief Define the 1ms timer interrupt provider.  */

/** \} */
/**
 * \name Interrupt configuration.
 * \{ */
#define INTERRUPT_TIMER             ISR_ASSIGN(ISR_PRIORITY_TIMER, ISR_PROVIDER_TIMER)                   /**< \brief Define the 1ms timer interrupt priority.  */

/** \} */

/** \} */
//------------------------------------------------------------------------------

#endif
