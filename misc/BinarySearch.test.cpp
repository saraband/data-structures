#include "BinarySearch.hpp"

int main ()
{

  // @TODO 
  TEST("Binary search with an empty array", {
    std::vector<int> array;

    ASSERT_EQ(binarySearchFindIndex(array, 42), -1);
  });

  TEST("Binary search", {
    std::vector<int> array;
    array.push_back(1);
    array.push_back(2);
    array.push_back(4);
    array.push_back(18);
    array.push_back(466);

    ASSERT_EQ(binarySearchFindIndex(array, 5), 1);
  });

  return 0;
}