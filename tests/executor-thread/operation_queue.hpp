/*
 * Component Operation Queue Class
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.12
 */

#ifndef OPERATION_QUEUE
#define OPERATION_QUEUE

#include <iostream>
#include <queue>
#include <mutex>

class Operation_Queue;
Operation_Queue * operation_queue;

struct Operation {
  Operation(std::string name, unsigned int priority) : 
    name(name), priority(priority){ }
  std::string name;
  unsigned int priority;
};

class Operation_Queue {
public:
  
  void enqueue(const Operation& new_operation) {
    queue_lock.lock();
    std::cout << "Operation Enqueue::" << "Name::" << new_operation.name 
      << "::Priority::" << new_operation.priority;
    operation_queue.push(new_operation);
    std::cout << "::Operation Queue Size::" << operation_queue.size() <<std::endl; 
    queue_lock.unlock();
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

  struct PriorityOrdering {
    bool operator()(const Operation& lhs, const Operation& rhs) const {
      return lhs.priority < rhs.priority;
    }
  };

private:
  std::priority_queue<Operation, std::vector<Operation>, PriorityOrdering> operation_queue;
  std::mutex queue_lock;
};

#endif
