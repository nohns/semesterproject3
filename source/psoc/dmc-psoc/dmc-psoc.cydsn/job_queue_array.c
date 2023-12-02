#include "packet.h"

enum job_type
{
  JOB_TYPE_UNDEFINED,
  JOB_TYPE_PACKET,
  JOB_TYPE_TIMER,
};

struct job
{
  enum job_type type;
  void         *data;
};

#define MAX_QUEUE_JOBS 10

volatile int        queue_size = 0;
volatile struct job queue[MAX_QUEUE_JOBS];

void job_enqueue_packet(struct dmc_packet *packet)
{
  // Enqueue packet
  job_enqueue(JOB_TYPE_PACKET, (void *)packet);
}

void job_enqueue_timer(void *data)
{
  // Enqueue timer
  job_enqueue(JOB_TYPE_TIMER, data);
}

void job_enqueue(enum job_type type, void *data)
{
  if (queue_size == MAX_QUEUE_JOBS)
  {
    return;
  }

  queue[queue_size].type = type;
  queue[queue_size].data = data;
  queue_size++;
}

struct job job_dequeue()
{
  struct job next = queue[0];

  // Shift elements downwards
  for (int i = 1; i < queue_size; i++)
  {
    queue[i - 1] = queue[i];
  }

  queue_size--;
  return next;
}