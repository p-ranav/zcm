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
#include "operation.hpp"

class Operation_Queue;
Operation_Queue * operation_queue;
std::mutex queue_mutex;

class Operation_Queue {
public:
  void enqueue(const Operation& new_operation) {
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

  Operation top() {
    return operation_queue.top();
  }

  void process() {
    while(true) {
      if (operation_queue.size() > 0) {
	queue_mutex.lock();
	Operation top_operation = operation_queue.top();
	top_operation.execute();
	dequeue();
	queue_mutex.unlock();
      }
    }
  }

  std::thread spawn() {
    return std::thread(&Operation_Queue::process, this);
  }

  struct PriorityOrdering {
    bool operator()(const Operation& lhs, const Operation& rhs) const {
      return lhs.get_priority() < rhs.get_priority();
    }
  };
private:
  std::priority_queue<Operation, std::vector<Operation>, PriorityOrdering> operation_queue;
};

#endif
