/*******************************************************************************
* File Name: weight_adc_ExtVref.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_weight_adc_ExtVref_H) /* Pins weight_adc_ExtVref_H */
#define CY_PINS_weight_adc_ExtVref_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "weight_adc_ExtVref_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 weight_adc_ExtVref__PORT == 15 && ((weight_adc_ExtVref__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    weight_adc_ExtVref_Write(uint8 value);
void    weight_adc_ExtVref_SetDriveMode(uint8 mode);
uint8   weight_adc_ExtVref_ReadDataReg(void);
uint8   weight_adc_ExtVref_Read(void);
void    weight_adc_ExtVref_SetInterruptMode(uint16 position, uint16 mode);
uint8   weight_adc_ExtVref_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the weight_adc_ExtVref_SetDriveMode() function.
     *  @{
     */
        #define weight_adc_ExtVref_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define weight_adc_ExtVref_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define weight_adc_ExtVref_DM_RES_UP          PIN_DM_RES_UP
        #define weight_adc_ExtVref_DM_RES_DWN         PIN_DM_RES_DWN
        #define weight_adc_ExtVref_DM_OD_LO           PIN_DM_OD_LO
        #define weight_adc_ExtVref_DM_OD_HI           PIN_DM_OD_HI
        #define weight_adc_ExtVref_DM_STRONG          PIN_DM_STRONG
        #define weight_adc_ExtVref_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define weight_adc_ExtVref_MASK               weight_adc_ExtVref__MASK
#define weight_adc_ExtVref_SHIFT              weight_adc_ExtVref__SHIFT
#define weight_adc_ExtVref_WIDTH              1u

/* Interrupt constants */
#if defined(weight_adc_ExtVref__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in weight_adc_ExtVref_SetInterruptMode() function.
     *  @{
     */
        #define weight_adc_ExtVref_INTR_NONE      (uint16)(0x0000u)
        #define weight_adc_ExtVref_INTR_RISING    (uint16)(0x0001u)
        #define weight_adc_ExtVref_INTR_FALLING   (uint16)(0x0002u)
        #define weight_adc_ExtVref_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define weight_adc_ExtVref_INTR_MASK      (0x01u) 
#endif /* (weight_adc_ExtVref__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define weight_adc_ExtVref_PS                     (* (reg8 *) weight_adc_ExtVref__PS)
/* Data Register */
#define weight_adc_ExtVref_DR                     (* (reg8 *) weight_adc_ExtVref__DR)
/* Port Number */
#define weight_adc_ExtVref_PRT_NUM                (* (reg8 *) weight_adc_ExtVref__PRT) 
/* Connect to Analog Globals */                                                  
#define weight_adc_ExtVref_AG                     (* (reg8 *) weight_adc_ExtVref__AG)                       
/* Analog MUX bux enable */
#define weight_adc_ExtVref_AMUX                   (* (reg8 *) weight_adc_ExtVref__AMUX) 
/* Bidirectional Enable */                                                        
#define weight_adc_ExtVref_BIE                    (* (reg8 *) weight_adc_ExtVref__BIE)
/* Bit-mask for Aliased Register Access */
#define weight_adc_ExtVref_BIT_MASK               (* (reg8 *) weight_adc_ExtVref__BIT_MASK)
/* Bypass Enable */
#define weight_adc_ExtVref_BYP                    (* (reg8 *) weight_adc_ExtVref__BYP)
/* Port wide control signals */                                                   
#define weight_adc_ExtVref_CTL                    (* (reg8 *) weight_adc_ExtVref__CTL)
/* Drive Modes */
#define weight_adc_ExtVref_DM0                    (* (reg8 *) weight_adc_ExtVref__DM0) 
#define weight_adc_ExtVref_DM1                    (* (reg8 *) weight_adc_ExtVref__DM1)
#define weight_adc_ExtVref_DM2                    (* (reg8 *) weight_adc_ExtVref__DM2) 
/* Input Buffer Disable Override */
#define weight_adc_ExtVref_INP_DIS                (* (reg8 *) weight_adc_ExtVref__INP_DIS)
/* LCD Common or Segment Drive */
#define weight_adc_ExtVref_LCD_COM_SEG            (* (reg8 *) weight_adc_ExtVref__LCD_COM_SEG)
/* Enable Segment LCD */
#define weight_adc_ExtVref_LCD_EN                 (* (reg8 *) weight_adc_ExtVref__LCD_EN)
/* Slew Rate Control */
#define weight_adc_ExtVref_SLW                    (* (reg8 *) weight_adc_ExtVref__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define weight_adc_ExtVref_PRTDSI__CAPS_SEL       (* (reg8 *) weight_adc_ExtVref__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define weight_adc_ExtVref_PRTDSI__DBL_SYNC_IN    (* (reg8 *) weight_adc_ExtVref__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define weight_adc_ExtVref_PRTDSI__OE_SEL0        (* (reg8 *) weight_adc_ExtVref__PRTDSI__OE_SEL0) 
#define weight_adc_ExtVref_PRTDSI__OE_SEL1        (* (reg8 *) weight_adc_ExtVref__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define weight_adc_ExtVref_PRTDSI__OUT_SEL0       (* (reg8 *) weight_adc_ExtVref__PRTDSI__OUT_SEL0) 
#define weight_adc_ExtVref_PRTDSI__OUT_SEL1       (* (reg8 *) weight_adc_ExtVref__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define weight_adc_ExtVref_PRTDSI__SYNC_OUT       (* (reg8 *) weight_adc_ExtVref__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(weight_adc_ExtVref__SIO_CFG)
    #define weight_adc_ExtVref_SIO_HYST_EN        (* (reg8 *) weight_adc_ExtVref__SIO_HYST_EN)
    #define weight_adc_ExtVref_SIO_REG_HIFREQ     (* (reg8 *) weight_adc_ExtVref__SIO_REG_HIFREQ)
    #define weight_adc_ExtVref_SIO_CFG            (* (reg8 *) weight_adc_ExtVref__SIO_CFG)
    #define weight_adc_ExtVref_SIO_DIFF           (* (reg8 *) weight_adc_ExtVref__SIO_DIFF)
#endif /* (weight_adc_ExtVref__SIO_CFG) */

/* Interrupt Registers */
#if defined(weight_adc_ExtVref__INTSTAT)
    #define weight_adc_ExtVref_INTSTAT            (* (reg8 *) weight_adc_ExtVref__INTSTAT)
    #define weight_adc_ExtVref_SNAP               (* (reg8 *) weight_adc_ExtVref__SNAP)
    
	#define weight_adc_ExtVref_0_INTTYPE_REG 		(* (reg8 *) weight_adc_ExtVref__0__INTTYPE)
#endif /* (weight_adc_ExtVref__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_weight_adc_ExtVref_H */


/* [] END OF FILE */
