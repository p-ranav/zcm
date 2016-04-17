/*
 * Publish-Subscribe Component
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.16
 */

#ifndef PUB_SUB_COMPONENT
#define PUB_SUB_COMPONENT
#include "operation_queue.hpp"
#include "timer.hpp"
#include "publisher.hpp"
#include "subscriber.hpp"

class Pub_Sub_Component {
public:
  Pub_Sub_Component() {
    operation_queue = new Operation_Queue();
    component_timer = new Timer("timer_operation",
				50, 
				1000000000, 
				std::bind(&Pub_Sub_Component::timer_function, this), 
				operation_queue);
    component_publisher = new Publisher("timer_pub", "tcp://*:5555");
    component_subscriber = new Subscriber("subscriber_operation", 
					  60, 
					  "", 
					  "tcp://127.0.0.1:5555", 
					  std::bind(&Pub_Sub_Component::subscriber_function, this,
						    std::placeholders::_1), 
					  operation_queue);    
  }

  ~Pub_Sub_Component() {
    delete operation_queue;
    delete component_timer;
    delete component_publisher;
    delete component_subscriber;
  }
  
  void timer_function() {
    component_publisher->send("timer_message");
  }

  void subscriber_function(std::string received_message) {
    std::cout << "Subscriber Operation : Received : " << received_message << std::endl;  
  }

  void run() {
    std::thread executor_thread = operation_queue->spawn();
    std::thread new_subscriber_thread = component_subscriber->spawn();
    std::thread new_timer_thread = component_timer->spawn();

    new_subscriber_thread.join();
    new_timer_thread.join();
    executor_thread.join();
  }

private:
  Operation_Queue * operation_queue;
  Timer * component_timer;
  Publisher * component_publisher;
  Subscriber * component_subscriber;
};

#endif
