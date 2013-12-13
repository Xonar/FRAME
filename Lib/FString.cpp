/*
 * File :
 *      ./Lib/FString.cpp
 *
 * Author : 
 *      Xonar <Paul le Roux>
 *
 * Description :
 *      Definitions of ./Lib/FString.h
 */

#include "FString.h"

namespace FL {
  //Precalculated powers of 10
  static const unsigned long long pow10[] = {0,10,100,1000,10000,100000,1000000,10000000,100000000,
   1000000000,10000000000,100000000000,1000000000000,10000000000000,100000000000000,1000000000000000,
   10000000000000000,100000000000000000,1000000000000000000,10000000000000000000u};
}
char* FL::itoa(unsigned long long num)
{
  int s = std::upper_bound(FL::pow10, FL::pow10 + 20,num) - FL::pow10; 
      
  char* str = new char[s];
  char* it = str + s;

  *it = '\0';

  while(it-- > str)
  {
    *it = num%10 + '0';
    num /= 10;
  }

  return str;
}

std::string FL::to_string(unsigned long long num)
{
  int s = std::upper_bound(FL::pow10, FL::pow10 + 20,num) - FL::pow10; 

  char* str = new char[s];
  char* it = str + s;

  *it = '\0';

  while(it-- > str)
  {
    *it = num%10 + '0';
    num /= 10;
  }

  std::string out(str);

  delete[] str;

  return out;
}

