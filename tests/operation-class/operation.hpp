/*
 * Operation Class - Initial Design
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.16
 */

#ifndef OPERATION
#define OPERATION
#include <iostream>
#include <functional>

class Operation {
public:
  Operation(std::function<void ()> operation_function) : 
    operation_function(operation_function) {}

  void execute() {
    operation_function();
  }

private:
  std::string name;
  std::function<void ()> operation_function;
};

#endif
