/*
 * Component class
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.17
 */

#ifndef COMPONENT
#define COMPONENT
#include "timer.hpp"
#include "subscriber.hpp"
#include "publisher.hpp"

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

  std::thread * spawn() {
    executor_thread = operation_queue->spawn();
    for(auto timer : timers)
      timer->start();
    for(auto subscriber : subscribers)
      subscriber->start();
    return executor_thread;
  }

protected:
  Operation_Queue * operation_queue;
  std::thread * executor_thread;

  std::vector<Publisher*> publishers;
  std::vector<Subscriber*> subscribers;
  std::vector<Timer*> timers;
};

#endif
