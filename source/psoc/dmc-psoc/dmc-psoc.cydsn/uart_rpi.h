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
#include "project.h"

void init_uart_rpi(int (*raise_flag)(struct dmc_packet*) );
void init_uart_rpi_simple();


/* [] END OF FILE */



#endif //UART_RPI_H