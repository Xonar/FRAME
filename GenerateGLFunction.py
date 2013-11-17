#!/bin/python

##
# File:
#       ./GenerateGLFunction.py
#
# Author :
#      Xonar <Paul le Roux>
#
# Description:
#      Generates Graphics/GLFunctions.h and Graphics/GLFunctions.cpp
##

#Class that handles GL Functions
class GLFunction:
  glReturn="NULL"
  glFunction="NULL"
  glParameters="NULL"

  #Return Function Decleration
  def decl(self):
    return self.glReturn + " (APIENTRY *" + self.glFunction + ")(" + self.glParameters + ");"
  
  #Return Function Definition
  def defi(self):
    return self.glFunction + " = (__typeof__("+self.glFunction+"))SDL_GL_GetProcAddress(\"" + self.glFunction + "\");"
  
  #Read Function Line
  def read(self,n):
    c1 = n.find('(');
    c2 = n.rfind(')');
    c3 = n.rfind(' ',0,c1);
    self.glReturn = n[:c3];
    self.glFunction = n[c3+1:c1];
    self.glParameters = n[c1+1:c2];

#MAIN LOOP
def main():
  #Open File for reading
  f = open("GLFunctions.list","r")

  #Define list to hold functions
  glFunctions = []

  #Read functions from file
  for i in f.readlines():
    i = i.strip()
    if(len(i)<3 or i[0]=='#'):
      continue #Skip line
    tmp = GLFunction()
    tmp.read(i)
    glFunctions.append(tmp)
    del tmp

  #Close file
  f.close()

  #Write Function Definitions and Declerations to file

  #-------------------
  #Write GLFunctions.h
  #-------------------

  f = open("./Graphics/GLFunctions.h","w")
  
  #Write Comment Block
  f.write("/*\
\n * File :\
\n *      ./Graphics/GLFunctions.h\
\n *\
\n * Author :\
\n *      Xonar <Paul le Roux>\
\n *\
\n * Description:\
\n *      This file contains the GL Function declerations\
\n *\
\n * NOTE:\
\n *      This file is generated from GLFunctions.list and will be overwritten at compile time\
\n */\n")

  #Write Header #ifndef
  f.write("\
\n#ifndef _F_H_GLFUNCTIONS_\
\n#define _F_H_GLFUNCTIONS_\n")

  #Write Header Includes
  f.write("\n#include <SDL2/SDL_opengl.h>\n")

  #Write initGlFunction decleration
  f.write("\nint initGLFunction();\n\n")

  #Write Namespace
  f.write("//NAMESPACE\
\n namespace FGL\
\n{\n\n");

  #Write Function Declerations
  for i in glFunctions:
    f.write("  extern " + i.decl() + "\n")

  #Write Endof namespace
  f.write("} // ENDOF NAMESPACE FGL\n")

  #Write defines
  for i in glFunctions:
    f.write("#define " + i.glFunction + " FGL::" + i.glFunction + "\n")

  #Write Header #endif
  f.write("\n#endif // _F_H_GLFUNCTIONS_")

  #Close GLFunctions.h
  f.close()

  #--------------------
  #Write GLFunctions.cpp
  #--------------------

  f = open("./Graphics/GLFunctions.cpp","w")

  #Write Comment Block
  f.write("/*\
\n * File :\
\n *      ./Graphics/GLFunctions.cpp\
\n *\
\n * Author :\
\n *      Xonar <Paul le Roux>\
\n *\
\n * Description:\
\n *      This file contains the GL Function definitions and initializations\
\n *\
\n * NOTE:\
\n *      This file is generated from GLFunctions.list and will be overwritten at compile time\
\n */\n")

  #Write Header Includes
  f.write("\n#include \"GLFunctions.h\"\
\n#include <SDL2/SDL.h>\n")

  #Write Declerations
  f.write("\n// DECLERATIONS\n")
  for i in glFunctions:
    f.write(i.decl() + "\n")

  #Write initGLFunction()
  f.write("\n// INITIALIZATION\
\nint initGLFunction()\
\n{\
\n")

  #Write Definitions
  for i in glFunctions:
    f.write("  " + i.defi() + "\n")

  #Write end of initGLFunction
  f.write("\n  return 0;\n}\n")

  #Finish
  return 0

main()
