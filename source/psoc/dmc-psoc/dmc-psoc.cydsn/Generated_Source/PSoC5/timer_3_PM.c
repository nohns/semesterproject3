/*******************************************************************************
* File Name: timer_3_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "timer_3.h"

static timer_3_backupStruct timer_3_backup;


/*******************************************************************************
* Function Name: timer_3_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  timer_3_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void timer_3_SaveConfig(void) 
{
    #if (!timer_3_UsingFixedFunction)
        timer_3_backup.TimerUdb = timer_3_ReadCounter();
        timer_3_backup.InterruptMaskValue = timer_3_STATUS_MASK;
        #if (timer_3_UsingHWCaptureCounter)
            timer_3_backup.TimerCaptureCounter = timer_3_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!timer_3_UDB_CONTROL_REG_REMOVED)
            timer_3_backup.TimerControlRegister = timer_3_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: timer_3_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  timer_3_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void timer_3_RestoreConfig(void) 
{   
    #if (!timer_3_UsingFixedFunction)

        timer_3_WriteCounter(timer_3_backup.TimerUdb);
        timer_3_STATUS_MASK =timer_3_backup.InterruptMaskValue;
        #if (timer_3_UsingHWCaptureCounter)
            timer_3_SetCaptureCount(timer_3_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!timer_3_UDB_CONTROL_REG_REMOVED)
            timer_3_WriteControlRegister(timer_3_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: timer_3_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  timer_3_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void timer_3_Sleep(void) 
{
    #if(!timer_3_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(timer_3_CTRL_ENABLE == (timer_3_CONTROL & timer_3_CTRL_ENABLE))
        {
            /* Timer is enabled */
            timer_3_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            timer_3_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    timer_3_Stop();
    timer_3_SaveConfig();
}


/*******************************************************************************
* Function Name: timer_3_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  timer_3_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void timer_3_Wakeup(void) 
{
    timer_3_RestoreConfig();
    #if(!timer_3_UDB_CONTROL_REG_REMOVED)
        if(timer_3_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                timer_3_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
