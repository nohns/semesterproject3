/*******************************************************************************
* File Name: check_weight_timer_PM.c
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

#include "check_weight_timer.h"

static check_weight_timer_backupStruct check_weight_timer_backup;


/*******************************************************************************
* Function Name: check_weight_timer_SaveConfig
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
*  check_weight_timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void check_weight_timer_SaveConfig(void) 
{
    #if (!check_weight_timer_UsingFixedFunction)
        check_weight_timer_backup.TimerUdb = check_weight_timer_ReadCounter();
        check_weight_timer_backup.InterruptMaskValue = check_weight_timer_STATUS_MASK;
        #if (check_weight_timer_UsingHWCaptureCounter)
            check_weight_timer_backup.TimerCaptureCounter = check_weight_timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!check_weight_timer_UDB_CONTROL_REG_REMOVED)
            check_weight_timer_backup.TimerControlRegister = check_weight_timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: check_weight_timer_RestoreConfig
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
*  check_weight_timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void check_weight_timer_RestoreConfig(void) 
{   
    #if (!check_weight_timer_UsingFixedFunction)

        check_weight_timer_WriteCounter(check_weight_timer_backup.TimerUdb);
        check_weight_timer_STATUS_MASK =check_weight_timer_backup.InterruptMaskValue;
        #if (check_weight_timer_UsingHWCaptureCounter)
            check_weight_timer_SetCaptureCount(check_weight_timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!check_weight_timer_UDB_CONTROL_REG_REMOVED)
            check_weight_timer_WriteControlRegister(check_weight_timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: check_weight_timer_Sleep
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
*  check_weight_timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void check_weight_timer_Sleep(void) 
{
    #if(!check_weight_timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(check_weight_timer_CTRL_ENABLE == (check_weight_timer_CONTROL & check_weight_timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            check_weight_timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            check_weight_timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    check_weight_timer_Stop();
    check_weight_timer_SaveConfig();
}


/*******************************************************************************
* Function Name: check_weight_timer_Wakeup
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
*  check_weight_timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void check_weight_timer_Wakeup(void) 
{
    check_weight_timer_RestoreConfig();
    #if(!check_weight_timer_UDB_CONTROL_REG_REMOVED)
        if(check_weight_timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                check_weight_timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
