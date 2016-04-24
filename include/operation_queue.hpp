/*
 * Operation Queue class
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.16
 */

#ifndef OPERATION_QUEUE
#define OPERATION_QUEUE
#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include <functional>
#include "operation_types.hpp"

class Operation_Queue {
public:
  void enqueue(Base_Operation * new_operation) {
    queue_mutex.lock();
    operation_queue.push(new_operation);
    queue_mutex.unlock();
  }

  void dequeue() {
    if (!empty())
      operation_queue.pop();
  }

  bool empty() {
    return operation_queue.empty();
  }

  Base_Operation * top() {
    return operation_queue.top();
  }

  void process() {
    while(true) {
      if (operation_queue.size() > 0) {
	queue_mutex.lock();
	Base_Operation * top_operation = operation_queue.top();
	dequeue();
	queue_mutex.unlock();
	top_operation->execute();	  
      }
    }
  }

  std::thread * spawn() {
    return new std::thread(&Operation_Queue::process, this);
  }

  struct PriorityOrdering {
    bool operator()(const Base_Operation * lhs, const Base_Operation * rhs) const {
      return lhs->get_priority() < rhs->get_priority();
    }
  };
private:
  std::priority_queue<Base_Operation, std::vector<Base_Operation*>, PriorityOrdering> operation_queue;
  std::mutex queue_mutex;
};

#endif
