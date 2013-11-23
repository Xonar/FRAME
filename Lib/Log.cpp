/*
 * File :
 *      ./Lib/Log.cpp
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Definitions of ./Lib/Log.h
 */

#include <iostream>

#include "Log.h"
#include "../Global.h"

Logger gLoge(std::cerr, TERM_COL_RED TERM_STATE_BOLD);
Logger gLogw(std::cerr, TERM_COL_YELLOW TERM_STATE_BOLD);
Logger gLogi(std::cout, TERM_STATE_RESET);
Logger gLogv(std::cout, TERM_STATE_RESET);

#ifdef COLOUR_TERMINAL
std::string FGL_HIDDEN::lastCol;
#endif

Logger& operator<< (Logger& log, std::ostream& (*manipulator) (std::ostream&))
{
  if(log.getLogging())
  {
    log.getStream() << manipulator;
  }

  return log;
}

Logger::Logger(std::ostream &out, const std::string &col)
{
  this->col = col;
  this->out = &out;
}

Logger::~Logger()
{
  
}

inline void Logger::setLogging(bool val)
{
  this->logging = val;
}
