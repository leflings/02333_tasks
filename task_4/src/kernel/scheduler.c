/*!
 * \file scheduler.c
 * \brief
 *  This file holds the scheduler code. 
 */

#include "kernel.h"
#define MAX_TICKS 6

void
scheduler_called_from_system_call_handler(const register int schedule)
{
	int thread_running, thread_to_run;
	if(schedule) {
		/* in this case we must reschedule */
		cpu_private_data.ticks_left_of_time_slice = MAX_TICKS;
		cpu_private_data.thread_index = thread_queue_dequeue(&ready_queue);
		return;
	}
	/*
	else
	{
		if(system_time-last_switch > 10) {
			last_switch = system_time;
			thread_running = cpu_private_data.thread_index;
			thread_queue_enqueue(&ready_queue, thread_running);
			thread_to_run = thread_queue_dequeue(&ready_queue);
			cpu_private_data.thread_index = thread_to_run;
			return;
		}
	}
	*/
}

void
scheduler_called_from_timer_interrupt_handler(const register int thread_changed)
{
	if(thread_changed)
	{
		/* We must reset the time_slice */
		cpu_private_data.ticks_left_of_time_slice = MAX_TICKS;
		return;
	}
	else
	{
		/* decrement time slice and check if its expired */
		if(--cpu_private_data.ticks_left_of_time_slice < 1)
		{
			/* it's expired, stop execution, put in back of quere and fetch next */
			thread_queue_enqueue(&ready_queue, cpu_private_data.thread_index);
			cpu_private_data.thread_index = thread_queue_dequeue(&ready_queue);
			cpu_private_data.ticks_left_of_time_slice = MAX_TICKS;
			return;
		}
	}
}
