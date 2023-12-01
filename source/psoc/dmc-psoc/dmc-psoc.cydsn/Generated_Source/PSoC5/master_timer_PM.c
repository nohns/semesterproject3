/*******************************************************************************
* File Name: master_timer_PM.c
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

#include "master_timer.h"

static master_timer_backupStruct master_timer_backup;


/*******************************************************************************
* Function Name: master_timer_SaveConfig
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
*  master_timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void master_timer_SaveConfig(void) 
{
    #if (!master_timer_UsingFixedFunction)
        master_timer_backup.TimerUdb = master_timer_ReadCounter();
        master_timer_backup.InterruptMaskValue = master_timer_STATUS_MASK;
        #if (master_timer_UsingHWCaptureCounter)
            master_timer_backup.TimerCaptureCounter = master_timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!master_timer_UDB_CONTROL_REG_REMOVED)
            master_timer_backup.TimerControlRegister = master_timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: master_timer_RestoreConfig
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
*  master_timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void master_timer_RestoreConfig(void) 
{   
    #if (!master_timer_UsingFixedFunction)

        master_timer_WriteCounter(master_timer_backup.TimerUdb);
        master_timer_STATUS_MASK =master_timer_backup.InterruptMaskValue;
        #if (master_timer_UsingHWCaptureCounter)
            master_timer_SetCaptureCount(master_timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!master_timer_UDB_CONTROL_REG_REMOVED)
            master_timer_WriteControlRegister(master_timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: master_timer_Sleep
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
*  master_timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void master_timer_Sleep(void) 
{
    #if(!master_timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(master_timer_CTRL_ENABLE == (master_timer_CONTROL & master_timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            master_timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            master_timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    master_timer_Stop();
    master_timer_SaveConfig();
}


/*******************************************************************************
* Function Name: master_timer_Wakeup
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
*  master_timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void master_timer_Wakeup(void) 
{
    master_timer_RestoreConfig();
    #if(!master_timer_UDB_CONTROL_REG_REMOVED)
        if(master_timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                master_timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
