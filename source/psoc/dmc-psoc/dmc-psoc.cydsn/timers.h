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
#pragma once

#include <stdio.h>
#include <stdint.h>

//uint16_t timer_1_counter;
//uint16_t timer_1_finished = 0;

//Timer has a periodtime between 2ms (2 value) and 150s (60000 value). This can be modied to fit the needs of a drink.
//master_timer_WritePeriod(liquid_amount);

enum dmc_pump_timer
{
    PUMP_TIMER_1 = 1,
    PUMP_TIMER_2 = 2,
    PUMP_TIMER_3 = 3,
};

enum timer_action_type
    {
        TIMER_ACTION_STOP_PUMP,
        TIMER_ACTION_CHECK_WEIGHT,
    };

struct timer_action{
    enum timer_action_type type;
    enum dmc_pump_timer origin;
};


void init_timers();
void set_period(enum dmc_pump_timer timer, uint16_t period);