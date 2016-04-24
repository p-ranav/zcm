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
	dequeue();
	queue_mutex.unlock();
	zmq::socket_t * socket_ptr = top_operation.get_socket_ptr();
	if (!socket_ptr)
	  top_operation.execute();	  
	else {
	  std::string response = top_operation.execute_server();
	  zmq::message_t reply(response.length());
	  memcpy(reply.data(), response.c_str(), response.length());
	  socket_ptr->send(reply);
	  top_operation.set_ready();
	}
      }
    }
  }

  std::thread * spawn() {
    return new std::thread(&Operation_Queue::process, this);
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
