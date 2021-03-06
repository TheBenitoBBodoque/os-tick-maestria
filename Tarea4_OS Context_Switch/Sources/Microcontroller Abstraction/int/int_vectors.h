/******************************************************************************
*   Filename:   int_vectors.h
*
*   Description: Interrupt Vector functions and prototypes
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


#ifndef __INT_VECTORS_H
#define    __INT_VECTORS_H    

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core modules */
/** Configuration Options */
#include    "mcu_cfg.h"
/** MCU derivative information */
#include <mc9s12xep100.h>
/** Variable types and common definitions */
#include    "typedefs.h"

/** Used modules */
/** PIT definitions and prototypes*/
#include    "gpt.h"
/** PLL definitions and prototypes*/
#include    "mcu.h"
#include    "serial.h"

/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/
extern volatile u8 gInterrupt_nested_flag;

/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/


/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt  vfnDummy_D_Isr( void  );
void interrupt vfnSoftware_Isr(void);
#pragma CODE_SEG DEFAULT

#define SERIAL_COMM_CHANNEL0
extern void DisableAllInterrupts(void);
extern void EnableAllInterrupts(void);
#endif /*__INT_VECTORS_H */ 
/****************************************************************************************************/ 