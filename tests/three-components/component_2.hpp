/*
 * Component 2
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.23
 */

#ifndef COMPONENT_2
#define COMPONENT_2
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/random/mersenne_twister.hpp>
#include "component.hpp"

class Component_2 : public Component {
public:
  Component_2() {
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

  void timer_function() {
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

  std::string server_function(std::string request) {
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

private:
  Timer * timer;
  Publisher * publisher;
  Server * server;
};

#endif
