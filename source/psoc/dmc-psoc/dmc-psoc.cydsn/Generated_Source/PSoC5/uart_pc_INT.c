/*******************************************************************************
* File Name: uart_pcINT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "uart_pc.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (uart_pc_RX_INTERRUPT_ENABLED && (uart_pc_RX_ENABLED || uart_pc_HD_ENABLED))
    /*******************************************************************************
    * Function Name: uart_pc_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  uart_pc_rxBuffer - RAM buffer pointer for save received data.
    *  uart_pc_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  uart_pc_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  uart_pc_rxBufferOverflow - software overflow flag. Set to one
    *     when uart_pc_rxBufferWrite index overtakes
    *     uart_pc_rxBufferRead index.
    *  uart_pc_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when uart_pc_rxBufferWrite is equal to
    *    uart_pc_rxBufferRead
    *  uart_pc_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  uart_pc_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(uart_pc_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef uart_pc_RXISR_ENTRY_CALLBACK
        uart_pc_RXISR_EntryCallback();
    #endif /* uart_pc_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START uart_pc_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = uart_pc_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in uart_pc_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (uart_pc_RX_STS_BREAK | 
                            uart_pc_RX_STS_PAR_ERROR |
                            uart_pc_RX_STS_STOP_ERROR | 
                            uart_pc_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                uart_pc_errorStatus |= readStatus & ( uart_pc_RX_STS_BREAK | 
                                                            uart_pc_RX_STS_PAR_ERROR | 
                                                            uart_pc_RX_STS_STOP_ERROR | 
                                                            uart_pc_RX_STS_OVERRUN);
                /* `#START uart_pc_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef uart_pc_RXISR_ERROR_CALLBACK
                uart_pc_RXISR_ERROR_Callback();
            #endif /* uart_pc_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & uart_pc_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = uart_pc_RXDATA_REG;
            #if (uart_pc_RXHW_ADDRESS_ENABLED)
                if(uart_pc_rxAddressMode == (uint8)uart_pc__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & uart_pc_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & uart_pc_RX_STS_ADDR_MATCH) != 0u)
                        {
                            uart_pc_rxAddressDetected = 1u;
                        }
                        else
                        {
                            uart_pc_rxAddressDetected = 0u;
                        }
                    }
                    if(uart_pc_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        uart_pc_rxBuffer[uart_pc_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    uart_pc_rxBuffer[uart_pc_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                uart_pc_rxBuffer[uart_pc_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (uart_pc_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(uart_pc_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        uart_pc_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    uart_pc_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(uart_pc_rxBufferWrite >= uart_pc_RX_BUFFER_SIZE)
                    {
                        uart_pc_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(uart_pc_rxBufferWrite == uart_pc_rxBufferRead)
                    {
                        uart_pc_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (uart_pc_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            uart_pc_RXSTATUS_MASK_REG  &= (uint8)~uart_pc_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(uart_pc_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (uart_pc_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & uart_pc_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START uart_pc_RXISR_END` */

        /* `#END` */

    #ifdef uart_pc_RXISR_EXIT_CALLBACK
        uart_pc_RXISR_ExitCallback();
    #endif /* uart_pc_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (uart_pc_RX_INTERRUPT_ENABLED && (uart_pc_RX_ENABLED || uart_pc_HD_ENABLED)) */


#if (uart_pc_TX_INTERRUPT_ENABLED && uart_pc_TX_ENABLED)
    /*******************************************************************************
    * Function Name: uart_pc_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  uart_pc_txBuffer - RAM buffer pointer for transmit data from.
    *  uart_pc_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  uart_pc_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(uart_pc_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef uart_pc_TXISR_ENTRY_CALLBACK
        uart_pc_TXISR_EntryCallback();
    #endif /* uart_pc_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START uart_pc_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((uart_pc_txBufferRead != uart_pc_txBufferWrite) &&
             ((uart_pc_TXSTATUS_REG & uart_pc_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(uart_pc_txBufferRead >= uart_pc_TX_BUFFER_SIZE)
            {
                uart_pc_txBufferRead = 0u;
            }

            uart_pc_TXDATA_REG = uart_pc_txBuffer[uart_pc_txBufferRead];

            /* Set next pointer */
            uart_pc_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START uart_pc_TXISR_END` */

        /* `#END` */

    #ifdef uart_pc_TXISR_EXIT_CALLBACK
        uart_pc_TXISR_ExitCallback();
    #endif /* uart_pc_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (uart_pc_TX_INTERRUPT_ENABLED && uart_pc_TX_ENABLED) */


/* [] END OF FILE */
