/*
 * Publish-Subscribe Component
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.16
 */

#ifndef PUB_SUB_COMPONENT
#define PUB_SUB_COMPONENT
#include "operation_queue.hpp"
#include "timer.hpp"
#include "publisher.hpp"
#include "subscriber.hpp"

class Timer_Component {
public:
  Timer_Component() {
    operation_queue = new Operation_Queue();
    timer_1 = new Timer("timer_1",
			50, 
			1000000000, 
			std::bind(&Timer_Component::timer_1_operation, this), 
			operation_queue);
    timer_2 = new Timer("timer_2",
			60, 
			500000000, 
			std::bind(&Timer_Component::timer_2_operation, this), 
			operation_queue);
    timer_3 = new Timer("timer_3",
			70, 
			250000000, 
			std::bind(&Timer_Component::timer_3_operation, this), 
			operation_queue);
    timer_4 = new Timer("timer_4",
			80, 
			100000000, 
			std::bind(&Timer_Component::timer_4_operation, this), 
			operation_queue);
    timer_5 = new Timer("timer_5",
			90, 
			50000000, 
			std::bind(&Timer_Component::timer_5_operation, this), 
			operation_queue);
  }

  ~Timer_Component() {
    delete operation_queue;
    delete timer_1;
    delete timer_2;
    delete timer_3;
    delete timer_4;
    delete timer_5;
  }
  
  void timer_1_operation() {
    std::cout << "Timer_1 Expired!" << std::endl;
  }

  void timer_2_operation() {
    std::cout << "Timer_2 Expired!" << std::endl;
  }

  void timer_3_operation() {
    std::cout << "Timer_3 Expired!" << std::endl;
  }

  void timer_4_operation() {
    std::cout << "Timer_4 Expired!" << std::endl;
  }

  void timer_5_operation() {
    std::cout << "Timer_5 Expired!" << std::endl;
  }

  void run() {
    std::thread executor_thread = operation_queue->spawn();
    std::thread timer_1_thread = timer_1->spawn();
    std::thread timer_2_thread = timer_2->spawn();
    std::thread timer_3_thread = timer_3->spawn();
    std::thread timer_4_thread = timer_4->spawn();
    std::thread timer_5_thread = timer_5->spawn();

    timer_1_thread.join();
    timer_2_thread.join();
    timer_3_thread.join();
    timer_4_thread.join();
    timer_5_thread.join();
    executor_thread.join();
  }

private:
  Operation_Queue * operation_queue;
  Timer * timer_1;
  Timer * timer_2;
  Timer * timer_3;
  Timer * timer_4;
  Timer * timer_5;
};

#endif
