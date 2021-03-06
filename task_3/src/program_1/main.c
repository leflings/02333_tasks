/*! \file main.c
 *      \brief The second user program - never ending loop that busy waits
 *             100 clock ticks in a CPU time consuming way. It does
 *             use system calls which allows the system to switch to other
 *             processes.
 *
 */

#include <scwrapper.h>

void 
main(int argc, char* argv[])
{
	int last;
 while(1)
 {
  long curr_time=time();

  while((time()-curr_time) < 200);

  printhex(time()-last);
  prints("  Pong ++\n");
  last = time();
 }
}
