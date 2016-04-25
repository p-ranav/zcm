/*
 * Component 1
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.23
 */

#ifndef COMPONENT_1
#define COMPONENT_1
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/random/mersenne_twister.hpp>
#include "component.hpp"

namespace zcm {

  class Component_1 : public Component {
  public:

    Component_1();
    void timer_1_function();
    void subscriber_function(std::string received_message);

  private:
    Timer * timer;
    Publisher * publisher;
    Subscriber * subscriber;
  };

}

#endif
