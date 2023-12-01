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
#include "pc_uart.h"


void echo_uart(const char* string)
{
    uart_pc_PutStringConst(string);
}

void init_uart_pc()
{
    uart_pc_Start();

}



/* [] END OF FILE */
