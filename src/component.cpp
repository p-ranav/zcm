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
  }

  // Spawn the component executor thread
  std::thread * Component::spawn() {
    executor_thread = operation_queue->spawn();
    return executor_thread;
  }

}
