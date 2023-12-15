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
#ifndef TIMERS_H
#define TIMERS_H

#include <stdio.h>
#include <stdint.h>


enum dmc_pump_timer
{
    PUMP_TIMER_1 = 1,
    PUMP_TIMER_2 = 2,
    PUMP_TIMER_3 = 3,
};

enum dmc_timer_action_type
    {
        TIMER_ACTION_STOP_PUMP,
        TIMER_ACTION_CHECK_WEIGHT,
    };

struct dmc_timer_action{
    enum dmc_timer_action_type type;
    enum dmc_pump_timer origin;
};

void dmc_timer_action_free(struct dmc_timer_action *timer_action);
void init_timers();
void set_period(enum dmc_pump_timer timer, uint16_t period);


#endif //TIMERS_H