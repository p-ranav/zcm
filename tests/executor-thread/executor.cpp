/*
 * Component Executor Thread
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.13
 */

#include "operation_queue.hpp"
#include "timer.hpp"

int main() {

  operation_queue = new Operation_Queue();

  // Create a New Timer - Name, Priority, Period (ns)
  Timer timer_1("Timer_1", 50, 1000000000);  
  Timer timer_2("Timer_2", 50, 500000000);  

  std::thread timer_1_thread = timer_1.spawn();
  std::thread timer_2_thread = timer_2.spawn();

  timer_1_thread.join();
  timer_2_thread.join();

  return 0;
}
