/*******************************************************************************
* File Name: weight_adc_PM.c
* Version 3.10
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

#include "weight_adc.h"


/***************************************
* Local data allocation
***************************************/

static weight_adc_BACKUP_STRUCT  weight_adc_backup =
{
    weight_adc_DISABLED
};


/*******************************************************************************
* Function Name: weight_adc_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void weight_adc_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: weight_adc_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void weight_adc_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: weight_adc_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The weight_adc_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  weight_adc_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void weight_adc_Sleep(void)
{
    if((weight_adc_PWRMGR_SAR_REG  & weight_adc_ACT_PWR_SAR_EN) != 0u)
    {
        if((weight_adc_SAR_CSR0_REG & weight_adc_SAR_SOF_START_CONV) != 0u)
        {
            weight_adc_backup.enableState = weight_adc_ENABLED | weight_adc_STARTED;
        }
        else
        {
            weight_adc_backup.enableState = weight_adc_ENABLED;
        }
        weight_adc_Stop();
    }
    else
    {
        weight_adc_backup.enableState = weight_adc_DISABLED;
    }
}


/*******************************************************************************
* Function Name: weight_adc_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  weight_adc_Sleep() was called. If the component was enabled before the
*  weight_adc_Sleep() function was called, the
*  weight_adc_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  weight_adc_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void weight_adc_Wakeup(void)
{
    if(weight_adc_backup.enableState != weight_adc_DISABLED)
    {
        weight_adc_Enable();
        #if(weight_adc_DEFAULT_CONV_MODE != weight_adc__HARDWARE_TRIGGER)
            if((weight_adc_backup.enableState & weight_adc_STARTED) != 0u)
            {
                weight_adc_StartConvert();
            }
        #endif /* End weight_adc_DEFAULT_CONV_MODE != weight_adc__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */
