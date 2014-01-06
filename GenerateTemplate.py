#!/usr/bin/python

##
# File:
#       ./GenerateTemplate.py
#
# Author :
#      Xonar <Paul le Roux>
#
# Description:
#      Generates file templates for source, header and script files.
##

import sys
import os

#Generate Header
def genHeader(f, path):
  #Write Comment Block
  f.write("""/*
 * File :
 *      FILE
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      DESCRIPTION
 */

""".replace("FILE",path))

  #Get MACRO NAME
  macro = path[path.rindex('/')+1:path.rindex('.')].replace(".","_").upper()
  
  #Write ifndef
  f.write("""#ifndef _F_H_MACRO_
#define _F_H_MACRO_

#endif // _F_H_MACRO_""".replace("MACRO", macro))

  #Close file
  f.close()

#Generate CPP Source
def genCPPSource(f, path):
  #Write Comment Block
  f.write("""/*
 * File :
 *      FILE.cpp
 *
 * Author : 
 *      Xonar <Paul le Roux>
 *
 * Description :
 *      Definitions of FILE.h
 *      
 */
 
""".replace("FILE", path[:path.rindex('.')]))

  #include Header
  f.write("#include \"FILE.h\"".replace("FILE", path[path.rindex('/')+1:path.rindex('.')]))

#Generate Python Scipr
def genPython(f, path):
  #Write Comment Block
  f.write("""#!/usr/bin/python

##
# File:
#      FILE
#
# Author :
#      Xonar <Paul le Roux>
#
# Description:
#      DESCRIPTION
##
""".replace("FILE", path))

#File table
files = {"h" : genHeader,
         "cpp" : genCPPSource,
         "py" : genPython
        }

print("Template Generator");

if(len(sys.argv)!=2):
  print("Cannot specify multiple files\n")
  print("Usage template.py FILE")
else:
  path = sys.argv[1]
  if not path.startswith("./"):
    path = "./" + path
  print("Creating Template for : " + path)

  assert not os.path.exists(path), "File already exists!"

  f = open(path, 'w')

  files[path[path.rindex('.')+1:]](f,path)
