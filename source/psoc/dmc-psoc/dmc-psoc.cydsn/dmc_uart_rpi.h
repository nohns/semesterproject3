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


#ifndef UART_RPI_H
#define UART_RPI_H
    
#include "..\..\..\common\hw\include\packet.h"


void init_uart_rpi(int (*raise_flag)(struct dmc_packet*) );
void init_uart_rpi_simple();
void send_out_of_order_message(struct dmc_packet_out_of_order* out_of_order_message);
void send_machine_ok_message(struct dmc_packet_machine_ok* machine_ok_message);
void send_container_volume_measured(struct dmc_packet_container_volume_measured* measured_volume_packet);


/* [] END OF FILE */



#endif //UART_RPI_H