#include <iostream>
#include <string>
#include "operation_queue.hpp"
#include "timer.hpp"
#include "publisher.hpp"
#include "subscriber.hpp"

Publisher timer_pub("timer_pub", "tcp://*:5555");

void timer_function() {
  timer_pub.send("timer_message");
}

void subscriber_function(std::string received_message) {
  std::cout << "Subscriber Operation : Received : " << received_message << std::endl;  
}

int main() {

  // Prepare the Operation Queue
  operation_queue = new Operation_Queue();
  std::thread executor_thread = operation_queue->spawn();
  
  // Spawn the Subscriber Thread that waits for messages
  Subscriber new_subscriber("subscriber_operation", 
			    60, 
			    "", 
			    "tcp://127.0.0.1:5555", 
			    std::bind(&subscriber_function, 
				      std::placeholders::_1));
  std::thread new_subscriber_thread = new_subscriber.spawn();

  // Spawn the Periodic Timer - Inside this timer, we publish messages
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
