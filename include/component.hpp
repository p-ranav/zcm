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
    if (operation_queue)
      delete operation_queue;
  }

  std::thread * spawn() {
    executor_thread = operation_queue->spawn();   
    return executor_thread;
  }

protected:
  Operation_Queue * operation_queue;
  std::thread * executor_thread;
};

#endif
