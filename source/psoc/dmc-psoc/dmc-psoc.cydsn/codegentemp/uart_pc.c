/*******************************************************************************
* File Name: uart_pc.c
* Version 2.50
*
* Description:
*  This file provides all API functionality of the UART component
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
#if (uart_pc_INTERNAL_CLOCK_USED)
    #include "uart_pc_IntClock.h"
#endif /* End uart_pc_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 uart_pc_initVar = 0u;

#if (uart_pc_TX_INTERRUPT_ENABLED && uart_pc_TX_ENABLED)
    volatile uint8 uart_pc_txBuffer[uart_pc_TX_BUFFER_SIZE];
    volatile uint8 uart_pc_txBufferRead = 0u;
    uint8 uart_pc_txBufferWrite = 0u;
#endif /* (uart_pc_TX_INTERRUPT_ENABLED && uart_pc_TX_ENABLED) */

#if (uart_pc_RX_INTERRUPT_ENABLED && (uart_pc_RX_ENABLED || uart_pc_HD_ENABLED))
    uint8 uart_pc_errorStatus = 0u;
    volatile uint8 uart_pc_rxBuffer[uart_pc_RX_BUFFER_SIZE];
    volatile uint8 uart_pc_rxBufferRead  = 0u;
    volatile uint8 uart_pc_rxBufferWrite = 0u;
    volatile uint8 uart_pc_rxBufferLoopDetect = 0u;
    volatile uint8 uart_pc_rxBufferOverflow   = 0u;
    #if (uart_pc_RXHW_ADDRESS_ENABLED)
        volatile uint8 uart_pc_rxAddressMode = uart_pc_RX_ADDRESS_MODE;
        volatile uint8 uart_pc_rxAddressDetected = 0u;
    #endif /* (uart_pc_RXHW_ADDRESS_ENABLED) */
#endif /* (uart_pc_RX_INTERRUPT_ENABLED && (uart_pc_RX_ENABLED || uart_pc_HD_ENABLED)) */


/*******************************************************************************
* Function Name: uart_pc_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  uart_pc_Start() sets the initVar variable, calls the
*  uart_pc_Init() function, and then calls the
*  uart_pc_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The uart_pc_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time uart_pc_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the uart_pc_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void uart_pc_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(uart_pc_initVar == 0u)
    {
        uart_pc_Init();
        uart_pc_initVar = 1u;
    }

    uart_pc_Enable();
}


/*******************************************************************************
* Function Name: uart_pc_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call uart_pc_Init() because
*  the uart_pc_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void uart_pc_Init(void) 
{
    #if(uart_pc_RX_ENABLED || uart_pc_HD_ENABLED)

        #if (uart_pc_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(uart_pc_RX_VECT_NUM, &uart_pc_RXISR);
            CyIntSetPriority(uart_pc_RX_VECT_NUM, uart_pc_RX_PRIOR_NUM);
            uart_pc_errorStatus = 0u;
        #endif /* (uart_pc_RX_INTERRUPT_ENABLED) */

        #if (uart_pc_RXHW_ADDRESS_ENABLED)
            uart_pc_SetRxAddressMode(uart_pc_RX_ADDRESS_MODE);
            uart_pc_SetRxAddress1(uart_pc_RX_HW_ADDRESS1);
            uart_pc_SetRxAddress2(uart_pc_RX_HW_ADDRESS2);
        #endif /* End uart_pc_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        uart_pc_RXBITCTR_PERIOD_REG = uart_pc_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        uart_pc_RXSTATUS_MASK_REG  = uart_pc_INIT_RX_INTERRUPTS_MASK;
    #endif /* End uart_pc_RX_ENABLED || uart_pc_HD_ENABLED*/

    #if(uart_pc_TX_ENABLED)
        #if (uart_pc_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(uart_pc_TX_VECT_NUM, &uart_pc_TXISR);
            CyIntSetPriority(uart_pc_TX_VECT_NUM, uart_pc_TX_PRIOR_NUM);
        #endif /* (uart_pc_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (uart_pc_TXCLKGEN_DP)
            uart_pc_TXBITCLKGEN_CTR_REG = uart_pc_BIT_CENTER;
            uart_pc_TXBITCLKTX_COMPLETE_REG = ((uart_pc_NUMBER_OF_DATA_BITS +
                        uart_pc_NUMBER_OF_START_BIT) * uart_pc_OVER_SAMPLE_COUNT) - 1u;
        #else
            uart_pc_TXBITCTR_PERIOD_REG = ((uart_pc_NUMBER_OF_DATA_BITS +
                        uart_pc_NUMBER_OF_START_BIT) * uart_pc_OVER_SAMPLE_8) - 1u;
        #endif /* End uart_pc_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (uart_pc_TX_INTERRUPT_ENABLED)
            uart_pc_TXSTATUS_MASK_REG = uart_pc_TX_STS_FIFO_EMPTY;
        #else
            uart_pc_TXSTATUS_MASK_REG = uart_pc_INIT_TX_INTERRUPTS_MASK;
        #endif /*End uart_pc_TX_INTERRUPT_ENABLED*/

    #endif /* End uart_pc_TX_ENABLED */

    #if(uart_pc_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        uart_pc_WriteControlRegister( \
            (uart_pc_ReadControlRegister() & (uint8)~uart_pc_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(uart_pc_PARITY_TYPE << uart_pc_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End uart_pc_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: uart_pc_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call uart_pc_Enable() because the uart_pc_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  uart_pc_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void uart_pc_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (uart_pc_RX_ENABLED || uart_pc_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        uart_pc_RXBITCTR_CONTROL_REG |= uart_pc_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        uart_pc_RXSTATUS_ACTL_REG  |= uart_pc_INT_ENABLE;

        #if (uart_pc_RX_INTERRUPT_ENABLED)
            uart_pc_EnableRxInt();

            #if (uart_pc_RXHW_ADDRESS_ENABLED)
                uart_pc_rxAddressDetected = 0u;
            #endif /* (uart_pc_RXHW_ADDRESS_ENABLED) */
        #endif /* (uart_pc_RX_INTERRUPT_ENABLED) */
    #endif /* (uart_pc_RX_ENABLED || uart_pc_HD_ENABLED) */

    #if(uart_pc_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!uart_pc_TXCLKGEN_DP)
            uart_pc_TXBITCTR_CONTROL_REG |= uart_pc_CNTR_ENABLE;
        #endif /* End uart_pc_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        uart_pc_TXSTATUS_ACTL_REG |= uart_pc_INT_ENABLE;
        #if (uart_pc_TX_INTERRUPT_ENABLED)
            uart_pc_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            uart_pc_EnableTxInt();
        #endif /* (uart_pc_TX_INTERRUPT_ENABLED) */
     #endif /* (uart_pc_TX_INTERRUPT_ENABLED) */

    #if (uart_pc_INTERNAL_CLOCK_USED)
        uart_pc_IntClock_Start();  /* Enable the clock */
    #endif /* (uart_pc_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: uart_pc_Stop
********************************************************************************
*
* Summary:
*  Disables the UART operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void uart_pc_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (uart_pc_RX_ENABLED || uart_pc_HD_ENABLED)
        uart_pc_RXBITCTR_CONTROL_REG &= (uint8) ~uart_pc_CNTR_ENABLE;
    #endif /* (uart_pc_RX_ENABLED || uart_pc_HD_ENABLED) */

    #if (uart_pc_TX_ENABLED)
        #if(!uart_pc_TXCLKGEN_DP)
            uart_pc_TXBITCTR_CONTROL_REG &= (uint8) ~uart_pc_CNTR_ENABLE;
        #endif /* (!uart_pc_TXCLKGEN_DP) */
    #endif /* (uart_pc_TX_ENABLED) */

    #if (uart_pc_INTERNAL_CLOCK_USED)
        uart_pc_IntClock_Stop();   /* Disable the clock */
    #endif /* (uart_pc_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (uart_pc_RX_ENABLED || uart_pc_HD_ENABLED)
        uart_pc_RXSTATUS_ACTL_REG  &= (uint8) ~uart_pc_INT_ENABLE;

        #if (uart_pc_RX_INTERRUPT_ENABLED)
            uart_pc_DisableRxInt();
        #endif /* (uart_pc_RX_INTERRUPT_ENABLED) */
    #endif /* (uart_pc_RX_ENABLED || uart_pc_HD_ENABLED) */

    #if (uart_pc_TX_ENABLED)
        uart_pc_TXSTATUS_ACTL_REG &= (uint8) ~uart_pc_INT_ENABLE;

        #if (uart_pc_TX_INTERRUPT_ENABLED)
            uart_pc_DisableTxInt();
        #endif /* (uart_pc_TX_INTERRUPT_ENABLED) */
    #endif /* (uart_pc_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: uart_pc_ReadControlRegister
********************************************************************************
*
* Summary:
*  Returns the current value of the control register.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the control register.
*
*******************************************************************************/
uint8 uart_pc_ReadControlRegister(void) 
{
    #if (uart_pc_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(uart_pc_CONTROL_REG);
    #endif /* (uart_pc_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: uart_pc_WriteControlRegister
********************************************************************************
*
* Summary:
*  Writes an 8-bit value into the control register
*
* Parameters:
*  control:  control register value
*
* Return:
*  None.
*
*******************************************************************************/
void  uart_pc_WriteControlRegister(uint8 control) 
{
    #if (uart_pc_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       uart_pc_CONTROL_REG = control;
    #endif /* (uart_pc_CONTROL_REG_REMOVED) */
}


#if(uart_pc_RX_ENABLED || uart_pc_HD_ENABLED)
    /*******************************************************************************
    * Function Name: uart_pc_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      uart_pc_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      uart_pc_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      uart_pc_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      uart_pc_RX_STS_BREAK            Interrupt on break.
    *      uart_pc_RX_STS_OVERRUN          Interrupt on overrun error.
    *      uart_pc_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      uart_pc_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void uart_pc_SetRxInterruptMode(uint8 intSrc) 
    {
        uart_pc_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: uart_pc_ReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Returns the next byte of received data. This function returns data without
    *  checking the status. You must check the status separately.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received data from RX register
    *
    * Global Variables:
    *  uart_pc_rxBuffer - RAM buffer pointer for save received data.
    *  uart_pc_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  uart_pc_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  uart_pc_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 uart_pc_ReadRxData(void) 
    {
        uint8 rxData;

    #if (uart_pc_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        uart_pc_DisableRxInt();

        locRxBufferRead  = uart_pc_rxBufferRead;
        locRxBufferWrite = uart_pc_rxBufferWrite;

        if( (uart_pc_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = uart_pc_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= uart_pc_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            uart_pc_rxBufferRead = locRxBufferRead;

            if(uart_pc_rxBufferLoopDetect != 0u)
            {
                uart_pc_rxBufferLoopDetect = 0u;
                #if ((uart_pc_RX_INTERRUPT_ENABLED) && (uart_pc_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( uart_pc_HD_ENABLED )
                        if((uart_pc_CONTROL_REG & uart_pc_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            uart_pc_RXSTATUS_MASK_REG  |= uart_pc_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        uart_pc_RXSTATUS_MASK_REG  |= uart_pc_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end uart_pc_HD_ENABLED */
                #endif /* ((uart_pc_RX_INTERRUPT_ENABLED) && (uart_pc_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = uart_pc_RXDATA_REG;
        }

        uart_pc_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = uart_pc_RXDATA_REG;

    #endif /* (uart_pc_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: uart_pc_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the receiver status register and the software
    *  buffer overflow status.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Side Effect:
    *  All status register bits are clear-on-read except
    *  uart_pc_RX_STS_FIFO_NOTEMPTY.
    *  uart_pc_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  uart_pc_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   uart_pc_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   uart_pc_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 uart_pc_ReadRxStatus(void) 
    {
        uint8 status;

        status = uart_pc_RXSTATUS_REG & uart_pc_RX_HW_MASK;

    #if (uart_pc_RX_INTERRUPT_ENABLED)
        if(uart_pc_rxBufferOverflow != 0u)
        {
            status |= uart_pc_RX_STS_SOFT_BUFF_OVER;
            uart_pc_rxBufferOverflow = 0u;
        }
    #endif /* (uart_pc_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: uart_pc_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. uart_pc_GetChar() is
    *  designed for ASCII characters and returns a uint8 where 1 to 255 are values
    *  for valid characters and 0 indicates an error occurred or no data is present.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Global Variables:
    *  uart_pc_rxBuffer - RAM buffer pointer for save received data.
    *  uart_pc_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  uart_pc_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  uart_pc_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 uart_pc_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (uart_pc_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        uart_pc_DisableRxInt();

        locRxBufferRead  = uart_pc_rxBufferRead;
        locRxBufferWrite = uart_pc_rxBufferWrite;

        if( (uart_pc_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = uart_pc_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= uart_pc_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            uart_pc_rxBufferRead = locRxBufferRead;

            if(uart_pc_rxBufferLoopDetect != 0u)
            {
                uart_pc_rxBufferLoopDetect = 0u;
                #if( (uart_pc_RX_INTERRUPT_ENABLED) && (uart_pc_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( uart_pc_HD_ENABLED )
                        if((uart_pc_CONTROL_REG & uart_pc_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            uart_pc_RXSTATUS_MASK_REG |= uart_pc_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        uart_pc_RXSTATUS_MASK_REG |= uart_pc_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end uart_pc_HD_ENABLED */
                #endif /* uart_pc_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = uart_pc_RXSTATUS_REG;
            if((rxStatus & uart_pc_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = uart_pc_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (uart_pc_RX_STS_BREAK | uart_pc_RX_STS_PAR_ERROR |
                                uart_pc_RX_STS_STOP_ERROR | uart_pc_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        uart_pc_EnableRxInt();

    #else

        rxStatus =uart_pc_RXSTATUS_REG;
        if((rxStatus & uart_pc_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = uart_pc_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (uart_pc_RX_STS_BREAK | uart_pc_RX_STS_PAR_ERROR |
                            uart_pc_RX_STS_STOP_ERROR | uart_pc_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (uart_pc_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: uart_pc_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, returns received character and error
    *  condition.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains status and LSB contains UART RX data. If the MSB is nonzero,
    *  an error has occurred.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 uart_pc_GetByte(void) 
    {
        
    #if (uart_pc_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        uart_pc_DisableRxInt();
        locErrorStatus = (uint16)uart_pc_errorStatus;
        uart_pc_errorStatus = 0u;
        uart_pc_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | uart_pc_ReadRxData() );
    #else
        return ( ((uint16)uart_pc_ReadRxStatus() << 8u) | uart_pc_ReadRxData() );
    #endif /* uart_pc_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: uart_pc_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received bytes available in the RX buffer.
    *  * RX software buffer is disabled (RX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty RX FIFO or 1 for not empty RX FIFO.
    *  * RX software buffer is enabled: returns the number of bytes available in 
    *    the RX software buffer. Bytes available in the RX FIFO do not take to 
    *    account.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Number of bytes in the RX buffer. 
    *    Return value type depends on RX Buffer Size parameter.
    *
    * Global Variables:
    *  uart_pc_rxBufferWrite - used to calculate left bytes.
    *  uart_pc_rxBufferRead - used to calculate left bytes.
    *  uart_pc_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 uart_pc_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (uart_pc_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        uart_pc_DisableRxInt();

        if(uart_pc_rxBufferRead == uart_pc_rxBufferWrite)
        {
            if(uart_pc_rxBufferLoopDetect != 0u)
            {
                size = uart_pc_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(uart_pc_rxBufferRead < uart_pc_rxBufferWrite)
        {
            size = (uart_pc_rxBufferWrite - uart_pc_rxBufferRead);
        }
        else
        {
            size = (uart_pc_RX_BUFFER_SIZE - uart_pc_rxBufferRead) + uart_pc_rxBufferWrite;
        }

        uart_pc_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((uart_pc_RXSTATUS_REG & uart_pc_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (uart_pc_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: uart_pc_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receiver memory buffer and hardware RX FIFO of all received data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  uart_pc_rxBufferWrite - cleared to zero.
    *  uart_pc_rxBufferRead - cleared to zero.
    *  uart_pc_rxBufferLoopDetect - cleared to zero.
    *  uart_pc_rxBufferOverflow - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may
    *  have remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM or FIFO buffer will be lost.
    *
    *******************************************************************************/
    void uart_pc_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        uart_pc_RXDATA_AUX_CTL_REG |= (uint8)  uart_pc_RX_FIFO_CLR;
        uart_pc_RXDATA_AUX_CTL_REG &= (uint8) ~uart_pc_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (uart_pc_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        uart_pc_DisableRxInt();

        uart_pc_rxBufferRead = 0u;
        uart_pc_rxBufferWrite = 0u;
        uart_pc_rxBufferLoopDetect = 0u;
        uart_pc_rxBufferOverflow = 0u;

        uart_pc_EnableRxInt();

    #endif /* (uart_pc_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: uart_pc_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  uart_pc__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  uart_pc__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  uart_pc__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  uart_pc__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  uart_pc__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  uart_pc_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  uart_pc_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void uart_pc_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(uart_pc_RXHW_ADDRESS_ENABLED)
            #if(uart_pc_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* uart_pc_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = uart_pc_CONTROL_REG & (uint8)~uart_pc_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << uart_pc_CTRL_RXADDR_MODE0_SHIFT);
                uart_pc_CONTROL_REG = tmpCtrl;

                #if(uart_pc_RX_INTERRUPT_ENABLED && \
                   (uart_pc_RXBUFFERSIZE > uart_pc_FIFO_LENGTH) )
                    uart_pc_rxAddressMode = addressMode;
                    uart_pc_rxAddressDetected = 0u;
                #endif /* End uart_pc_RXBUFFERSIZE > uart_pc_FIFO_LENGTH*/
            #endif /* End uart_pc_CONTROL_REG_REMOVED */
        #else /* uart_pc_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End uart_pc_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: uart_pc_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Sets the first of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #1 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void uart_pc_SetRxAddress1(uint8 address) 
    {
        uart_pc_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: uart_pc_SetRxAddress2
    ********************************************************************************
    *
    * Summary:
    *  Sets the second of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #2 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void uart_pc_SetRxAddress2(uint8 address) 
    {
        uart_pc_RXADDRESS2_REG = address;
    }

#endif  /* uart_pc_RX_ENABLED || uart_pc_HD_ENABLED*/


#if( (uart_pc_TX_ENABLED) || (uart_pc_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: uart_pc_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   uart_pc_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   uart_pc_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   uart_pc_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   uart_pc_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void uart_pc_SetTxInterruptMode(uint8 intSrc) 
    {
        uart_pc_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: uart_pc_WriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data into the transmit buffer to be sent when the bus is
    *  available without checking the TX status register. You must check status
    *  separately.
    *
    * Parameters:
    *  txDataByte: data byte
    *
    * Return:
    * None.
    *
    * Global Variables:
    *  uart_pc_txBuffer - RAM buffer pointer for save data for transmission
    *  uart_pc_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  uart_pc_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  uart_pc_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void uart_pc_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(uart_pc_initVar != 0u)
        {
        #if (uart_pc_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            uart_pc_DisableTxInt();

            if( (uart_pc_txBufferRead == uart_pc_txBufferWrite) &&
                ((uart_pc_TXSTATUS_REG & uart_pc_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                uart_pc_TXDATA_REG = txDataByte;
            }
            else
            {
                if(uart_pc_txBufferWrite >= uart_pc_TX_BUFFER_SIZE)
                {
                    uart_pc_txBufferWrite = 0u;
                }

                uart_pc_txBuffer[uart_pc_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                uart_pc_txBufferWrite++;
            }

            uart_pc_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            uart_pc_TXDATA_REG = txDataByte;

        #endif /*(uart_pc_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: uart_pc_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Reads the status register for the TX portion of the UART.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the TX status register, which is cleared on read.
    *  It is up to the user to handle all bits in this return value accordingly,
    *  even if the bit was not enabled as an interrupt source the event happened
    *  and must be handled accordingly.
    *
    *******************************************************************************/
    uint8 uart_pc_ReadTxStatus(void) 
    {
        return(uart_pc_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: uart_pc_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Puts a byte of data into the transmit buffer to be sent when the bus is
    *  available. This is a blocking API that waits until the TX buffer has room to
    *  hold the data.
    *
    * Parameters:
    *  txDataByte: Byte containing the data to transmit
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  uart_pc_txBuffer - RAM buffer pointer for save data for transmission
    *  uart_pc_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  uart_pc_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  uart_pc_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void uart_pc_PutChar(uint8 txDataByte) 
    {
    #if (uart_pc_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((uart_pc_TX_BUFFER_SIZE > uart_pc_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            uart_pc_DisableTxInt();
        #endif /* (uart_pc_TX_BUFFER_SIZE > uart_pc_MAX_BYTE_VALUE) && (CY_PSOC3) */

            locTxBufferWrite = uart_pc_txBufferWrite;
            locTxBufferRead  = uart_pc_txBufferRead;

        #if ((uart_pc_TX_BUFFER_SIZE > uart_pc_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            uart_pc_EnableTxInt();
        #endif /* (uart_pc_TX_BUFFER_SIZE > uart_pc_MAX_BYTE_VALUE) && (CY_PSOC3) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(uart_pc_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((uart_pc_TXSTATUS_REG & uart_pc_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            uart_pc_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= uart_pc_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            uart_pc_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((uart_pc_TX_BUFFER_SIZE > uart_pc_MAX_BYTE_VALUE) && (CY_PSOC3))
            uart_pc_DisableTxInt();
        #endif /* (uart_pc_TX_BUFFER_SIZE > uart_pc_MAX_BYTE_VALUE) && (CY_PSOC3) */

            uart_pc_txBufferWrite = locTxBufferWrite;

        #if ((uart_pc_TX_BUFFER_SIZE > uart_pc_MAX_BYTE_VALUE) && (CY_PSOC3))
            uart_pc_EnableTxInt();
        #endif /* (uart_pc_TX_BUFFER_SIZE > uart_pc_MAX_BYTE_VALUE) && (CY_PSOC3) */

            if(0u != (uart_pc_TXSTATUS_REG & uart_pc_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                uart_pc_SetPendingTxInt();
            }
        }

    #else

        while((uart_pc_TXSTATUS_REG & uart_pc_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        uart_pc_TXDATA_REG = txDataByte;

    #endif /* uart_pc_TX_INTERRUPT_ENABLED */
    }


    /*******************************************************************************
    * Function Name: uart_pc_PutString
    ********************************************************************************
    *
    * Summary:
    *  Sends a NULL terminated string to the TX buffer for transmission.
    *
    * Parameters:
    *  string[]: Pointer to the null terminated string array residing in RAM or ROM
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  uart_pc_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void uart_pc_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(uart_pc_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                uart_pc_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: uart_pc_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Places N bytes of data from a memory array into the TX buffer for
    *  transmission.
    *
    * Parameters:
    *  string[]: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of bytes to be transmitted. The type depends on TX Buffer
    *             Size parameter.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  uart_pc_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void uart_pc_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(uart_pc_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                uart_pc_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: uart_pc_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Writes a byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) to the transmit buffer.
    *
    * Parameters:
    *  txDataByte: Data byte to transmit before the carriage return and line feed.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  uart_pc_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void uart_pc_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(uart_pc_initVar != 0u)
        {
            uart_pc_PutChar(txDataByte);
            uart_pc_PutChar(0x0Du);
            uart_pc_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: uart_pc_GetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of bytes in the TX buffer which are waiting to be 
    *  transmitted.
    *  * TX software buffer is disabled (TX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty TX FIFO, 1 for not full TX FIFO or 4 for full TX FIFO.
    *  * TX software buffer is enabled: returns the number of bytes in the TX 
    *    software buffer which are waiting to be transmitted. Bytes available in the
    *    TX FIFO do not count.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Number of bytes used in the TX buffer. Return value type depends on the TX 
    *  Buffer Size parameter.
    *
    * Global Variables:
    *  uart_pc_txBufferWrite - used to calculate left space.
    *  uart_pc_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 uart_pc_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (uart_pc_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        uart_pc_DisableTxInt();

        if(uart_pc_txBufferRead == uart_pc_txBufferWrite)
        {
            size = 0u;
        }
        else if(uart_pc_txBufferRead < uart_pc_txBufferWrite)
        {
            size = (uart_pc_txBufferWrite - uart_pc_txBufferRead);
        }
        else
        {
            size = (uart_pc_TX_BUFFER_SIZE - uart_pc_txBufferRead) +
                    uart_pc_txBufferWrite;
        }

        uart_pc_EnableTxInt();

    #else

        size = uart_pc_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & uart_pc_TX_STS_FIFO_FULL) != 0u)
        {
            size = uart_pc_FIFO_LENGTH;
        }
        else if((size & uart_pc_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (uart_pc_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: uart_pc_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears all data from the TX buffer and hardware TX FIFO.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  uart_pc_txBufferWrite - cleared to zero.
    *  uart_pc_txBufferRead - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may have
    *  remained in the RAM.
    *
    * Side Effects:
    *  Data waiting in the transmit buffer is not sent; a byte that is currently
    *  transmitting finishes transmitting.
    *
    *******************************************************************************/
    void uart_pc_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        uart_pc_TXDATA_AUX_CTL_REG |= (uint8)  uart_pc_TX_FIFO_CLR;
        uart_pc_TXDATA_AUX_CTL_REG &= (uint8) ~uart_pc_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (uart_pc_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        uart_pc_DisableTxInt();

        uart_pc_txBufferRead = 0u;
        uart_pc_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        uart_pc_EnableTxInt();

    #endif /* (uart_pc_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: uart_pc_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   uart_pc_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   uart_pc_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   uart_pc_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   uart_pc_SEND_WAIT_REINIT - Performs both options: 
    *      uart_pc_SEND_BREAK and uart_pc_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  uart_pc_initVar - checked to identify that the component has been
    *     initialized.
    *  txPeriod - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  There are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Function will block CPU until transmission
    *     complete.
    *  2) User may want to use blocking time if UART configured to the low speed
    *     operation
    *     Example for this case:
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to initialize and use the interrupt to
    *     complete break operation.
    *     Example for this case:
    *     Initialize TX interrupt with "TX - On TX Complete" parameter
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     When interrupt appear with uart_pc_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The uart_pc_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void uart_pc_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(uart_pc_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(uart_pc_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == uart_pc_SEND_BREAK) ||
                (retMode == uart_pc_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                uart_pc_WriteControlRegister(uart_pc_ReadControlRegister() |
                                                      uart_pc_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                uart_pc_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = uart_pc_TXSTATUS_REG;
                }
                while((tmpStat & uart_pc_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == uart_pc_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == uart_pc_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = uart_pc_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & uart_pc_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == uart_pc_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == uart_pc_REINIT) ||
                (retMode == uart_pc_SEND_WAIT_REINIT) )
            {
                uart_pc_WriteControlRegister(uart_pc_ReadControlRegister() &
                                              (uint8)~uart_pc_CTRL_HD_SEND_BREAK);
            }

        #else /* uart_pc_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == uart_pc_SEND_BREAK) ||
                (retMode == uart_pc_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (uart_pc_PARITY_TYPE != uart_pc__B_UART__NONE_REVB) || \
                                    (uart_pc_PARITY_TYPE_SW != 0u) )
                    uart_pc_WriteControlRegister(uart_pc_ReadControlRegister() |
                                                          uart_pc_CTRL_HD_SEND_BREAK);
                #endif /* End uart_pc_PARITY_TYPE != uart_pc__B_UART__NONE_REVB  */

                #if(uart_pc_TXCLKGEN_DP)
                    txPeriod = uart_pc_TXBITCLKTX_COMPLETE_REG;
                    uart_pc_TXBITCLKTX_COMPLETE_REG = uart_pc_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = uart_pc_TXBITCTR_PERIOD_REG;
                    uart_pc_TXBITCTR_PERIOD_REG = uart_pc_TXBITCTR_BREAKBITS8X;
                #endif /* End uart_pc_TXCLKGEN_DP */

                /* Send zeros */
                uart_pc_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = uart_pc_TXSTATUS_REG;
                }
                while((tmpStat & uart_pc_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == uart_pc_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == uart_pc_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = uart_pc_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & uart_pc_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == uart_pc_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == uart_pc_REINIT) ||
                (retMode == uart_pc_SEND_WAIT_REINIT) )
            {

            #if(uart_pc_TXCLKGEN_DP)
                uart_pc_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                uart_pc_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End uart_pc_TXCLKGEN_DP */

            #if( (uart_pc_PARITY_TYPE != uart_pc__B_UART__NONE_REVB) || \
                 (uart_pc_PARITY_TYPE_SW != 0u) )
                uart_pc_WriteControlRegister(uart_pc_ReadControlRegister() &
                                                      (uint8) ~uart_pc_CTRL_HD_SEND_BREAK);
            #endif /* End uart_pc_PARITY_TYPE != NONE */
            }
        #endif    /* End uart_pc_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: uart_pc_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       uart_pc_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       uart_pc_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears uart_pc_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void uart_pc_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( uart_pc_CONTROL_REG_REMOVED == 0u )
            uart_pc_WriteControlRegister(uart_pc_ReadControlRegister() |
                                                  uart_pc_CTRL_MARK);
        #endif /* End uart_pc_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( uart_pc_CONTROL_REG_REMOVED == 0u )
            uart_pc_WriteControlRegister(uart_pc_ReadControlRegister() &
                                                  (uint8) ~uart_pc_CTRL_MARK);
        #endif /* End uart_pc_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* Enduart_pc_TX_ENABLED */

#if(uart_pc_HD_ENABLED)


    /*******************************************************************************
    * Function Name: uart_pc_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the receiver configuration in half duplex mode. After calling this
    *  function, the UART is ready to receive data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the transmitter
    *  configuration.
    *
    *******************************************************************************/
    void uart_pc_LoadRxConfig(void) 
    {
        uart_pc_WriteControlRegister(uart_pc_ReadControlRegister() &
                                                (uint8)~uart_pc_CTRL_HD_SEND);
        uart_pc_RXBITCTR_PERIOD_REG = uart_pc_HD_RXBITCTR_INIT;

    #if (uart_pc_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        uart_pc_SetRxInterruptMode(uart_pc_INIT_RX_INTERRUPTS_MASK);
    #endif /* (uart_pc_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: uart_pc_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the transmitter configuration in half duplex mode. After calling this
    *  function, the UART is ready to transmit data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the receiver configuration.
    *
    *******************************************************************************/
    void uart_pc_LoadTxConfig(void) 
    {
    #if (uart_pc_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        uart_pc_SetRxInterruptMode(0u);
    #endif /* (uart_pc_RX_INTERRUPT_ENABLED) */

        uart_pc_WriteControlRegister(uart_pc_ReadControlRegister() | uart_pc_CTRL_HD_SEND);
        uart_pc_RXBITCTR_PERIOD_REG = uart_pc_HD_TXBITCTR_INIT;
    }

#endif  /* uart_pc_HD_ENABLED */


/* [] END OF FILE */
