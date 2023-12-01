/*******************************************************************************
* File Name: uart_rpi.h
* Version 2.50
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_uart_rpi_H)
#define CY_UART_uart_rpi_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define uart_rpi_RX_ENABLED                     (1u)
#define uart_rpi_TX_ENABLED                     (1u)
#define uart_rpi_HD_ENABLED                     (0u)
#define uart_rpi_RX_INTERRUPT_ENABLED           (0u)
#define uart_rpi_TX_INTERRUPT_ENABLED           (0u)
#define uart_rpi_INTERNAL_CLOCK_USED            (1u)
#define uart_rpi_RXHW_ADDRESS_ENABLED           (0u)
#define uart_rpi_OVER_SAMPLE_COUNT              (8u)
#define uart_rpi_PARITY_TYPE                    (0u)
#define uart_rpi_PARITY_TYPE_SW                 (0u)
#define uart_rpi_BREAK_DETECT                   (0u)
#define uart_rpi_BREAK_BITS_TX                  (13u)
#define uart_rpi_BREAK_BITS_RX                  (13u)
#define uart_rpi_TXCLKGEN_DP                    (1u)
#define uart_rpi_USE23POLLING                   (1u)
#define uart_rpi_FLOW_CONTROL                   (0u)
#define uart_rpi_CLK_FREQ                       (0u)
#define uart_rpi_TX_BUFFER_SIZE                 (4u)
#define uart_rpi_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(uart_rpi_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define uart_rpi_CONTROL_REG_REMOVED            (0u)
#else
    #define uart_rpi_CONTROL_REG_REMOVED            (1u)
#endif /* End uart_rpi_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct uart_rpi_backupStruct_
{
    uint8 enableState;

    #if(uart_rpi_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End uart_rpi_CONTROL_REG_REMOVED */

} uart_rpi_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void uart_rpi_Start(void) ;
void uart_rpi_Stop(void) ;
uint8 uart_rpi_ReadControlRegister(void) ;
void uart_rpi_WriteControlRegister(uint8 control) ;

void uart_rpi_Init(void) ;
void uart_rpi_Enable(void) ;
void uart_rpi_SaveConfig(void) ;
void uart_rpi_RestoreConfig(void) ;
void uart_rpi_Sleep(void) ;
void uart_rpi_Wakeup(void) ;

/* Only if RX is enabled */
#if( (uart_rpi_RX_ENABLED) || (uart_rpi_HD_ENABLED) )

    #if (uart_rpi_RX_INTERRUPT_ENABLED)
        #define uart_rpi_EnableRxInt()  CyIntEnable (uart_rpi_RX_VECT_NUM)
        #define uart_rpi_DisableRxInt() CyIntDisable(uart_rpi_RX_VECT_NUM)
        CY_ISR_PROTO(uart_rpi_RXISR);
    #endif /* uart_rpi_RX_INTERRUPT_ENABLED */

    void uart_rpi_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void uart_rpi_SetRxAddress1(uint8 address) ;
    void uart_rpi_SetRxAddress2(uint8 address) ;

    void  uart_rpi_SetRxInterruptMode(uint8 intSrc) ;
    uint8 uart_rpi_ReadRxData(void) ;
    uint8 uart_rpi_ReadRxStatus(void) ;
    uint8 uart_rpi_GetChar(void) ;
    uint16 uart_rpi_GetByte(void) ;
    uint8 uart_rpi_GetRxBufferSize(void)
                                                            ;
    void uart_rpi_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define uart_rpi_GetRxInterruptSource   uart_rpi_ReadRxStatus

#endif /* End (uart_rpi_RX_ENABLED) || (uart_rpi_HD_ENABLED) */

/* Only if TX is enabled */
#if(uart_rpi_TX_ENABLED || uart_rpi_HD_ENABLED)

    #if(uart_rpi_TX_INTERRUPT_ENABLED)
        #define uart_rpi_EnableTxInt()  CyIntEnable (uart_rpi_TX_VECT_NUM)
        #define uart_rpi_DisableTxInt() CyIntDisable(uart_rpi_TX_VECT_NUM)
        #define uart_rpi_SetPendingTxInt() CyIntSetPending(uart_rpi_TX_VECT_NUM)
        #define uart_rpi_ClearPendingTxInt() CyIntClearPending(uart_rpi_TX_VECT_NUM)
        CY_ISR_PROTO(uart_rpi_TXISR);
    #endif /* uart_rpi_TX_INTERRUPT_ENABLED */

    void uart_rpi_SetTxInterruptMode(uint8 intSrc) ;
    void uart_rpi_WriteTxData(uint8 txDataByte) ;
    uint8 uart_rpi_ReadTxStatus(void) ;
    void uart_rpi_PutChar(uint8 txDataByte) ;
    void uart_rpi_PutString(const char8 string[]) ;
    void uart_rpi_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void uart_rpi_PutCRLF(uint8 txDataByte) ;
    void uart_rpi_ClearTxBuffer(void) ;
    void uart_rpi_SetTxAddressMode(uint8 addressMode) ;
    void uart_rpi_SendBreak(uint8 retMode) ;
    uint8 uart_rpi_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define uart_rpi_PutStringConst         uart_rpi_PutString
    #define uart_rpi_PutArrayConst          uart_rpi_PutArray
    #define uart_rpi_GetTxInterruptSource   uart_rpi_ReadTxStatus

#endif /* End uart_rpi_TX_ENABLED || uart_rpi_HD_ENABLED */

#if(uart_rpi_HD_ENABLED)
    void uart_rpi_LoadRxConfig(void) ;
    void uart_rpi_LoadTxConfig(void) ;
#endif /* End uart_rpi_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_uart_rpi) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    uart_rpi_CyBtldrCommStart(void) CYSMALL ;
    void    uart_rpi_CyBtldrCommStop(void) CYSMALL ;
    void    uart_rpi_CyBtldrCommReset(void) CYSMALL ;
    cystatus uart_rpi_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus uart_rpi_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_uart_rpi)
        #define CyBtldrCommStart    uart_rpi_CyBtldrCommStart
        #define CyBtldrCommStop     uart_rpi_CyBtldrCommStop
        #define CyBtldrCommReset    uart_rpi_CyBtldrCommReset
        #define CyBtldrCommWrite    uart_rpi_CyBtldrCommWrite
        #define CyBtldrCommRead     uart_rpi_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_uart_rpi) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define uart_rpi_BYTE2BYTE_TIME_OUT (25u)
    #define uart_rpi_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define uart_rpi_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define uart_rpi_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define uart_rpi_SET_SPACE      (0x00u)
#define uart_rpi_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (uart_rpi_TX_ENABLED) || (uart_rpi_HD_ENABLED) )
    #if(uart_rpi_TX_INTERRUPT_ENABLED)
        #define uart_rpi_TX_VECT_NUM            (uint8)uart_rpi_TXInternalInterrupt__INTC_NUMBER
        #define uart_rpi_TX_PRIOR_NUM           (uint8)uart_rpi_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* uart_rpi_TX_INTERRUPT_ENABLED */

    #define uart_rpi_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define uart_rpi_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define uart_rpi_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(uart_rpi_TX_ENABLED)
        #define uart_rpi_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (uart_rpi_HD_ENABLED) */
        #define uart_rpi_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (uart_rpi_TX_ENABLED) */

    #define uart_rpi_TX_STS_COMPLETE            (uint8)(0x01u << uart_rpi_TX_STS_COMPLETE_SHIFT)
    #define uart_rpi_TX_STS_FIFO_EMPTY          (uint8)(0x01u << uart_rpi_TX_STS_FIFO_EMPTY_SHIFT)
    #define uart_rpi_TX_STS_FIFO_FULL           (uint8)(0x01u << uart_rpi_TX_STS_FIFO_FULL_SHIFT)
    #define uart_rpi_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << uart_rpi_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (uart_rpi_TX_ENABLED) || (uart_rpi_HD_ENABLED)*/

#if( (uart_rpi_RX_ENABLED) || (uart_rpi_HD_ENABLED) )
    #if(uart_rpi_RX_INTERRUPT_ENABLED)
        #define uart_rpi_RX_VECT_NUM            (uint8)uart_rpi_RXInternalInterrupt__INTC_NUMBER
        #define uart_rpi_RX_PRIOR_NUM           (uint8)uart_rpi_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* uart_rpi_RX_INTERRUPT_ENABLED */
    #define uart_rpi_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define uart_rpi_RX_STS_BREAK_SHIFT             (0x01u)
    #define uart_rpi_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define uart_rpi_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define uart_rpi_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define uart_rpi_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define uart_rpi_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define uart_rpi_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define uart_rpi_RX_STS_MRKSPC           (uint8)(0x01u << uart_rpi_RX_STS_MRKSPC_SHIFT)
    #define uart_rpi_RX_STS_BREAK            (uint8)(0x01u << uart_rpi_RX_STS_BREAK_SHIFT)
    #define uart_rpi_RX_STS_PAR_ERROR        (uint8)(0x01u << uart_rpi_RX_STS_PAR_ERROR_SHIFT)
    #define uart_rpi_RX_STS_STOP_ERROR       (uint8)(0x01u << uart_rpi_RX_STS_STOP_ERROR_SHIFT)
    #define uart_rpi_RX_STS_OVERRUN          (uint8)(0x01u << uart_rpi_RX_STS_OVERRUN_SHIFT)
    #define uart_rpi_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << uart_rpi_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define uart_rpi_RX_STS_ADDR_MATCH       (uint8)(0x01u << uart_rpi_RX_STS_ADDR_MATCH_SHIFT)
    #define uart_rpi_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << uart_rpi_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define uart_rpi_RX_HW_MASK                     (0x7Fu)
#endif /* End (uart_rpi_RX_ENABLED) || (uart_rpi_HD_ENABLED) */

/* Control Register definitions */
#define uart_rpi_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define uart_rpi_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define uart_rpi_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define uart_rpi_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define uart_rpi_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define uart_rpi_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define uart_rpi_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define uart_rpi_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define uart_rpi_CTRL_HD_SEND               (uint8)(0x01u << uart_rpi_CTRL_HD_SEND_SHIFT)
#define uart_rpi_CTRL_HD_SEND_BREAK         (uint8)(0x01u << uart_rpi_CTRL_HD_SEND_BREAK_SHIFT)
#define uart_rpi_CTRL_MARK                  (uint8)(0x01u << uart_rpi_CTRL_MARK_SHIFT)
#define uart_rpi_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << uart_rpi_CTRL_PARITY_TYPE0_SHIFT)
#define uart_rpi_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << uart_rpi_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define uart_rpi_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define uart_rpi_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define uart_rpi_SEND_BREAK                         (0x00u)
#define uart_rpi_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define uart_rpi_REINIT                             (0x02u)
#define uart_rpi_SEND_WAIT_REINIT                   (0x03u)

#define uart_rpi_OVER_SAMPLE_8                      (8u)
#define uart_rpi_OVER_SAMPLE_16                     (16u)

#define uart_rpi_BIT_CENTER                         (uart_rpi_OVER_SAMPLE_COUNT - 2u)

#define uart_rpi_FIFO_LENGTH                        (4u)
#define uart_rpi_NUMBER_OF_START_BIT                (1u)
#define uart_rpi_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define uart_rpi_TXBITCTR_BREAKBITS8X   ((uart_rpi_BREAK_BITS_TX * uart_rpi_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define uart_rpi_TXBITCTR_BREAKBITS ((uart_rpi_BREAK_BITS_TX * uart_rpi_OVER_SAMPLE_COUNT) - 1u)

#define uart_rpi_HALF_BIT_COUNT   \
                            (((uart_rpi_OVER_SAMPLE_COUNT / 2u) + (uart_rpi_USE23POLLING * 1u)) - 2u)
#if (uart_rpi_OVER_SAMPLE_COUNT == uart_rpi_OVER_SAMPLE_8)
    #define uart_rpi_HD_TXBITCTR_INIT   (((uart_rpi_BREAK_BITS_TX + \
                            uart_rpi_NUMBER_OF_START_BIT) * uart_rpi_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define uart_rpi_RXBITCTR_INIT  ((((uart_rpi_BREAK_BITS_RX + uart_rpi_NUMBER_OF_START_BIT) \
                            * uart_rpi_OVER_SAMPLE_COUNT) + uart_rpi_HALF_BIT_COUNT) - 1u)

#else /* uart_rpi_OVER_SAMPLE_COUNT == uart_rpi_OVER_SAMPLE_16 */
    #define uart_rpi_HD_TXBITCTR_INIT   ((8u * uart_rpi_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define uart_rpi_RXBITCTR_INIT      (((7u * uart_rpi_OVER_SAMPLE_COUNT) - 1u) + \
                                                      uart_rpi_HALF_BIT_COUNT)
#endif /* End uart_rpi_OVER_SAMPLE_COUNT */

#define uart_rpi_HD_RXBITCTR_INIT                   uart_rpi_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 uart_rpi_initVar;
#if (uart_rpi_TX_INTERRUPT_ENABLED && uart_rpi_TX_ENABLED)
    extern volatile uint8 uart_rpi_txBuffer[uart_rpi_TX_BUFFER_SIZE];
    extern volatile uint8 uart_rpi_txBufferRead;
    extern uint8 uart_rpi_txBufferWrite;
#endif /* (uart_rpi_TX_INTERRUPT_ENABLED && uart_rpi_TX_ENABLED) */
#if (uart_rpi_RX_INTERRUPT_ENABLED && (uart_rpi_RX_ENABLED || uart_rpi_HD_ENABLED))
    extern uint8 uart_rpi_errorStatus;
    extern volatile uint8 uart_rpi_rxBuffer[uart_rpi_RX_BUFFER_SIZE];
    extern volatile uint8 uart_rpi_rxBufferRead;
    extern volatile uint8 uart_rpi_rxBufferWrite;
    extern volatile uint8 uart_rpi_rxBufferLoopDetect;
    extern volatile uint8 uart_rpi_rxBufferOverflow;
    #if (uart_rpi_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 uart_rpi_rxAddressMode;
        extern volatile uint8 uart_rpi_rxAddressDetected;
    #endif /* (uart_rpi_RXHW_ADDRESS_ENABLED) */
#endif /* (uart_rpi_RX_INTERRUPT_ENABLED && (uart_rpi_RX_ENABLED || uart_rpi_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define uart_rpi__B_UART__AM_SW_BYTE_BYTE 1
#define uart_rpi__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define uart_rpi__B_UART__AM_HW_BYTE_BY_BYTE 3
#define uart_rpi__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define uart_rpi__B_UART__AM_NONE 0

#define uart_rpi__B_UART__NONE_REVB 0
#define uart_rpi__B_UART__EVEN_REVB 1
#define uart_rpi__B_UART__ODD_REVB 2
#define uart_rpi__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define uart_rpi_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define uart_rpi_NUMBER_OF_STOP_BITS    (1u)

#if (uart_rpi_RXHW_ADDRESS_ENABLED)
    #define uart_rpi_RX_ADDRESS_MODE    (0u)
    #define uart_rpi_RX_HW_ADDRESS1     (0u)
    #define uart_rpi_RX_HW_ADDRESS2     (0u)
#endif /* (uart_rpi_RXHW_ADDRESS_ENABLED) */

#define uart_rpi_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << uart_rpi_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << uart_rpi_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << uart_rpi_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << uart_rpi_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << uart_rpi_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << uart_rpi_RX_STS_BREAK_SHIFT) \
                                        | (0 << uart_rpi_RX_STS_OVERRUN_SHIFT))

#define uart_rpi_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << uart_rpi_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << uart_rpi_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << uart_rpi_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << uart_rpi_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef uart_rpi_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define uart_rpi_CONTROL_REG \
                            (* (reg8 *) uart_rpi_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define uart_rpi_CONTROL_PTR \
                            (  (reg8 *) uart_rpi_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End uart_rpi_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(uart_rpi_TX_ENABLED)
    #define uart_rpi_TXDATA_REG          (* (reg8 *) uart_rpi_BUART_sTX_TxShifter_u0__F0_REG)
    #define uart_rpi_TXDATA_PTR          (  (reg8 *) uart_rpi_BUART_sTX_TxShifter_u0__F0_REG)
    #define uart_rpi_TXDATA_AUX_CTL_REG  (* (reg8 *) uart_rpi_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define uart_rpi_TXDATA_AUX_CTL_PTR  (  (reg8 *) uart_rpi_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define uart_rpi_TXSTATUS_REG        (* (reg8 *) uart_rpi_BUART_sTX_TxSts__STATUS_REG)
    #define uart_rpi_TXSTATUS_PTR        (  (reg8 *) uart_rpi_BUART_sTX_TxSts__STATUS_REG)
    #define uart_rpi_TXSTATUS_MASK_REG   (* (reg8 *) uart_rpi_BUART_sTX_TxSts__MASK_REG)
    #define uart_rpi_TXSTATUS_MASK_PTR   (  (reg8 *) uart_rpi_BUART_sTX_TxSts__MASK_REG)
    #define uart_rpi_TXSTATUS_ACTL_REG   (* (reg8 *) uart_rpi_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define uart_rpi_TXSTATUS_ACTL_PTR   (  (reg8 *) uart_rpi_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(uart_rpi_TXCLKGEN_DP)
        #define uart_rpi_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) uart_rpi_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define uart_rpi_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) uart_rpi_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define uart_rpi_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) uart_rpi_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define uart_rpi_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) uart_rpi_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define uart_rpi_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) uart_rpi_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define uart_rpi_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) uart_rpi_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define uart_rpi_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) uart_rpi_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define uart_rpi_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) uart_rpi_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define uart_rpi_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) uart_rpi_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define uart_rpi_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) uart_rpi_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* uart_rpi_TXCLKGEN_DP */

#endif /* End uart_rpi_TX_ENABLED */

#if(uart_rpi_HD_ENABLED)

    #define uart_rpi_TXDATA_REG             (* (reg8 *) uart_rpi_BUART_sRX_RxShifter_u0__F1_REG )
    #define uart_rpi_TXDATA_PTR             (  (reg8 *) uart_rpi_BUART_sRX_RxShifter_u0__F1_REG )
    #define uart_rpi_TXDATA_AUX_CTL_REG     (* (reg8 *) uart_rpi_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define uart_rpi_TXDATA_AUX_CTL_PTR     (  (reg8 *) uart_rpi_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define uart_rpi_TXSTATUS_REG           (* (reg8 *) uart_rpi_BUART_sRX_RxSts__STATUS_REG )
    #define uart_rpi_TXSTATUS_PTR           (  (reg8 *) uart_rpi_BUART_sRX_RxSts__STATUS_REG )
    #define uart_rpi_TXSTATUS_MASK_REG      (* (reg8 *) uart_rpi_BUART_sRX_RxSts__MASK_REG )
    #define uart_rpi_TXSTATUS_MASK_PTR      (  (reg8 *) uart_rpi_BUART_sRX_RxSts__MASK_REG )
    #define uart_rpi_TXSTATUS_ACTL_REG      (* (reg8 *) uart_rpi_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define uart_rpi_TXSTATUS_ACTL_PTR      (  (reg8 *) uart_rpi_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End uart_rpi_HD_ENABLED */

#if( (uart_rpi_RX_ENABLED) || (uart_rpi_HD_ENABLED) )
    #define uart_rpi_RXDATA_REG             (* (reg8 *) uart_rpi_BUART_sRX_RxShifter_u0__F0_REG )
    #define uart_rpi_RXDATA_PTR             (  (reg8 *) uart_rpi_BUART_sRX_RxShifter_u0__F0_REG )
    #define uart_rpi_RXADDRESS1_REG         (* (reg8 *) uart_rpi_BUART_sRX_RxShifter_u0__D0_REG )
    #define uart_rpi_RXADDRESS1_PTR         (  (reg8 *) uart_rpi_BUART_sRX_RxShifter_u0__D0_REG )
    #define uart_rpi_RXADDRESS2_REG         (* (reg8 *) uart_rpi_BUART_sRX_RxShifter_u0__D1_REG )
    #define uart_rpi_RXADDRESS2_PTR         (  (reg8 *) uart_rpi_BUART_sRX_RxShifter_u0__D1_REG )
    #define uart_rpi_RXDATA_AUX_CTL_REG     (* (reg8 *) uart_rpi_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define uart_rpi_RXBITCTR_PERIOD_REG    (* (reg8 *) uart_rpi_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define uart_rpi_RXBITCTR_PERIOD_PTR    (  (reg8 *) uart_rpi_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define uart_rpi_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) uart_rpi_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define uart_rpi_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) uart_rpi_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define uart_rpi_RXBITCTR_COUNTER_REG   (* (reg8 *) uart_rpi_BUART_sRX_RxBitCounter__COUNT_REG )
    #define uart_rpi_RXBITCTR_COUNTER_PTR   (  (reg8 *) uart_rpi_BUART_sRX_RxBitCounter__COUNT_REG )

    #define uart_rpi_RXSTATUS_REG           (* (reg8 *) uart_rpi_BUART_sRX_RxSts__STATUS_REG )
    #define uart_rpi_RXSTATUS_PTR           (  (reg8 *) uart_rpi_BUART_sRX_RxSts__STATUS_REG )
    #define uart_rpi_RXSTATUS_MASK_REG      (* (reg8 *) uart_rpi_BUART_sRX_RxSts__MASK_REG )
    #define uart_rpi_RXSTATUS_MASK_PTR      (  (reg8 *) uart_rpi_BUART_sRX_RxSts__MASK_REG )
    #define uart_rpi_RXSTATUS_ACTL_REG      (* (reg8 *) uart_rpi_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define uart_rpi_RXSTATUS_ACTL_PTR      (  (reg8 *) uart_rpi_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (uart_rpi_RX_ENABLED) || (uart_rpi_HD_ENABLED) */

#if(uart_rpi_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define uart_rpi_INTCLOCK_CLKEN_REG     (* (reg8 *) uart_rpi_IntClock__PM_ACT_CFG)
    #define uart_rpi_INTCLOCK_CLKEN_PTR     (  (reg8 *) uart_rpi_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define uart_rpi_INTCLOCK_CLKEN_MASK    uart_rpi_IntClock__PM_ACT_MSK
#endif /* End uart_rpi_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(uart_rpi_TX_ENABLED)
    #define uart_rpi_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End uart_rpi_TX_ENABLED */

#if(uart_rpi_HD_ENABLED)
    #define uart_rpi_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End uart_rpi_HD_ENABLED */

#if( (uart_rpi_RX_ENABLED) || (uart_rpi_HD_ENABLED) )
    #define uart_rpi_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (uart_rpi_RX_ENABLED) || (uart_rpi_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define uart_rpi_WAIT_1_MS      uart_rpi_BL_CHK_DELAY_MS   

#define uart_rpi_TXBUFFERSIZE   uart_rpi_TX_BUFFER_SIZE
#define uart_rpi_RXBUFFERSIZE   uart_rpi_RX_BUFFER_SIZE

#if (uart_rpi_RXHW_ADDRESS_ENABLED)
    #define uart_rpi_RXADDRESSMODE  uart_rpi_RX_ADDRESS_MODE
    #define uart_rpi_RXHWADDRESS1   uart_rpi_RX_HW_ADDRESS1
    #define uart_rpi_RXHWADDRESS2   uart_rpi_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define uart_rpi_RXAddressMode  uart_rpi_RXADDRESSMODE
#endif /* (uart_rpi_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define uart_rpi_initvar                    uart_rpi_initVar

#define uart_rpi_RX_Enabled                 uart_rpi_RX_ENABLED
#define uart_rpi_TX_Enabled                 uart_rpi_TX_ENABLED
#define uart_rpi_HD_Enabled                 uart_rpi_HD_ENABLED
#define uart_rpi_RX_IntInterruptEnabled     uart_rpi_RX_INTERRUPT_ENABLED
#define uart_rpi_TX_IntInterruptEnabled     uart_rpi_TX_INTERRUPT_ENABLED
#define uart_rpi_InternalClockUsed          uart_rpi_INTERNAL_CLOCK_USED
#define uart_rpi_RXHW_Address_Enabled       uart_rpi_RXHW_ADDRESS_ENABLED
#define uart_rpi_OverSampleCount            uart_rpi_OVER_SAMPLE_COUNT
#define uart_rpi_ParityType                 uart_rpi_PARITY_TYPE

#if( uart_rpi_TX_ENABLED && (uart_rpi_TXBUFFERSIZE > uart_rpi_FIFO_LENGTH))
    #define uart_rpi_TXBUFFER               uart_rpi_txBuffer
    #define uart_rpi_TXBUFFERREAD           uart_rpi_txBufferRead
    #define uart_rpi_TXBUFFERWRITE          uart_rpi_txBufferWrite
#endif /* End uart_rpi_TX_ENABLED */
#if( ( uart_rpi_RX_ENABLED || uart_rpi_HD_ENABLED ) && \
     (uart_rpi_RXBUFFERSIZE > uart_rpi_FIFO_LENGTH) )
    #define uart_rpi_RXBUFFER               uart_rpi_rxBuffer
    #define uart_rpi_RXBUFFERREAD           uart_rpi_rxBufferRead
    #define uart_rpi_RXBUFFERWRITE          uart_rpi_rxBufferWrite
    #define uart_rpi_RXBUFFERLOOPDETECT     uart_rpi_rxBufferLoopDetect
    #define uart_rpi_RXBUFFER_OVERFLOW      uart_rpi_rxBufferOverflow
#endif /* End uart_rpi_RX_ENABLED */

#ifdef uart_rpi_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define uart_rpi_CONTROL                uart_rpi_CONTROL_REG
#endif /* End uart_rpi_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(uart_rpi_TX_ENABLED)
    #define uart_rpi_TXDATA                 uart_rpi_TXDATA_REG
    #define uart_rpi_TXSTATUS               uart_rpi_TXSTATUS_REG
    #define uart_rpi_TXSTATUS_MASK          uart_rpi_TXSTATUS_MASK_REG
    #define uart_rpi_TXSTATUS_ACTL          uart_rpi_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(uart_rpi_TXCLKGEN_DP)
        #define uart_rpi_TXBITCLKGEN_CTR        uart_rpi_TXBITCLKGEN_CTR_REG
        #define uart_rpi_TXBITCLKTX_COMPLETE    uart_rpi_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define uart_rpi_TXBITCTR_PERIOD        uart_rpi_TXBITCTR_PERIOD_REG
        #define uart_rpi_TXBITCTR_CONTROL       uart_rpi_TXBITCTR_CONTROL_REG
        #define uart_rpi_TXBITCTR_COUNTER       uart_rpi_TXBITCTR_COUNTER_REG
    #endif /* uart_rpi_TXCLKGEN_DP */
#endif /* End uart_rpi_TX_ENABLED */

#if(uart_rpi_HD_ENABLED)
    #define uart_rpi_TXDATA                 uart_rpi_TXDATA_REG
    #define uart_rpi_TXSTATUS               uart_rpi_TXSTATUS_REG
    #define uart_rpi_TXSTATUS_MASK          uart_rpi_TXSTATUS_MASK_REG
    #define uart_rpi_TXSTATUS_ACTL          uart_rpi_TXSTATUS_ACTL_REG
#endif /* End uart_rpi_HD_ENABLED */

#if( (uart_rpi_RX_ENABLED) || (uart_rpi_HD_ENABLED) )
    #define uart_rpi_RXDATA                 uart_rpi_RXDATA_REG
    #define uart_rpi_RXADDRESS1             uart_rpi_RXADDRESS1_REG
    #define uart_rpi_RXADDRESS2             uart_rpi_RXADDRESS2_REG
    #define uart_rpi_RXBITCTR_PERIOD        uart_rpi_RXBITCTR_PERIOD_REG
    #define uart_rpi_RXBITCTR_CONTROL       uart_rpi_RXBITCTR_CONTROL_REG
    #define uart_rpi_RXBITCTR_COUNTER       uart_rpi_RXBITCTR_COUNTER_REG
    #define uart_rpi_RXSTATUS               uart_rpi_RXSTATUS_REG
    #define uart_rpi_RXSTATUS_MASK          uart_rpi_RXSTATUS_MASK_REG
    #define uart_rpi_RXSTATUS_ACTL          uart_rpi_RXSTATUS_ACTL_REG
#endif /* End  (uart_rpi_RX_ENABLED) || (uart_rpi_HD_ENABLED) */

#if(uart_rpi_INTERNAL_CLOCK_USED)
    #define uart_rpi_INTCLOCK_CLKEN         uart_rpi_INTCLOCK_CLKEN_REG
#endif /* End uart_rpi_INTERNAL_CLOCK_USED */

#define uart_rpi_WAIT_FOR_COMLETE_REINIT    uart_rpi_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_uart_rpi_H */


/* [] END OF FILE */
