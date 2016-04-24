/** @file    component.hpp 
 *  @author  Pranav Srinivas Kumar
 *  @date    2016.04.24
 *  @brief   This file declares the Component class
 */

#ifndef COMPONENT
#define COMPONENT
#include "timer.hpp"
#include "publisher.hpp"
#include "subscriber.hpp"
#include "client.hpp"
#include "server.hpp"

/**
 * @brief Component class
 */
class Component {
public:

  /*
   * @brief Construct a component
   * Prepare the component operation queue
   */
  Component();

  /*
   * @brief Destroy the component
   */  
  ~Component();

  /*
   * @brief Spawn the component executor thread
   * @return Return a pointer to the executor thread
   */    
  std::thread * spawn();

protected:
  Operation_Queue * operation_queue;
  std::thread * executor_thread;
};

#endif
