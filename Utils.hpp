#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <sstream>

template<typename T>
std::string toString (T data)
{
  std::stringstream ss;
  std::string str;

  ss << data;
  ss >> str;

  return str;
}

#endif