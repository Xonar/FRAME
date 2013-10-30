/*
 * File :
 *      ./Lib/Files.cpp
 *
 * Author :
 *      Xonar <Paul le Roux>
 *
 * Description:
 *      Definitions of ./Lib/Files.h
 */

#include "Files.h"

#include <fstream>
#include <iostream>

std::string readFileIntoString(const std::string &path)
{
  std::ifstream in(path, std::ios::in | std::ios::binary );

  if(in)
  {
    std::string out;

    in.seekg(0, std::ios::end);
    out.resize(in.tellg());

    in.seekg(0, std::ios::beg);
    in.read(&out[0], out.size());

    in.close();

    return out;
  }
  else
  {
    std::cerr << "Failed reading file : \"" << path << "\"" << std::endl;
    return "";
  }
}
