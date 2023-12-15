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
#ifndef PUMP_H
#define PUMP_H
    

enum dmc_pump
{
    PUMP_1 = 1,
    PUMP_2 = 2,
    PUMP_3 = 3,
};

void pump_fluid(enum dmc_pump pump);

void stop_pump(enum dmc_pump pump);

int is_pumping(enum dmc_pump pump);

#endif //PUMP_H
/* [] END OF FILE */
