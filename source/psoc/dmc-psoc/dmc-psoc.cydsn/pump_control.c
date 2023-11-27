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
#include "pump_control.h"
#include "project.h"


//Times a million
static uint32_t period_pr_cL = 2400;

//Used for calculating CL amount of liquid, to a timers period.
void pump_fluid(enum dmc_pump pump)
{
    
    switch (pump)
    {
    case PUMP_1:
        {
            //set_period(PUMP_TIMER_1, timer_calc);
            gpio_pump_1_Write(1);
            break;
        }
   case PUMP_2:
        {
            //set_period(PUMP_TIMER_2, timer_calc);
            gpio_pump_2_Write(1);
            break;
        }
    case PUMP_3:
        {
            //set_period(PUMP_TIMER_3, timer_calc);
            gpio_pump_3_Write(1);
            break;
        } 
    }
}

int is_pumping(enum dmc_pump pump)
{
    switch (pump)
    {
    case PUMP_1: return gpio_pump_1_Read(); 
    case PUMP_2: return gpio_pump_2_Read();
    case PUMP_3: return gpio_pump_3_Read();
    }
}

void stop_pump(enum dmc_pump pump)
{
    switch (pump)
    {
    case PUMP_1:
        {
            gpio_pump_1_Write(0); 
            break;
        }
   case PUMP_2:
        {
            gpio_pump_2_Write(0); 
            break;
        }
    case PUMP_3:
        {
            gpio_pump_3_Write(0); 
            break;
        } 
    }  
    
}

/* [] END OF FILE */
