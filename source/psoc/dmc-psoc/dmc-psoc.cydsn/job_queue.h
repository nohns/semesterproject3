
/*
Our own implemention of a queue based on a linked list

*/

#ifndef JOB_QUEUE_H
#define JOB_QUEUE_H

#include "..\..\..\common\hw\include\packet.h"

enum job_type {
    JOB_TYPE_UNDEFINED,
    JOB_TYPE_PACKET,
    JOB_TYPE_TIMER,
};

struct job {
   enum job_type type;
   void* data;
   struct job *next_job;
};

void init_queue();
void job_enqueue_packet(struct dmc_packet* job_packet);
struct dmc_packet* job_dequeue_packet();
struct job* job_dequeue();
void job_enqueue_timer(void* data);

#endif //JOB_QUEUE_H