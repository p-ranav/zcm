/*
 * Subscriber class
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.16
 */

#ifndef SUBSCRIBER
#define SUBSCRIBER
#include <iostream>
#include <sstream>
#include <zmq.hpp>
#include "operation_queue.hpp"

class Subscriber {
public:
    Subscriber(std::string name, 
	       unsigned int priority, 
	       std::string filter,
	       std::string endpoint, 
	       std::function<void(const std::string&)> operation_function) : 
      name(name),
      priority(priority),
      filter(filter),
      endpoint(endpoint),
      operation_function(operation_function) {}

  void recv() {
    while (true) {
      zmq::context_t context (1);
      zmq::socket_t subscriber (context, ZMQ_SUB);
      subscriber.connect(endpoint);
      if (!subscriber.connected())
	std::cout << "Connect failed!" << std::endl;
      subscriber.setsockopt(ZMQ_SUBSCRIBE, filter.c_str(), filter.length());
      zmq::message_t received_message; 
      subscriber.recv(&received_message, ZMQ_NOBLOCK);
      std::istringstream recv_string(static_cast<char*>(received_message.data()));
      if (recv_string.str().length() > 0)
	std::cout << "Receive successful" << std::endl;
      //Operation new_operation(name, priority,
      // std::bind(operation_function, 
      //				recv_string));
      //operation_queue->enqueue(new_operation);
    }
  }

  std::thread spawn() {
    return std::thread(&Subscriber::recv, this);
  }

private:
  std::string name;
  unsigned int priority;
  std::string filter;
  std::string endpoint;
  std::function<void(const std::string&)> operation_function;
};

#endif
