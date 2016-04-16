#include <iostream>
#include <string>
#include "operation_queue.hpp"
#include "timer.hpp"

void timer_function() {
  std::cout << "Timer Operation Function" << std::endl;
}

int main() {

  operation_queue = new Operation_Queue();
  std::thread executor_thread = operation_queue->spawn();

  Timer new_timer("timer_operation", 50, 1000000000, timer_function);
  std::thread new_timer_thread = new_timer.spawn();

  new_timer_thread.join();
  executor_thread.join();

  return 0;
}
