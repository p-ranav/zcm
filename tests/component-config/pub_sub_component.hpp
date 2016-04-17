/*
 * Publish-Subscribe Component
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.16
 */

#ifndef PUB_SUB_COMPONENT
#define PUB_SUB_COMPONENT
#include "component.hpp"

class Pub_Sub_Component : public Component {
public:

  void init() {
    // Initialize First Publisher
    component_timer_1 = new Timer("timer_1",
				  50, 
				  500000000, 
				  std::bind(&Pub_Sub_Component::timer_1_function, this), 
				  operation_queue);    
    component_publisher_1 = new Publisher("timer_pub_1", "tcp://*:5555");

    // Initialize Second Publisher
    component_timer_2 = new Timer("timer_2",
				  50, 
				  1000000000, 
				  std::bind(&Pub_Sub_Component::timer_2_function, this), 
				  operation_queue);
    component_publisher_2 = new Publisher("timer_pub_2", "tcp://*:5556");

    // Initialize Subscriber
    std::vector<std::string> subscriber_endpoints = {"tcp://127.0.0.1:5555",
						     "tcp://127.0.0.1:5556"};
    component_subscriber = new Subscriber("subscriber_operation", 
					  60, 
					  "", 
					  subscriber_endpoints,
					  std::bind(&Pub_Sub_Component::subscriber_function, 
						    this,
						    std::placeholders::_1), 
					  operation_queue);

    add_timer(component_timer_1);
    add_publisher(component_publisher_1);
    add_timer(component_timer_2);
    add_publisher(component_publisher_2);
    add_subscriber(component_subscriber);
  }
  
  void timer_1_function() {
    component_publisher_1->send("timer_1_message");
  }

  void timer_2_function() {
    component_publisher_2->send("timer_2_message");
  }

  void subscriber_function(std::string received_message) {
    std::cout << "Subscriber Operation : Received : " << received_message << std::endl;  
  }

private:

  Timer * component_timer_1;
  Publisher * component_publisher_1;

  Timer * component_timer_2;
  Publisher * component_publisher_2;

  Subscriber * component_subscriber;
};

#endif
