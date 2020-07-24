#include "List.hpp"

int main ()
{
  TEST("successfull test", {})
  TEST("Mon test", {
    std::string s = "yolo";
    ASSERT_EQ(s, "yolo");
    ASSERT_EQ(s, "yala");
    ASSERT_EQ(1, 1);
    ASSERT_EQ(1, 2);
    ASSERT_EQ("hello", "hello");
    ASSERT_EQ("hello", "yolo");
  });
  return 0;
}