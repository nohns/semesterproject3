
/*
Our own implemention of a queue based on a linked list

*/

#ifndef JOB_QUEUE_H
#define JOB_QUEUE_H

#include "..\..\..\common\hw\include\packet.h"
#include "dmc_timers.h"

enum job_type {
    JOB_TYPE_UNDEFINED,
    JOB_TYPE_PACKET,
    JOB_TYPE_TIMER,
};

struct job {
   enum job_type type;
   void* data;
    
};

void init_queue();
void job_enqueue_packet(struct dmc_packet* job_packet);
struct dmc_packet* job_dequeue_packet();
int job_dequeue(struct job* next);
void job_enqueue_timer(struct dmc_timer_action* action);

#endif //JOB_QUEUE_H