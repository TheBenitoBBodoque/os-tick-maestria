#ifndef __SCHM_H
#define __SCHM_H
/******************************************************************************
*   Filename:   SchM.h
*
*   Description:  
*
*
*   Revision history:
*
*   Date          CP#           Author     
*   MM-DD-YY      XXXXX:1       Initials   Description of change
*   -----------   -----------   --------   ------------------------------------
*   03-01-14       02            SPA        OS Task Initial Release
******************************************************************************/

/******************************************************************************
*   Include Files
******************************************************************************/
#include "typedefs.h"
/******************************************************************************
*   Macro Definitions  
******************************************************************************/

/******************************************************************************
*   Type Definitions
******************************************************************************/

/******************************************************************************
*   External Variables
******************************************************************************/
 
/******************************************************************************
*   Global Function Prototypes  
******************************************************************************/
/* vfnPIT0_Callback, function to be called upon timeout of PIT channel 0 */
void SchM_OsTick(void);
void SchM_SchedulerCore(void);

#endif /*__SCHM_H*/
