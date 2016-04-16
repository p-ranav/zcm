#include <iostream>
#include <string>
#include "operation_queue.hpp"
#include "timer.hpp"
#include "publisher.hpp"
#include "subscriber.hpp"

void timer_function() {
  Publisher timer_pub("timer_pub", "tcp://*:5559");
  timer_pub.publish("timer_message 12345");
}

void subscriber_function(std::string received_message) {
  std::cout << "Subscriber Operation : Received : " << received_message << std::endl;  
}

int main() {

  operation_queue = new Operation_Queue();
  std::thread executor_thread = operation_queue->spawn();

  Subscriber new_subscriber("subscriber_operation", 
			    60, 
			    "timer_message", 
			    "tcp://localhost:5559", 
			    std::bind(&subscriber_function, 
				      std::placeholders::_1));
  std::thread new_subscriber_thread = new_subscriber.spawn();

  Timer new_timer("timer_operation", 
		  50, 
		  1000000000, 
		  timer_function);
  std::thread new_timer_thread = new_timer.spawn();
  
  new_subscriber_thread.join();
  new_timer_thread.join();
  executor_thread.join();

  return 0;
}
