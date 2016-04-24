/** @file    publisher.cpp 
 *  @author  Pranav Srinivas Kumar
 *  @date    2016.04.24
 *  @brief   This file contains definitions for the Publisher class
 */

#include "publisher.hpp"

// Construct a simple publisher
Publisher::Publisher(std::string name) : name(name) {}

// Construct a publisher with known endpoints
Publisher::Publisher(std::string name, std::vector<std::string> endpoints) : 
  name(name),
  endpoints(endpoints) {
  context = new zmq::context_t(1);
  publisher_socket = new zmq::socket_t(*context, ZMQ_PUB);
  for (auto endpoint : endpoints) {
    try {
      publisher_socket->bind(endpoint);
    } catch (zmq::error_t error) {
      std::cout << "Unable to bind publisher " << 
	name << " to " << endpoint << std::endl;      
    }
  }
}

// Destroy the publisher
Publisher::~Publisher() {
  publisher_socket->close();
  delete context;
  delete publisher_socket;
}

// Bind a publisher to a new set of endpoints
void Publisher::bind(std::vector<std::string> new_endpoints) {
  endpoints = new_endpoints;
  context = new zmq::context_t(1);
  publisher_socket = new zmq::socket_t(*context, ZMQ_PUB);
  for (auto endpoint : endpoints) {
    try {
      publisher_socket->bind(endpoint);
    } catch (zmq::error_t error) {
      std::cout << "Unable to bind publisher " << 
	name << " to " << endpoint << std::endl;      
    }
  }
}

// Return the publisher name
std::string Publisher::get_name() {
  return name;
}

// Add a new endpoint to the publisher
void Publisher::add_connection(std::string new_connection){
  try {
    publisher_socket->bind(new_connection);
  } catch (zmq::error_t error) {
    std::cout << "ERROR::add_connection failed trying to bind to address: " 
	      << new_connection << std::endl;
  }
}

// Publish a new message
void Publisher::send(std::string message) {
  zmq::message_t message_struct (message.length());
  memcpy(message_struct.data(), message.c_str(), message.length());
  publisher_socket->send(message_struct); 
}
