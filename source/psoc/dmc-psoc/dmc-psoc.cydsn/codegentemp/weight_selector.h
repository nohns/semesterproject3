/*******************************************************************************
* File Name: weight_selector.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_weight_selector_H)
#define CY_AMUX_weight_selector_H

#include "cyfitter.h"
#include "cyfitter_cfg.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))    
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif /* ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */


/***************************************
*        Function Prototypes
***************************************/

void weight_selector_Start(void) ;
#define weight_selector_Init() weight_selector_Start()
void weight_selector_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void weight_selector_Stop(void); */
/* void weight_selector_Select(uint8 channel); */
/* void weight_selector_Connect(uint8 channel); */
/* void weight_selector_Disconnect(uint8 channel); */
/* void weight_selector_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define weight_selector_CHANNELS  3u
#define weight_selector_MUXTYPE   1
#define weight_selector_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define weight_selector_NULL_CHANNEL 0xFFu
#define weight_selector_MUX_SINGLE   1
#define weight_selector_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if weight_selector_MUXTYPE == weight_selector_MUX_SINGLE
# if !weight_selector_ATMOSTONE
#  define weight_selector_Connect(channel) weight_selector_Set(channel)
# endif
# define weight_selector_Disconnect(channel) weight_selector_Unset(channel)
#else
# if !weight_selector_ATMOSTONE
void weight_selector_Connect(uint8 channel) ;
# endif
void weight_selector_Disconnect(uint8 channel) ;
#endif

#if weight_selector_ATMOSTONE
# define weight_selector_Stop() weight_selector_DisconnectAll()
# define weight_selector_Select(channel) weight_selector_FastSelect(channel)
void weight_selector_DisconnectAll(void) ;
#else
# define weight_selector_Stop() weight_selector_Start()
void weight_selector_Select(uint8 channel) ;
# define weight_selector_DisconnectAll() weight_selector_Start()
#endif

#endif /* CY_AMUX_weight_selector_H */


/* [] END OF FILE */
