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

/* [] END OF FILE */

#include "timers.h"
#include "project.h"
//#include "job_queue.h"






CY_ISR(ISR_pump_timer_1_handler)
{
    pump_timer_1_Stop();
    //job_enqueue_timer(stop pump 1)
    
}
CY_ISR(ISR_pump_timer_2_handler)
{
    pump_timer_2_Stop();   
}
CY_ISR(ISR_pump_timer_3_handler)
{
    pump_timer_3_Stop();   
}
CY_ISR(ISR_check_weight_timer_handler)
{
    
}


void init_timers()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_pump_timer_1_StartEx(ISR_pump_timer_1_handler);
    isr_pump_timer_2_StartEx(ISR_pump_timer_2_handler);
    isr_pump_timer_3_StartEx(ISR_pump_timer_3_handler);
    isr_check_weight_timer_StartEx(ISR_check_weight_timer_handler);
    
    return;
}


void set_period(enum dmc_pump_timer timer, uint16_t period)
{
    switch (timer)
    {
    case PUMP_TIMER_1:
    {
        pump_timer_1_WritePeriod(period);
        pump_timer_1_Start();
        break;
    }
    case PUMP_TIMER_2:
    {
        pump_timer_2_WritePeriod(period);
        pump_timer_2_Start();
        break;
    }
    case PUMP_TIMER_3:
    {
        pump_timer_3_WritePeriod(period);
        pump_timer_3_Start();
        break;
    }
    }
    return;
}
