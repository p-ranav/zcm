/*
 * Periodic Timers Component
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.25
 */

#include "periodic_timers.hpp"

namespace zcm {

  extern "C" {
    Component* create_component() {
      return new Timers_Component();
    }
  }     

  Timers_Component::Timers_Component() {
    timer_1 = new Timer("timer_1",
			50,
			1000000000, // 1 sec				
			std::bind(&Timers_Component::timer_1_function, this),
			operation_queue);
    timer_2 = new Timer("timer_2",
			50,
			500000000, // 500 msec				
			std::bind(&Timers_Component::timer_2_function, this),
			operation_queue);
    timer_3 = new Timer("timer_3",
			50,
			250000000, // 250 msec				
			std::bind(&Timers_Component::timer_3_function, this),
			operation_queue);
    timer_4 = new Timer("timer_4",
			50,
			100000000, // 100 msec				
			std::bind(&Timers_Component::timer_4_function, this),
			operation_queue);
    timer_5 = new Timer("timer_5",
			50,
			500000000, // 50 msec				
			std::bind(&Timers_Component::timer_5_function, this),
			operation_queue);
    add_timer(timer_1);
    add_timer(timer_2);
    add_timer(timer_3);
    add_timer(timer_4);
    add_timer(timer_5);
  }

  void Timers_Component::timer_1_function() {
    std::cout << "Timer 1 expiry handled!" << std::endl;
  }

  void Timers_Component::timer_2_function() {
    std::cout << "Timer 2 expiry handled!" << std::endl;
  }
  void Timers_Component::timer_3_function() {
    std::cout << "Timer 3 expiry handled!" << std::endl;
  }
  void Timers_Component::timer_4_function() {
    std::cout << "Timer 4 expiry handled!" << std::endl;
  }
  void Timers_Component::timer_5_function() {
    std::cout << "Timer 5 expiry handled!" << std::endl;
  }  

}
