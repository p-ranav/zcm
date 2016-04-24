/*
 * Operation Types
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.24
 */

#ifndef OPERATION_TYPES
#define OPERATION_TYPES
#include <iostream>
#include <functional>
#include "zmq.hpp"

class Base_Operation {
public:
  Base_Operation(std::string name,
		 unsigned int priority) :
    name(name),
    priority(priority) {}

  std::string get_name() {
    return name;
  }

  unsigned int get_priority() const {
    return priority;
  }

  virtual void execute() {
    std::cout << "Calling base class execute" << std::endl;
  }

private:
  std::string name;
  unsigned int priority;
};

class Timer_Operation : public Base_Operation {
public:
  Timer_Operation(std::string name,
		  unsigned int priority,
		  std::function<void()> operation_function) :
    Base_Operation(name, priority),
    operation_function(operation_function) {}

  void execute() {
    operation_function();
  }

private:
  std::function<void()> operation_function;
};

class Subscriber_Operation : public Base_Operation {
public:
  Subscriber_Operation(std::string name,
		       unsigned int priority,
		       std::function<void()> operation_function) :
    Base_Operation(name, priority),
    operation_function(operation_function) {}

  void execute() {
    operation_function();
  }

private:
  std::function<void()> operation_function;
};

class Server_Operation : public Base_Operation {
public:
  Server_Operation(std::string name,
		   unsigned int priority,
		   std::function<std::string()> operation_function,
		   zmq::socket_t * socket_ptr,
		   bool * recv_ready) :
    Base_Operation(name, priority),
    operation_function(operation_function),
    socket_ptr(socket_ptr),
    recv_ready(recv_ready) {}

  void execute() {
    std::string response = operation_function();
    zmq::message_t reply(response.length());
    memcpy(reply.data(), response.c_str(), response.length());
    socket_ptr->send(reply);
    set_ready();
  }

  zmq::socket_t * get_socket_ptr() {
    return socket_ptr;
  }

  void set_ready() {
    *recv_ready = true;
  }  

private:
  std::function<std::string()> operation_function;
  zmq::socket_t * socket_ptr;
  bool * recv_ready;
};

#endif
