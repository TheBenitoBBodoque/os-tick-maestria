/******************************************************************************
*   Filename:   mcu.h 
*
*   Description: S12XE/S12XS CPU and PLL initialization prototypes and definitions
*
*
*   Revision History: This driver was developed by TEAM 4.
*                             
*   Date          #Change       Author
*   MM-DD-YY      Number:       Initials   Description of change
*   -----------   -----------   --------   ------------------------------------
*   02-10-14       00            JMR         Initial release
******************************************************************************/


#ifndef __MCU_H
#define __MCU_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core modules */
/** Configuration Options */
  #include "mcu_cfg.h"
/** S12X derivative information */
  #include <mc9s12xep100.h>
/** Variable types and common definitions */
  #include "typedefs.h"   

/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/
extern u32 mcal_mcu_gu32BusFrequency;

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/

/** System Clock status definitions */   
#define CLOCK_STATUS_PLL_OFF            0u   
#define CLOCK_STATUS_PLL_OK             1u
#define CLOCK_STATUS_PLL_SELECTED       2u
#define CLOCK_STATUS_XTAL_SELECTED      3u
#define CLOCK_STATUS_PLL_LOCK_ERROR     4u
#define CLOCK_STATUS_SCM_ERROR          5u


/** Clock configuration macros and definitions */
/** BUS clock frequency */
#define CNF_BUS_FREQ_MHZ        CNF_BUS_FREQ_KHZ/1000       
/** Xtal frequency */ 
#define XTAL_FREQ_MHZ       CNF_XTAL_FREQ_KHZ/1000


#define XTAL_FREQ_MIN_KHZ   4000u 
#define XTAL_FREQ_MAX_KHZ   16000u 

#define BUS_FREQ_MIN_KHZ    8000u 
#define BUS_FREQ_MAX_KHZ    50000u 

/* Validate XTAL frequency range */
#if (CNF_XTAL_FREQ_KHZ < XTAL_FREQ_MIN_KHZ)
    #error "XTAL frequency is below the minimum allowed frequency"
#endif    
#if (CNF_XTAL_FREQ_KHZ > XTAL_FREQ_MAX_KHZ)
    #error "XTAL frequency is above the maximum allowed frequency"
#endif       

/* Validate CNF_BUS_FREQ_KHZ range */
#if (CNF_BUS_FREQ_KHZ < BUS_FREQ_MIN_KHZ)
    #error "CNF_BUS_FREQ_KHZ is below the minimum allowed frequency"
#endif    
#if (CNF_BUS_FREQ_KHZ > BUS_FREQ_MAX_KHZ)
    #error "CNF_BUS_FREQ_KHZ is above the maximum allowed frequency"    
#endif   

/** ~~~~~~~~~~~~ System configuration definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
     
/** Select POSTDIV value to obtain the lowest possible FVCO/F_REF ratio and stable VCO value */
#if (CNF_BUS_FREQ_MHZ*4 > 120)
    #define CNF_POSTDIV_VALUE   0u
#elif ((CNF_BUS_FREQ_MHZ*4 >= 32) & (CNF_BUS_FREQ_MHZ*4 <= 120))
    #define CNF_POSTDIV_VALUE   1u
#elif (CNF_BUS_FREQ_MHZ*4 <= 32)
    #define CNF_POSTDIV_VALUE   (64/(CNF_BUS_FREQ_MHZ*4))
#endif    

/*-- Macros ------------------------------------------------------------------*/

/** ~~~~~~~~~~~~~ System clock related macros ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** FVCO = 2 * XTAL_FREQ * (SYNR+1) / (REFDV+1)                     Equation 1  */
/** FPLL = FVC0 / (2 * POSTDIV) (If POSTDIV != 0)                   Equation 2  */
/** FPLL = FVC0                 (If POSTDIV == 0)                   Equation 2a */
/** FBUS = FPLL/2                                                   Equation 4  */
/** FREF = XTAL_FREQ /(REFDV+1)                                     Equation 5  */
/** FPLL = 2 * XTAL_FREQ * (SYNR+1) / ((REFDV+1)*(2 * POSTDIV))     Equation 6  */
/** FBUS = FVC0/2               (If POSTDIV == 0)                   Equation 6  */
/** FBUS = FVCO/(4 * POSTDIV)   (If POSTDIV != 0)                   Equation 6a */

/** Select REFDV factor to obtain the highest possible REFCLK frequency F_REF */
#define REFDV_FACTOR        (XTAL_FREQ_MHZ/4)

/* Define CNF_REFDV_VALUE */
#define CNF_REFDV_VALUE         (REFDV_FACTOR-1)

/** Define desired VCO frequency value */
#if (CNF_POSTDIV_VALUE == 0)
    #define VCO_FREQ        (CNF_BUS_FREQ_MHZ*2)
#else
    #define VCO_FREQ        (CNF_BUS_FREQ_MHZ*4*CNF_POSTDIV_VALUE)
#endif    

/** Configure VCO gain for optimal stability and lock time */
/** VCOFRQ = 0; 32MHz <= fVCO <= 48MHz  */
#if ((VCO_FREQ >= 32) & (VCO_FREQ <= 48))
    #define CNF_VCOFRQ_VALUE    0u                                            
/** VCOFRQ = 1; 48MHz <  fVCO <= 80MHz  */
#elif ((VCO_FREQ > 48) & (VCO_FREQ <= 80))
    #define CNF_VCOFRQ_VALUE    1u 
/** VCOFRQ = 3; 80MHz <  fVCO <= 120MHz */    
#elif ((VCO_FREQ > 80) & (VCO_FREQ <= 120))
    #define CNF_VCOFRQ_VALUE    3u 
#else 
/** Selected VCO frequency is out of range */
    #error  "VCO Frequency is out of Range"
#endif

/* Define REFDV value based on Equation 1 */
#define SYNR_FACTOR     (REFDV_FACTOR*VCO_FREQ)/(2*XTAL_FREQ_MHZ)
/* Define SYNR value */
#define CNF_SYNR_VALUE      (SYNR_FACTOR-1)

/* Define F_REF based on Equation 4 */
#define F_REF           (XTAL_FREQ_MHZ/(CNF_REFDV_VALUE+1))

/** Configure PLL filter for optimal stability and lock time */
/** REFFRQ = 0; 1MHz <= fREF <= 2MHz */
#if ((F_REF >= 1) & (F_REF <= 2))
    #define CNF_REFFRQ_VALUE    0u  
/** REFFRQ = 1; 2MHz <  fREF <= 6MHz */
#elif ((F_REF >  2) & (F_REF <= 6))
    #define CNF_REFFRQ_VALUE    1u 
/** REFFRQ = 2; 6MHz <  fREF <= 12MHz */
#elif ((F_REF >  6) & (F_REF <= 12))
    #define CNF_REFFRQ_VALUE    2u 
/** REFFRQ = 3; fREF > 12MHz */
#elif (F_REF >  12)
    #define CNF_REFFRQ_VALUE    3u
#else
/** Selected F_REF frequency is out of range */
    #error  "F_REF Frequency is out of Range"        
#endif

/** Define actual BUS_FREQ value to be programmed in PLL circuit */
#if (CNF_POSTDIV_VALUE == 0)
    #define ACTUAL_BUS_FREQ         (u32)(2*XTAL_FREQ_MHZ*(SYNR_SYNDIV+1))*1000000 / ((REFDV_REFDIV+1)*2)
    #define ACTUAL_BUS_FREQ_KHZ     (2*XTAL_FREQ_MHZ*SYNR_FACTOR)*1000 / (REFDV_FACTOR*2)
#else
    #define ACTUAL_BUS_FREQ         (u32)(2*XTAL_FREQ_MHZ*(SYNR_SYNDIV+1))*1000000 / ((REFDV_REFDIV+1)*4*POSTDIV_POSTDIV)
    #define ACTUAL_BUS_FREQ_KHZ     (2*XTAL_FREQ_MHZ*SYNR_FACTOR)*1000 / (REFDV_FACTOR*4*CNF_POSTDIV_VALUE)
#endif
#if (ACTUAL_BUS_FREQ_KHZ != CNF_BUS_FREQ_KHZ)
    #error "Selected BUS Frequency can NOT be calculated automatically. Manually set PLL values"
#endif

/*-- Function Prototypes -----------------------------------------------------*/

/** System clock and PLL initialization */
void Mcu_Init(void);

/** Select the XTAL as a mcu clock */
void Mcu_InitClock(void);

/** Select the Pll as a mcu clock */
void Mcu_DistributePllClock(void);

/** Select PLL as clock source once it has been initialized */
void vfnSelectClockSource_PLL(void) ;

/** Clock Monitor Interrupt Service Routine */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void vfnPll_Clock_Monitor_Isr(void);
#pragma CODE_SEG DEFAULT

#endif /* __PLL_H */

/*******************************************************************************/