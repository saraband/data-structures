#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <string>
#include <stdexcept>

#define TESTABLE friend int main ();

#define assertEq(A, B) __assertEq(A, B, std::string(#A) + " == " + std::string(#B))
#define assertThrow(FN) __assertThrow<std::runtime_error>(FN, std::string(#FN) + " should throw a std::runtime_error")

namespace
{
void __assert (bool condition, const std::string& exp)
{
  if (!condition) {
    std::cout << "  Assertion failed: " << exp << std::endl;
  }
}
}

namespace test
{
template<typename T>
void registerTest (std::string name, T fn)
{
  std::cout << name << std::endl;
  fn();
}

template<typename T, typename U>
void __assertEq (T a, U b, const std::string& exp)
{
  __assert(a == b, exp);
}

template<>
void __assertEq (std::string a, const char* b, const std::string& exp)
{
  __assert(a.compare(b) == 0, exp);
}

template<typename U, typename T>
void __assertThrow (const T& fn, const std::string& exp)
{
  bool hasThrown = false;

  try {
    fn();
  } catch (const U& exception) {
    hasThrown = true;
  }

  __assert(hasThrown, exp);
}
}

#endif