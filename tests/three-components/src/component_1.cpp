/** @file    component_1.cpp 
 *  @author  Pranav Srinivas Kumar
 *  @date    2016.04.24
 *  @brief   This file contains definitions of the Component_1 class
 */

#include "component_1.hpp"

namespace zcm {

  extern "C" {
    Component* create_component() {
      return new Component_1();
    }
  }

  Component_1::Component_1() {
    timer = new Timer("Timer_1",
		      50, 
		      500000000, // 500 msec 
		      std::bind(&Component_1::timer_1_function, this), 
		      operation_queue);
    publisher = new Publisher("Name_Publisher", {"tcp://*:5555"});
    subscriber = new Subscriber("subscriber_operation", 
				60, 
				"",
				{"tcp://127.0.0.1:5555",
				    "tcp://127.0.0.1:5556"},
				std::bind(&Component_1::subscriber_function, 
					  this,
					  std::placeholders::_1), 
				operation_queue);
    add_timer(timer);
    add_publisher(publisher);
    add_subscriber(subscriber);
  }

  void Component_1::timer_1_function() {
    boost::random::mt19937 rng;
    boost::random::uniform_int_distribution<> loop_iteration_random(500000 * 0.6, 500000);
    int loop_max = loop_iteration_random(rng);    
  
    // Business Logic for Timer_1_operation
    for(int i=0; i < loop_max; i++) {
      double result = 0.0;
      double x = 41865185131.214415;
      double y = 562056205.1515;
      result = x*y;
    }
    publisher->send("Component_1");
    std::cout << "Component 1 : Timer : Published message: Component_1" << std::endl;    
  }

  void Component_1::subscriber_function(std::string received_message) {
    boost::random::mt19937 rng;
    boost::random::uniform_int_distribution<> loop_iteration_random(700000 * 0.6, 700000);
    int loop_max = loop_iteration_random(rng);  
  
    // Business Logic for Name_Subscriber_operation
    for(int i=0; i < loop_max; i++) {
      double result = 0.0;
      double x = 41865185131.214415;
      double y = 562056205.1515;
      result = x*y;
    }
    std::cout << "Component 1 : Subscriber : Received message: " << received_message << std::endl;
  }    
    
}

