/*
 * Subscriber class
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.16
 */

#ifndef SUBSCRIBER
#define SUBSCRIBER
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <zmq.hpp>
#include "operation_queue.hpp"

class Subscriber {
public:

  Subscriber(std::string name,
	     unsigned int priority, 
	     std::string filter,
	     std::function<void(const std::string&)> operation_function, 
	     Operation_Queue * operation_queue_ptr) : 
    name(name),
    priority(priority),
    filter(filter),
    operation_function(operation_function),
    operation_queue_ptr(operation_queue_ptr) {}    

  Subscriber(std::string name, 
	     unsigned int priority, 
	     std::string filter,
	     std::vector<std::string> endpoints, 
	     std::function<void(const std::string&)> operation_function, 
	     Operation_Queue * operation_queue_ptr) : 
    name(name),
    priority(priority),
    filter(filter),
    endpoints(endpoints),
    operation_function(operation_function),
    operation_queue_ptr(operation_queue_ptr) {
    context = new zmq::context_t(2);
    subscriber_socket = new zmq::socket_t(*context, ZMQ_SUB);
    for (auto endpoint : endpoints)
      subscriber_socket->connect(endpoint);
    subscriber_socket->setsockopt(ZMQ_SUBSCRIBE, filter.c_str(), filter.length());
  }

  ~Subscriber() {
    subscriber_socket->close();
    delete context;
    delete subscriber_socket;
  }

  void connect(std::vector<std::string> new_endpoints) {
    endpoints = new_endpoints;
    context = new zmq::context_t(2);
    subscriber_socket = new zmq::socket_t(*context, ZMQ_SUB);
    for (auto endpoint : endpoints)
      subscriber_socket->connect(endpoint);
    subscriber_socket->setsockopt(ZMQ_SUBSCRIBE, filter.c_str(), filter.length());
  }

  std::string get_name() {
    return name;
  }

  unsigned int get_priority() {
    return priority;
  }

  void add_connection(std::string new_connection) {
    subscriber_socket->connect(new_connection);
  }

  void recv() {
    while(true) {
      zmq::message_t received_message; 
      subscriber_socket->recv(&received_message);
      std::string message = std::string(static_cast<char*>(received_message.data()), 
					received_message.size());
      if (message.length() > 0) {
	func_mutex.lock();      
	Operation new_operation(name, priority, std::bind(operation_function, message));
	operation_queue_ptr->enqueue(new_operation);
	func_mutex.unlock();      
      }
    }
  }

  void rebind_operation_function(std::function<void(const std::string&)> 
				 new_operation_function) {
    func_mutex.lock();
    operation_function = new_operation_function;
    func_mutex.unlock();
  }

  std::thread spawn() {
    return std::thread(&Subscriber::recv, this);
  }

  void start() {
    std::thread subscriber_thread = spawn();
    subscriber_thread.detach();
  }

private:
  std::string name;
  unsigned int priority;
  std::string filter;
  std::vector<std::string> endpoints;
  std::function<void(const std::string&)> operation_function;
  Operation_Queue * operation_queue_ptr;
  zmq::context_t * context;
  zmq::socket_t * subscriber_socket; 
  std::mutex func_mutex; // used when changing operation_function at runtime 
};

#endif
