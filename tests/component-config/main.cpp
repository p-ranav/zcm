#include <iostream>
#include "pub_sub_component.hpp"

int main() {
  // FIRST INSTANCE OF PUB_SUB_COMPONENT
  Pub_Sub_Component * new_instance = new Pub_Sub_Component();
  new_instance->port_config(
		       // Publisher ZMQ bindings
		       {
			 {"timer_pub_1", {"tcp://*:5555"}},
			   {"timer_pub_2", {"tcp://*:5556"}}
		       },
		       // Susbcriber ZMQ bindings
		       {
			 {"subscriber_operation", 
			     {"tcp://127.0.0.1:5555",
			       "tcp://127.0.0.1:5556"}}
		       }      
		       );
  std::thread * instance_1_thread = new_instance->spawn();


  // SECOND INSTANCE OF SAME COMPONENT WITH DIFFERENT CONFIGURATION
  Pub_Sub_Component * another_instance = new Pub_Sub_Component();
  another_instance->port_config(
		       // Publisher ZMQ bindings
		       {
			 {"timer_pub_1", {"tcp://*:9000"}},
			   {"timer_pub_2", {"tcp://*:9999"}}
		       },
		       // Susbcriber ZMQ bindings
		       {
			 {"subscriber_operation", 
			     {"tcp://127.0.0.1:9000",
			       "tcp://127.0.0.1:9999"}}
		       }      
		       );
  std::thread * instance_2_thread = another_instance->spawn();
    
  instance_1_thread->join();
  instance_2_thread->join();
  return 0;
}
