/*******************************************************************************
* File Name: uart_rpi_PM.c
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

#include "uart_rpi.h"


/***************************************
* Local data allocation
***************************************/

static uart_rpi_BACKUP_STRUCT  uart_rpi_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: uart_rpi_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the uart_rpi_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  uart_rpi_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_rpi_SaveConfig(void)
{
    #if(uart_rpi_CONTROL_REG_REMOVED == 0u)
        uart_rpi_backup.cr = uart_rpi_CONTROL_REG;
    #endif /* End uart_rpi_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: uart_rpi_RestoreConfig
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
*  uart_rpi_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling uart_rpi_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void uart_rpi_RestoreConfig(void)
{
    #if(uart_rpi_CONTROL_REG_REMOVED == 0u)
        uart_rpi_CONTROL_REG = uart_rpi_backup.cr;
    #endif /* End uart_rpi_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: uart_rpi_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The uart_rpi_Sleep() API saves the current component state. Then it
*  calls the uart_rpi_Stop() function and calls 
*  uart_rpi_SaveConfig() to save the hardware configuration.
*  Call the uart_rpi_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  uart_rpi_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_rpi_Sleep(void)
{
    #if(uart_rpi_RX_ENABLED || uart_rpi_HD_ENABLED)
        if((uart_rpi_RXSTATUS_ACTL_REG  & uart_rpi_INT_ENABLE) != 0u)
        {
            uart_rpi_backup.enableState = 1u;
        }
        else
        {
            uart_rpi_backup.enableState = 0u;
        }
    #else
        if((uart_rpi_TXSTATUS_ACTL_REG  & uart_rpi_INT_ENABLE) !=0u)
        {
            uart_rpi_backup.enableState = 1u;
        }
        else
        {
            uart_rpi_backup.enableState = 0u;
        }
    #endif /* End uart_rpi_RX_ENABLED || uart_rpi_HD_ENABLED*/

    uart_rpi_Stop();
    uart_rpi_SaveConfig();
}


/*******************************************************************************
* Function Name: uart_rpi_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  uart_rpi_Sleep() was called. The uart_rpi_Wakeup() function
*  calls the uart_rpi_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  uart_rpi_Sleep() function was called, the uart_rpi_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  uart_rpi_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_rpi_Wakeup(void)
{
    uart_rpi_RestoreConfig();
    #if( (uart_rpi_RX_ENABLED) || (uart_rpi_HD_ENABLED) )
        uart_rpi_ClearRxBuffer();
    #endif /* End (uart_rpi_RX_ENABLED) || (uart_rpi_HD_ENABLED) */
    #if(uart_rpi_TX_ENABLED || uart_rpi_HD_ENABLED)
        uart_rpi_ClearTxBuffer();
    #endif /* End uart_rpi_TX_ENABLED || uart_rpi_HD_ENABLED */

    if(uart_rpi_backup.enableState != 0u)
    {
        uart_rpi_Enable();
    }
}


/* [] END OF FILE */
