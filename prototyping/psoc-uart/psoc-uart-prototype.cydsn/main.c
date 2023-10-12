/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>

CY_ISR_PROTO(ISR_UART_rx_handler);
void handleByteReceived(uint8_t byteReceived);

int offset_weight1 = 374;
float64 divider_weight1 = 1201.3;
int offset_weight2 = 316;
float64 divider_weight2 = 1841.3;
float64 tara_weight1 = 0;
float64 tara_weight2 = 0;
float64 result = 0;
int weight = 1;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    char uartBuffer[256];
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    isr_uart_rx_StartEx(ISR_UART_rx_handler);
    UART_1_Start();
    
    // Start explaining program
    UART_1_PutString("UART test program started\r\n");

    for (;;)
    {
        snprintf(uartBuffer, sizeof(uartBuffer), "UART has recived\r\n"); //String is created
        UART_1_PutString(uartBuffer); //String is sent through UART   
    }
    
    
        
}

CY_ISR(ISR_UART_rx_handler)
{
    uint8_t bytesToRead = UART_1_GetRxBufferSize();
    while (bytesToRead > 0)
    {
        uint8_t byteReceived = UART_1_ReadRxData();
        UART_1_WriteTxData(byteReceived); // echo back
        
        handleByteReceived(byteReceived);
        
        bytesToRead--;
    }
}

void handleByteReceived(uint8_t byteReceived)
{
    switch(byteReceived)
    {
        case '1' :
        {
        }

    }
}

/* [] END OF FILE */
