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
#include "dmc_pump_control.h"
#include "project.h"



    int pump_1_pumping = 0;
    int pump_2_pumping = 0;
    int pump_3_pumping = 0;

    
void pump_fluid(enum dmc_pump pump)
{
    
    switch (pump)
    {
    case PUMP_1:
        {
            pump_1_Write(1);
            pump_1_pumping = 1;
            break;
        }
   case PUMP_2:
        {
            pump_2_Write(1);
            pump_2_pumping = 1;
            break;
        }
    case PUMP_3:
        {
            pump_3_Write(1);
            pump_3_pumping = 1;
            break;
        } 
    }
}

int is_pumping(enum dmc_pump pump)
{
    switch (pump)
    {
    case PUMP_1: return pump_1_pumping; 
    case PUMP_2: return pump_2_pumping;
    case PUMP_3: return pump_3_pumping;
    }
}

void stop_pump(enum dmc_pump pump)
{
    switch (pump)
    {
    case PUMP_1:
        {
            pump_1_Write(0);
            pump_1_pumping = 0;
            break;
        }
   case PUMP_2:
        {
            pump_2_Write(0); 
            pump_2_pumping = 0;
            break;
        }
    case PUMP_3:
        {
            pump_3_Write(0);
            pump_3_pumping = 0;
            break;
        } 
    }  
    
}

/* [] END OF FILE */
