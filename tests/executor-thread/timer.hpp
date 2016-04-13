/*
 * Timer Class
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.13
 */

#ifndef TIMER
#define TIMER
#include <iostream>
#include <string>
#include <chrono>
#include <ratio>
#include <thread>
#include <mutex>

#include "operation_queue.hpp"

class Timer {
public:

  Timer(std::string name, unsigned int priority, long long period) : 
    name(name), 
    priority(priority),
    period(std::chrono::nanoseconds(period)) {}

  void operation() {
    while(true) {
      auto start = std::chrono::high_resolution_clock::now();
      while(std::chrono::duration_cast<std::chrono::nanoseconds>
      (std::chrono::high_resolution_clock::now() - start) < period) {}
      auto expiry = std::chrono::high_resolution_clock::now();
    queue_mutex.lock();
    std::cout << name << "::Timer Expired::Period::" <<
      std::chrono::duration_cast<std::chrono::nanoseconds>(expiry - start).count() 
	      << " ns" << std::endl;    
    Operation new_operation(name, priority);
    operation_queue->enqueue(new_operation);
    queue_mutex.unlock();   
    }    
  }

  std::thread spawn() {
    return std::thread(&Timer::operation, this);
  }

private:
  std::string name;
  unsigned int priority;
  std::chrono::duration<long long, std::ratio<1, 1000000000>> period;
};

#endif
