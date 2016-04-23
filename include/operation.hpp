/*
 * Operation class
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.16
 */

#ifndef OPERATION
#define OPERATION
#include <iostream>
#include <functional>
#include "zmq.hpp"

class Operation {
public:
  Operation(std::string name, 
	    unsigned int priority, 
	    std::function<void()> operation_function = NULL,
	    std::function<std::string()> server_operation_function = NULL,
	    zmq::socket_t * socket_ptr = NULL,
	    bool * recv_ready = NULL) : 
    name(name),
    priority(priority),
    operation_function(operation_function),
    server_operation_function(server_operation_function),
    socket_ptr(socket_ptr),
    recv_ready(recv_ready) {}  

  void execute() {
      operation_function();
  }

  std::string execute_server() {
    return server_operation_function();
  }

  void rebind_operation_function(std::function<void()> new_operation_function) {
    operation_function = new_operation_function;
  }

  std::string get_name() const {
    return name;
  }

  std::function<void()> get_operation_function() {
    return operation_function;
  }

  unsigned int get_priority() const {
    return priority;
  }

  zmq::socket_t * get_socket_ptr() {
    return socket_ptr;
  }

  void set_ready() {
    *recv_ready = true;
  }

private:
  std::string name;
  unsigned int priority;
  std::function<void()> operation_function;
  std::function<std::string()> server_operation_function;
  zmq::socket_t * socket_ptr;
  bool * recv_ready;
};

#endif
