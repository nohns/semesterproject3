/*
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

#include "job_queue.h"
#include "project.h"
#include "uart_rpi.h"
#include "stdio.h"

const char *byte_to_binary(uint8_t x)
{
    static char b[9];
    b[0] = '\0';

    int z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

CY_ISR_PROTO(ISR_uart_rpi_rx_handler);


struct dmc_packet* current_packet;
int discard_packet = 0;


int (*raise_flag_handler)(struct dmc_packet*);


void init_uart_rpi(int (*raise_flag)(struct dmc_packet*) )
{   
    
    raise_flag_handler = raise_flag;
    
    isr_uart_rpi_rx_StartEx(ISR_uart_rpi_rx_handler);
    
    uart_rpi_Start();
}


void init_uart_rpi_simple()
{
    isr_uart_rpi_rx_StartEx(ISR_uart_rpi_rx_handler);
    
    uart_rpi_Start();
}

void handleByteReceived(uint8_t byteReceived)
{
    char buf[255];
    snprintf(buf, sizeof(buf), "Calling handleByteRecived. byte = %s\r\n", byte_to_binary(byteReceived));
    uart_pc_PutString(buf);
   //Put first byte through packet init
   if (current_packet == NULL)
    {
        uart_pc_PutString("NULL packet found\r\n");
        //TO DO: Validate packet type is valid        
        current_packet = dmc_packet_init((enum dmc_packet_type)byteReceived);
        discard_packet = raise_flag_handler(current_packet);
        if (!dmc_packet_complete(current_packet) || discard_packet)
            return;
        
        job_enqueue_packet(current_packet);
        current_packet = NULL;
        return;  
    }
   
    //Append byterecived to current_packet
    dmc_packet_append_byte(current_packet, (unsigned char)byteReceived);
    
    //Push packet to job_queue if payload is complete
    if (dmc_packet_complete(current_packet))
    {
        uart_pc_PutString("dmc packet complete\r\n");
        if (!discard_packet)
            job_enqueue_packet(current_packet);
        current_packet = NULL;
    }
    
    uart_pc_PutString("Finished byte recived\r\n");
}


CY_ISR(ISR_uart_rpi_rx_handler)
{
    uint8_t bytesToRead = uart_rpi_GetRxBufferSize();
    while (bytesToRead > 0)
    {
        uint8_t byteReceived = uart_rpi_ReadRxData();
        uart_pc_WriteTxData(byteReceived); // echo into PC for debugging - program sometime be buggin
        
        handleByteReceived(byteReceived);
        
        bytesToRead--;
    }
}


/* [] END OF FILE */

/* [] END OF FILE */
