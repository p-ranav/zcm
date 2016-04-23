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

  Pub_Sub_Component() {

    component_timer_1 = new Timer("timer_1",
				  50, 
				  500000000, 
				  std::bind(&Pub_Sub_Component::timer_1_function, this), 
				  operation_queue);   
    component_publisher_1 = new Publisher("timer_pub_1");

    component_timer_2 = new Timer("timer_2",
				  50, 
				  1000000000, 
				  std::bind(&Pub_Sub_Component::timer_2_function, this), 
				  operation_queue);
    component_publisher_2 = new Publisher("timer_pub_2");

    component_subscriber = new Subscriber("subscriber_operation", 
					  60, 
					  "", 
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

    // Create new message
    TestMessage new_message;
    new_message.set_message("timer_1_message");
    new_message.set_id(0);

    // Prepare string to publish
    std::string * message_string = new std::string; 
    new_message.SerializeToString(message_string);

    // Publish message
    component_publisher_1->send(*message_string);
  }

  void timer_2_function() {

    // Create new message

    TestMessage new_message;
    new_message.set_message("timer_2_message");
    new_message.set_id(1);

    // Prepare string to publish
    std::string * message_string = new std::string; 
    new_message.SerializeToString(message_string);

    component_publisher_2->send(*message_string);
  }

  void subscriber_function(std::string received_message) {

    TestMessage received_message_obj;
    received_message_obj.ParseFromString(received_message);
    std::cout << "Subscriber Operation : Received Message: " 
	      << received_message_obj.message() 
	      << " ID : " << received_message_obj.id() << std::endl;  
  }

private:

  Timer * component_timer_1;
  Publisher * component_publisher_1;

  Timer * component_timer_2;
  Publisher * component_publisher_2;

  Subscriber * component_subscriber;
};

#endif
