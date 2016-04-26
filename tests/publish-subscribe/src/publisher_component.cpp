/*
 * Publisher Component
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.25
 */

#include "publisher_component.hpp"

namespace zcm {

  extern "C" {
    Component* create_component() {
      return new Publisher_Component();
    }
  }      

  Publisher_Component::Publisher_Component() {
    component_timer = new Timer("timer_1",
				50, 
				500000000, 
				std::bind(&Publisher_Component::timer_1_function, this), 
				operation_queue);
    component_publisher = new Publisher("timer_pub_1");
    add_timer(component_timer);
    add_publisher(component_publisher);
  }

  void Publisher_Component::timer_1_function() {
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

}
