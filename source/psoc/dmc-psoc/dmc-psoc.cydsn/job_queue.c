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
#include <stdlib.h>
#include "job_queue.h"


#define MAX_QUEUE_SIZE 10

struct queue main_queue;



struct queue{
    struct job* head;
    struct job* next;
    size_t size;
};

void init_queue()
{  
  main_queue.size = 0;
  main_queue.head = NULL;
  main_queue.next = NULL;
}

void job_enqueue(enum job_type type, void* data)
{
    //If more than MAX_QUEUE_SIZE jobs in queue. Ignore job enqueue.
    if (main_queue.size >= MAX_QUEUE_SIZE)
        return;
    
    struct job* new_job = (struct job*)malloc(sizeof(struct job));
    new_job->type = type;
    new_job->data = data;
    new_job->next_job = NULL;
    
    main_queue.head->next_job = new_job;
    main_queue.head = new_job;
    main_queue.size++;
}


void job_enqueue_packet(struct dmc_packet* job_packet){
    job_enqueue(JOB_TYPE_PACKET, (void*)job_packet);
    return;
}

void job_enqueue_timer(void* data){
    job_enqueue(JOB_TYPE_TIMER, data);
    return;
}

struct job* job_dequeue()
{
    //Check if queue is empty
    if (main_queue.size == 0)
        return NULL;
    
    struct job* temp_job = main_queue.next;
    main_queue.next = main_queue.next->next_job;
    
    main_queue.size--;
    return temp_job;    
}
