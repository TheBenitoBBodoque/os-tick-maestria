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
*   03-29-14       10            SPA        OS Dispatcher and OSEK functions
*   03-29-14       11            JMR        Fix Issues found in OS Dispatcher and OSEK functions
******************************************************************************/

/******************************************************************************
*   Include Files
******************************************************************************/
#include "typedefs.h"
#include "Os_Task.h"
#include "Os_TaskCfg.h"
#include "Os_TaskM.h"
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
extern void SchM_OsTick(void);
extern void SchM_Init(const TaskConfigType *SchM_Config);
extern void SchM_DeInit(void);
extern void SchM_Start(void);
extern void SchM_Background(void);
extern void Dispatcher(void);


#endif /*__SCHM_H*/
