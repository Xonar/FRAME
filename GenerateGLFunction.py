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

#imports
import os

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
    if self.glParameters == "GLvoid":
      self.glParameters = ""
    return self

#MAIN LOOP
def main():
  #Open File for reading
  f = open("GLFunctions.list","r")

  #Define dictionary to hold functions groups
  glFunctions = {}

  #Read core functions
  glFunctions["Core"] = []
  for i in f.readlines():
    if(len(i)>3 and i[0]!='#'):
      glFunctions["Core"].append(GLFunction().read(i.strip()))

  #Close file
  f.close()

  #Read extension functions
  for l in os.listdir("./Graphics/GLFunctions/"):
    if l.endswith(".list"):
      f = open("./Graphics/GLFunctions/" + l) 
      filedata = ""
      for i in f.readlines():
        if(len(i)>4 and i[0] != '#'):
          filedata+=i.strip()
      filedata=filedata[:-1]
      glFunctions[l[:-5]] = [GLFunction().read(i) for i in [i+";" for i in filedata.split(";")]]
      f.close()

  #Write Function Definitions and Declerations to file

  #-------------------
  #Write GLFunctions.h
  #-------------------

  f = open("./Graphics/GLFunctions.h", "w")

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
\n *      This file is generated from ./Graphics/GLFunctions.list and\
\n *      will be overwritten at compile time!\
\n */\n")

  #Write Header #ifndef
  f.write("\
\n#ifndef _F_H_GLFUNCTIONS_\
\n#define _F_H_GLFUNCTIONS_\n")

  #Write Header Includes
  f.write("\n#include <SDL2/SDL_opengl.h>\n")

  #Write Namespace
  f.write("\n//NAMESPACE\
\n namespace FGL\
\n{\n\n");

  #Write Load GL Functions decleration
  f.write("//Load Functions\n")
  for key, val in glFunctions.iteritems():
    f.write("  GLint Load_GL_" + key + "();\n")

  f.write("\n")

  #Write Function Declerations
  for key, val in glFunctions.iteritems():
    for i in val:
      f.write("  extern " + i.decl() + "\n")

  #Write Extension loaded namespace

  #Write Endof namespace
  f.write("} // ENDOF NAMESPACE FGL\n\n")

  #Write defines
  for key, val in glFunctions.iteritems():
    for i in val:
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
  for key, val in glFunctions.iteritems():
    for i in val:
      f.write(i.decl() + "\n")

  #Write Load GL Functions definitions
  f.write("\n//Load Functions")
  for key, val in glFunctions.iteritems():
    f.write("\nGLint FGL::Load_GL_" + key + "()\
\n{\
\n")
    #Write Definitions
    for i in val:
      f.write("  " + i.defi() + "\n")

    #ENDOF
    f.write("\n  return 0;\n}\n")

  #Finish
  return 0

main()
