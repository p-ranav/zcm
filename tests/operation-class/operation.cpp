#include <iostream>
#include <string>
#include "operation_queue.hpp"

void timer_function() {
  std::cout << "Timer" << std::endl;
}

void subscriber_function(std::string message) {
  std::cout << "Subscriber " << message << std::endl;
}

int main() {

  Operation timer_operation("timer_operation", 50, timer_function);
  Operation subscriber_operation("subscriber_operation", 60, 
				 std::bind(subscriber_function, "received_message"));

  Operation_Queue new_queue;
  new_queue.enqueue(timer_operation);
  new_queue.enqueue(subscriber_operation);
  std::thread executor_thread = new_queue.spawn();

  executor_thread.join();

  return 0;
}
