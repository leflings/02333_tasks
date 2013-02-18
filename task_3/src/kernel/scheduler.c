/*!
 * \file scheduler.c
 * \brief
 *  This file holds the scheduler code. 
 */

#include "kernel.h"
int last_switch = 0;

void
scheduler_called_from_system_call_handler(const register int schedule)
{
	int thread_running, thread_to_run;
	if(schedule) {
		/* in this case we must reschedule */
		last_switch = system_time;
		thread_to_run = thread_queue_dequeue(&ready_queue);
		cpu_private_data.thread_index = thread_to_run;
		return;
	}
	else
	{
		/* lets see if current thread has used up its quantum (~50ms) */
		if(system_time-last_switch > 10) {
			last_switch = system_time;
			/* put it back in the queue */
			thread_running = cpu_private_data.thread_index;
			thread_queue_enqueue(&ready_queue, thread_running);
			thread_to_run = thread_queue_dequeue(&ready_queue);
			cpu_private_data.thread_index = thread_to_run;
			return;
		}
	}
}

void
scheduler_called_from_timer_interrupt_handler(const register int thread_changed)
{

}
