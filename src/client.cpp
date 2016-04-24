/** @file    client.cpp 
 *  @author  Pranav Srinivas Kumar
 *  @date    2016.04.24
 *  @brief   This file contains definitions for the Client class
 */

#include "client.hpp"

// Construct a simple client
Client::Client(std::string name) : name(name) {}

// Construct a client with known endpoints
Client::Client(std::string name, std::vector<std::string> endpoints) :
  name(name),
  endpoints(endpoints) {
  context = new zmq::context_t(1);
  client_socket = new zmq::socket_t(*context, ZMQ_REQ);
  for (auto endpoint : endpoints) {
    try {
      client_socket->connect(endpoint);
    } catch (zmq::error_t error) {
      std::cout << "Unable to connect client " << 
	name << " to " << endpoint << std::endl;      
    }
  }
}

// Destroy the client
Client::~Client() {
  client_socket->close();
  delete context;
  delete client_socket;
}

void Client::connect(std::vector<std::string> new_endpoints) {
  endpoints = new_endpoints;
  context = new zmq::context_t(1);
  client_socket = new zmq::socket_t(*context, ZMQ_REQ);
  for (auto endpoint : endpoints) {
    try {
      client_socket->connect(endpoint);
    } catch (zmq::error_t error) {
      std::cout << "Unable to connect client " << 
	name << " to " << endpoint << std::endl;      
    }
  }
}  

std::string Client::get_name() {
  return name;
}

std::string Client::call(std::string message) {
  zmq::message_t request(message.length());
  memcpy(request.data(), message.c_str(), message.length());
  client_socket->send(request);

  // Wait for response
  zmq::message_t reply;
  client_socket->recv(&reply);
  return std::string(static_cast<char*>(reply.data()), reply.size());
}
