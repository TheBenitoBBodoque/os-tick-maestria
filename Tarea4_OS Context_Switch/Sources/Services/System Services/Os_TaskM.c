/******************************************************************************
*   Filename:   Os_TaskM.c 
*
*   Description:
*
*
*   Revision History:
*
*   Date          #Change       Author     
*   MM-DD-YY      Number:       Initials   Description of change
*   -----------   -----------   --------   ------------------------------------
*   03-29-14       10            SPA        OS Dispatcher and OSEK functions
*   03-29-14       11            JMR        Fix Issues found in OS Dispatcher and OSEK functions
*   03-29-14       12            EBA        Fix more issues
******************************************************************************/

/******************************************************************************
*   Include Files
******************************************************************************/ 
#include "typedefs.h"
#include "Os_TaskM.h"
#include "SchM.h"
/******************************************************************************
*   Local Macro Definitions
******************************************************************************/ 

/******************************************************************************
*   Local Type Definitions
******************************************************************************/

/******************************************************************************
*   Local Function Declarations
******************************************************************************/ 

/******************************************************************************
*   Global Variable Definitions
******************************************************************************/
u16 TaskExecuted_ID = 0xFFFF;
extern u8 gInterruptFlag;
/******************************************************************************
*   Static Variable Definitions
******************************************************************************/

/******************************************************************************
*   Global and Static Function Definitions
******************************************************************************/ 

/*****************************************************************************************************                                                                        
*   Function: ActivateTask(TaskType taskID)
*
*   Description: This API service moves the task identified by the input
*   taskID from the SUSPENDED state to the READY state if
*   no error occurred, and put the task into the priority buffer
*   queue tail
*
*   Caveats:
*****************************************************************************************************/
Status_Type ActivateTask(TaskType taskID)
{ 
  u16 index = 0;
  Status_Type Status = E_OK;
  u8 Processing_Done = FALSE;
  if(MAX_NUM_TASK > taskID)
  {
    for(index = 0; index < CNF_MAXTASKQUEUE; index++)
    {
      if(Processing_Done == FALSE)
      {
        if(DispacherArray[TaskConfigInitial->ptr_Task[taskID].Task_Priority][index] == 0xFFFF)
        {
           DispacherArray[TaskConfigInitial->ptr_Task[taskID].Task_Priority][index] = taskID;

           Processing_Done = TRUE;
        }
      }
    }
    TaskControlBlock[taskID].Task_State = READY;
    if(Processing_Done == FALSE)
    {
       Status = E_OS_LIMIT;
    }
    if(gInterruptFlag==0){
      __asm SWI;
    }
  }
  else
  {
     Status = E_OS_ID;
  }
  return Status;
}

/*****************************************************************************************************                                                                        
*   Function: TerminateTask(void)
*
*   Description: This function terminates the task that invoked the service,
*   transferring it from the RUNNING to the SUSPENDED state, and move the task out
*   of the priority buffer queue
*
*   Caveats:
*****************************************************************************************************/
Status_Type TerminateTask (void)
{
  Status_Type Status = E_OK;
  u16 IndexQueue=0;
  
  TaskControlBlock[TaskExecuted_ID].Task_State = SUSPENDED;
  for(IndexQueue;IndexQueue < CNF_MAXTASKQUEUE;IndexQueue++)
  {
     DispacherArray[TaskConfigInitial->ptr_Task[TaskExecuted_ID].Task_Priority][IndexQueue] =
     DispacherArray[TaskConfigInitial->ptr_Task[TaskExecuted_ID].Task_Priority][IndexQueue+1];
  }
  DispacherArray[TaskConfigInitial->ptr_Task[TaskExecuted_ID].Task_Priority][IndexQueue-1] = 0xFFFF;
  TaskExecuted_ID = 0xFFFF;
  Dispatcher();
  return Status;
}

/*****************************************************************************************************                                                                        
*   Function: TaskStateType GetTaskID(TaskRefType taskIDRef)
*
*   Description: This service provides the application with the identifier of the
*   task that is presently running. It is intended to be used in hook
*   routines and library functions to check the task from which it
*   was invoked
*   Caveats:
*****************************************************************************************************/

Status_Type GetTaskID(TaskRefType taskIDRef)
{
  u16 index_ControlBlock;
  u8  TaskIsRunning;
  Status_Type Status = E_OK;
  
  for(index_ControlBlock=0U;index_ControlBlock < MAX_NUM_TASK;index_ControlBlock++)
  {
    if(TaskControlBlock[index_ControlBlock].Task_State == RUNNING){
          *taskIDRef = index_ControlBlock;
          TaskIsRunning=1;
          break;
    }else{
          TaskIsRunning=0;
    }
  }
  if(!TaskIsRunning){ 
    *taskIDRef = 0xFFFF;
  }
  return Status;
}

/*****************************************************************************************************                                                                        
*   Function: TaskStateType GetTaskState(TaskType taskID, TaskStateRefType stateRef)
*
*   Description: This service identifies the current state of the task identified
*   by the taskID parameter and places this value into the
*   variable referenced by stateRef
*   Caveats:
*****************************************************************************************************/

Status_Type GetTaskState(TaskType taskID, TaskStateRefType stateRef)
{
     Status_Type Status = E_OK;
     if(MAX_NUM_TASK > taskID)
     {
        *stateRef = TaskControlBlock[taskID].Task_State;
     }
     else
     {
        Status = E_OS_ID;
     }
     return Status;
}
