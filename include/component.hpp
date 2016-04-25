/** @file    component.hpp 
 *  @author  Pranav Srinivas Kumar
 *  @date    2016.04.24
 *  @brief   This file declares the Component class
 */

#ifndef COMPONENT
#define COMPONENT
#include "timer.hpp"
#include "publisher.hpp"
#include "subscriber.hpp"
#include "client.hpp"
#include "server.hpp"

namespace zcm {

  /**
   * @brief Component class
   */
  class Component {
  public:

    /**
     * @brief Construct a component
     * Prepare the component operation queue
     */
    Component();

    /**
     * @brief Destroy the component
     */  
    ~Component();

    /**
     * @brief Add a timer to this component
     * @param[in] new_timer Pointer to a timer object
     */
    void add_timer(Timer * new_timer);

    /**
     * @brief Add a publisher to this component
     * @param[in] new_publisher Pointer to a publisher object
     */
    void add_publisher(Publisher * new_publisher);

    /**
     * @brief Add a subscriber to this component
     * @param[in] new_subscriber Pointer to a subscriber object
     */
    void add_subscriber(Subscriber * new_subscriber);

    /**
     * @brief Add a client to this component
     * @param[in] new_client Pointer to a client object
     */
    void add_client(Client * new_client);

    /**
     * @brief Add a server to this component
     * @param[in] new_server Pointer to a server object
     */
    void add_server(Server * new_server);     

    /**
     * @brief Spawn the component executor thread
     * @return Return a pointer to the executor thread
     */    
    std::thread * spawn();

  protected:

    /** @brief Pointer to the Component Operation Queue */  
    Operation_Queue * operation_queue;

    /** @brief Pointer to the Component Executor Thread */    
    std::thread * executor_thread;

    /** @brief A vector of component timers */
    std::vector<Timer*> timers;    

    /** @brief A vector of component publishers */
    std::vector<Publisher*> publishers;

    /** @brief A vector of component subscribers */
    std::vector<Subscriber*> subscribers;

    /** @brief A vector of component clients */
    std::vector<Client*> clients;

    /** @brief A vector of component servers */
    std::vector<Server*> servers;    
  };

}

#endif
