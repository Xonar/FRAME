/*
 * File :
 *      ./Time/Time.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      This is the encapsulating module that handles all timings/ticks for FRAME
 */

#ifndef _F_H_TIME_
#define _F_H_TIME_

#include <SDL2/SDL_opengl.h>
#include <string>

struct FTime
{
  GLuint s,n; //Seconds and Nanoseconds

  //Operators
  bool operator<( const FTime &B); 
  bool operator>( const FTime &B); 
  bool operator==( const FTime &B); 
  FTime operator=( const FTime &B); 
  FTime operator+( const FTime &B); 
  FTime operator-( const FTime &B); 
  FTime operator+=( const FTime &B); 
  FTime operator-=( const FTime &B); 
  bool operator>=( const FTime &B); 
  bool operator<=( const FTime &B); 
  bool operator!=( const FTime &B);

  void normalize();
};

GLvoid initTime();

enum FTimeUnit { F_NANO, F_MICRO, F_MILI, F_SECOND };

extern const char* F_TIME_UNIT_MAP[];

struct FTimePrecision
{
  FTimeUnit unit;
  GLint amount;
};

FTimePrecision FGetTimePrecision();

GLuint FGetTicks();  // Uses SDL_Ticks no need to reinvent the wheel
FTime FGetTime();    // Returns seconds and nanoseconds

FTime FGetStartTime();
FTime FGetTimeSinceStart();

std::string FTimePrecisionString(const FTimePrecision &A);
std::string FTimeString(const FTime &A);

#endif //_F_H_TIME_
