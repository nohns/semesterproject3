/*******************************************************************************
* File Name: uart_pc_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "uart_pc.h"


/***************************************
* Local data allocation
***************************************/

static uart_pc_BACKUP_STRUCT  uart_pc_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: uart_pc_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the uart_pc_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  uart_pc_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_pc_SaveConfig(void)
{
    #if(uart_pc_CONTROL_REG_REMOVED == 0u)
        uart_pc_backup.cr = uart_pc_CONTROL_REG;
    #endif /* End uart_pc_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: uart_pc_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the nonretention control register except FIFO.
*  Does not restore the FIFO which is a set of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  uart_pc_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling uart_pc_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void uart_pc_RestoreConfig(void)
{
    #if(uart_pc_CONTROL_REG_REMOVED == 0u)
        uart_pc_CONTROL_REG = uart_pc_backup.cr;
    #endif /* End uart_pc_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: uart_pc_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The uart_pc_Sleep() API saves the current component state. Then it
*  calls the uart_pc_Stop() function and calls 
*  uart_pc_SaveConfig() to save the hardware configuration.
*  Call the uart_pc_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  uart_pc_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_pc_Sleep(void)
{
    #if(uart_pc_RX_ENABLED || uart_pc_HD_ENABLED)
        if((uart_pc_RXSTATUS_ACTL_REG  & uart_pc_INT_ENABLE) != 0u)
        {
            uart_pc_backup.enableState = 1u;
        }
        else
        {
            uart_pc_backup.enableState = 0u;
        }
    #else
        if((uart_pc_TXSTATUS_ACTL_REG  & uart_pc_INT_ENABLE) !=0u)
        {
            uart_pc_backup.enableState = 1u;
        }
        else
        {
            uart_pc_backup.enableState = 0u;
        }
    #endif /* End uart_pc_RX_ENABLED || uart_pc_HD_ENABLED*/

    uart_pc_Stop();
    uart_pc_SaveConfig();
}


/*******************************************************************************
* Function Name: uart_pc_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  uart_pc_Sleep() was called. The uart_pc_Wakeup() function
*  calls the uart_pc_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  uart_pc_Sleep() function was called, the uart_pc_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  uart_pc_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_pc_Wakeup(void)
{
    uart_pc_RestoreConfig();
    #if( (uart_pc_RX_ENABLED) || (uart_pc_HD_ENABLED) )
        uart_pc_ClearRxBuffer();
    #endif /* End (uart_pc_RX_ENABLED) || (uart_pc_HD_ENABLED) */
    #if(uart_pc_TX_ENABLED || uart_pc_HD_ENABLED)
        uart_pc_ClearTxBuffer();
    #endif /* End uart_pc_TX_ENABLED || uart_pc_HD_ENABLED */

    if(uart_pc_backup.enableState != 0u)
    {
        uart_pc_Enable();
    }
}


/* [] END OF FILE */
