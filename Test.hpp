#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <string>
#include <stdexcept>

#define TESTABLE friend int main ();

#define expect(EXPRESSION) __expect(EXPRESSION, std::string(#EXPRESSION))
#define expectThrow(FN) __expectThrow(FN, true, std::string(#FN) + " should throw")
#define expectNoThrow(FN) __expectThrow(FN, false, std::string(#FN) + " should NOT throw")

namespace test
{
template<typename T>
void registerTest (std::string name, T fn)
{
  std::cout << name << std::endl;
  fn();
}

void __expect (bool expression, const std::string& message)
{
  if (!expression)
    std::cerr << "  Assertion failed: " << message << std::endl;
}

template<typename FunctionType>
void __expectThrow (const FunctionType& fn, bool shouldThrow, const std::string& message)
{
  bool hasThrown = false;

  try {
    fn();
  } catch (const std::runtime_error& exception) {
    hasThrown = true;
  }

  if (hasThrown != shouldThrow)
    std::cerr << "  Assertion failed: " << message << std::endl;
}
}

#endif