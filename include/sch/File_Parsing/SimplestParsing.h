#pragma once
#include <exception>
#include <iostream>
#include <sstream>
#include <string.h>

namespace FileParsing
{

  class SimplestParsing
  {
  public:
    SimplestParsing(void);
    virtual ~SimplestParsing(void);

    /*!
    *\brief returns the ifstream of the instance
    */
    std::stringstream& operator()();

    /*!
    *\brief looks for the string in the file (non optimized version, efficient with small files). The stream at the end of exectution is either just at the end of found string or at the end of the file if not found
    *\return A boolean saying if it found it or not
    */
    bool find(const std::string&);

    /*!
    *\brief Checks if the next string in the file is a given one, if it is, the stream will be at the end of the string if not, the stream will stay qt it's original position
    *\return A boolean answer
    */
    bool checkIfNextString(const std::string&);


    /*!
    *\brief Jumps the blanks, tabs and all non text separators
    */
    bool jumpSeparators();

    /*!
     *\brief Opens a file and stores its content into a buffer.
     */
    void load(const char* filename);

  private:
    std::stringstream stream_;
  };
}
