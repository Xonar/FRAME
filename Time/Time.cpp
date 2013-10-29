/*
 * File :
 *      ./Time/Time.cpp
 *
 * Author : 
 *      Xonar <Paul le Roux>
 *
 * Description :
 *      Definitions of ./Time.h
 */

#include "Time.h"
#include <SDL2/SDL.h>

#ifdef _POSIX_SOURCE
  #include <unistd.h>
  #include <ctime>
  #if _POSIX_TIMERS <= 0
    #warning "CURRENT POSIX SYSTEM DOESN'T SUPPORT _POSIX_TIMERS. TIME WILL ONLY BE MS ACCURATE"
  #endif
#else
  #warning "FINE TIME NOT IMPLEMENTED OR SUPPORTED IN CURRENT OS. TIME WILL ONLY BE MS ACCURATE"
#endif

const char* F_TIME_UNIT_MAP[] = {"ns", "us", "ms", "s"};
bool FTime::operator<(const FTime &B)
{
  return (this->s < B.s)?true:(this->n < B.n);
}

bool FTime::operator>(const FTime &B)
{
  return (this->s > B.s)?true:(this->n > B.n);
}

bool FTime::operator==(const FTime &B)
{
  return (this->s == B.s)?(this->n == B.n):false;
}

FTime FTime::operator=(const FTime &B)
{
  this->s = B.s;
  this->n = B.n;

  return *this;
}

FTime FTime::operator+(const FTime &B)
{
  FTime out;
  out.s = this->s + B.s;
  out.n = this->n + B.n;

  out.normalize();

  return out;
}

FTime FTime::operator-(const FTime &B)
{
  FTime out;
  out.s = this->s - B.s;
  out.n = this->n - B.n;

  out.normalize();

  return out;
}

FTime FTime::operator+=(const FTime &B)
{
  this->s += B.s;
  this->n += B.s;

  this->normalize();

  return *this;
}

FTime FTime::operator-=(const FTime &B)
{
  this->s -= B.s;
  this->n -= B.s;

  this->normalize();

  return *this;
}

bool FTime::operator>=(const FTime &B)
{
  return (this->s > B.s)?true:((this->s == B.s)?(this->n >= B.n):false);
}

bool FTime::operator<=(const FTime &B)
{
  return (this->s < B.s)?true:((this->s == B.s)?(this->n <= B.n):false);
}

bool FTime::operator!=(const FTime &B)
{
  return (this->s != B.s)?true:(this->n != B.n);
}

void FTime::normalize()
{
  int mod = this->n / 1000000000;

  this->s += mod;
  this->n -= mod * 1000000000;

  if(this->n < 0)
  {
    this->s--;
    this->n += 1000000000; 
  }

  if(this->s < 0)
  {
    //Negative Time
    this->s ++;
    this->n -= 1000000000;
  }
  //All is good with positive time
}

FTime startTime;

void initTime()
{
  startTime = FGetTime();
}

GLuint FGetTicks()
{
  return SDL_GetTicks();
}

FTimePrecision FGetTimePrecision()
{
  FTime fTime = {0,0};

  #ifdef _POSIX_SOURCE
    #if _POSIX_TIMERS > 0
      struct timespec time;

      #ifdef _POSIX_MONOTONIC_CLOCK
        clock_getres(CLOCK_MONOTONIC, &time);
      #else
        #warning "Using Realtime Clock, errors may occur when system time changes"
        clock_getres(CLOCK_REALTIME, &time);
      #endif

      fTime.s = time.tv_sec;
      fTime.n = time.tv_nsec;
    #endif
  #else
    fTime.s = 0;
    fTime.n = 1000000;
  #endif

  FTimePrecision out;

  if(fTime.n > 0)
  {
    if(fTime.n>1000)
    {
      out.unit = F_MILI;
      out.amount = fTime.n / 1000;
    }
    else
    {
      out.unit = F_NANO;
      out.amount = fTime.n;
    }
  }
  else
  {
    out.unit = F_SECOND;
    out.amount = fTime.s;
  }

  return out;
}

FTime FGetTime()
{
  FTime out = { 0, 0 };

  #ifdef _POSIX_SOURCE
    #if _POSIX_TIMERS > 0
      struct timespec time;

      #ifdef _POSIX_MONOTONIC_CLOCK
        clock_gettime(CLOCK_MONOTONIC, &time);
      #else
        clock_gettime(CLOCK_REALTIME, &time);
      #endif

      out.s = time.tv_sec;
      out.n = time.tv_nsec;
    #endif
  #else
    GLuint time = SDL_GetTime();
    
    out.s = time/1000;
    out.n = (time%1000) * 1000000;
  #endif

  return out;
}

FTime FGetStartTime()
{
  return startTime;
}

FTime FGetTimeSinceStart()
{
  return startTime - FGetTime();
}

std::string FTimeString(const FTime &A)
{
  std::string out;

  if(A.s != 0)
  {

  }
  else
  {
    if(A.n % 1000 == 0)
    {
      if(A.n % 1000000 == 0)
      {
        out = std::to_string(A.n/1000000);
        out.append(F_TIME_UNIT_MAP[F_MILI]);
      }
      else
      {
        out = std::to_string(A.n/1000);
        out.append(F_TIME_UNIT_MAP[F_MICRO]);
      }
    }
    else
    {
      out = std::to_string(A.n);
      out.append(F_TIME_UNIT_MAP[F_NANO]);
    }
  }

  return out;
}

std::string FTimePrecisionString(const FTimePrecision &A)
{
  std::string out = std::to_string(A.amount);
  out.append(F_TIME_UNIT_MAP[A.unit]);
  return out;
}
