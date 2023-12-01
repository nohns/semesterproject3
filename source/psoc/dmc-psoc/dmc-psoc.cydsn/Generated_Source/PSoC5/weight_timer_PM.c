/*******************************************************************************
* File Name: weight_timer_PM.c
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

#include "weight_timer.h"

static weight_timer_backupStruct weight_timer_backup;


/*******************************************************************************
* Function Name: weight_timer_SaveConfig
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
*  weight_timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void weight_timer_SaveConfig(void) 
{
    #if (!weight_timer_UsingFixedFunction)
        weight_timer_backup.TimerUdb = weight_timer_ReadCounter();
        weight_timer_backup.InterruptMaskValue = weight_timer_STATUS_MASK;
        #if (weight_timer_UsingHWCaptureCounter)
            weight_timer_backup.TimerCaptureCounter = weight_timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!weight_timer_UDB_CONTROL_REG_REMOVED)
            weight_timer_backup.TimerControlRegister = weight_timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: weight_timer_RestoreConfig
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
*  weight_timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void weight_timer_RestoreConfig(void) 
{   
    #if (!weight_timer_UsingFixedFunction)

        weight_timer_WriteCounter(weight_timer_backup.TimerUdb);
        weight_timer_STATUS_MASK =weight_timer_backup.InterruptMaskValue;
        #if (weight_timer_UsingHWCaptureCounter)
            weight_timer_SetCaptureCount(weight_timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!weight_timer_UDB_CONTROL_REG_REMOVED)
            weight_timer_WriteControlRegister(weight_timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: weight_timer_Sleep
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
*  weight_timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void weight_timer_Sleep(void) 
{
    #if(!weight_timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(weight_timer_CTRL_ENABLE == (weight_timer_CONTROL & weight_timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            weight_timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            weight_timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    weight_timer_Stop();
    weight_timer_SaveConfig();
}


/*******************************************************************************
* Function Name: weight_timer_Wakeup
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
*  weight_timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void weight_timer_Wakeup(void) 
{
    weight_timer_RestoreConfig();
    #if(!weight_timer_UDB_CONTROL_REG_REMOVED)
        if(weight_timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                weight_timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
