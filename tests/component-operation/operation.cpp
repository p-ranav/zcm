/*
 * Sample Component Operation class
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.12
 */

#include <iostream>
#include <queue>
#include <mutex>

struct Operation {
  Operation(unsigned int opn_priority) {
    priority = opn_priority;
  }
  unsigned int priority;
};

class Operation_Queue {
public:
  
  void enqueue(const Operation& new_operation) {
    queue_lock.lock();
    std::cout << "Operation: " << new_operation.priority << std::endl;
    operation_queue.push(new_operation);
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

int main() {

  Operation timer_operation_1(40);
  Operation timer_operation_2(55);
  Operation timer_operation_3(66);

  Operation_Queue * my_queue = new Operation_Queue();
  my_queue->enqueue(timer_operation_1);
  my_queue->enqueue(timer_operation_2);
  my_queue->enqueue(timer_operation_3);

  while(!my_queue->empty()) {
    std::cout << my_queue->top().priority << std::endl;
    my_queue->dequeue();
  }

  return 0;
}
