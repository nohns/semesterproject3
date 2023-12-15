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

#include "dmc_timers.h"
#include "project.h"
#include "dmc_job_queue.h"


int pump_timer_1_trigger = 0;
int pump_timer_2_trigger = 0;
int pump_timer_3_trigger = 0;


void enqueue_timer_stop(enum dmc_pump_timer pump_timer)
{
    struct dmc_timer_action* action = (struct dmc_timer_action*)malloc(sizeof(struct dmc_timer_action));
    action->type = TIMER_ACTION_STOP_PUMP;
    action->origin = pump_timer;
    
    job_enqueue_timer(action);
}

void enqueue_timer_check()
{
    struct dmc_timer_action* action = (struct dmc_timer_action*)malloc(sizeof(struct dmc_timer_action));
    action->type = TIMER_ACTION_CHECK_WEIGHT;
    job_enqueue_timer(action);
}


CY_ISR(ISR_pump_timer_1_handler)
{
    if (pump_timer_1_trigger)
    {
        enqueue_timer_stop(PUMP_TIMER_1);
        pump_timer_1_trigger = 0;
    }
    
}

CY_ISR(ISR_pump_timer_2_handler)
{
    if (pump_timer_2_trigger)
    {
        enqueue_timer_stop(PUMP_TIMER_2);
        pump_timer_2_trigger = 0;
    }
}

CY_ISR(ISR_pump_timer_3_handler)
{
    if (pump_timer_3_trigger)
    {
        enqueue_timer_stop(PUMP_TIMER_3);
        pump_timer_3_trigger = 0;
    }
}
CY_ISR(ISR_check_weight_timer_handler)
{
    
    enqueue_timer_check();
    check_weight_timer_ReadStatusRegister();
    
}

void dmc_timer_action_free(struct dmc_timer_action *timer_action)
{
    free(timer_action);
}

void init_timers()
{
    pump_timer_1_Start();
    pump_timer_2_Start();
    pump_timer_3_Start();
    check_weight_timer_Start();
    isr_pump_timer_1_StartEx(ISR_pump_timer_1_handler);
    isr_pump_timer_2_StartEx(ISR_pump_timer_2_handler);
    isr_pump_timer_3_StartEx(ISR_pump_timer_3_handler);
    isr_check_weight_timer_StartEx(ISR_check_weight_timer_handler);
    return;
}


void 
set_period(enum dmc_pump_timer timer, uint16_t period)
{
    switch (timer)
    {
    case PUMP_TIMER_1:
    {
        pump_timer_1_WriteCounter(period);
        pump_timer_1_ReadStatusRegister();
        pump_timer_1_trigger = 1;
        break;
    }
    case PUMP_TIMER_2:
    {
        pump_timer_2_WriteCounter(period);
        pump_timer_2_ReadStatusRegister();
        pump_timer_2_trigger = 1;
        break;
    }
    case PUMP_TIMER_3:
    {   
        pump_timer_3_WriteCounter(period);
        pump_timer_3_ReadStatusRegister();
        pump_timer_3_trigger = 1;
        break;
    }
    }
    return;
}

