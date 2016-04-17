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

  Component(std::string name) : 
    name(name) {
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

  std::thread * spawn() {
    executor_thread = operation_queue->spawn();
    for(auto timer : timers)
      timer->start();
    for(auto subscriber : subscribers)
      subscriber->start();
    return executor_thread;
  }

protected:
  std::string name;

  Operation_Queue * operation_queue;
  std::thread * executor_thread;

  std::vector<Publisher*> publishers;
  std::vector<Subscriber*> subscribers;
  std::vector<Timer*> timers;
};

#endif
