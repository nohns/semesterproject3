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
#include "packet_uart.h"

struct dmc_packet* current_packet;
int discard_packet = 0;


int (*raise_flag_handler)(struct dmc_packet*);

CY_ISR_PROTO(ISR_UART_rx_handler);

void init_uart(int (*raise_flag)(struct dmc_packet*) )
{   
    raise_flag_handler = raise_flag;
    
    isr_uart_rx_StartEx(ISR_UART_rx_handler);
    
    UART_1_Start();
}

void handleByteReceived(uint8_t byteReceived)
{
    
   //Put first byte through packet init
   if (current_packet == NULL)
    {
        //TO DO: Validate packet type is valid        
        current_packet = dmc_packet_init((enum dmc_packet_type)byteReceived);
        discard_packet = raise_flag_handler(current_packet);
        return;
            
            
    }
   
    //Append byterecived to current_packet
    dmc_packet_append_byte(current_packet, (unsigned char)byteReceived);
    
    //Push packet to job_queue if payload is complete
    if (dmc_packet_complete(current_packet))
    {
        if (!discard_packet)
            job_enqueue_packet(current_packet);
        current_packet = NULL;
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




/* [] END OF FILE */
