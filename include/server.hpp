/** @file    server.hpp 
 *  @author  Pranav Srinivas Kumar
 *  @date    2016.04.24
 *  @brief   This file declares the Server class
 */

#ifndef SERVER
#define SERVER
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <zmq.hpp>
#include "operation_queue.hpp"

namespace zcm {

  /**
   * @brief Server class
   */
  class Server {
  public:

    /**
     * @brief Construct a server object
     * @param[in] name Server name
     * @param[in] priority Priority of the server
     * @param[in] operation_function Operation function of the server
     * @param[in] operation_queue_ptr Pointer to the operation queue
     */    
    Server(std::string name,
	   unsigned int priority,
	   std::function<std::string(const std::string&)> operation_function,
	   Operation_Queue * operation_queue_ptr) :
      name(name),
      priority(priority),
      operation_function(operation_function),
      operation_queue_ptr(operation_queue_ptr) {}

    /**
     * @brief Construct a server object with known endpoints
     * @param[in] name Server name
     * @param[in] priority Priority of the server
     * @param[in] endpoints A vector of endpoints to bind to
     * @param[in] operation_function Operation function of the server
     * @param[in] operation_queue_ptr Pointer to the operation queue
     */      
    Server(std::string name,
	   unsigned int priority,
	   std::vector<std::string> endpoints,
	   std::function<std::string(const std::string&)> operation_function,
	   Operation_Queue * operation_queue_ptr);

    /**
     * @brief Close the server socket and destroy the ZMQ context
     */  
    ~Server();

    /**
     * @brief Bind to a new set of endpoints
     * param[in] new_endpoints A new vector of endpoints to bind to
     */  
    void bind(std::vector<std::string> new_endpoints);

    /**
     * @brief Get the name of the server
     */  
    std::string get_name();

    /**
     * @brief Get the priority of the server
     */   
    unsigned int get_priority();

    /**
     * @brief Add a new connection to the server
     * @param[in] new_connection New connection address to bind to
     */      
    void add_connection(std::string new_connection);

    /**
     * @brief Thread function of the server
     * Behavior:
     * (1) Wait for a new request on the server ZMQ socket
     * (2) Create a Server Operation
     * (3) Enqueue onto operation_queue
     * (4) Goto step (1)
     */  
    void recv();
 
    /**
     * @brief Rebind the server operation function
     * @param[in] new_operation_function New server function to be handled upon recv() 
     */  
    void rebind_operation_function(std::function<std::string(const std::string&)> new_operation_function);

    /**
     * @brief Spawn a new thread for the server
     * @return Server thread
     */    
    std::thread spawn();

    /**
     * @brief Start the server thread
     */  
    void start();

  private:

    /** @brief Name of the server */
    std::string name;

    /** @brief Priority of the server */
    unsigned int priority;

    /** @brief Vector of connection endpoints */
    std::vector<std::string> endpoints;

    /** @brief Operation function bound to the server - Component method that handles received requests */
    std::function<std::string(const std::string&)> operation_function;

    /** @brief Pointer to the operation_queue */
    Operation_Queue * operation_queue_ptr;

    /** @brief Pointer to the server ZMQ context */
    zmq::context_t * context;

    /** @brief Pointer to the server ZMQ socket */
    zmq::socket_t * server_socket;

    /** @brief Boolean representing the state of the server to receive new requests */
    bool ready;

    /** @brief Mutex used when changing operation_function at runtime */
    std::mutex func_mutex;
  };

}

#endif
