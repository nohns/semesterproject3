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

#include "dmc_job_queue.h"
#include "project.h"
#include "dmc_uart_rpi.h"
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



void uart_send_packet(struct dmc_packet* packet) {
    
    // Send type as first byte
    uart_rpi_WriteTxData((uint8_t)packet->type);
    
    // Send all data bytes
    for (size_t i = 0; i < packet->data_len; i++) {
        uart_rpi_WriteTxData((uint8_t)packet->data[i]);
    }
}


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


void handle_byte_received(uint8_t byteReceived)
{    
    if (byteReceived == 0)
    {
        return;
    }
    
   //Put first byte through packet init
   if (current_packet == NULL)
{
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

        if (!discard_packet)
            job_enqueue_packet(current_packet);
        current_packet = NULL;
    }
}


CY_ISR(ISR_uart_rpi_rx_handler)
{
    
    while (uart_rpi_GetRxBufferSize() != 0)
    {
        uint8_t byteReceived = uart_rpi_ReadRxData();
        handle_byte_received(byteReceived);
        
    }
    
}
void send_out_of_order_message(struct dmc_packet_out_of_order* out_of_order_message)
{
    struct dmc_packet *base = NULL;
    dmc_packet_marshal_out_of_order(&base, out_of_order_message);
    uart_send_packet(base);
    dmc_packet_free(base);
}

void send_machine_ok_message(struct dmc_packet_machine_ok* machine_ok_message)
{
    struct dmc_packet *base = NULL;
    dmc_packet_marshal_machine_ok(&base, machine_ok_message);
    uart_send_packet(base);
    dmc_packet_free(base);
}

void send_container_volume_measured(struct dmc_packet_container_volume_measured* measured_volume_packet)
{
    struct dmc_packet *base = NULL;
    dmc_packet_marshal_container_volume_measured(&base, measured_volume_packet);
    uart_send_packet(base);
    dmc_packet_free(base);
}


/* [] END OF FILE */

/* [] END OF FILE */
