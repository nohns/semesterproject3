/*******************************************************************************
* File Name: weight_selector.c
* Version 1.80
*
*  Description:
*    This file contains all functions required for the analog multiplexer
*    AMux User Module.
*
*   Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "weight_selector.h"

static uint8 weight_selector_lastChannel = weight_selector_NULL_CHANNEL;


/*******************************************************************************
* Function Name: weight_selector_Start
********************************************************************************
* Summary:
*  Disconnect all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void weight_selector_Start(void) 
{
    uint8 chan;

    for(chan = 0u; chan < weight_selector_CHANNELS ; chan++)
    {
#if (weight_selector_MUXTYPE == weight_selector_MUX_SINGLE)
        weight_selector_Unset(chan);
#else
        weight_selector_CYAMUXSIDE_A_Unset(chan);
        weight_selector_CYAMUXSIDE_B_Unset(chan);
#endif
    }

    weight_selector_lastChannel = weight_selector_NULL_CHANNEL;
}


#if (!weight_selector_ATMOSTONE)
/*******************************************************************************
* Function Name: weight_selector_Select
********************************************************************************
* Summary:
*  This functions first disconnects all channels then connects the given
*  channel.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void weight_selector_Select(uint8 channel) 
{
    weight_selector_DisconnectAll();        /* Disconnect all previous connections */
    weight_selector_Connect(channel);       /* Make the given selection */
    weight_selector_lastChannel = channel;  /* Update last channel */
}
#endif


/*******************************************************************************
* Function Name: weight_selector_FastSelect
********************************************************************************
* Summary:
*  This function first disconnects the last connection made with FastSelect or
*  Select, then connects the given channel. The FastSelect function is similar
*  to the Select function, except it is faster since it only disconnects the
*  last channel selected rather than all channels.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void weight_selector_FastSelect(uint8 channel) 
{
    /* Disconnect the last valid channel */
    if( weight_selector_lastChannel != weight_selector_NULL_CHANNEL)
    {
        weight_selector_Disconnect(weight_selector_lastChannel);
    }

    /* Make the new channel connection */
#if (weight_selector_MUXTYPE == weight_selector_MUX_SINGLE)
    weight_selector_Set(channel);
#else
    weight_selector_CYAMUXSIDE_A_Set(channel);
    weight_selector_CYAMUXSIDE_B_Set(channel);
#endif


    weight_selector_lastChannel = channel;   /* Update last channel */
}


#if (weight_selector_MUXTYPE == weight_selector_MUX_DIFF)
#if (!weight_selector_ATMOSTONE)
/*******************************************************************************
* Function Name: weight_selector_Connect
********************************************************************************
* Summary:
*  This function connects the given channel without affecting other connections.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void weight_selector_Connect(uint8 channel) 
{
    weight_selector_CYAMUXSIDE_A_Set(channel);
    weight_selector_CYAMUXSIDE_B_Set(channel);
}
#endif

/*******************************************************************************
* Function Name: weight_selector_Disconnect
********************************************************************************
* Summary:
*  This function disconnects the given channel from the common or output
*  terminal without affecting other connections.
*
* Parameters:
*  channel:  The channel to disconnect from the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void weight_selector_Disconnect(uint8 channel) 
{
    weight_selector_CYAMUXSIDE_A_Unset(channel);
    weight_selector_CYAMUXSIDE_B_Unset(channel);
}
#endif

#if (weight_selector_ATMOSTONE)
/*******************************************************************************
* Function Name: weight_selector_DisconnectAll
********************************************************************************
* Summary:
*  This function disconnects all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void weight_selector_DisconnectAll(void) 
{
    if(weight_selector_lastChannel != weight_selector_NULL_CHANNEL) 
    {
        weight_selector_Disconnect(weight_selector_lastChannel);
        weight_selector_lastChannel = weight_selector_NULL_CHANNEL;
    }
}
#endif

/* [] END OF FILE */
