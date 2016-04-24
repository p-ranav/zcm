/*
 * Publisher Component
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.16
 */

#ifndef PUBLISHER_COMPONENT
#define PUBLISHER_COMPONENT
#include "component.hpp"

class Publisher_Component : public Component {
public:
  Publisher_Component() {
    component_timer = new Timer("timer_1",
				  50, 
				  500000000, 
				  std::bind(&Publisher_Component::timer_1_function, this), 
				  operation_queue);   
    component_publisher = new Publisher("timer_pub_1", {"tcp://*:5555"});

    add_timer(component_timer);
    add_publisher(component_publisher);
  }
  
  void timer_1_function() {

    // Create new message
    TestMessage new_message;
    new_message.set_message("timer_1_message");
    new_message.set_id(0);

    // Prepare string to publish
    std::string * message_string = new std::string; 
    new_message.SerializeToString(message_string);

    // Publish message
    component_publisher->send(*message_string);
  }

private:
  Timer * component_timer;
  Publisher * component_publisher;
};

#endif
