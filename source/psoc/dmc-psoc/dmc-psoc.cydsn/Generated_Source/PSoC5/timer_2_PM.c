/*******************************************************************************
* File Name: timer_2_PM.c
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

#include "timer_2.h"

static timer_2_backupStruct timer_2_backup;


/*******************************************************************************
* Function Name: timer_2_SaveConfig
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
*  timer_2_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void timer_2_SaveConfig(void) 
{
    #if (!timer_2_UsingFixedFunction)
        timer_2_backup.TimerUdb = timer_2_ReadCounter();
        timer_2_backup.InterruptMaskValue = timer_2_STATUS_MASK;
        #if (timer_2_UsingHWCaptureCounter)
            timer_2_backup.TimerCaptureCounter = timer_2_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!timer_2_UDB_CONTROL_REG_REMOVED)
            timer_2_backup.TimerControlRegister = timer_2_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: timer_2_RestoreConfig
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
*  timer_2_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void timer_2_RestoreConfig(void) 
{   
    #if (!timer_2_UsingFixedFunction)

        timer_2_WriteCounter(timer_2_backup.TimerUdb);
        timer_2_STATUS_MASK =timer_2_backup.InterruptMaskValue;
        #if (timer_2_UsingHWCaptureCounter)
            timer_2_SetCaptureCount(timer_2_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!timer_2_UDB_CONTROL_REG_REMOVED)
            timer_2_WriteControlRegister(timer_2_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: timer_2_Sleep
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
*  timer_2_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void timer_2_Sleep(void) 
{
    #if(!timer_2_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(timer_2_CTRL_ENABLE == (timer_2_CONTROL & timer_2_CTRL_ENABLE))
        {
            /* Timer is enabled */
            timer_2_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            timer_2_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    timer_2_Stop();
    timer_2_SaveConfig();
}


/*******************************************************************************
* Function Name: timer_2_Wakeup
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
*  timer_2_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void timer_2_Wakeup(void) 
{
    timer_2_RestoreConfig();
    #if(!timer_2_UDB_CONTROL_REG_REMOVED)
        if(timer_2_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                timer_2_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
