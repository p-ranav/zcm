/** @file    xml_parser.hpp 
 *  @author  Pranav Srinivas Kumar
 *  @date    2016.04.24
 *  @brief   This file declares the XML_Parser class
 */

#ifndef XML_PARSER
#define XML_PARSER
#include <iostream>
#include "tinyxml2.hpp"

namespace zcm {

  /**
   * @brief XML_Parser class
   */  
  class XML_Parser {
  public:

    /**
     * @brief Construct an XML_Parser object
     * @param[in] filename XML file name
     */     
    XML_Parser(const char * filename);

    /**
     * @brief Parse XML document
     */      
    void parse();

  private:

    /** @brief tinyxml2 Document */
    tinyxml2::XMLDocument document;

    /** @brief Pointer to the root node */
    tinyxml2::XMLNode * root;

    /** @brief XML filename */
    const char * filename;
  };

}

#endif
