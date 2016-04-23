/*
 * Subscriber Component
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.16
 */

#ifndef SUBSCRIBER_COMPONENT
#define SUBSCRIBER_COMPONENT
#include "component.hpp"

class Subscriber_Component : public Component {
public:
  Subscriber_Component() {
    component_subscriber = new Subscriber("subscriber_operation", 
					  60, 
					  "",
					  {"tcp://127.0.0.1:5555",
					      "tcp://127.0.0.1:5556"},
					  std::bind(&Subscriber_Component::subscriber_function, 
						    this,
						    std::placeholders::_1), 
					  operation_queue);
    add_subscriber(component_subscriber);
  }

  void subscriber_function(std::string received_message) {

    TestMessage received_message_obj;
    received_message_obj.ParseFromString(received_message);
    std::cout << "Subscriber Operation : Received Message: " 
	      << received_message_obj.message() 
	      << " ID : " << received_message_obj.id() << std::endl;  
  }
  
private:
  Subscriber * component_subscriber;
};

#endif
