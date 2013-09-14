/*
 * File :
 *      ./Room/Room.h
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      The FRoom class is a handler for Room Objects
 */

#ifndef _F_H_ROOM_
#define _F_H_ROOM_

#include "../Object/Object.h"
#include "../Font/Font.h"

#include <list>

#include 

class FRoom
{
private:

  std::list<FObject*> objects;
  std::list<FFont*> fonts;
  
public:
  FRoom();
  ~FRoom();

  void Render();


}

#endif //_F_H_ROOM_
