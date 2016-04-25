/*
 * Component 3
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.23
 */

#ifndef COMPONENT_3
#define COMPONENT_3
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/random/mersenne_twister.hpp>
#include "component.hpp"

namespace zcm {

  class Component_3 : public Component {
  public:
    
    Component_3();
    void timer_function();

  private:
    Timer * timer;
    Client * client;
  };

}

#endif
