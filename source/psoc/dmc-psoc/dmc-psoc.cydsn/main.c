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
#include "project.h"
#include "job_queue.h"
#include "pump_control.h"
#include <stdio.h>
#include "weight.h"
#include "uart_rpi.h"
#include "uart_pc.h"


int MAX_VOLUME_IN_CONTAINER = 70;
int PROCENTAGE_OF_MAX = 5;
int PERIODS_PR_CL = 2400;


int weight_to_cl(enum dmc_weight_number weight_to_calculate)
{
    set_current_weight(weight_to_calculate);
    
    return ((((current_weight->result - current_weight->min) * 1000)  
            /((current_weight->max - current_weight -> min)) * 1000))//this is used for calculating the procentage of liquid in the container
            * MAX_VOLUME_IN_CONTAINER;
}

int is_weight_within_lower_threshold(uint16_t measured_weight_value)
{
    uint16_t lower_threshold = measured_weight_value - (current_weight->max*PROCENTAGE_OF_MAX); //Fix procentage of max
    
    return (current_weight->result > lower_threshold);
}

int is_weight_within_upper_threshold(uint16_t measured_weight_value)
{
    uint16_t upper_threshold = measured_weight_value + (current_weight->max*PROCENTAGE_OF_MAX);
    
    return (current_weight->result < upper_threshold);
}

void do_periodic_weight_check()
{
    for (enum dmc_weight_number weight_to_check = WEIGHT_1; weight_to_check <= WEIGHT_3; weight_to_check++)
    {
        set_current_weight(weight_to_check);
        uint16_t measured_weight_value = measure_weight_value(weight_to_check);
        
        if (!is_pumping((enum dmc_pump)weight_to_check))
        {
            if (!is_weight_within_lower_threshold(measured_weight_value)){} //Ignore measurement
                //SEND ERROR ON NO IM DIEING - SOMEBODY STOLE THE DAMN 
            
            else if (!is_weight_within_upper_threshold(measured_weight_value))
                current_weight->result = measured_weight_value;
            
            else 
            {
                //TARA
                current_weight->tara = current_weight->result - measured_weight_value;
            }
           
        }
        else current_weight->result = measured_weight_value;        
    }
}


int raise_flag(struct dmc_packet *packet_to_check)
{
    switch(packet_to_check->type) {
        case DMC_PACKET_USER_CONFIRM:
        {
            return 1;
        }
        default:
            return 0;
    }
}

void handle_packet(struct dmc_packet* packet){
    
    switch(packet->type)
    {
        case DMC_PACKET_FLUID_POUR_REQUESTED:
        {
            struct dmc_packet_fluid_pour_requested requested_drink;
            dmc_packet_unmarshal_fluid_pour_requested(&requested_drink, packet);
            pump_fluid((enum dmc_pump)requested_drink.container);
            uint16_t timer_period = requested_drink.amount*PERIODS_PR_CL;
            set_period((enum dmc_pump_timer)requested_drink.container, timer_period);
            break;
        }
        case DMC_PACKET_USER_CONFIRM:
        {
            //To do: Implement with touchscreen
            break;
        }
        
    }
    
    dmc_packet_free(packet);
}

void handle_timer(struct dmc_timer_action* action)
{
    switch (action->type)
    {
    case TIMER_ACTION_CHECK_WEIGHT:
        {
            do_periodic_weight_check();
            break;
        }
    case TIMER_ACTION_STOP_PUMP:
        {
            stop_pump((enum dmc_pump)action->origin);
            break;
        }
    }  
    dmc_timer_action_free(action);
}


int main(void)
{
    uart_pc_Start();
    uart_pc_PutString("Program starting :)\r\n");
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    init_queue();
    init_uart_rpi(raise_flag);
    
    init_timers();
    
    uart_pc_PutString("Program starting :)\r\n");
    
    struct job* current_job;
    
    for(;;)
    {
        
        //uart_pc_PutString("Checking queue\r\n");
        current_job = job_dequeue();
        
        
        if (current_job == NULL)
            continue;
            
        switch (current_job->type)
        {
            case JOB_TYPE_UNDEFINED:
            {
                uart_pc_PutString("Found job with type: UNDEFINED\r\n");
                //Doo doo fart
                break;
            }
            case JOB_TYPE_PACKET:
            {
                uart_pc_PutString("Found job with type: PACKET\r\n");
                handle_packet((struct dmc_packet*)current_job->data);
                
                //Piss boy 123
                break;
            }
            case JOB_TYPE_TIMER:
            {
                uart_pc_PutString("Found job with type: TIMER\r\n");
                handle_timer((struct timer_action*)current_job->data);
                //Martin er en so
                break;
            }
            default: uart_pc_PutString("Found job with type: DEFAULT\r\n");
            break;
        }
    }    
}


/*
//UART_1_PutString("Scale application started\r\n");
    uint16_t counter;
    uint16_t procent;
    
    pump_fluid(PUMP_1, 20);

    for(;;)
    {
        counter = pump_timer_1_ReadCounter();
        counter = 60000-counter;
        procent = ((float)counter/60000)*100;
        snprintf(uartBuffer, sizeof(uartBuffer), "Pump 1 status: %d procent \n\r", procent);
        UART_1_PutString(uartBuffer);
        CyDelay(100);
    }*/



