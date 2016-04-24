/** @file    operation_types.cpp 
 *  @author  Pranav Srinivas Kumar
 *  @date    2016.04.24
 *  @brief   This file contains definitions for various Operation Types
 */

#include "operation_types.hpp"

// Return the operation name
std::string Base_Operation::get_name() {
  return name;
}

// Return the operation priority
unsigned int Base_Operation::get_priority() const {
  return priority;
}

// Execute a timer operation
void Timer_Operation::execute() {
  operation_function();
}

// Execute a subsciber operation
void Subscriber_Operation::execute() {
  operation_function();
}

// Execute the server operation and respond to the client
void Server_Operation::execute() {
  std::string response = operation_function();
  zmq::message_t reply(response.length());
  memcpy(reply.data(), response.c_str(), response.length());
  socket_ptr->send(reply);
  set_ready();
}

// Return the ZMQ server socket pointer
zmq::socket_t * Server_Operation::get_socket_ptr() {
  return socket_ptr;
}

// Set the server as "ready" to receive new request from client
void Server_Operation::set_ready() {
  *recv_ready = true;
}  
