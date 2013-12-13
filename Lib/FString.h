/*
 * File :
 *      ./Lib/FString.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      String functions that aren't available in all compilers
 *
 * Namespace : FL (FRAME Library)
 */

#ifndef _F_H_FSTRING_
#define _F_H_FSTRING_

#include "Log.h"
#include <algorithm>
#include <string>

//Encase these functions into a namespace since they might clash with other functions
namespace FL
{
  char* itoa(unsigned long long num);

  std::string to_string(unsigned long long num);
}

#endif //_F_H_FSTRING_
