/*
 * Subscriber Component
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.25
 */

#include "subscriber_component.hpp"

namespace zcm {

  extern "C" {
    Component* create_component() {
      return new Subscriber_Component();
    }
  }    

  Subscriber_Component::Subscriber_Component() {
    component_subscriber = new Subscriber("subscriber_operation", 
					  60, 
					  "",
					  std::bind(&Subscriber_Component::subscriber_function, 
						    this,
						    std::placeholders::_1), 
					  operation_queue);
    add_subscriber(component_subscriber);
  }

  void Subscriber_Component::subscriber_function(std::string received_message) {
    TestMessage received_message_obj;
    received_message_obj.ParseFromString(received_message);
    std::cout << "Subscriber Operation : Received Message: " 
	      << received_message_obj.message() 
	      << " ID : " << received_message_obj.id() << std::endl;  
  }

}
