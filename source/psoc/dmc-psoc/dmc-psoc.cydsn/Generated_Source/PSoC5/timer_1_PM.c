/*******************************************************************************
* File Name: timer_1_PM.c
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

#include "timer_1.h"

static timer_1_backupStruct timer_1_backup;


/*******************************************************************************
* Function Name: timer_1_SaveConfig
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
*  timer_1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void timer_1_SaveConfig(void) 
{
    #if (!timer_1_UsingFixedFunction)
        timer_1_backup.TimerUdb = timer_1_ReadCounter();
        timer_1_backup.InterruptMaskValue = timer_1_STATUS_MASK;
        #if (timer_1_UsingHWCaptureCounter)
            timer_1_backup.TimerCaptureCounter = timer_1_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!timer_1_UDB_CONTROL_REG_REMOVED)
            timer_1_backup.TimerControlRegister = timer_1_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: timer_1_RestoreConfig
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
*  timer_1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void timer_1_RestoreConfig(void) 
{   
    #if (!timer_1_UsingFixedFunction)

        timer_1_WriteCounter(timer_1_backup.TimerUdb);
        timer_1_STATUS_MASK =timer_1_backup.InterruptMaskValue;
        #if (timer_1_UsingHWCaptureCounter)
            timer_1_SetCaptureCount(timer_1_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!timer_1_UDB_CONTROL_REG_REMOVED)
            timer_1_WriteControlRegister(timer_1_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: timer_1_Sleep
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
*  timer_1_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void timer_1_Sleep(void) 
{
    #if(!timer_1_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(timer_1_CTRL_ENABLE == (timer_1_CONTROL & timer_1_CTRL_ENABLE))
        {
            /* Timer is enabled */
            timer_1_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            timer_1_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    timer_1_Stop();
    timer_1_SaveConfig();
}


/*******************************************************************************
* Function Name: timer_1_Wakeup
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
*  timer_1_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void timer_1_Wakeup(void) 
{
    timer_1_RestoreConfig();
    #if(!timer_1_UDB_CONTROL_REG_REMOVED)
        if(timer_1_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                timer_1_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
