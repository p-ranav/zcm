/** @file    server.cpp 
 *  @author  Pranav Srinivas Kumar
 *  @date    2016.04.24
 *  @brief   This file contains definitions for the Server class
 */

#include "server.hpp"


Server::Server(std::string name,
	       unsigned int priority,
	       std::vector<std::string> endpoints,
	       std::function<std::string(const std::string&)> operation_function,
	       Operation_Queue * operation_queue_ptr) :
  name(name),
  priority(priority),
  endpoints(endpoints),
  operation_function(operation_function),
  operation_queue_ptr(operation_queue_ptr) {
  context = new zmq::context_t(2);
  server_socket = new zmq::socket_t(*context, ZMQ_REP);
  for (auto endpoint : endpoints)
    server_socket->bind(endpoint);
  ready = true;
  }

Server::~Server() {
  server_socket->close();
  delete context;
  delete server_socket;
}

void Server::bind(std::vector<std::string> new_endpoints) {
  endpoints = new_endpoints;
  context = new zmq::context_t(2);
  server_socket = new zmq::socket_t(*context, ZMQ_REP);
  for (auto endpoint : endpoints)
    server_socket->bind(endpoint);
  ready = true;
}

std::string Server::get_name() {
  return name;
}

unsigned int Server::get_priority() {
  return priority;
}

void Server::add_connection(std::string new_connection) {
  server_socket->bind(new_connection);
}

void Server::recv() {
  while(true) {
    while(!ready) {}
    zmq::message_t received_request;
    server_socket->recv(&received_request);
    std::string request = std::string(static_cast<char*>(received_request.data()), 
				      received_request.size());
    ready = false;
    if (request.length() > 0) {
      func_mutex.lock();
      // Create a new operation & bind the request as the first argument
      Server_Operation * new_operation
	= new Server_Operation(name, priority, std::bind(operation_function, request),
			       server_socket, &ready);
      operation_queue_ptr->enqueue(new_operation);
      func_mutex.unlock();
    }
  }
}

void Server::rebind_operation_function(std::function<std::string(const std::string&)>
				       new_operation_function) {
  func_mutex.lock();
  operation_function = new_operation_function;
  func_mutex.unlock();
}

std::thread Server::spawn() {
  return std::thread(&Server::recv, this);
}

void Server::start() {
  std::thread server_thread = spawn();
  server_thread.detach();
}

