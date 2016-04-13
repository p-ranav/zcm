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
#include <thread>

class Operation_Queue;
Operation_Queue * operation_queue;
std::mutex queue_mutex;

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

  void process() {
    while(true) {
      if (operation_queue.size() > 0) {
        queue_mutex.lock();
        Operation top_operation = operation_queue.top();
	std::cout << "Dequeueing Top Operation: " << top_operation.name << std::endl;
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
      return lhs.priority < rhs.priority;
    }
  };

private:
  std::priority_queue<Operation, std::vector<Operation>, PriorityOrdering> operation_queue;
  std::mutex queue_lock;
};

#endif
