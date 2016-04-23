/*
 * Component class
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.17
 */

#ifndef COMPONENT
#define COMPONENT
#include "timer.hpp"
#include "publisher.hpp"
#include "subscriber.hpp"
#include "client.hpp"
#include "server.hpp"

class Component {
public:

  Component() {
    operation_queue = new Operation_Queue();
  }

  ~Component() {
    for(auto timer : timers)
      delete timer;
    for(auto publisher : publishers)
      delete publisher;
    for(auto subscriber : subscribers)
      delete subscriber;
    for(auto client : clients)
      delete client;
    for(auto server : servers)
      delete server;    
  }

  void add_timer(Timer * new_timer) {
    timers.push_back(new_timer);
  }

  void add_publisher(Publisher * new_publisher) {
    publishers.push_back(new_publisher);
  }

  void add_subscriber(Subscriber * new_subscriber) {
    subscribers.push_back(new_subscriber);
  }

  void add_client(Client * new_client) {
    clients.push_back(new_client);
  }

  void add_server(Server * new_server) {
    servers.push_back(new_server);
  }  

  Timer * get_timer(std::string timer_name) {
    for (auto timer : timers) 
      if(timer->get_name().compare(timer_name) == 0)
	return timer;
    return NULL;
  }

  Publisher * get_publisher(std::string publisher_name) {
    for (auto publisher : publishers) 
      if(publisher->get_name().compare(publisher_name) == 0)
	return publisher;
    return NULL;
  }

  Subscriber * get_subscriber(std::string subscriber_name) {
    for (auto subscriber : subscribers) 
      if(subscriber->get_name().compare(subscriber_name) == 0)
	return subscriber;
    return NULL;
  }

  Client * get_client(std::string client_name) {
    for (auto client : clients) 
      if(client->get_name().compare(client_name) == 0)
	return client;
    return NULL;
  }

  Server * get_server(std::string server_name) {
    for (auto server : servers) 
      if(server->get_name().compare(server_name) == 0)
	return server;
    return NULL;
  }

  typedef std::map<std::string, std::vector<std::string>> endpoints_map;

  void publisher_config(endpoints_map publisher_endpoints) {
    for (auto pub_map : publisher_endpoints) {
      Publisher * pub_ptr = get_publisher(pub_map.first);
      if (pub_ptr)
	pub_ptr->bind(pub_map.second);
      else
	std::cout << "ERROR::Unable to find publisher \"" << pub_map.first << "\"" << std::endl;
    }        
  }
  void subscriber_config(endpoints_map subscriber_endpoints) {
    for (auto sub_map : subscriber_endpoints) {
      Subscriber * sub_ptr = get_subscriber(sub_map.first);
      if (sub_ptr)
	sub_ptr->connect(sub_map.second);
      else
	std::cout << "ERROR::Unable to find subscriber \"" << sub_map.first << "\"" << std::endl;
    }
  }

  void client_config(endpoints_map client_endpoints) {
    for (auto client_map : client_endpoints) {
      Client * client_ptr = get_client(client_map.first);
      if (client_ptr)
	client_ptr->connect(client_map.second);
      else
	std::cout << "ERROR::Unable to find client \"" << client_map.first << "\"" << std::endl;
    }  
  }

  void server_config(endpoints_map server_endpoints) {
    for (auto server_map : server_endpoints) {
      Server * server_ptr = get_server(server_map.first);
      if (server_ptr)
	server_ptr->bind(server_map.second);
      else
	std::cout << "ERROR::Unable to find server \"" << server_map.first << "\"" << std::endl;
    }  
  }

  std::thread * spawn() {
    executor_thread = operation_queue->spawn();
    for(auto timer : timers)
      timer->start();
    for(auto subscriber : subscribers)
      subscriber->start();
    for(auto server : servers)
      server->start();    
    return executor_thread;
  }

protected:
  Operation_Queue * operation_queue;
  std::thread * executor_thread;

  std::vector<Publisher*> publishers;
  std::vector<Subscriber*> subscribers;
  std::vector<Client*> clients;
  std::vector<Server*> servers;
  std::vector<Timer*> timers;
};

#endif
