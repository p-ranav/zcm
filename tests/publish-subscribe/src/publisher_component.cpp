/** @file    publisher_component.cpp 
 *  @author  Pranav Srinivas Kumar
 *  @date    2016.04.24
 *  @brief   This file contains definitions for the Publisher_Component class
 */

#include "publisher_component.hpp"

namespace zcm {

  /**
   * @brief Function required to dynamically load publisher_component.so
   */  
  extern "C" {
    Component* create_component() {
      return new Publisher_Component();
    }
  }      

  /**
   * @brief Construct a publisher component
   * Register all operations exposed by this component
   */   
  Publisher_Component::Publisher_Component() {
    register_timer_operation("timer_1_function",
			     std::bind(&Publisher_Component::timer_1_function, this));
  }

  /**
   * @brief A timer operation
   * This operation can be triggered by a periodic timer
   * Bind this operation to a periodic timer in the JSON configuration
   */    
  void Publisher_Component::timer_1_function() {
    // Create new message
    TestMessage new_message;
    new_message.set_message("timer_1_message");
    new_message.set_id(0);

    // Prepare string to publish
    std::string * message_string = new std::string; 
    new_message.SerializeToString(message_string);

    // Publish message
    publisher("timer_pub_1")->send(*message_string);
  }

}
