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
#include "dmc_job_queue.h"
#include "dmc_pump_control.h"
#include <stdio.h>
#include "dmc_weight.h"
#include "dmc_uart_rpi.h"


uint8_t MAX_VOLUME_IN_CONTAINER = 70;
int pump_1_periods_pr_cl = 2400;
int pump_2_periods_pr_cl = 2960;
int pump_3_periods_pr_cl = 2960;


int PERIODS_PR_CL(enum dmc_pump_timer pump_timer)
{
    switch (pump_timer)
    {
    case PUMP_TIMER_1: return pump_1_periods_pr_cl;
    case PUMP_TIMER_2: return pump_2_periods_pr_cl;
    case PUMP_TIMER_3: return pump_3_periods_pr_cl;
    }

}

uint16_t weight_to_cl()
{   
    
    uint16_t temp_result = (current_weight->result - current_weight->tara - current_weight->min);
    uint16_t temp_max = (current_weight->max - current_weight->min);
    uint16_t temp_min = current_weight->min;
    
    
    //If value is extraordinary big, it is error from weight
    if (temp_result > 2500)
        temp_result = 0;
    
    
    double percent = (double)temp_result/(double)temp_max;
    
    double print = percent*70;
    
    if (percent > 120 || percent < 0)
        return 0;
    
    return (double)(percent*MAX_VOLUME_IN_CONTAINER);
    
    
}

void container_amount_init()
{
    for (int weight_to_check = 1; weight_to_check <= 3; weight_to_check++)
            {
                CyDelay(10);
                set_current_weight((enum dmc_weight_number)weight_to_check);
                struct dmc_packet_container_volume_measured packet;
                packet.container = (uint8_t)current_weight->weight_number;
                packet.volume = weight_to_cl();
                send_container_volume_measured(&packet);
            }
}


int is_weight_within_lower_threshold(uint16_t measured_weight_value)
{
    return measured_weight_value > current_weight->min - 10;
}

void set_out_of_order_reason(struct dmc_packet_out_of_order* out_of_order_packet)
{
    if (weight1.out_of_order)
        out_of_order_packet->reason = DMC_PACKET_OUT_OF_ORDER_REASON_FLUID_CONTAINER_1_REMOVED;
    if (weight2.out_of_order)
        out_of_order_packet->reason = DMC_PACKET_OUT_OF_ORDER_REASON_FLUID_CONTAINER_2_REMOVED;
    if (weight3.out_of_order)
        out_of_order_packet->reason = DMC_PACKET_OUT_OF_ORDER_REASON_FLUID_CONTAINER_3_REMOVED;       
}


void do_periodic_weight_check()
{
   
    for (int weight_to_check = 1; weight_to_check <= 3; weight_to_check++)
    {
        set_current_weight((enum dmc_weight_number)weight_to_check);
    
        uint16_t measured_weight_value = measure_weight_value();

        if (!is_weight_within_lower_threshold(measured_weight_value))
            {
                if (!weight1.out_of_order && !weight2.out_of_order && !weight3.out_of_order)
                {
                    current_weight->out_of_order = 1;
                    struct dmc_packet_out_of_order out_of_order_message;
                    set_out_of_order_reason(&out_of_order_message);
                    send_out_of_order_message(&out_of_order_message);
                }
                
                current_weight->out_of_order = 1;
            }
        else if (current_weight->out_of_order)
            {
                current_weight->out_of_order = 0;
                               
                if (!weight1.out_of_order && !weight2.out_of_order && !weight3.out_of_order)
                {
                    struct dmc_packet_machine_ok machine_ok;
                    send_machine_ok_message(&machine_ok);
                    current_weight->result = measured_weight_value;
                    
                    //Sending updated weight
                    struct dmc_packet_container_volume_measured packet;
                    packet.container = (uint8_t)current_weight->weight_number;
                    packet.volume = weight_to_cl();
                    send_container_volume_measured(&packet);
                    
                } else {
                    struct dmc_packet_out_of_order out_of_order_message;
                    set_out_of_order_reason(&out_of_order_message);
                    send_out_of_order_message(&out_of_order_message);
                }
            }
        if (is_pumping((enum dmc_pump)weight_to_check) && !current_weight->out_of_order)
        {
            current_weight->result = measured_weight_value;
            struct dmc_packet_container_volume_measured packet;
            packet.container = (uint8_t)current_weight->weight_number;
            packet.volume = weight_to_cl();
            send_container_volume_measured(&packet);
            
        }
       
    }
}

 /*
        else if (!current_weight->out_of_order)
        {
            int diff = measured_weight_value - current_weight->result;
            if (diff < 25 && diff > -25)
                current_weight->tara = measured_weight_value - current_weight->result;
        }
        */
//Remove this 

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
                     
            uint16_t timer_period = requested_drink.amount*PERIODS_PR_CL((enum dmc_pump_timer)requested_drink.container);
            
            set_period((enum dmc_pump_timer)requested_drink.container, timer_period);
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
            
            //Make final measurement
            set_current_weight((enum dmc_weight_number)action->origin);
            current_weight->result = measure_weight_value();
            break;
        }
    }  
    dmc_timer_action_free(action);
}


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    init_uart_rpi_simple(); //Initiate uart and ISR
    
    init_timers(); //Initaite timer, ISR and start timer
    
    weight_init(); //Start ADC and make irst measurement
    
    container_amount_init(); //Send current weights to RPi
  
    for(;;)
    {
        struct job current_job;
        
        if (job_dequeue(&current_job) != 0) {
            continue;
        }
        switch (current_job.type)
        {
            case JOB_TYPE_PACKET: //Job sent from uart
            {
                handle_packet((struct dmc_packet*)current_job.data);
                break;
            }
            case JOB_TYPE_TIMER: //Job sent from timer
            {
                handle_timer((struct dmc_timer_action*)current_job.data);
                break;
            }
        }
        
    }    
}



