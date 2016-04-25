/** @file    component.cpp 
 *  @author  Pranav Srinivas Kumar
 *  @date    2016.04.24
 *  @brief   This file contains definitions for the Component class
 */

#include "component.hpp"

namespace zcm {

  // Construct the operation queue
  Component::Component() {
    operation_queue = new Operation_Queue();
  }

  // Delete the operation queue
  Component::~Component() {
    if (operation_queue)
      delete operation_queue;
    for(auto publisher : publishers)
      delete publisher;
    for(auto subscriber : subscribers)
      delete subscriber;
    for(auto client : clients)
      delete client;
    for(auto server : servers)
      delete server;    
  }

  // Add a new timer
  void Component::add_timer(Timer * new_timer) {
    timers.push_back(new_timer);
  }

  // Add a new publisher
  void Component::add_publisher(Publisher * new_publisher) {
    publishers.push_back(new_publisher);
  }

  // Add a new subscriber
  void Component::add_subscriber(Subscriber * new_subscriber) {
    subscribers.push_back(new_subscriber);
  }

  // Add a new client
  void Component::add_client(Client * new_client) {
    clients.push_back(new_client);
  }

  // Add a new server
  void Component::add_server(Server * new_server) {
    servers.push_back(new_server);
  }  

  // Spawn the component executor thread
  std::thread * Component::spawn() {
    executor_thread = operation_queue->spawn();
    for(auto timer : timers)
      timer->start();
    for(auto subscriber : subscribers)
      subscriber->start();
    for(auto server : servers)
      server->start();
    return executor_thread;
  }

}
