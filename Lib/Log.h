/*
 * File :
 *      ./Lib/Log.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Handles logging of messages
 */

#ifndef _F_H_LOG_
#define _F_H_LOG_


#include <iostream>

class Logger
{
  private:
    std::string col;

    bool logging = true;

    std::ostream *out;
  public:
    Logger(std::ostream &out, const std::string &col);
    ~Logger();

    inline void setLogging(bool val);

    inline bool getLogging() const { return this->logging; }
    inline const std::string& getColour() const { return this->col; }
    inline std::ostream& getStream() const { return *(this->out); }
};

//Template Functions Operators
#include "Log.template.h"

Logger& operator<< (Logger& log, std::ostream& (*manipulator) (std::ostream&));

//Loggers
extern Logger gLoge; //Error Logger
extern Logger gLogw; //Warning Logger
extern Logger gLogi; //Info Logger
extern Logger gLogv; //Verbose Logger

#endif //_F_H_LOG_
