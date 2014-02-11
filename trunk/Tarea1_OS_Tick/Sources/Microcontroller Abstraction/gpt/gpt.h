/******************************************************************************
*   Filename:   gpt.h 
*
*   Description: Periodic Interrupt Timer initialization and low-level functions and prototypes
*
*
*   Revision History:
*
*                             
*   Date          #Change       Author
*   MM-DD-YY      Number:       Initials   Description of change
*   -----------   -----------   --------   ------------------------------------
*   02-10-14       00            JMR         Initial release
******************************************************************************/

#ifndef __GPT_H        /*prevent duplicated includes*/
#define __GPT_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core Modules */
/** Configuration Options */
  #include    "gpt_cfg.h"
/** S12X derivative information */
  #include  <mc9s12xep100.h>  
/** Variable types and common definitions */
  #include    "typedefs.h"

/** Used Modules */
/** Clock definitions and prototypes*/
  #include    "mcu.h"

/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/* vfnPIT0_Callback, function to be called upon timeout of PIT channel 0 */
extern void Gpt_Channel0_callback(void);
extern void Gpt_Channel1_callback(void);
extern void Gpt_Channel2_callback(void);
extern void Gpt_Channel3_callback(void);

/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/

/** Periodic Interrupt Timer definitions */
#define    PIT_MICROTIMER_PERIOD            1000000
#define    PIT_TARGET_FREQ                  2000

/** Periodic Interrupt Timer macros */
#define    PIT_MICROTIMER_DIV               ( u8 ) ( ( mcal_mcu_gu32BusFrequency / PIT_MICROTIMER_PERIOD ) - 1 )
#define    PIT_VALUE                        ( ( PIT_MICROTIMER_PERIOD / PIT_TARGET_FREQ ) - 1 )


/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

 void Gpt_Init( const Gpt_ConfigType* ConfigPtr );
 void Gpt_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value ) ;
 void Gpt_StopTimer( Gpt_ChannelType Channel ) ;
 void Gpt_EnableNotification( Gpt_ChannelType Channel ) ;
 void Gpt_DisableNotification( Gpt_ChannelType Channel ) ;

/** PIT Channel 0 ISR --> Main CPU  */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
	void interrupt  vfnPIT_Channel0_Isr( void  );
	void interrupt  vfnPIT_Channel1_Isr( void  );
	void interrupt  vfnPIT_Channel2_Isr( void  );
	void interrupt  vfnPIT_Channel3_Isr( void  );
#pragma CODE_SEG DEFAULT

/*******************************************************************************/

#endif /* __GPT_H */