/** @file    component_3.cpp 
 *  @author  Pranav Srinivas Kumar
 *  @date    2016.04.24
 *  @brief   This file contains definitions of the Component_3 class
 */

#include "component_3.hpp"

namespace zcm {

  extern "C" {
    Component* create_component() {
      return new Component_3();
    }
  }  

  Component_3::Component_3() {
    timer = new Timer("Timer_3",
		      50, 
		      2000000000, 
		      std::bind(&Component_3::timer_function, this), 
		      operation_queue);
    timer->start();
    client = new Client("client", {"tcp://127.0.0.1:5510"});
  }

  void Component_3::timer_function() {
    boost::random::mt19937 rng;
    boost::random::uniform_int_distribution<> loop_iteration_random(500000 * 0.6, 500000);
    int loop_max = loop_iteration_random(rng);  
  
    // Business Logic for Timer_3_operation
    for(int i=0; i < loop_max; i++) {
      double result = 0.0;
      double x = 41865185131.214415;
      double y = 562056205.1515;
      result = x*y;
    }
    std::string response = client->call("Component_3");
    std::cout << "Component 3 : Timer : Called Component_2::Server : " << "Received: " << response << std::endl;
  }  
}
