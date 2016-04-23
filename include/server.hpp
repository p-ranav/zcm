/*
 * Server class
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.23
 */

#ifndef SERVER
#define SERVER
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <zmq.hpp>
#include "operation_queue.hpp"

class Server {
public:
  Server(std::string name,
	 unsigned int priority,
	 std::function<std::string(const std::string&)> operation_function,
	 Operation_Queue * operation_queue_ptr) :
    name(name),
    priority(priority),
    operation_function(operation_function),
    operation_queue_ptr(operation_queue_ptr) {}

  Server(std::string name,
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

  ~Server() {
    server_socket->close();
    delete context;
    delete server_socket;
  }

  void bind(std::vector<std::string> new_endpoints) {
    endpoints = new_endpoints;
    context = new zmq::context_t(2);
    server_socket = new zmq::socket_t(*context, ZMQ_REP);
    for (auto endpoint : endpoints)
      server_socket->bind(endpoint);
    ready = true;
  }

  std::string get_name() {
    return name;
  }

  unsigned int get_priority() {
    return priority;
  }

  void add_connection(std::string new_connection) {
    server_socket->bind(new_connection);
  }

  void recv() {
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
	Operation new_operation(name, priority, NULL, std::bind(operation_function, request),
				server_socket, &ready);
	operation_queue_ptr->enqueue(new_operation);
	func_mutex.unlock();
      }
    }
  }

  void rebind_operation_function(std::function<std::string(const std::string&)>
				 new_operation_function) {
    func_mutex.lock();
    operation_function = new_operation_function;
    func_mutex.unlock();
  }

  std::thread spawn() {
    return std::thread(&Server::recv, this);
  }

  void start() {
    std::thread server_thread = spawn();
    server_thread.detach();
  }

private:
  std::string name;
  unsigned int priority;
  std::vector<std::string> endpoints;
  std::function<std::string(const std::string&)> operation_function;
  Operation_Queue * operation_queue_ptr;
  zmq::context_t * context;
  zmq::socket_t * server_socket;
  bool ready;
  std::mutex func_mutex; // used when changing operation_function at runtime
};

#endif
