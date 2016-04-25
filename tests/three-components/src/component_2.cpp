/** @file    component_2.cpp 
 *  @author  Pranav Srinivas Kumar
 *  @date    2016.04.24
 *  @brief   This file contains definitions of the Component_2 class
 */

#include "component_2.hpp"

namespace zcm {

  extern "C" {
    Component* create_component() {
      return new Component_2();
    }
  }  

  Component_2::Component_2() {
    timer = new Timer("Timer_2",
		      50, 
		      1000000000, 
		      std::bind(&Component_2::timer_function, this), 
		      operation_queue);
    publisher = new Publisher("Name_Publisher", {"tcp://*:5556"});
    server = new Server("server",
			60,
			{"tcp://*:5510"},
			std::bind(&Component_2::server_function,
				  this,
				  std::placeholders::_1),
			operation_queue);
    add_timer(timer);
    add_publisher(publisher);
    add_server(server);
  }

  void Component_2::timer_function() {
    boost::random::mt19937 rng;
    boost::random::uniform_int_distribution<> loop_iteration_random(800000 * 0.6, 800000);
    int loop_max = loop_iteration_random(rng);    
  
    // Business Logic for Timer_2_operation
    for(int i=0; i < loop_max; i++) {
      double result = 0.0;
      double x = 41865185131.214415;
      double y = 562056205.1515;
      result = x*y;
    } 
    publisher->send("Component_2");
    std::cout << "Component 2 : Timer : Published message: Component_2" << std::endl;    
  }

  std::string Component_2::server_function(std::string request) {
    std::cout << "Component 2 : Server : Received request: " << request << std::endl;
    boost::random::mt19937 rng;
    boost::random::uniform_int_distribution<> loop_iteration_random(600000 * 0.6, 600000);
    int loop_max = loop_iteration_random(rng);  
  
    // Business Logic for Service_Server_operation
    for(int i=0; i < loop_max; i++) {
      double result = 0.0;
      double x = 41865185131.214415;
      double y = 562056205.1515;
      result = x*y;
    }
    publisher->send("Component_2");
    std::cout << "Component 2 : Server : Published message: Component_2" << std::endl;     
    return "Component_2";
  }

}
