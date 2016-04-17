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
				500000000, 
				std::bind(&Pub_Sub_Component::timer_function, this), 
				operation_queue);

    // Two component publishers that are set to publish in different ports
    component_publisher = new Publisher("timer_pub", "tcp://*:5555");
    second_publisher = new Publisher("second_pub", "tcp://*:5556");

    // Subscriber receives from both publishers
    component_subscriber = new Subscriber("subscriber_operation", 
					  60, 
					  "", 
					  "tcp://127.0.0.1:5555", 
					  std::bind(&Pub_Sub_Component::subscriber_function, this,
						    std::placeholders::_1), 
					  operation_queue);  
    // If there is more than one port to listen to, use the add_connection function 
    // and conenct to new endpoint
    component_subscriber->add_connection("tcp://127.0.0.1:5556");
  }

  ~Pub_Sub_Component() {
    delete operation_queue;
    delete component_timer;
    delete component_publisher;
    delete second_publisher;
    delete component_subscriber;
  }
  
  void timer_function() {
    component_publisher->send("timer_message");
    second_publisher->send("different_publisher");
  }

  void subscriber_function(std::string received_message) {
    std::cout << "Subscriber Operation : Received : " << received_message << std::endl;  
  }

  void run() {
    std::thread executor_thread = operation_queue->spawn();
    component_timer->start();
    component_subscriber->start();
    executor_thread.join();
  }

private:
  Operation_Queue * operation_queue;
  Timer * component_timer;
  Publisher * component_publisher;
  Publisher * second_publisher;
  Subscriber * component_subscriber;
};

#endif
