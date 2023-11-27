/*******************************************************************************
* File Name: weight_timer.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_weight_timer_H)
#define CY_TIMER_weight_timer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 weight_timer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define weight_timer_Resolution                 16u
#define weight_timer_UsingFixedFunction         1u
#define weight_timer_UsingHWCaptureCounter      0u
#define weight_timer_SoftwareCaptureMode        0u
#define weight_timer_SoftwareTriggerMode        0u
#define weight_timer_UsingHWEnable              0u
#define weight_timer_EnableTriggerMode          0u
#define weight_timer_InterruptOnCaptureCount    0u
#define weight_timer_RunModeUsed                0u
#define weight_timer_ControlRegRemoved          0u

#if defined(weight_timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define weight_timer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (weight_timer_UsingFixedFunction)
    #define weight_timer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define weight_timer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End weight_timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!weight_timer_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (weight_timer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!weight_timer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}weight_timer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    weight_timer_Start(void) ;
void    weight_timer_Stop(void) ;

void    weight_timer_SetInterruptMode(uint8 interruptMode) ;
uint8   weight_timer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define weight_timer_GetInterruptSource() weight_timer_ReadStatusRegister()

#if(!weight_timer_UDB_CONTROL_REG_REMOVED)
    uint8   weight_timer_ReadControlRegister(void) ;
    void    weight_timer_WriteControlRegister(uint8 control) ;
#endif /* (!weight_timer_UDB_CONTROL_REG_REMOVED) */

uint16  weight_timer_ReadPeriod(void) ;
void    weight_timer_WritePeriod(uint16 period) ;
uint16  weight_timer_ReadCounter(void) ;
void    weight_timer_WriteCounter(uint16 counter) ;
uint16  weight_timer_ReadCapture(void) ;
void    weight_timer_SoftwareCapture(void) ;

#if(!weight_timer_UsingFixedFunction) /* UDB Prototypes */
    #if (weight_timer_SoftwareCaptureMode)
        void    weight_timer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!weight_timer_UsingFixedFunction) */

    #if (weight_timer_SoftwareTriggerMode)
        void    weight_timer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (weight_timer_SoftwareTriggerMode) */

    #if (weight_timer_EnableTriggerMode)
        void    weight_timer_EnableTrigger(void) ;
        void    weight_timer_DisableTrigger(void) ;
    #endif /* (weight_timer_EnableTriggerMode) */


    #if(weight_timer_InterruptOnCaptureCount)
        void    weight_timer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (weight_timer_InterruptOnCaptureCount) */

    #if (weight_timer_UsingHWCaptureCounter)
        void    weight_timer_SetCaptureCount(uint8 captureCount) ;
        uint8   weight_timer_ReadCaptureCount(void) ;
    #endif /* (weight_timer_UsingHWCaptureCounter) */

    void weight_timer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void weight_timer_Init(void)          ;
void weight_timer_Enable(void)        ;
void weight_timer_SaveConfig(void)    ;
void weight_timer_RestoreConfig(void) ;
void weight_timer_Sleep(void)         ;
void weight_timer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define weight_timer__B_TIMER__CM_NONE 0
#define weight_timer__B_TIMER__CM_RISINGEDGE 1
#define weight_timer__B_TIMER__CM_FALLINGEDGE 2
#define weight_timer__B_TIMER__CM_EITHEREDGE 3
#define weight_timer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define weight_timer__B_TIMER__TM_NONE 0x00u
#define weight_timer__B_TIMER__TM_RISINGEDGE 0x04u
#define weight_timer__B_TIMER__TM_FALLINGEDGE 0x08u
#define weight_timer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define weight_timer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define weight_timer_INIT_PERIOD             999u
#define weight_timer_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << weight_timer_CTRL_CAP_MODE_SHIFT))
#define weight_timer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << weight_timer_CTRL_TRIG_MODE_SHIFT))
#if (weight_timer_UsingFixedFunction)
    #define weight_timer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << weight_timer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << weight_timer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define weight_timer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << weight_timer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << weight_timer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << weight_timer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (weight_timer_UsingFixedFunction) */
#define weight_timer_INIT_CAPTURE_COUNT      (2u)
#define weight_timer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << weight_timer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (weight_timer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define weight_timer_STATUS         (*(reg8 *) weight_timer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define weight_timer_STATUS_MASK    (*(reg8 *) weight_timer_TimerHW__SR0 )
    #define weight_timer_CONTROL        (*(reg8 *) weight_timer_TimerHW__CFG0)
    #define weight_timer_CONTROL2       (*(reg8 *) weight_timer_TimerHW__CFG1)
    #define weight_timer_CONTROL2_PTR   ( (reg8 *) weight_timer_TimerHW__CFG1)
    #define weight_timer_RT1            (*(reg8 *) weight_timer_TimerHW__RT1)
    #define weight_timer_RT1_PTR        ( (reg8 *) weight_timer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define weight_timer_CONTROL3       (*(reg8 *) weight_timer_TimerHW__CFG2)
        #define weight_timer_CONTROL3_PTR   ( (reg8 *) weight_timer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define weight_timer_GLOBAL_ENABLE  (*(reg8 *) weight_timer_TimerHW__PM_ACT_CFG)
    #define weight_timer_GLOBAL_STBY_ENABLE  (*(reg8 *) weight_timer_TimerHW__PM_STBY_CFG)

    #define weight_timer_CAPTURE_LSB         (* (reg16 *) weight_timer_TimerHW__CAP0 )
    #define weight_timer_CAPTURE_LSB_PTR       ((reg16 *) weight_timer_TimerHW__CAP0 )
    #define weight_timer_PERIOD_LSB          (* (reg16 *) weight_timer_TimerHW__PER0 )
    #define weight_timer_PERIOD_LSB_PTR        ((reg16 *) weight_timer_TimerHW__PER0 )
    #define weight_timer_COUNTER_LSB         (* (reg16 *) weight_timer_TimerHW__CNT_CMP0 )
    #define weight_timer_COUNTER_LSB_PTR       ((reg16 *) weight_timer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define weight_timer_BLOCK_EN_MASK                     weight_timer_TimerHW__PM_ACT_MSK
    #define weight_timer_BLOCK_STBY_EN_MASK                weight_timer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define weight_timer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define weight_timer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define weight_timer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define weight_timer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define weight_timer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define weight_timer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << weight_timer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define weight_timer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define weight_timer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << weight_timer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define weight_timer_CTRL_MODE_SHIFT                 0x01u
        #define weight_timer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << weight_timer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define weight_timer_CTRL_RCOD_SHIFT        0x02u
        #define weight_timer_CTRL_ENBL_SHIFT        0x00u
        #define weight_timer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define weight_timer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << weight_timer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define weight_timer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << weight_timer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define weight_timer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << weight_timer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define weight_timer_CTRL_RCOD       ((uint8)((uint8)0x03u << weight_timer_CTRL_RCOD_SHIFT))
        #define weight_timer_CTRL_ENBL       ((uint8)((uint8)0x80u << weight_timer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define weight_timer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define weight_timer_RT1_MASK                        ((uint8)((uint8)0x03u << weight_timer_RT1_SHIFT))
    #define weight_timer_SYNC                            ((uint8)((uint8)0x03u << weight_timer_RT1_SHIFT))
    #define weight_timer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define weight_timer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << weight_timer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define weight_timer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << weight_timer_SYNCDSI_SHIFT))

    #define weight_timer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << weight_timer_CTRL_MODE_SHIFT))
    #define weight_timer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << weight_timer_CTRL_MODE_SHIFT))
    #define weight_timer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << weight_timer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define weight_timer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define weight_timer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define weight_timer_STATUS_TC_INT_MASK_SHIFT        (weight_timer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define weight_timer_STATUS_CAPTURE_INT_MASK_SHIFT   (weight_timer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define weight_timer_STATUS_TC                       ((uint8)((uint8)0x01u << weight_timer_STATUS_TC_SHIFT))
    #define weight_timer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << weight_timer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define weight_timer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << weight_timer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define weight_timer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << weight_timer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define weight_timer_STATUS              (* (reg8 *) weight_timer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define weight_timer_STATUS_MASK         (* (reg8 *) weight_timer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define weight_timer_STATUS_AUX_CTRL     (* (reg8 *) weight_timer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define weight_timer_CONTROL             (* (reg8 *) weight_timer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(weight_timer_Resolution <= 8u) /* 8-bit Timer */
        #define weight_timer_CAPTURE_LSB         (* (reg8 *) weight_timer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define weight_timer_CAPTURE_LSB_PTR       ((reg8 *) weight_timer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define weight_timer_PERIOD_LSB          (* (reg8 *) weight_timer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define weight_timer_PERIOD_LSB_PTR        ((reg8 *) weight_timer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define weight_timer_COUNTER_LSB         (* (reg8 *) weight_timer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define weight_timer_COUNTER_LSB_PTR       ((reg8 *) weight_timer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(weight_timer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define weight_timer_CAPTURE_LSB         (* (reg16 *) weight_timer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define weight_timer_CAPTURE_LSB_PTR       ((reg16 *) weight_timer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define weight_timer_PERIOD_LSB          (* (reg16 *) weight_timer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define weight_timer_PERIOD_LSB_PTR        ((reg16 *) weight_timer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define weight_timer_COUNTER_LSB         (* (reg16 *) weight_timer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define weight_timer_COUNTER_LSB_PTR       ((reg16 *) weight_timer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define weight_timer_CAPTURE_LSB         (* (reg16 *) weight_timer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define weight_timer_CAPTURE_LSB_PTR       ((reg16 *) weight_timer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define weight_timer_PERIOD_LSB          (* (reg16 *) weight_timer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define weight_timer_PERIOD_LSB_PTR        ((reg16 *) weight_timer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define weight_timer_COUNTER_LSB         (* (reg16 *) weight_timer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define weight_timer_COUNTER_LSB_PTR       ((reg16 *) weight_timer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(weight_timer_Resolution <= 24u)/* 24-bit Timer */
        #define weight_timer_CAPTURE_LSB         (* (reg32 *) weight_timer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define weight_timer_CAPTURE_LSB_PTR       ((reg32 *) weight_timer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define weight_timer_PERIOD_LSB          (* (reg32 *) weight_timer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define weight_timer_PERIOD_LSB_PTR        ((reg32 *) weight_timer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define weight_timer_COUNTER_LSB         (* (reg32 *) weight_timer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define weight_timer_COUNTER_LSB_PTR       ((reg32 *) weight_timer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define weight_timer_CAPTURE_LSB         (* (reg32 *) weight_timer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define weight_timer_CAPTURE_LSB_PTR       ((reg32 *) weight_timer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define weight_timer_PERIOD_LSB          (* (reg32 *) weight_timer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define weight_timer_PERIOD_LSB_PTR        ((reg32 *) weight_timer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define weight_timer_COUNTER_LSB         (* (reg32 *) weight_timer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define weight_timer_COUNTER_LSB_PTR       ((reg32 *) weight_timer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define weight_timer_CAPTURE_LSB         (* (reg32 *) weight_timer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define weight_timer_CAPTURE_LSB_PTR       ((reg32 *) weight_timer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define weight_timer_PERIOD_LSB          (* (reg32 *) weight_timer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define weight_timer_PERIOD_LSB_PTR        ((reg32 *) weight_timer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define weight_timer_COUNTER_LSB         (* (reg32 *) weight_timer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define weight_timer_COUNTER_LSB_PTR       ((reg32 *) weight_timer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define weight_timer_COUNTER_LSB_PTR_8BIT       ((reg8 *) weight_timer_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (weight_timer_UsingHWCaptureCounter)
        #define weight_timer_CAP_COUNT              (*(reg8 *) weight_timer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define weight_timer_CAP_COUNT_PTR          ( (reg8 *) weight_timer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define weight_timer_CAPTURE_COUNT_CTRL     (*(reg8 *) weight_timer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define weight_timer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) weight_timer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (weight_timer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define weight_timer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define weight_timer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define weight_timer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define weight_timer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define weight_timer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define weight_timer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << weight_timer_CTRL_INTCNT_SHIFT))
    #define weight_timer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << weight_timer_CTRL_TRIG_MODE_SHIFT))
    #define weight_timer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << weight_timer_CTRL_TRIG_EN_SHIFT))
    #define weight_timer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << weight_timer_CTRL_CAP_MODE_SHIFT))
    #define weight_timer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << weight_timer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define weight_timer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define weight_timer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define weight_timer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define weight_timer_STATUS_TC_INT_MASK_SHIFT       weight_timer_STATUS_TC_SHIFT
    #define weight_timer_STATUS_CAPTURE_INT_MASK_SHIFT  weight_timer_STATUS_CAPTURE_SHIFT
    #define weight_timer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define weight_timer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define weight_timer_STATUS_FIFOFULL_INT_MASK_SHIFT weight_timer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define weight_timer_STATUS_TC                      ((uint8)((uint8)0x01u << weight_timer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define weight_timer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << weight_timer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define weight_timer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << weight_timer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define weight_timer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << weight_timer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define weight_timer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << weight_timer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define weight_timer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << weight_timer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define weight_timer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << weight_timer_STATUS_FIFOFULL_SHIFT))

    #define weight_timer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define weight_timer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define weight_timer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define weight_timer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define weight_timer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define weight_timer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_weight_timer_H */


/* [] END OF FILE */
