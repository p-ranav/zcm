/*
 * Component Executor Thread
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.13
 */

#include "operation_queue.hpp"
#include "timer.hpp"

void timer_1_function() {
  std::cout << "TIMER_1_FUNCTION::Timer_1::Priority::50::Period::1000000000" << std::endl;
}

void timer_2_function() {
  std::cout << "TIMER_2_FUNCTION::Timer_2::Priority::40::Period::500000000" << std::endl;
}

int main() {

  operation_queue = new Operation_Queue();
  std::thread executor_thread = operation_queue->spawn();

  // Create a New Timer - Name, Priority, Period (ns)
  Timer timer_1("Timer_1", 50, 1000000000, timer_1_function);  
  Timer timer_2("Timer_2", 40, 500000000, timer_2_function);  

  std::thread timer_1_thread = timer_1.spawn();
  std::thread timer_2_thread = timer_2.spawn();

  timer_1_thread.join();
  timer_2_thread.join();
  executor_thread.join();

  return 0;
}
